// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from i2cpwm_controller:msg/ServoConfig.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "i2cpwm_controller/msg/detail/servo_config__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace i2cpwm_controller
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ServoConfig_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) i2cpwm_controller::msg::ServoConfig(_init);
}

void ServoConfig_fini_function(void * message_memory)
{
  auto typed_message = static_cast<i2cpwm_controller::msg::ServoConfig *>(message_memory);
  typed_message->~ServoConfig();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ServoConfig_message_member_array[4] = {
  {
    "servo",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller::msg::ServoConfig, servo),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "center",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller::msg::ServoConfig, center),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "range",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller::msg::ServoConfig, range),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "direction",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller::msg::ServoConfig, direction),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ServoConfig_message_members = {
  "i2cpwm_controller::msg",  // message namespace
  "ServoConfig",  // message name
  4,  // number of fields
  sizeof(i2cpwm_controller::msg::ServoConfig),
  ServoConfig_message_member_array,  // message members
  ServoConfig_init_function,  // function to initialize message memory (memory has to be allocated)
  ServoConfig_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ServoConfig_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ServoConfig_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace i2cpwm_controller


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<i2cpwm_controller::msg::ServoConfig>()
{
  return &::i2cpwm_controller::msg::rosidl_typesupport_introspection_cpp::ServoConfig_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, i2cpwm_controller, msg, ServoConfig)() {
  return &::i2cpwm_controller::msg::rosidl_typesupport_introspection_cpp::ServoConfig_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
