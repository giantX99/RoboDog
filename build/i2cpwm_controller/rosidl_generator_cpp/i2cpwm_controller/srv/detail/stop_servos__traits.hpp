// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from i2cpwm_controller:srv/StopServos.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__TRAITS_HPP_
#define I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "i2cpwm_controller/srv/detail/stop_servos__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace i2cpwm_controller
{

namespace srv
{

inline void to_flow_style_yaml(
  const StopServos_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StopServos_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StopServos_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace i2cpwm_controller

namespace rosidl_generator_traits
{

[[deprecated("use i2cpwm_controller::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const i2cpwm_controller::srv::StopServos_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  i2cpwm_controller::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use i2cpwm_controller::srv::to_yaml() instead")]]
inline std::string to_yaml(const i2cpwm_controller::srv::StopServos_Request & msg)
{
  return i2cpwm_controller::srv::to_yaml(msg);
}

template<>
inline const char * data_type<i2cpwm_controller::srv::StopServos_Request>()
{
  return "i2cpwm_controller::srv::StopServos_Request";
}

template<>
inline const char * name<i2cpwm_controller::srv::StopServos_Request>()
{
  return "i2cpwm_controller/srv/StopServos_Request";
}

template<>
struct has_fixed_size<i2cpwm_controller::srv::StopServos_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<i2cpwm_controller::srv::StopServos_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<i2cpwm_controller::srv::StopServos_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace i2cpwm_controller
{

namespace srv
{

inline void to_flow_style_yaml(
  const StopServos_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StopServos_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StopServos_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace i2cpwm_controller

namespace rosidl_generator_traits
{

[[deprecated("use i2cpwm_controller::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const i2cpwm_controller::srv::StopServos_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  i2cpwm_controller::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use i2cpwm_controller::srv::to_yaml() instead")]]
inline std::string to_yaml(const i2cpwm_controller::srv::StopServos_Response & msg)
{
  return i2cpwm_controller::srv::to_yaml(msg);
}

template<>
inline const char * data_type<i2cpwm_controller::srv::StopServos_Response>()
{
  return "i2cpwm_controller::srv::StopServos_Response";
}

template<>
inline const char * name<i2cpwm_controller::srv::StopServos_Response>()
{
  return "i2cpwm_controller/srv/StopServos_Response";
}

template<>
struct has_fixed_size<i2cpwm_controller::srv::StopServos_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<i2cpwm_controller::srv::StopServos_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<i2cpwm_controller::srv::StopServos_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<i2cpwm_controller::srv::StopServos>()
{
  return "i2cpwm_controller::srv::StopServos";
}

template<>
inline const char * name<i2cpwm_controller::srv::StopServos>()
{
  return "i2cpwm_controller/srv/StopServos";
}

template<>
struct has_fixed_size<i2cpwm_controller::srv::StopServos>
  : std::integral_constant<
    bool,
    has_fixed_size<i2cpwm_controller::srv::StopServos_Request>::value &&
    has_fixed_size<i2cpwm_controller::srv::StopServos_Response>::value
  >
{
};

template<>
struct has_bounded_size<i2cpwm_controller::srv::StopServos>
  : std::integral_constant<
    bool,
    has_bounded_size<i2cpwm_controller::srv::StopServos_Request>::value &&
    has_bounded_size<i2cpwm_controller::srv::StopServos_Response>::value
  >
{
};

template<>
struct is_service<i2cpwm_controller::srv::StopServos>
  : std::true_type
{
};

template<>
struct is_service_request<i2cpwm_controller::srv::StopServos_Request>
  : std::true_type
{
};

template<>
struct is_service_response<i2cpwm_controller::srv::StopServos_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__TRAITS_HPP_
