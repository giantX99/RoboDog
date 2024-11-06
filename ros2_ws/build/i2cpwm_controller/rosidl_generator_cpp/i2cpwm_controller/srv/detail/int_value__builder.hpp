// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:srv/IntValue.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__INT_VALUE__BUILDER_HPP_
#define I2CPWM_CONTROLLER__SRV__DETAIL__INT_VALUE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/srv/detail/int_value__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace srv
{

namespace builder
{

class Init_IntValue_Request_value
{
public:
  Init_IntValue_Request_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::i2cpwm_controller::srv::IntValue_Request value(::i2cpwm_controller::srv::IntValue_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::srv::IntValue_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::IntValue_Request>()
{
  return i2cpwm_controller::srv::builder::Init_IntValue_Request_value();
}

}  // namespace i2cpwm_controller


namespace i2cpwm_controller
{

namespace srv
{

namespace builder
{

class Init_IntValue_Response_error
{
public:
  Init_IntValue_Response_error()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::i2cpwm_controller::srv::IntValue_Response error(::i2cpwm_controller::srv::IntValue_Response::_error_type arg)
  {
    msg_.error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::srv::IntValue_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::srv::IntValue_Response>()
{
  return i2cpwm_controller::srv::builder::Init_IntValue_Response_error();
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__INT_VALUE__BUILDER_HPP_
