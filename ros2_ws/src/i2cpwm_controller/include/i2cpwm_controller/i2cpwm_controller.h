#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>

extern "C" {
    #include <i2c/smbus.h>
}

// ROS 2 headers
#include "rclcpp/rclcpp.h"

// ROS 2 messages and services
#include "std_srvs/srv/empty.h"
#include "geometry_msgs/msg/twist.h"
#include "i2cpwm_controller/msg/servo.h"
#include "i2cpwm_controller/msg/servo_array.h"
#include "i2cpwm_controller/msg/servo_config.h"
#include "i2cpwm_controller/msg/servo_config_array.h"
#include "i2cpwm_controller/srv/servos_config.h"
#include "i2cpwm_controller/srv/drive_mode.h"
#include "i2cpwm_controller/msg/position.h"
#include "i2cpwm_controller/msg/position_array.h"
#include "i2cpwm_controller/srv/int_value.h"


// Define structs
typedef struct _servo_config {
    int center;
    int range;
    int direction;
    int mode_pos;
} servo_config;

typedef struct _drive_mode {
	int mode;
	float rpm;
	float radius;
	float track;
	float scale;
} drive_mode;

// Global variables
#define MAX_BOARDS 62
#define MAX_SERVOS (16 * MAX_BOARDS)


class I2cPwmController : public rclcpp::Node {
public:

    // Constructor
    I2cPwmController(const rclcpp::NodeOptions &options);
    
    // Destructor
    ~I2cPwmController();

    // Public methods
    int get_io_handle() const { return _controller_io_handle; }

private:

    // Global Variables:
    servo_config _servo_configs[MAX_SERVOS]; // Support up to 62 boards with 16 servos each
    drive_mode _active_drive;                // Active drive mode for converting Twist geometry
    int _last_servo = -1;

    int _pwm_boards[MAX_BOARDS];  // Support up to 62 boards
    int _active_board = 0;        // Active board index for I2C communication
    int _controller_io_handle;    // File handle for I2C
    int _controller_io_device;    // I2C device identifier

    int _pwm_frequency = 50;      // PWM frequency, default is 50Hz for RC servos


    // Private utility methods:
    int _smoothing (float speed);
    float _convert_mps_to_proportional (float speed);

    void _set_pwm_frequency (int freq);
    void _set_pwm_interval_all (int start, int end);
    void _set_active_board (int board);
    void _set_pwm_interval (int servo, int start, int end);
    void _set_pwm_interval_proportional (int servo, float value);
    
    void _config_servo (int servo, int center, int range, int direction);
    int _config_servo_position (int servo, int position);
    int _config_drive_mode (std::string mode, float rpm, float radius, float track, float scale);


    // ROS 2 Subscribers
    rclcpp::Subscription<i2cpwm_controller::msg::ServoArray>::SharedPtr servos_absolute_sub_;
    rclcpp::Subscription<i2cpwm_controller::msg::ServoArray>::SharedPtr servos_proportional_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr servos_drive_sub_;

    // ROS 2 Services
    rclcpp::Service<i2cpwm_controller::srv::IntValue>::SharedPtr set_pwm_frequency_srv_;
    rclcpp::Service<i2cpwm_controller::srv::ServosConfig>::SharedPtr config_servos_srv_;
    rclcpp::Service<i2cpwm_controller::srv::DriveMode>::SharedPtr config_drive_mode_srv_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr stop_servos_srv_;
    
    //Subscription Callbacks
    void servos_absolute(const i2cpwm_controller::msg::ServoArray::SharedPtr msg);
    void servos_proportional(const i2cpwm_controller::msg::ServoArray::SharedPtr msg);
    void servos_drive(const geometry_msgs::msg::Twist::SharedPtr msg);

    // Service Callbacks
    bool set_pwm_frequency(const std::shared_ptr<i2cpwm_controller::srv::IntValue::Request> req,
                                    std::shared_ptr<i2cpwm_controller::srv::IntValue::Response> res);
    bool config_servos(const std::shared_ptr<i2cpwm_controller::srv::ServosConfig::Request> req,
                                std::shared_ptr<i2cpwm_controller::srv::ServosConfig::Response> res);
    bool config_drive_mode(const std::shared_ptr<i2cpwm_controller::srv::DriveMode::Request> req,
                                    std::shared_ptr<i2cpwm_controller::srv::DriveMode::Response> res);
    bool stop_servos(const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                              std::shared_ptr<std_srvs::srv::Empty::Response> res);

    // Helper Methods for ROS Parameters and Configuration
    void load_configuration_from_parameters();

}

