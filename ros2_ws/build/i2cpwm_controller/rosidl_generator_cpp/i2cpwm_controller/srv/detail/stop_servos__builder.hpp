// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:srv/StopServos.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__BUILDER_HPP_
#define I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/srv/detail/stop_servos__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::StopServos_Request>()
{
  return ::i2cpwm_controller::srv::StopServos_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace i2cpwm_controller


namespace i2cpwm_controller
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::StopServos_Response>()
{
  return ::i2cpwm_controller::srv::StopServos_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__BUILDER_HPP_
