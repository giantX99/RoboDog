#pragma once // designed to include the current source file only once in a single compilation.

#include <eigen3/Eigen/Geometry>
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_eigen/tf2_eigen.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "rclcpp/rclcpp.hpp"

// Utility functions for spot micro motion command node

// Convert a Eigen Matrix4f to an Affine3d
Eigen::Affine3d matrix4fToAffine3d(const Eigen::Matrix4f& in);

// Create a ROS tf2 TransformStamped from a Eigen Affine3d, 
// parent frame id and child frame id. Stamped with current time, 
// so should be broadcast ASAP
geometry_msgs::msg::TransformStamped eigAndFramesToTrans(
    const Eigen::Affine3d& transform, 
    std::string parent_frame_id, std::string child_frame_id,
    rclcpp::Clock::SharedPtr clock);

// Create a transform from a translation, rotation, and parent and 
// child frame IDs. Will stamp the transform with ROS 2 time.
geometry_msgs::msg::TransformStamped createTransform(
    std::string parent_frame_id, std::string child_frame_id,
    double x, double y, double z, 
    double roll, double pitch, double yaw,
    rclcpp::Clock::SharedPtr clock);
