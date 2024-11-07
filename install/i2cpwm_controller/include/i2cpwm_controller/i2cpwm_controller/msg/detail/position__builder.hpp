// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__BUILDER_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/msg/detail/position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace msg
{

namespace builder
{

class Init_Position_position
{
public:
  explicit Init_Position_position(::i2cpwm_controller::msg::Position & msg)
  : msg_(msg)
  {}
  ::i2cpwm_controller::msg::Position position(::i2cpwm_controller::msg::Position::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::msg::Position msg_;
};

class Init_Position_servo
{
public:
  Init_Position_servo()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Position_position servo(::i2cpwm_controller::msg::Position::_servo_type arg)
  {
    msg_.servo = std::move(arg);
    return Init_Position_position(msg_);
  }

private:
  ::i2cpwm_controller::msg::Position msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::msg::Position>()
{
  return i2cpwm_controller::msg::builder::Init_Position_servo();
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__BUILDER_HPP_
