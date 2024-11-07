// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from i2cpwm_controller:msg/PositionArray.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__POSITION_ARRAY__TRAITS_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__POSITION_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "i2cpwm_controller/msg/detail/position_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'servos'
#include "i2cpwm_controller/msg/detail/position__traits.hpp"

namespace i2cpwm_controller
{

namespace msg
{

inline void to_flow_style_yaml(
  const PositionArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: servos
  {
    if (msg.servos.size() == 0) {
      out << "servos: []";
    } else {
      out << "servos: [";
      size_t pending_items = msg.servos.size();
      for (auto item : msg.servos) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PositionArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: servos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.servos.size() == 0) {
      out << "servos: []\n";
    } else {
      out << "servos:\n";
      for (auto item : msg.servos) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PositionArray & msg, bool use_flow_style = false)
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
  const i2cpwm_controller::msg::PositionArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  i2cpwm_controller::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use i2cpwm_controller::msg::to_yaml() instead")]]
inline std::string to_yaml(const i2cpwm_controller::msg::PositionArray & msg)
{
  return i2cpwm_controller::msg::to_yaml(msg);
}

template<>
inline const char * data_type<i2cpwm_controller::msg::PositionArray>()
{
  return "i2cpwm_controller::msg::PositionArray";
}

template<>
inline const char * name<i2cpwm_controller::msg::PositionArray>()
{
  return "i2cpwm_controller/msg/PositionArray";
}

template<>
struct has_fixed_size<i2cpwm_controller::msg::PositionArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<i2cpwm_controller::msg::PositionArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<i2cpwm_controller::msg::PositionArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__POSITION_ARRAY__TRAITS_HPP_
