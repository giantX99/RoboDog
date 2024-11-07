// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:srv/ServosConfig.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__BUILDER_HPP_
#define I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/srv/detail/servos_config__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace srv
{

namespace builder
{

class Init_ServosConfig_Request_servos
{
public:
  Init_ServosConfig_Request_servos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::i2cpwm_controller::srv::ServosConfig_Request servos(::i2cpwm_controller::srv::ServosConfig_Request::_servos_type arg)
  {
    msg_.servos = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::srv::ServosConfig_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::ServosConfig_Request>()
{
  return i2cpwm_controller::srv::builder::Init_ServosConfig_Request_servos();
}

}  // namespace i2cpwm_controller


namespace i2cpwm_controller
{

namespace srv
{

namespace builder
{

class Init_ServosConfig_Response_error
{
public:
  Init_ServosConfig_Response_error()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::i2cpwm_controller::srv::ServosConfig_Response error(::i2cpwm_controller::srv::ServosConfig_Response::_error_type arg)
  {
    msg_.error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::srv::ServosConfig_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::ServosConfig_Response>()
{
  return i2cpwm_controller::srv::builder::Init_ServosConfig_Response_error();
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__BUILDER_HPP_
