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
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#include "spot_micro_kinematics/spot_micro_kinematics.h"
#include "i2cpwm_controller/msg/servo.hpp"
#include "i2cpwm_controller/msg/servo_array.hpp"
#include "i2cpwm_controller/msg/servo_config.hpp"
#include "i2cpwm_controller/srv/servos_config.hpp"
#include "idle.h"
#include "utils.h"

using namespace smk;
using namespace Eigen;
using namespace geometry_msgs;
typedef std::vector<std::pair<std::string, std::string>> VectorStringPairs;

/////////////////////////////////////////////////////////////////////////////////
// Constructor
SpotMicroMotionCmd::SpotMicroMotionCmd(rclcpp::NodeOptions & options) : Node("spot_micro_motion_cmd", options) {
  if (smnc_.debug_mode) {
    RCLCPP_INFO(this->get_logger(), "from Constructor");
  }

  // Initialize Command 
  cmd_ = Command();

  // Initialize state to Idle state
  state_ = std::make_unique<SpotMicroIdleState>();

  // Read in config parameters into smnc_
  readInConfigParameters();

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
    i2cpwm_controller::Servo temp_servo;
    temp_servo.servo = i;
    temp_servo.value = 0;
    servo_array_.servos.push_back(temp_servo);
  }

  // Initialize servo array absolute message with 12 servo object with a value of zero
  servo_array_absolute_.servos = servo_array_.servos;

  // Initialize publishers and subscribers
  stand_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/stand_cmd", 1, std::bind(&SpotMicroMotionCmd::standCommandCallback, this, std::placeholders::_1));

  idle_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/idle_cmd", 1, std::bind(&SpotMicroMotionCmd::idleCommandCallback, this, std::placeholders::_1));

  walk_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/walk_cmd", 1, std::bind(&SpotMicroMotionCmd::walkCommandCallback, this, std::placeholders::_1));

  body_angle_cmd_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/angle_cmd", 1, std::bind(&SpotMicroMotionCmd::angleCommandCallback, this, std::placeholders::_1));

  vel_cmd_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/cmd_vel", 1, std::bind(&SpotMicroMotionCmd::velCommandCallback, this, std::placeholders::_1));

  servos_absolute_pub_ = this->create_publisher<i2cpwm_controller::ServoArray>("servos_absolute", 1);
  servos_proportional_pub_ = this->create_publisher<i2cpwm_controller::ServoArray>("servos_proportional", 1);

  // Service client for servo configuration
  servos_config_client_ = this->create_client<i2cpwm_controller::ServosConfig>("config_servos");

  // Body state publisher for plotting
  body_state_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("body_state", 1);

  // State string publisher for LCD monitor
  lcd_state_pub_ = this->create_publisher<std_msgs::msg::String>("lcd_state", 1);

  // Velocity command state publisher for LCD monitor
  lcd_vel_cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("lcd_vel_cmd", 1);

  // Angle command state publisher for LCD monitor
  lcd_angle_cmd_pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("lcd_angle_cmd", 1);

  // Transforms broadcaster initialization
  transform_br_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
  static_transform_br_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
  

  // Initialize LCD monitor messages
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

  // Initialize body state message for plot debug only if plot mode is enabled
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
/////////////////////////////////////////////////////////////////////////////////

// Main node logic flux
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
    auto temp_servo_config_array = std::make_shared<i2cpwm_controller::srv::ServosConfig::Request>();

    // Loop through servo configuration dictionary in smnc_, append servo to temp config array
    for (auto iter = smnc_.servo_config.begin(); iter != smnc_.servo_config.end(); ++iter) {
        std::map<std::string, float> servo_config_params = iter->second;

        temp_servo_config->center = servo_config_params["center"];
        temp_servo_config->range = servo_config_params["range"];
        temp_servo_config->servo = servo_config_params["num"];
        temp_servo_config->direction = servo_config_params["direction"];

        // Append to temp_servo_config_array
        temp_servo_config_array->servos.push_back(*temp_servo_config);
    }

    // Call the service
    auto result = servos_config_client_->async_send_request(temp_servo_config_array);

    // Check the service result
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) != rclcpp::FutureReturnCode::SUCCESS) {
        if (!smnc_.debug_mode && !smnc_.run_standalone) {
            // Only error out if not in debug mode or standalone mode
            RCLCPP_ERROR(get_logger(), "Failed to call service servo_config");
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
    for (auto iter = smnc_.servo_config.begin(); iter != smnc_.servo_config.end(); ++iter) {
        std::string servo_name = iter->first;
        std::map<std::string, float> servo_config_params = iter->second;
        
        int servo_num = servo_config_params["num"];
        float cmd_ang_rad = servo_cmds_rad_[servo_name];
        float center_ang_rad = servo_config_params["center_angle_deg"] * M_PI / 180.0f;
        float servo_proportional_cmd = (cmd_ang_rad - center_ang_rad) / 
                                       (smnc_.servo_max_angle_deg * M_PI / 180.0f);
        
        if (servo_proportional_cmd > 1.0f) {
            servo_proportional_cmd = 1.0f;
            RCLCPP_WARN(this->get_logger(), 
                        "Proportional Command above +1.0 was computed, clipped to 1.0");
            RCLCPP_WARN(this->get_logger(), 
                        "Joint %s, Angle: %1.2f", servo_name.c_str(), cmd_ang_rad * 180.0 / M_PI);
        
        } else if (servo_proportional_cmd < -1.0f) {
            servo_proportional_cmd = -1.0f;
            RCLCPP_WARN(this->get_logger(), 
                        "Proportional Command below -1.0 was computed, clipped to -1.0");
            RCLCPP_WARN(this->get_logger(), 
                        "Joint %s, Angle: %1.2f", servo_name.c_str(), cmd_ang_rad * 180.0 / M_PI);
        }

        servo_array_.servos[servo_num - 1].servo = servo_num;
        servo_array_.servos[servo_num - 1].value = servo_proportional_cmd;
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

////////////////////////////////////////////////////////////////////////////////////////////
// Legs Pose methods:
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
////////////////////////////////////////////////////////////////////////////////

void SpotMicroMotionCmd::commandIdle() {
  cmd_.idle_cmd_ = true;
}

std::string SpotMicroMotionCmd::getCurrentStateName() {
  return state_->getCurrentStateName();
}


void SpotMicroMotionCmd::readInConfigParameters() {
    // Declare and read in parameters, including nested ones for the servo configuration
    // Parameters hard coded and extracted from config file spot_micro_motion_cmd.yaml
    smnc_.smc.hip_link_length = this->declare_parameter("hip_link_length", 0.055);  
    smnc_.smc.upper_leg_link_length = this->declare_parameter("upper_leg_link_length", 0.1075);  
    smnc_.smc.lower_leg_link_length = this->declare_parameter("lower_leg_link_length", 0.130);  
    smnc_.smc.body_width = this->declare_parameter("body_width", 0.078);  
    smnc_.smc.body_length = this->declare_parameter("body_length", 0.186);  
    smnc_.default_stand_height = this->declare_parameter("default_stand_height", 0.155);  
    smnc_.stand_front_x_offset = this->declare_parameter("stand_front_x_offset", 0.015);  
    smnc_.stand_back_x_offset = this->declare_parameter("stand_back_x_offset", 0.000);  
    smnc_.lie_down_height = this->declare_parameter("lie_down_height", 0.083);  
    smnc_.lie_down_feet_x_offset = this->declare_parameter("lie_down_foot_x_offset", 0.065);  
    smnc_.num_servos = this->declare_parameter("num_servos", 12);  // Defaulting to 12 servos, from config
    smnc_.servo_max_angle_deg = this->declare_parameter("servo_max_angle_deg", 82.5);  // Corrected from config
    smnc_.transit_tau = this->declare_parameter("transit_tau", 0.3);  
    smnc_.transit_rl = this->declare_parameter("transit_rl", 0.06);  
    smnc_.transit_angle_rl = this->declare_parameter("transit_angle_rl", 0.35);  
    smnc_.dt = this->declare_parameter("dt", 0.02);  
    smnc_.debug_mode = this->declare_parameter("debug_mode", false);  
    smnc_.run_standalone = this->declare_parameter("standalone_mode", false);  
    smnc_.plot_mode = this->declare_parameter("plot_mode", false);  
    smnc_.max_fwd_velocity = this->declare_parameter("max_fwd_velocity", 0.4);  
    smnc_.max_side_velocity = this->declare_parameter("max_side_velocity", 0.4);  
    smnc_.max_yaw_rate = this->declare_parameter("max_yaw_rate", 0.35);  
    smnc_.z_clearance = this->declare_parameter("z_clearance", 0.05);  
    smnc_.alpha = this->declare_parameter("alpha", 0.5);  
    smnc_.beta = this->declare_parameter("beta", 0.5);  
    smnc_.num_phases = this->declare_parameter("num_phases", 8);  // 8 phases, from config
    smnc_.overlap_time = this->declare_parameter("overlap_time", 0.0);  
    smnc_.swing_time = this->declare_parameter("swing_time", 0.36);  
    smnc_.foot_height_time_constant = this->declare_parameter("foot_height_time_constant", 0.02);  
    smnc_.fwd_body_balance_shift = this->declare_parameter("fwd_body_balance_shift", 0.035);  
    smnc_.side_body_balance_shift = this->declare_parameter("side_body_balance_shift", 0.015);  
    smnc_.back_body_balance_shift = this->declare_parameter("back_body_balance_shift", 0.005);  
    smnc_.publish_odom = this->declare_parameter("publish_odom", true);  
    smnc_.lidar_x_pos = this->declare_parameter("lidar_x_pos", 0.045);  
    smnc_.lidar_y_pos = this->declare_parameter("lidar_y_pos", 0.0);  
    smnc_.lidar_z_pos = this->declare_parameter("lidar_z_pos", 0.085);  
    smnc_.lidar_yaw_angle = this->declare_parameter("lidar_yaw_angle", 180.0);  

    // Derived parameters, round result of division of floats
    smnc_.overlap_ticks = std::round(smnc_.overlap_time / smnc_.dt);
    smnc_.swing_ticks = std::round(smnc_.swing_time / smnc_.dt);

    // Gait-specific configurations (8 phase vs 4 phase)
    if (smnc_.num_phases == 8) {
        smnc_.stance_ticks = 7 * smnc_.swing_ticks;
        smnc_.phase_ticks = std::vector<int>(8, smnc_.swing_ticks);
        smnc_.phase_length = smnc_.num_phases * smnc_.swing_ticks;
    } else {
        smnc_.stance_ticks = 2 * smnc_.overlap_ticks + smnc_.swing_ticks;
        smnc_.phase_ticks = {smnc_.overlap_ticks, smnc_.swing_ticks, smnc_.overlap_ticks, smnc_.swing_ticks};
        smnc_.phase_length = 2 * smnc_.swing_ticks + 2 * smnc_.overlap_ticks;
    }

    // Read in the servo configuration parameters (nested map)
    for (auto &servo : servo_cmds_rad_) {
        std::string servo_name = servo.first;
        std::map<std::string, float> temp_map;
        this->declare_parameter(servo_name);  // Declare the servo parameters
        get_parameter(servo_name, temp_map);  // Get nested servo parameters
        smnc_.servo_config[servo_name] = temp_map;
    }
}

///////////////////////////////////////////////////////////////////////
//Callbacks:

void SpotMicroMotionCmd::standCommandCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    cmd_.stand_cmd_ = msg->data; // Set stand_cmd_ based on the received message
}

void SpotMicroMotionCmd::idleCommandCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    cmd_.idle_cmd_ = msg->data; // Set idle_cmd_ based on the received message
}

void SpotMicroMotionCmd::walkCommandCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    cmd_.walk_cmd_ = msg->data; // Set walk_cmd_ based on the received message
}

void SpotMicroMotionCmd::angleCommandCallback(const geometry_msgs::msg::Vector3::SharedPtr msg) {
    cmd_.phi_cmd_ = msg->x;     // Set phi_cmd_ from Vector3 message
    cmd_.theta_cmd_ = msg->y;    // Set theta_cmd_ from Vector3 message
    cmd_.psi_cmd_ = msg->z;      // Set psi_cmd_ from Vector3 message
}

void SpotMicroMotionCmd::velCommandCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    cmd_.x_vel_cmd_mps_ = msg->linear.x;  // Set linear x velocity
    cmd_.y_vel_cmd_mps_ = msg->linear.y;  // Set linear y velocity
    cmd_.yaw_rate_cmd_rps_ = msg->angular.z; // Set angular z velocity (yaw rate)
}

///////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////
// Publishers

void SpotMicroMotionCmd::publishBodyState() {
    // Order of the float array:
    // 3 floats for xyz of right back leg foot pos
    // 3 floats for xyz of right front leg foot pos
    // 3 floats for xyz of left front leg foot pos
    // 3 floats for xyz of left back leg foot pos
    // 3 floats for xyz body position
    // 3 floats for phi, theta, psi body angles

    body_state_msg_.data.resize(18); // Resize the array to hold 18 floats

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

    // Publish the body state message
    body_state_pub_->publish(body_state_msg_);
}


void SpotMicroMotionCmd::publishLcdMonitorData() {
    // Set LCD state message with current state name
    lcd_state_string_msg_.data = getCurrentStateName();

    // Set velocity command message
    lcd_vel_cmd_msg_.linear.x = cmd_.getXSpeedCmd();
    lcd_vel_cmd_msg_.linear.y = cmd_.getYSpeedCmd();
    lcd_vel_cmd_msg_.angular.z = cmd_.getYawRateCmd();

    // Set body angle command message
    lcd_angle_cmd_msg_.x = cmd_.getPhiCmd();
    lcd_angle_cmd_msg_.y = cmd_.getThetaCmd();
    lcd_angle_cmd_msg_.z = cmd_.getPsiCmd();

    // Publish the state, velocity, and angle messages
    lcd_state_pub_->publish(lcd_state_string_msg_);
    lcd_vel_cmd_pub_->publish(lcd_vel_cmd_msg_);
    lcd_angle_cmd_pub_->publish(lcd_angle_cmd_msg_);
}


void SpotMicroMotionCmd::publishStaticTransforms() {

  geometry_msgs::msg::TransformStamped tr_stamped;

  // base_link to front_link transform
  tr_stamped = createTransform("base_link", "front_link",
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0,
                               this->get_clock());
  static_transform_br_->sendTransform(tr_stamped);

  // base_link to rear_link transform
  tr_stamped = createTransform("base_link", "rear_link",
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0,
                               this->get_clock());
  static_transform_br_->sendTransform(tr_stamped);

  // base_link to lidar_link transform
  float x_offset = smnc_.lidar_x_pos;
  float y_offset = smnc_.lidar_y_pos;
  float z_offset = smnc_.lidar_z_pos;
  float yaw_angle = smnc_.lidar_yaw_angle * M_PI / 180.0; // Converted to radians
  tr_stamped = createTransform("base_link", "lidar_link",
                               x_offset, y_offset, z_offset,
                               0.0, 0.0, yaw_angle,
                               this->get_clock());
  static_transform_br_->sendTransform(tr_stamped);

  // Legs to leg cover transforms
  const VectorStringPairs leg_cover_pairs {
      { "front_left_leg_link",  "front_left_leg_link_cover" },
      { "front_right_leg_link", "front_right_leg_link_cover" },
      { "rear_right_leg_link",  "rear_right_leg_link_cover" },
      { "rear_left_leg_link",   "rear_left_leg_link_cover" }
  };

  // Loop over all leg to leg cover name pairs, publish a 0 distance/rotation transform
  for (const auto& pair : leg_cover_pairs) {
    tr_stamped = createTransform(pair.first, pair.second,
                               0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0,
                               this->get_clock());
    static_transform_br_->sendTransform(tr_stamped);
  }

  // Foot to toe link transforms
  const VectorStringPairs foot_toe_pairs {
      { "front_left_foot_link",  "front_left_toe_link" },
      { "front_right_foot_link", "front_right_toe_link" },
      { "rear_right_foot_link",  "rear_right_toe_link" },
      { "rear_left_foot_link",   "rear_left_toe_link" }
  };

  // Loop over all name pairs, publish the same transform
  for (const auto& pair : foot_toe_pairs) {
    tr_stamped = createTransform(pair.first, pair.second,
                               0.0, 0.0, -0.13, // TODO: Change to a parameter
                               0.0, 0.0, 0.0,
                               this->get_clock());
    static_transform_br_->sendTransform(tr_stamped);
  }
}


void SpotMicroMotionCmd::publishDynamicTransforms() {
    // Get joint angles
    LegsJointAngles joint_angs = sm_.getLegsJointAngles();

    // Declare utility variables
    geometry_msgs::msg::TransformStamped transform_stamped;
    Eigen::Affine3d temp_trans;

    /////////////////
    // ODOMETRY /////
    /////////////////
    if (smnc_.publish_odom) {
        transform_stamped = eigAndFramesToTrans(getOdometryTransform(), "odom", "base_footprint", this->get_clock());
        // transform_stamped.header.stamp = this->get_clock()->now();
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
    temp_trans =  Eigen::AngleAxisd(M_PI/2.0, Eigen::Vector3d::UnitX()) * 
                  temp_trans * 
                  Eigen::AngleAxisd(-M_PI/2.0, Eigen::Vector3d::UnitX());

    // Create and broadcast the transform
    transform_stamped = eigAndFramesToTrans(temp_trans, "base_footprint", "base_link", this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    /////////////////////
    // FRONT RIGHT LEG //
    /////////////////////
    // Shoulder
    transform_stamped = createTransform("base_link", "front_right_shoulder_link",
                                        smnc_.smc.body_length/2.0, -smnc_.smc.body_width/2.0, 0.0,
                                        joint_angs.right_front.ang1, 0.0, 0.0,
                                        this->get_clock());  
    // transform_stamped.header.stamp = this->get_clock()->now();    
    transform_br_->sendTransform(transform_stamped);

    // Leg
    transform_stamped = createTransform("front_right_shoulder_link","front_right_leg_link",
                                        0.0, -smnc_.smc.hip_link_length, 0.0,
                                        0.0, -joint_angs.right_front.ang2, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    // Foot
    transform_stamped = createTransform("front_right_leg_link","front_right_foot_link",
                                        0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                        0.0, -joint_angs.right_front.ang3, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    ////////////////////
    // REAR RIGHT LEG //
    ////////////////////
    // Shoulder
    transform_stamped = createTransform("base_link", "rear_right_shoulder_link",
                                        -smnc_.smc.body_length/2.0, -smnc_.smc.body_width/2.0, 0.0,
                                        joint_angs.right_back.ang1, 0.0, 0.0,
                                        this->get_clock());  
    // transform_stamped.header.stamp = this->get_clock()->now();  
    transform_br_->sendTransform(transform_stamped);

    // Leg
    transform_stamped = createTransform("rear_right_shoulder_link","rear_right_leg_link",
                                        0.0, -smnc_.smc.hip_link_length, 0.0,
                                        0.0, -joint_angs.right_back.ang2, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    // Foot
    transform_stamped = createTransform("rear_right_leg_link","rear_right_foot_link",
                                        0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                        0.0, -joint_angs.right_back.ang3, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    ////////////////////
    // FRONT LEFT LEG //
    ////////////////////
    // Shoulder
    transform_stamped = createTransform("base_link", "front_left_shoulder_link",
                                        smnc_.smc.body_length/2.0, smnc_.smc.body_width/2.0, 0.0,
                                        -joint_angs.left_front.ang1, 0.0, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    // Leg
    transform_stamped = createTransform("front_left_shoulder_link","front_left_leg_link",
                                        0.0, smnc_.smc.hip_link_length, 0.0,
                                        0.0, joint_angs.left_front.ang2, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    // Foot
    transform_stamped = createTransform("front_left_leg_link","front_left_foot_link",
                                        0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                        0.0, joint_angs.left_front.ang3, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    ///////////////////
    // REAR LEFT LEG //
    ///////////////////
    // Shoulder
    transform_stamped = createTransform("base_link", "rear_left_shoulder_link",
                                        -smnc_.smc.body_length/2.0, smnc_.smc.body_width/2.0, 0.0,
                                        -joint_angs.left_back.ang1, 0.0, 0.0,
                                        this->get_clock());  
    // transform_stamped.header.stamp = this->get_clock()->now();    
    transform_br_->sendTransform(transform_stamped);

    // Leg
    transform_stamped = createTransform("rear_left_shoulder_link","rear_left_leg_link",
                                        0.0, smnc_.smc.hip_link_length, 0.0,
                                        0.0, joint_angs.left_back.ang2, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);

    // Foot
    transform_stamped = createTransform("rear_left_leg_link","rear_left_foot_link",
                                        0.0, 0.0, -smnc_.smc.upper_leg_link_length,
                                        0.0, joint_angs.left_back.ang3, 0.0,
                                        this->get_clock());
    // transform_stamped.header.stamp = this->get_clock()->now();
    transform_br_->sendTransform(transform_stamped);
}

///////////////////////////////////////////////////////////////////////
// Odometry methods

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