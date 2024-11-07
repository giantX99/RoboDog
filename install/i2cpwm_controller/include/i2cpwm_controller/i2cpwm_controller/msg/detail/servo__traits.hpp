// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from i2cpwm_controller:msg/Servo.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__TRAITS_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "i2cpwm_controller/msg/detail/servo__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace i2cpwm_controller
{

namespace msg
{

inline void to_flow_style_yaml(
  const Servo & msg,
  std::ostream & out)
{
  out << "{";
  // member: servo
  {
    out << "servo: ";
    rosidl_generator_traits::value_to_yaml(msg.servo, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: servo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "servo: ";
    rosidl_generator_traits::value_to_yaml(msg.servo, out);
    out << "\n";
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace i2cpwm_controller

namespace rosidl_generator_traits
{

[[deprecated("use i2cpwm_controller::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const i2cpwm_controller::msg::Servo & msg,
  std::ostream & out, size_t indentation = 0)
{
  i2cpwm_controller::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use i2cpwm_controller::msg::to_yaml() instead")]]
inline std::string to_yaml(const i2cpwm_controller::msg::Servo & msg)
{
  return i2cpwm_controller::msg::to_yaml(msg);
}

template<>
inline const char * data_type<i2cpwm_controller::msg::Servo>()
{
  return "i2cpwm_controller::msg::Servo";
}

template<>
inline const char * name<i2cpwm_controller::msg::Servo>()
{
  return "i2cpwm_controller/msg/Servo";
}

template<>
struct has_fixed_size<i2cpwm_controller::msg::Servo>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<i2cpwm_controller::msg::Servo>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<i2cpwm_controller::msg::Servo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__TRAITS_HPP_
