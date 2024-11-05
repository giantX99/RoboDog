#pragma once

#ifndef MOTION_CMD
#define MOTION_CMD

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "i2cpwm_controller/msg/servo.hpp"
#include "i2cpwm_controller/msg/servo_array.hpp"

#include "command.h"
#include "spot_micro_kinematics/spot_micro_kinematics.h"
#include "state.h"

// Define a configuration struct
struct SpotMicroNodeConfig {
    smk::SpotMicroConfig smc;
    float default_stand_height;
    float stand_front_x_offset;
    float stand_back_x_offset;
    float lie_down_height;
    float lie_down_feet_x_offset;
    int num_servos;
    float servo_max_angle_deg;
    std::map<std::string, std::map<std::string, float>> servo_config;
    float dt;
    float transit_tau;
    float transit_rl;
    float transit_angle_rl;
    bool debug_mode;
    bool run_standalone;
    bool plot_mode;
    float max_fwd_velocity;
    float max_side_velocity;
    float max_yaw_rate;
    float z_clearance;
    float alpha;
    float beta;
    int num_phases;
    std::vector<int> rb_contact_phases;
    std::vector<int> rf_contact_phases;
    std::vector<int> lf_contact_phases;
    std::vector<int> lb_contact_phases;
    float overlap_time;
    float swing_time;
    int overlap_ticks;
    int swing_ticks;
    int stance_ticks;
    std::vector<int> phase_ticks;
    int phase_length;
    float foot_height_time_constant;
    std::vector<int> body_shift_phases;
    float fwd_body_balance_shift;
    float side_body_balance_shift;
    float back_body_balance_shift;
    bool publish_odom;
    float lidar_x_pos;
    float lidar_y_pos;
    float lidar_z_pos;
    float lidar_yaw_angle;
};



// Defining the class
class SpotMicroMotionCmd : public rclcpp::Node {
public:
    // Constructor
    SpotMicroMotionCmd(const rclcpp::NodeOptions &options); 

    // Destructor
    ~SpotMicroMotionCmd(); 

    // Main loop runner, called periodically
    void runOnce();

    // Publish a servo configuration message
    bool publishServoConfiguration();

    // Set servo proportional message data
    void setServoCommandMessageData();

    // Publishes a servo proportional command message
    void publishServoProportionalCommand(); 

    // Publishes a servo absolute command message with all servos set to a command
    // value of 0. This effectively disables the servos (stops them from holding
    // position, should just freewheel)
    void publishZeroServoAbsoluteCommand();

    // Returns the loaded parameters
    SpotMicroNodeConfig getNodeConfig();

    // Returns leg positions representing a neutral stance
    smk::LegsFootPos getNeutralStance();

    // Returns leg positions representing a lying down stance
    smk::LegsFootPos getLieDownStance();

    // Manually override and command idle mode, used for shutdown
    void commandIdle();

    // Returns current state name
    std::string getCurrentStateName();

private:
    // Declare SpotMicroState a friend to access and modify private members
    friend class SpotMicroState;

    // Pointer to state object
    std::unique_ptr<SpotMicroState> state_;

    // Command object for encapsulating external commands
    Command cmd_; // Command object, encapsulate commands

    // Spot Micro Kinematics object
    // smk stands for spotmicro kinematics from spot_micro_kinematics/spot_micro_kinematics.h
    smk::SpotMicroKinematics sm_; 

    // Spot Micro Node Config object
    SpotMicroNodeConfig smnc_;

    // Holds the body state to be commanded: feet position, body position and
    // angles
    smk::BodyState body_state_cmd_; 

    // Odometry of the robot position and orientation based on integrated rate
    // commands. Only x and y position, and yaw angle, will be integrated from
    // rate commands
    smk::BodyState robot_odometry_;

    // Map to hold servo command values in radians
    std::map<std::string, float> servo_cmds_rad_ = {
        {"RF_3", 0.0f}, {"RF_2", 0.0f}, {"RF_1", 0.0f},
        {"RB_3", 0.0f}, {"RB_2", 0.0f}, {"RB_1", 0.0f},
        {"LB_3", 0.0f}, {"LB_2", 0.0f}, {"LB_1", 0.0f},
        {"LF_3", 0.0f}, {"LF_2", 0.0f}, {"LF_1", 0.0f}
    };

    // Reads parameters from parameter server to initialize config
    void readInConfigParameters();

    // Servo array message for servo proportional command
    i2cpwm_controller::msg::ServoArray servo_array_;

    // Servo array message for servo absolute command
    i2cpwm_controller::msg::ServoArray servo_array_absolute_;

    // ROS publishers and subscribers
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr stand_sub_; 
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr idle_sub_; 
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr walk_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr vel_cmd_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr body_angle_cmd_sub_;
    
    rclcpp::Publisher<i2cpwm_controller::msg::ServoArray>::SharedPtr servos_absolute_pub_;
    rclcpp::Publisher<i2cpwm_controller::msg::ServoArray>::SharedPtr servos_proportional_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr body_state_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr lcd_vel_cmd_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr lcd_angle_cmd_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr lcd_state_pub_;
    rclcpp::Client<i2cpwm_controller::srv::ServosConfig>::SharedPtr servos_config_client_;

    
    tf2_ros::TransformBroadcaster transform_br_;
    tf2_ros::StaticTransformBroadcaster static_transform_br_;

    // Message for encapsulating robot body state
    std_msgs::msg::Float32MultiArray body_state_msg_;

    // Messages for LCD monitoring
    std_msgs::msg::String lcd_state_string_msg_;
    geometry_msgs::msg::Twist lcd_vel_cmd_msg_;
    geometry_msgs::msg::Vector3 lcd_angle_cmd_msg_;

    // Callback methods
    void standCommandCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void idleCommandCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void walkCommandCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void angleCommandCallback(const geometry_msgs::msg::Vector3::SharedPtr msg);
    // Callback method for velocity command
    // Currently, the only supported commands from this message are 
    // x and y axis linear velocity, and z axis angular rate
    void velCommandCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

    // Resets all events if they were true
    void resetEventCommands();

    // State Machine Methods
    void handleInputCommands();
    void changeState(std::unique_ptr<SpotMicroState> sms);
    void publishBodyState();
    void publishLcdMonitorData();
    void publishStaticTransforms();
    void publishDynamicTransforms();
    void integrateOdometry();
    
    // Calculates the robot odometry coordinate frame
    Eigen::Affine3d getOdometryTransform();
};

