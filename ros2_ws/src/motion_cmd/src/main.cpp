#include "motion_cmd.h"
#include <iostream>
#include "rclcpp/rclcpp.hpp"


int main(int argc, char **argv) {
    // Initialize the ROS 2 node
    rclcpp::init(argc, argv);

    // Create an instance of SpotMicroMotionCmd using NodeOptions
    auto node = std::make_shared<SpotMicroMotionCmd>(rclcpp::NodeOptions());

    // Create a loop rate based on the config's `dt` value
    rclcpp::Rate rate(1.0 / node->getNodeConfig().dt);

    // Only proceed if the servo configuration publishing succeeds
    if (node->publishServoConfiguration()) {
        bool debug_mode = node->getNodeConfig().debug_mode;
        rclcpp::Time begin;

        // Main loop runs indefinitely unless there is an interrupt
        while (rclcpp::ok()) {
            if (debug_mode) {
                begin = node->get_clock()->now();
            }

            // Run one iteration of the control loop
            node->runOnce();

            // Handle any callbacks and spin
            rclcpp::spin_some(node);

            // Sleep for the remaining time to maintain the loop rate
            rate.sleep();

            if (debug_mode) {
                RCLCPP_INFO(node->get_logger(), "Loop execution time: %f", 
                            (node->get_clock()->now() - begin).seconds());
            }
        }
    }

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}
