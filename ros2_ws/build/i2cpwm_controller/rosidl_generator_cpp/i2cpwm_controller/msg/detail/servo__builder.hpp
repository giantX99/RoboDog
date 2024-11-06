// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:msg/Servo.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__BUILDER_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/msg/detail/servo__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace msg
{

namespace builder
{

class Init_Servo_value
{
public:
  explicit Init_Servo_value(::i2cpwm_controller::msg::Servo & msg)
  : msg_(msg)
  {}
  ::i2cpwm_controller::msg::Servo value(::i2cpwm_controller::msg::Servo::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::msg::Servo msg_;
};

class Init_Servo_servo
{
public:
  Init_Servo_servo()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Servo_value servo(::i2cpwm_controller::msg::Servo::_servo_type arg)
  {
    msg_.servo = std::move(arg);
    return Init_Servo_value(msg_);
  }

private:
  ::i2cpwm_controller::msg::Servo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::msg::Servo>()
{
  return i2cpwm_controller::msg::builder::Init_Servo_servo();
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__BUILDER_HPP_
