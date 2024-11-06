// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from i2cpwm_controller:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__TRAITS_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "i2cpwm_controller/msg/detail/position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace i2cpwm_controller
{

namespace msg
{

inline void to_flow_style_yaml(
  const Position & msg,
  std::ostream & out)
{
  out << "{";
  // member: servo
  {
    out << "servo: ";
    rosidl_generator_traits::value_to_yaml(msg.servo, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Position & msg,
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

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Position & msg, bool use_flow_style = false)
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
  const i2cpwm_controller::msg::Position & msg,
  std::ostream & out, size_t indentation = 0)
{
  i2cpwm_controller::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use i2cpwm_controller::msg::to_yaml() instead")]]
inline std::string to_yaml(const i2cpwm_controller::msg::Position & msg)
{
  return i2cpwm_controller::msg::to_yaml(msg);
}

template<>
inline const char * data_type<i2cpwm_controller::msg::Position>()
{
  return "i2cpwm_controller::msg::Position";
}

template<>
inline const char * name<i2cpwm_controller::msg::Position>()
{
  return "i2cpwm_controller/msg/Position";
}

template<>
struct has_fixed_size<i2cpwm_controller::msg::Position>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<i2cpwm_controller::msg::Position>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<i2cpwm_controller::msg::Position>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__POSITION__TRAITS_HPP_
