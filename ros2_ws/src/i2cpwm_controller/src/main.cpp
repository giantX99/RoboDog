#include "rclcpp/rclcpp.hpp"
#include "i2cpwm_controller.h"

int main(int argc, char **argv)
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    try {
        // Create a node instance of I2cPwmController
        auto node = std::make_shared<I2cPwmController>(rclcpp::NodeOptions());

        // Start the node and process callbacks (similar to ros::spin in ROS 1)
        rclcpp::spin(node);
    } catch (const std::exception &e) {
        // Catch any exception thrown during initialization or spin
        RCLCPP_FATAL(rclcpp::get_logger("rclcpp"), "Exception during initialization: %s", e.what());
    } catch (...) {
        // Catch any other unknown errors
        RCLCPP_FATAL(rclcpp::get_logger("rclcpp"), "Unknown error occurred during node initialization.");
    }

    // Ensure proper shutdown even if an exception occurs
    rclcpp::shutdown();

    return 0;
}
