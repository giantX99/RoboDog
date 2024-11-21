// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from i2cpwm_controller:msg/ServoConfigArray.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__BUILDER_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "i2cpwm_controller/msg/detail/servo_config_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace i2cpwm_controller
{

namespace msg
{

namespace builder
{

class Init_ServoConfigArray_servos
{
public:
  Init_ServoConfigArray_servos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::i2cpwm_controller::msg::ServoConfigArray servos(::i2cpwm_controller::msg::ServoConfigArray::_servos_type arg)
  {
    msg_.servos = std::move(arg);
    return std::move(msg_);
  }

private:
  ::i2cpwm_controller::msg::ServoConfigArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::i2cpwm_controller::msg::ServoConfigArray>()
{
  return i2cpwm_controller::msg::builder::Init_ServoConfigArray_servos();
}

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__BUILDER_HPP_