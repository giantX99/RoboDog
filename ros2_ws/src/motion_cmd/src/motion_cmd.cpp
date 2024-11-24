#include "motion_cmd.h"

#include <eigen3/Eigen/Geometry>
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_eigen/tf2_eigen.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

#include "motion_cmd.h"
#include "spot_micro_kinematics/spot_micro_kinematics.h"
#include "i2cpwm_controller/msg/servo.hpp"
#include "i2cpwm_controller/msg/servo_array.hpp"
#include "i2cpwm_controller/msg/servo_config.hpp"
#include "i2cpwm_controller/srv/servos_config.hpp"
#include "idle.h"
#include "utils.h"

using namespace smk;
using namespace Eigen;
using namespace geometry_msgs::msg;
typedef std::vector<std::pair<std::string,std::string>> VectorStringPairs;

// Constructor
SpotMicroMotionCmd::SpotMicroMotionCmd(std::shared_ptr<rclcpp::Node> nh) {

  nh_ = nh;
  // pnh_ = pnh;
  if (smnc_.debug_mode) {
    std::cout<<"from Constructor \n";
  }

  // Initialize Command 
  cmd_ = Command();

  // Initialize state to Idle state
  state_ = std::make_unique<SpotMicroIdleState>();

  // Read in config parameters into smnc_
  // readInConfigParameters();
  setupParameters();
  
  // Initialize spot micro kinematics object of this class
  sm_ = smk::SpotMicroKinematics(0.0f, 0.0f, 0.0f, smnc_.smc);

  // Set an initial body height and stance cmd for idle mode
  body_state_cmd_.euler_angs = {.phi = 0.0f, .theta = 0.0f, .psi = 0.0f};
  body_state_cmd_.xyz_pos = {.x = 0.0f, .y = smnc_.lie_down_height, .z = 0.0f};
  body_state_cmd_.leg_feet_pos = getLieDownStance();

  // Set the spot micro kinematics object to this initial command
  sm_.setBodyState(body_state_cmd_);

  // Set initial odometry state to zero
  robot_odometry_.euler_angs = {.phi = 0.0f, .theta = 0.0f, .psi = 0.0f};
  robot_odometry_.xyz_pos = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

  // Initialize servo array message with 12 servo objects
  for (int i = 1; i <= smnc_.num_servos; i++) {
    i2cpwm_controller::msg::Servo temp_servo;
    temp_servo.servo = i;
    temp_servo.value = 0;
    servo_array_.servos.push_back(temp_servo);
  }

  // Initialize servo array absolute message with 12 servo object with a value of
  // zero, just copy servo_array_msg since it's already correct 
  servo_array_absolute_.servos = servo_array_.servos;

  // Initialize publishers and subscribers
  // stand cmd event subscriber 
  stand_sub_ = nh_->create_subscription<std_msgs::msg::Bool>(
    "/stand_cmd", // Topic
    1, 
    std::bind(&SpotMicroMotionCmd::standCommandCallback, this, std::placeholders::_1) );
    
  // idle cmd event subscriber
  idle_sub_ = nh_->create_subscription<std_msgs::msg::Bool>(
    "/idle_cmd", 
    1, 
    std::bind(&SpotMicroMotionCmd::idleCommandCallback, this, std::placeholders::_1) );
  
  // walk cmd event subscriber
  walk_sub_ = nh_->create_subscription<std_msgs::msg::Bool>(
    "/walk_cmd", 
    1, 
    std::bind(&SpotMicroMotionCmd::walkCommandCallback, this, std::placeholders::_1) );

  // body angle command subscriber
  body_angle_cmd_sub_ = nh_->create_subscription<geometry_msgs::msg::Vector3>(
    "/angle_cmd",
    1,
    std::bind(&SpotMicroMotionCmd::angleCommandCallback, this, std::placeholders::_1) );  

  // velocity command subscriber 
  vel_cmd_sub_ = nh_->create_subscription<geometry_msgs::msg::Twist>(
    "/cmd_vel",
    1,
    std::bind(&SpotMicroMotionCmd::velCommandCallback, this, std::placeholders::_1) );  

  // servos_absolute publisher
  servos_absolute_pub_ = nh_->create_publisher<i2cpwm_controller::msg::ServoArray>("servos_absolute", 1);

  // Servos proportional publisher
  servos_proportional_pub_ = nh_->create_publisher<i2cpwm_controller::msg::ServoArray>("servos_proportional", 1);  
  
  // Servos configuration publisher
  servos_config_client_ = nh_->create_client<i2cpwm_controller::srv::ServosConfig>("config_servos");

  // Body state publisher for plotting
  body_state_pub_ = nh_->create_publisher<std_msgs::msg::Float32MultiArray>("body_state",1);

  // State string publisher for lcd monitor
  lcd_state_pub_ = nh_->create_publisher<std_msgs::msg::String>("lcd_state", 1);

  // Velocity command state publisher for lcd monitor
  lcd_vel_cmd_pub_ = nh_->create_publisher<geometry_msgs::msg::Twist>("lcd_vel_cmd", 1);

  // Angle command state publisher for lcd monitor
  lcd_angle_cmd_pub_ = nh_->create_publisher<geometry_msgs::msg::Vector3>("lcd_angle_cmd", 1);

  // Initialize transforms broadcasters
  transform_br_ = std::make_shared<tf2_ros::TransformBroadcaster>(nh_);
  static_transform_br_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(nh_);


  // Initialize lcd monitor messages
  lcd_state_string_msg_.data = "Idle";

  lcd_vel_cmd_msg_.linear.x = 0.0f;
  lcd_vel_cmd_msg_.linear.y = 0.0f;
  lcd_vel_cmd_msg_.linear.z = 0.0f;
  lcd_vel_cmd_msg_.angular.x = 0.0f;
  lcd_vel_cmd_msg_.angular.y = 0.0f;
  lcd_vel_cmd_msg_.angular.z = 0.0f;
  
  lcd_angle_cmd_msg_.x = 0.0f;
  lcd_angle_cmd_msg_.y = 0.0f;
  lcd_angle_cmd_msg_.z = 0.0f;
 

  // Only do if plot mode
  // Initialize body state message for plot debug only
  // Initialize 18 values to hold xyz positions of the four legs (12) + 
  // the body x,y,z positions (3), and the body angles (3) for a total of 18
  if (smnc_.plot_mode) {
    for (int i = 0; i < 18; i++) {
      body_state_msg_.data.push_back(0.0f); 
    }
  }

  // Publish static transforms
  publishStaticTransforms();
}


// Destructor method
SpotMicroMotionCmd::~SpotMicroMotionCmd() {

  if (smnc_.debug_mode) {
    std::cout<<"from Destructor \n";
  }
  // Free up the memory assigned from heap
}


void SpotMicroMotionCmd::runOnce() {
  if (smnc_.debug_mode) {
    std::cout<<"from Runonce \n";
  }

  // Call method to handle input commands
  handleInputCommands();

  // Consume all event commands.
  // This resets all event commands if they were true. Doing this enforces a rising edge detection
  resetEventCommands();

  // Only publish body state message in debug mode
  if (smnc_.plot_mode) {
    publishBodyState();
  }

  // Publish lcd monitor data
  publishLcdMonitorData();

  // Broadcast dynamic transforms
  publishDynamicTransforms();

  if (smnc_.publish_odom) {
    // Integrate robot odometry
    integrateOdometry();
  }
}


bool SpotMicroMotionCmd::publishServoConfiguration() {  
  // Create a temporary servo config
  i2cpwm_controller::msg::ServoConfig temp_servo_config;
  // Create a shared pointer for the service request
  auto request = std::make_shared<i2cpwm_controller::srv::ServosConfig::Request>();

  // Loop through servo configuration dictionary in smnc_, append servo to
  for (std::map<std::string, std::map<std::string, float>>::iterator
       iter = smnc_.servo_config.begin();
       iter != smnc_.servo_config.end();
       ++iter) {

    std::map<std::string, float> servo_config_params = iter->second;
    temp_servo_config.center = servo_config_params["center"];
    temp_servo_config.range = servo_config_params["range"];
    temp_servo_config.servo = servo_config_params["num"];
    temp_servo_config.direction = servo_config_params["direction"];

    // Append to temp_servo_config_array
    request->servos.push_back(temp_servo_config);
  }

  // call the client service, return true if succesfull, false if not
  auto result = servos_config_client_->async_send_request(request);
  if (rclcpp::spin_until_future_complete(nh_, result) != rclcpp::FutureReturnCode::SUCCESS) {
    if (!smnc_.debug_mode && !smnc_.run_standalone) {
      // Only error out if not in debug mode or standalone mode 
      RCLCPP_ERROR(nh_->get_logger(), "Failed to call service servo_config");
      return false;
    }
  }

  return true;
}


void SpotMicroMotionCmd::setServoCommandMessageData() {
  // Set the state of the spot micro kinematics object by setting the foot
  // positions, body position, and body orientation. Retrieve joint angles and
  // set the servo cmd message data
  sm_.setBodyState(body_state_cmd_);
  LegsJointAngles joint_angs = sm_.getLegsJointAngles();

  // Set the angles for the servo command message
  servo_cmds_rad_["RF_1"] = joint_angs.right_front.ang1;
  servo_cmds_rad_["RF_2"] = joint_angs.right_front.ang2;
  servo_cmds_rad_["RF_3"] = joint_angs.right_front.ang3;
 
  servo_cmds_rad_["RB_1"] = joint_angs.right_back.ang1;
  servo_cmds_rad_["RB_2"] = joint_angs.right_back.ang2;
  servo_cmds_rad_["RB_3"] = joint_angs.right_back.ang3;
 
  servo_cmds_rad_["LF_1"] = joint_angs.left_front.ang1;
  servo_cmds_rad_["LF_2"] = joint_angs.left_front.ang2;
  servo_cmds_rad_["LF_3"] = joint_angs.left_front.ang3;
 
  servo_cmds_rad_["LB_1"] = joint_angs.left_back.ang1;
  servo_cmds_rad_["LB_2"] = joint_angs.left_back.ang2;
  servo_cmds_rad_["LB_3"] = joint_angs.left_back.ang3;
}


void SpotMicroMotionCmd::publishServoProportionalCommand() {
  for (std::map<std::string, std::map<std::string, float>>::iterator
       iter = smnc_.servo_config.begin();
       iter != smnc_.servo_config.end();
       ++iter) {
 
    std::string servo_name = iter->first;
    std::map<std::string, float> servo_config_params = iter->second;
    
    int servo_num = servo_config_params["num"];
    float cmd_ang_rad = servo_cmds_rad_[servo_name];
    float center_ang_rad = servo_config_params["center_angle_deg"]*M_PI/180.0f;
    float servo_proportional_cmd = (cmd_ang_rad - center_ang_rad) /
                                   (smnc_.servo_max_angle_deg*M_PI/180.0f);
 
    if (servo_proportional_cmd > 1.0f) {
      servo_proportional_cmd = 1.0f;
      RCLCPP_WARN(nh_->get_logger(), "Proportional Command above +1.0 was computed, clipped to 1.0");
      // RCLCPP_WARN(nh_->get_logger(), "Joint %s, Angle: %1.2f", servo_name.c_str(), cmd_ang_rad * 180.0 / M_PI);
    } else if (servo_proportional_cmd < -1.0f) {
      servo_proportional_cmd = -1.0f;
      RCLCPP_WARN(nh_->get_logger(), "Proportional Command below -1.0 was computed, clipped to -1.0");
      // RCLCPP_WARN(nh_->get_logger(), "Joint %s, Angle: %1.2f", servo_name.c_str(), cmd_ang_rad * 180.0 / M_PI);
    }
 
    servo_array_.servos[servo_num-1].servo = servo_num;
    servo_array_.servos[servo_num-1].value = servo_proportional_cmd; 
 }

 // Publish message
 servos_proportional_pub_->publish(servo_array_);
}


void SpotMicroMotionCmd::publishZeroServoAbsoluteCommand() {
  // Publish the servo absolute message
  servos_absolute_pub_->publish(servo_array_absolute_);
}


SpotMicroNodeConfig SpotMicroMotionCmd::getNodeConfig() {
  return smnc_;
}


LegsFootPos SpotMicroMotionCmd::getNeutralStance() {
  float len = smnc_.smc.body_length; // body length
  float width = smnc_.smc.body_width; // body width
  float l1 = smnc_.smc.hip_link_length; // liength of the hip link
  float f_offset = smnc_.stand_front_x_offset; // x offset for front feet in neutral stance
  float b_offset = smnc_.stand_back_x_offset; // y offset for back feet in neutral stance

  LegsFootPos neutral_stance;
  neutral_stance.right_back  = {.x = -len/2 + b_offset, .y = 0.0f, .z =  width/2 + l1};
  neutral_stance.right_front = {.x =  len/2 + f_offset, .y = 0.0f, .z =  width/2 + l1};
  neutral_stance.left_front  = {.x =  len/2 + f_offset, .y = 0.0f, .z = -width/2 - l1};
  neutral_stance.left_back   = {.x = -len/2 + b_offset, .y = 0.0f, .z = -width/2 - l1};

  return neutral_stance;
}


LegsFootPos SpotMicroMotionCmd::getLieDownStance() {
  float len = smnc_.smc.body_length; // body length
  float width = smnc_.smc.body_width; // body width
  float l1 = smnc_.smc.hip_link_length; // length of the hip link
  float x_off = smnc_.lie_down_feet_x_offset;

  LegsFootPos lie_down_stance;
  lie_down_stance.right_back  = {.x = -len/2 + x_off, .y = 0.0f, .z =  width/2 + l1};
  lie_down_stance.right_front = {.x =  len/2 + x_off, .y = 0.0f, .z =  width/2 + l1};
  lie_down_stance.left_front  = {.x =  len/2 + x_off, .y = 0.0f, .z = -width/2 - l1};
  lie_down_stance.left_back   = {.x = -len/2 + x_off, .y = 0.0f, .z = -width/2 - l1};

  return lie_down_stance;
}


void SpotMicroMotionCmd::commandIdle() {
  cmd_.idle_cmd_ = true;
}


std::string SpotMicroMotionCmd::getCurrentStateName() {
  return state_->getCurrentStateName();
}


// void SpotMicroMotionCmd::readInConfigParameters() {
//   // Read in and save parameters 
//   // Use private node handle for getting params so just the relative
//   // parameter name can be used (as opposed to the global name, e.g.:
//   // /spot_micro_motion_cmd/param1
//   pnh_.getParam("hip_link_length", smnc_.smc.hip_link_length);
//   pnh_.getParam("upper_leg_link_length", smnc_.smc.upper_leg_link_length);
//   pnh_.getParam("lower_leg_link_length", smnc_.smc.lower_leg_link_length);
//   pnh_.getParam("body_width", smnc_.smc.body_width);
//   pnh_.getParam("body_length", smnc_.smc.body_length);
//   pnh_.getParam("default_stand_height", smnc_.default_stand_height);
//   pnh_.getParam("stand_front_x_offset", smnc_.stand_front_x_offset);
//   pnh_.getParam("stand_back_x_offset", smnc_.stand_back_x_offset);
//   pnh_.getParam("lie_down_height", smnc_.lie_down_height);
//   pnh_.getParam("lie_down_foot_x_offset", smnc_.lie_down_feet_x_offset);
//   pnh_.getParam("num_servos", smnc_.num_servos);
//   pnh_.getParam("servo_max_angle_deg", smnc_.servo_max_angle_deg);
//   pnh_.getParam("transit_tau", smnc_.transit_tau);
//   pnh_.getParam("transit_rl", smnc_.transit_rl);
//   pnh_.getParam("transit_angle_rl", smnc_.transit_angle_rl);
//   pnh_.getParam("dt", smnc_.dt);
//   pnh_.getParam("debug_mode", smnc_.debug_mode);
//   pnh_.getParam("run_standalone", smnc_.run_standalone);
//   pnh_.getParam("plot_mode", smnc_.plot_mode);
//   pnh_.getParam("max_fwd_velocity", smnc_.max_fwd_velocity);
//   pnh_.getParam("max_side_velocity", smnc_.max_side_velocity);
//   pnh_.getParam("max_yaw_rate", smnc_.max_yaw_rate);
//   pnh_.getParam("z_clearance", smnc_.z_clearance);
//   pnh_.getParam("alpha", smnc_.alpha);
//   pnh_.getParam("beta", smnc_.beta);
//   pnh_.getParam("num_phases", smnc_.num_phases);
//   pnh_.getParam("rb_contact_phases", smnc_.rb_contact_phases);
//   pnh_.getParam("rf_contact_phases", smnc_.rf_contact_phases);
//   pnh_.getParam("lf_contact_phases", smnc_.lf_contact_phases);
//   pnh_.getParam("lb_contact_phases", smnc_.lb_contact_phases);
//   pnh_.getParam("overlap_time", smnc_.overlap_time);
//   pnh_.getParam("swing_time", smnc_.swing_time);
//   pnh_.getParam("foot_height_time_constant", smnc_.foot_height_time_constant);
//   pnh_.getParam("body_shift_phases", smnc_.body_shift_phases);
//   pnh_.getParam("fwd_body_balance_shift", smnc_.fwd_body_balance_shift);
//   pnh_.getParam("back_body_balance_shift", smnc_.back_body_balance_shift);
//   pnh_.getParam("side_body_balance_shift", smnc_.side_body_balance_shift);
//   pnh_.getParam("publish_odom", smnc_.publish_odom);
//   pnh_.getParam("lidar_x_pos", smnc_.lidar_x_pos);
//   pnh_.getParam("lidar_y_pos", smnc_.lidar_y_pos);
//   pnh_.getParam("lidar_z_pos", smnc_.lidar_z_pos);
//   pnh_.getParam("lidar_yaw_angle", smnc_.lidar_yaw_angle);
  
//   // Derived parameters, round result of division of floats
//   smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
//   smnc_.swing_ticks = round(smnc_.swing_time / smnc_.dt);
  
//   // 8 Phase gait specific
//   if (smnc_.num_phases == 8) {    
//     smnc_.stance_ticks = 7 * smnc_.swing_ticks;
//     smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
//     smnc_.phase_ticks = std::vector<int>
//         {smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks,
//         smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks};
//     smnc_.phase_length = smnc_.num_phases * smnc_.swing_ticks;

//   } else { 
//     // 4 phase gait specific
//     smnc_.stance_ticks = 2 * smnc_.overlap_ticks + smnc_.swing_ticks;
//     smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
//     smnc_.phase_ticks = std::vector<int>
//         {smnc_.overlap_ticks, smnc_.swing_ticks, smnc_.overlap_ticks, smnc_.swing_ticks};
//     smnc_.phase_length = 2 * smnc_.swing_ticks + 2 * smnc_.overlap_ticks;
//   }

//   // Temporary map for populating map in smnc_
//   std::map<std::string, float> temp_map;
  
//   // Iterate over servo names, as defined in the map servo_cmds_rad, to populate
//   // the servo config map in smnc_
//   for(std::map<std::string, float>::iterator 
//       iter = servo_cmds_rad_.begin();
//       iter != servo_cmds_rad_.end();
//       ++iter) {

//     std::string servo_name = iter->first; // Get key, string of the servo name
    
//     pnh_.getParam(servo_name, temp_map); // Read the parameter. Parameter name must match servo name
//     smnc_.servo_config[servo_name] = temp_map; // Assing in servo config to map in the struct
//   }
  
// }


void SpotMicroMotionCmd::standCommandCallback(
    const std_msgs::msg::Bool::SharedPtr msg) {
  if (msg->data == true) {cmd_.stand_cmd_ = true;}
}


void SpotMicroMotionCmd::idleCommandCallback(
    const std_msgs::msg::Bool::SharedPtr msg) {
  if (msg->data == true) {cmd_.idle_cmd_ = true;}
}


void SpotMicroMotionCmd::walkCommandCallback(
    const std_msgs::msg::Bool::SharedPtr msg) {
  if (msg->data == true) {cmd_.walk_cmd_ = true;}
}


void SpotMicroMotionCmd::angleCommandCallback(
    const geometry_msgs::msg::Vector3::SharedPtr msg) {
  cmd_.phi_cmd_ = msg->x;
  cmd_.theta_cmd_ = msg->y;
  cmd_.psi_cmd_ = msg->z;
}


void SpotMicroMotionCmd::velCommandCallback(
    const geometry_msgs::msg::Twist::SharedPtr msg) {
  cmd_.x_vel_cmd_mps_ = msg->linear.x;
  cmd_.y_vel_cmd_mps_ = msg->linear.y;
  cmd_.yaw_rate_cmd_rps_ = msg->angular.z;
}


void SpotMicroMotionCmd::resetEventCommands() {
  // Reset all event commands, setting all command states false if they were true 
  cmd_.resetEventCmds(); 
}


void SpotMicroMotionCmd::handleInputCommands() {
  // Delegate input handling to state
  state_->handleInputCommands(sm_.getBodyState(), smnc_, cmd_, this, &body_state_cmd_);
}


void SpotMicroMotionCmd::changeState(std::unique_ptr<SpotMicroState> sms) {
  // Change the active state
  state_ = std::move(sms);

  // Call init method of new state
  state_->init(sm_.getBodyState(), smnc_, cmd_, this);

  // Reset all command values
  cmd_.resetAllCommands();
}


void SpotMicroMotionCmd::publishBodyState() {
  // Order of the float array:
  // 3 floats xyz for rightback leg foot pos
  // 3 floats xyz for rightfront leg foot pos
  // 3 floats xyz for leftfront leg foot pos
  // 3 floats xyz for leftback leg foot pos
  // 3 floats for xyz body position
  // 3 floats for phi, theta, psi body angles
  
  body_state_msg_.data[0] = body_state_cmd_.leg_feet_pos.right_back.x;
  body_state_msg_.data[1] = body_state_cmd_.leg_feet_pos.right_back.y;
  body_state_msg_.data[2] = body_state_cmd_.leg_feet_pos.right_back.z;

  body_state_msg_.data[3] = body_state_cmd_.leg_feet_pos.right_front.x;
  body_state_msg_.data[4] = body_state_cmd_.leg_feet_pos.right_front.y;
  body_state_msg_.data[5] = body_state_cmd_.leg_feet_pos.right_front.z;

  body_state_msg_.data[6] = body_state_cmd_.leg_feet_pos.left_front.x;
  body_state_msg_.data[7] = body_state_cmd_.leg_feet_pos.left_front.y;
  body_state_msg_.data[8] = body_state_cmd_.leg_feet_pos.left_front.z;

  body_state_msg_.data[9] = body_state_cmd_.leg_feet_pos.left_back.x;
  body_state_msg_.data[10] = body_state_cmd_.leg_feet_pos.left_back.y;
  body_state_msg_.data[11] = body_state_cmd_.leg_feet_pos.left_back.z;

  body_state_msg_.data[12] = body_state_cmd_.xyz_pos.x;
  body_state_msg_.data[13] = body_state_cmd_.xyz_pos.y;
  body_state_msg_.data[14] = body_state_cmd_.xyz_pos.z;

  body_state_msg_.data[15] = body_state_cmd_.euler_angs.phi;
  body_state_msg_.data[16] = body_state_cmd_.euler_angs.theta;
  body_state_msg_.data[17] = body_state_cmd_.euler_angs.psi;

  body_state_pub_->publish(body_state_msg_);
}


void SpotMicroMotionCmd::publishLcdMonitorData() {
  lcd_state_string_msg_.data = getCurrentStateName();

  lcd_vel_cmd_msg_.linear.x = cmd_.getXSpeedCmd();
  lcd_vel_cmd_msg_.linear.y = cmd_.getYSpeedCmd();
  lcd_vel_cmd_msg_.angular.z = cmd_.getYawRateCmd();
  
  lcd_angle_cmd_msg_.x = cmd_.getPhiCmd();
  lcd_angle_cmd_msg_.y = cmd_.getThetaCmd();
  lcd_angle_cmd_msg_.z = cmd_.getPsiCmd();  

  lcd_state_pub_->publish(lcd_state_string_msg_);
  lcd_vel_cmd_pub_->publish(lcd_vel_cmd_msg_);
  lcd_angle_cmd_pub_->publish(lcd_angle_cmd_msg_);
}


void SpotMicroMotionCmd::publishStaticTransforms() {

  TransformStamped tr_stamped;
  
  // base_link to front_link transform
  tr_stamped = createTransform("base_link", "front_link",
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0);
  static_transform_br_->sendTransform(tr_stamped);

  // base_link to rear_link transform
  tr_stamped = createTransform("base_link", "rear_link",
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0);                          
  static_transform_br_->sendTransform(tr_stamped);

  // base_link to lidar_link transform
  float x_offset = smnc_.lidar_x_pos;
  float y_offset = smnc_.lidar_y_pos;
  float z_offset = smnc_.lidar_z_pos;
  float yaw_angle = smnc_.lidar_yaw_angle*M_PI/180.0; // Converted to radians
  tr_stamped = createTransform("base_link", "lidar_link",
                               x_offset, y_offset, z_offset,
                               0.0, 0.0, yaw_angle);                       
  static_transform_br_->sendTransform(tr_stamped);

  // legs to leg cover transforms
  const VectorStringPairs leg_cover_pairs { 
      { "front_left_leg_link",  "front_left_leg_link_cover" },
      { "front_right_leg_link", "front_right_leg_link_cover"},
      { "rear_right_leg_link",  "rear_right_leg_link_cover" },
      { "rear_left_leg_link",   "rear_left_leg_link_cover" }};
  
  // Loop over all leg to leg cover name pairs, publish a 0 dist/rot transform
  for (auto it = leg_cover_pairs.begin(); it != leg_cover_pairs.end(); it++) {
    tr_stamped = createTransform(it->first, it->second,
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0);
    static_transform_br_->sendTransform(tr_stamped); 
  }

  // foot to toe link transforms
  const VectorStringPairs foot_toe_pairs { 
      { "front_left_foot_link",  "front_left_toe_link" },
      { "front_right_foot_link", "front_right_toe_link"},
      { "rear_right_foot_link",  "rear_right_toe_link" },
      { "rear_left_foot_link",   "rear_left_toe_link" }};
  
  // Loop over all name pairs, publish the same transform
  for (auto it = foot_toe_pairs.begin(); it != foot_toe_pairs.end(); it++) {
    tr_stamped = createTransform(it->first, it->second,
                               0.0, 0.0, -0.13, // TODO: Change to a parameter
                               0.0, 0.0, 0.0);
    static_transform_br_->sendTransform(tr_stamped); 
  }
}


void SpotMicroMotionCmd::publishDynamicTransforms() {

  // Get joint angles
  LegsJointAngles joint_angs = sm_.getLegsJointAngles();

  // Declare utility variables
  TransformStamped transform_stamped;
  Affine3d temp_trans;

  /////////////////
  // ODOMETRY /////
  /////////////////
  if (smnc_.publish_odom) {
    transform_stamped = eigAndFramesToTrans(getOdometryTransform(), "odom", "base_footprint");
    transform_br_->sendTransform(transform_stamped);
  }
  
  /////////////////
  // BODY CENTER //
  /////////////////
  
  temp_trans = matrix4fToAffine3d(sm_.getBodyHt());

  // Rotate body center transform to desired coordinate system
  // Original, kinematics, coordinate frame: x forward, y up, z right
  // Desired orientation: x forward, y left, z up
  // Rotate the robot frame +90 deg about the global +X axis (pre-multiply),
  // then rotate the local coordinate system by -90 (post multiply)
  temp_trans =  AngleAxisd(M_PI/2.0, Vector3d::UnitX()) * 
                temp_trans * 
                AngleAxisd(-M_PI/2.0, Vector3d::UnitX());

  // Create and broadcast the transform
  transform_stamped = eigAndFramesToTrans(temp_trans, "base_footprint", "base_link");
  transform_br_->sendTransform(transform_stamped);


  /////////////////////
  // FRONT RIGHT LEG //
  /////////////////////
  // Shoulder
  transform_stamped = createTransform("base_link", "front_right_shoulder_link",
                                      smnc_.smc.body_length/2.0, -smnc_.smc.body_width/2.0, 0.0,
                                      joint_angs.right_front.ang1, 0.0, 0.0);      
  transform_br_->sendTransform(transform_stamped);

  // leg
  transform_stamped = createTransform("front_right_shoulder_link","front_right_leg_link",
                                      0.0, -smnc_.smc.hip_link_length, 0.0,
                                      0.0, -joint_angs.right_front.ang2, 0.0);                         
  transform_br_->sendTransform(transform_stamped);

  // foot
  transform_stamped = createTransform("front_right_leg_link","front_right_foot_link",
                                      0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                      0.0, -joint_angs.right_front.ang3, 0.0);                         
  transform_br_->sendTransform(transform_stamped);


  ////////////////////
  // REAR RIGHT LEG //
  ////////////////////
  // shoulder
  transform_stamped = createTransform("base_link", "rear_right_shoulder_link",
                                      -smnc_.smc.body_length/2.0, -smnc_.smc.body_width/2.0, 0.0,
                                      joint_angs.right_back.ang1, 0.0, 0.0);      
  transform_br_->sendTransform(transform_stamped);
  
  // leg
  transform_stamped = createTransform("rear_right_shoulder_link","rear_right_leg_link",
                                      0.0, -smnc_.smc.hip_link_length, 0.0,
                                      0.0, -joint_angs.right_back.ang2, 0.0);                         
  transform_br_->sendTransform(transform_stamped);

  // foot
  transform_stamped = createTransform("rear_right_leg_link","rear_right_foot_link",
                                      0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                      0.0, -joint_angs.right_back.ang3, 0.0);                         
  transform_br_->sendTransform(transform_stamped);


  ////////////////////
  // FRONT LEFT LEG //
  ////////////////////
  // Shoulder
  transform_stamped = createTransform("base_link", "front_left_shoulder_link",
                                      smnc_.smc.body_length/2.0, smnc_.smc.body_width/2.0, 0.0,
                                      -joint_angs.left_front.ang1, 0.0, 0.0);      
  transform_br_->sendTransform(transform_stamped);

  // leg
  transform_stamped = createTransform("front_left_shoulder_link","front_left_leg_link",
                                      0.0, smnc_.smc.hip_link_length, 0.0,
                                      0.0, joint_angs.left_front.ang2, 0.0);                         
  transform_br_->sendTransform(transform_stamped);

  // foot
  transform_stamped = createTransform("front_left_leg_link","front_left_foot_link",
                                      0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                      0.0, joint_angs.left_front.ang3, 0.0);                         
  transform_br_->sendTransform(transform_stamped);


  ///////////////////
  // REAR LEFT LEG //
  ///////////////////
  // shoulder
  transform_stamped = createTransform("base_link", "rear_left_shoulder_link",
                                      -smnc_.smc.body_length/2.0, smnc_.smc.body_width/2.0, 0.0,
                                      -joint_angs.left_back.ang1, 0.0, 0.0);      
  transform_br_->sendTransform(transform_stamped);

  // leg
  transform_stamped = createTransform("rear_left_shoulder_link","rear_left_leg_link",
                                      0.0, smnc_.smc.hip_link_length, 0.0,
                                      0.0, joint_angs.left_back.ang2, 0.0);                         
  transform_br_->sendTransform(transform_stamped);

  // foot
  transform_stamped = createTransform("rear_left_leg_link","rear_left_foot_link",
                                      0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                      0.0, joint_angs.left_back.ang3, 0.0);                         
  transform_br_->sendTransform(transform_stamped);
}


void SpotMicroMotionCmd::integrateOdometry() {
  // Get loop time, heading, and rate commands
  float dt = smnc_.dt;
  float psi = robot_odometry_.euler_angs.psi;
  float x_spd = cmd_.getXSpeedCmd();
  float y_spd = -cmd_.getYSpeedCmd();
  float yaw_rate = -cmd_.getYawRateCmd();

  // This is the odometry coordinate frame (not the robot kinematic frame) 
  float x_dot = x_spd*cos(psi) - y_spd*sin(psi);
  float y_dot = x_spd*sin(psi) + y_spd*cos(psi);
  float yaw_dot = yaw_rate;

  // Integrate x and y position, and yaw angle, from commanded values
  // y speed and yaw rate are reversed due to mismatch between command 
  // coordinate frame and world coordinate frame
  robot_odometry_.xyz_pos.x += x_dot*dt;
  robot_odometry_.xyz_pos.y += y_dot*dt;
  robot_odometry_.euler_angs.psi += yaw_dot*dt;
} 


Affine3d SpotMicroMotionCmd::getOdometryTransform() {
  // Create odemtry translation and rotation, and combine together
  Translation3d translation(robot_odometry_.xyz_pos.x, robot_odometry_.xyz_pos.y, 0.0);
  AngleAxisd rotation(robot_odometry_.euler_angs.psi, Vector3d::UnitZ());

  return (translation * rotation);
}


// In ROS 2 reading parameters from configuration file is very different from ROS 1
// Thus setupParameters() cancel the need of the config file all parameters can be
// found in this function
void SpotMicroMotionCmd::setupParameters() {

  // Robots dimmensions
  smnc_.smc.hip_link_length = 0.055;
  smnc_.smc.upper_leg_link_length = 0.1075;
  smnc_.smc.lower_leg_link_length = 0.130;
  smnc_.smc.body_width = 0.078;
  smnc_.smc.body_length = 0.186;

  // Stance
  smnc_.default_stand_height = 0.155;
  smnc_.stand_front_x_offset = 0.015;
  smnc_.stand_back_x_offset = -0.000;
  smnc_.lie_down_height = 0.083;
  smnc_.lie_down_feet_x_offset = 0.065;

  // Servos
  smnc_.num_servos = 12;
  smnc_.servo_max_angle_deg = 82.5;
  smnc_.servo_config = {
    {"RF_3", {{"num", 1}, {"center", 306}, {"range", 385.0}, {"direction", 1}, {"center_angle_deg", 77.57}}},
    {"RF_2", {{"num", 2}, {"center", 306}, {"range", 405.2}, {"direction", 1}, {"center_angle_deg", -56.20}}},
    {"RF_1", {{"num", 3}, {"center", 306}, {"range", 333.7}, {"direction", -1}, {"center_angle_deg", 6.43}}},
    {"RB_3", {{"num", 4}, {"center", 306}, {"range", 392.3}, {"direction", 1}, {"center_angle_deg", 71.50}}},
    {"RB_2", {{"num", 5}, {"center", 306}, {"range", 407.0}, {"direction", 1}, {"center_angle_deg", -55.14}}},
    {"RB_1", {{"num", 6}, {"center", 306}, {"range", 407.0}, {"direction", 1}, {"center_angle_deg", -14.19}}},
    {"LB_3", {{"num", 7}, {"center", 306}, {"range", 370.3}, {"direction", 1}, {"center_angle_deg", -93.12}}},
    {"LB_2", {{"num", 8}, {"center", 306}, {"range", 396.0}, {"direction", 1}, {"center_angle_deg", 40.00}}},
    {"LB_1", {{"num", 9}, {"center", 306}, {"range", 337.3}, {"direction", -1}, {"center_angle_deg", 4.40}}},
    {"LF_3", {{"num", 10}, {"center", 306}, {"range", 375.8}, {"direction", 1}, {"center_angle_deg", -93.95}}},
    {"LF_2", {{"num", 11}, {"center", 306}, {"range", 416.2}, {"direction", 1}, {"center_angle_deg", 40.84}}},
    {"LF_1", {{"num", 12}, {"center", 306}, {"range", 341.0}, {"direction", 1}, {"center_angle_deg", -14.03}}}
  };

  // Control
  smnc_.transit_tau = 0.3;
  smnc_.transit_rl = 0.06;
  smnc_.transit_angle_rl = 0.35;
  smnc_.max_fwd_velocity = 0.4;
  smnc_.max_side_velocity = 0.4;
  smnc_.max_yaw_rate = 0.35;

  // Gait setup
  smnc_.z_clearance = 0.050;
  smnc_.alpha = 0.5;
  smnc_.beta = 0.5;
  smnc_.foot_height_time_constant = 0.02;
  // 8 Phase Gait
  smnc_.num_phases = 8;
  smnc_.rb_contact_phases = {1, 0, 1, 1, 1, 1, 1, 1};
  smnc_.rf_contact_phases = {1, 1, 1, 0, 1, 1, 1, 1};
  smnc_.lf_contact_phases = {1, 1, 1, 1, 1, 1, 1, 0};
  smnc_.lb_contact_phases = {1, 1, 1, 1, 1, 0, 1, 1};
  smnc_.overlap_time = 0.0;
  smnc_.swing_time = 0.36;
  smnc_.body_shift_phases = {1, 2, 3, 4, 5, 6, 7, 8};
  smnc_.fwd_body_balance_shift = 0.035;
  smnc_.back_body_balance_shift = 0.005;
  smnc_.side_body_balance_shift = 0.015;


  // TF Parameter
  smnc_.lidar_x_pos = 0.045;
  smnc_.lidar_y_pos = 0.0;
  smnc_.lidar_z_pos = 0.085;
  smnc_.lidar_yaw_angle = 180;

  // Node parameters
  smnc_.dt = 0.02;
  smnc_.publish_odom = true;

  smnc_.debug_mode = true;
  smnc_.plot_mode = false;
  smnc_.run_standalone = false;
  
  // Derived parameters, round result of division of floats
  smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
  smnc_.swing_ticks = round(smnc_.swing_time / smnc_.dt);
  
  // 8 Phase gait specific
  if (smnc_.num_phases == 8) {    
    smnc_.stance_ticks = 7 * smnc_.swing_ticks;
    smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
    smnc_.phase_ticks = std::vector<int>
        {smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks,
        smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks, smnc_.swing_ticks};
    smnc_.phase_length = smnc_.num_phases * smnc_.swing_ticks;

  } else { 
    // 4 phase gait specific
    smnc_.stance_ticks = 2 * smnc_.overlap_ticks + smnc_.swing_ticks;
    smnc_.overlap_ticks = round(smnc_.overlap_time / smnc_.dt);
    smnc_.phase_ticks = std::vector<int>
        {smnc_.overlap_ticks, smnc_.swing_ticks, smnc_.overlap_ticks, smnc_.swing_ticks};
    smnc_.phase_length = 2 * smnc_.swing_ticks + 2 * smnc_.overlap_ticks;
  }  

} 