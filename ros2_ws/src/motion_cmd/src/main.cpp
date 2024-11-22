// Node file to create object and initialising the ROS node
#include "motion_cmd.h" 
#include "rclcpp/rclcpp.hpp"
#include "builtin_interfaces/msg/time.hpp"
#include "rclcpp/clock.hpp" 
#include <iostream>


int main(int argc, char** argv) {
    /* initialising the ROS node creating node handle
    for regestring it to the master and then private node handle to
    handle the parameters */
    rclcpp::init(argc, argv);
    auto nh = rclcpp::Node::make_shared("motion_cmd");

    SpotMicroMotionCmd node(nh); // Creating the object

    rclcpp::Rate rate(1.0/node.getNodeConfig().dt); // Defing the looping rate

    // Only proceed if servo configuration publishing succeeds
    if (node.publishServoConfiguration()) {

        bool debug_mode = node.getNodeConfig().debug_mode;  
        rclcpp::Time begin;
        rclcpp::Clock clock;
        /* Looking for any interupt else it will continue looping */
        // Main loop runs indefinitely unless there is an interupt call
        while (rclcpp::ok())
        {   
            if (debug_mode) {
                begin = clock.now();
            }

            node.runOnce();
            rclcpp::spin_some(node.nh_);
            rate.sleep();

            if (debug_mode) {
                auto elapsed = clock.now() - begin;
                std::cout << "Elapsed time: " 
                          << elapsed.seconds() << " seconds" 
                          << std::endl;
            }
        }

    }
    return 0;
}
