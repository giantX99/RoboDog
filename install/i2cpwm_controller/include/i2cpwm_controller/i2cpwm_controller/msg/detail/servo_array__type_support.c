// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from i2cpwm_controller:msg/ServoArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "i2cpwm_controller/msg/detail/servo_array__rosidl_typesupport_introspection_c.h"
#include "i2cpwm_controller/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "i2cpwm_controller/msg/detail/servo_array__functions.h"
#include "i2cpwm_controller/msg/detail/servo_array__struct.h"


// Include directives for member types
// Member `servos`
#include "i2cpwm_controller/msg/servo.h"
// Member `servos`
#include "i2cpwm_controller/msg/detail/servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  i2cpwm_controller__msg__ServoArray__init(message_memory);
}

void i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_fini_function(void * message_memory)
{
  i2cpwm_controller__msg__ServoArray__fini(message_memory);
}

size_t i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__size_function__ServoArray__servos(
  const void * untyped_member)
{
  const i2cpwm_controller__msg__Servo__Sequence * member =
    (const i2cpwm_controller__msg__Servo__Sequence *)(untyped_member);
  return member->size;
}

const void * i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_const_function__ServoArray__servos(
  const void * untyped_member, size_t index)
{
  const i2cpwm_controller__msg__Servo__Sequence * member =
    (const i2cpwm_controller__msg__Servo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_function__ServoArray__servos(
  void * untyped_member, size_t index)
{
  i2cpwm_controller__msg__Servo__Sequence * member =
    (i2cpwm_controller__msg__Servo__Sequence *)(untyped_member);
  return &member->data[index];
}

void i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__fetch_function__ServoArray__servos(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const i2cpwm_controller__msg__Servo * item =
    ((const i2cpwm_controller__msg__Servo *)
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_const_function__ServoArray__servos(untyped_member, index));
  i2cpwm_controller__msg__Servo * value =
    (i2cpwm_controller__msg__Servo *)(untyped_value);
  *value = *item;
}

void i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__assign_function__ServoArray__servos(
  void * untyped_member, size_t index, const void * untyped_value)
{
  i2cpwm_controller__msg__Servo * item =
    ((i2cpwm_controller__msg__Servo *)
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_function__ServoArray__servos(untyped_member, index));
  const i2cpwm_controller__msg__Servo * value =
    (const i2cpwm_controller__msg__Servo *)(untyped_value);
  *item = *value;
}

bool i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__resize_function__ServoArray__servos(
  void * untyped_member, size_t size)
{
  i2cpwm_controller__msg__Servo__Sequence * member =
    (i2cpwm_controller__msg__Servo__Sequence *)(untyped_member);
  i2cpwm_controller__msg__Servo__Sequence__fini(member);
  return i2cpwm_controller__msg__Servo__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_member_array[1] = {
  {
    "servos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller__msg__ServoArray, servos),  // bytes offset in struct
    NULL,  // default value
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__size_function__ServoArray__servos,  // size() function pointer
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_const_function__ServoArray__servos,  // get_const(index) function pointer
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__get_function__ServoArray__servos,  // get(index) function pointer
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__fetch_function__ServoArray__servos,  // fetch(index, &value) function pointer
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__assign_function__ServoArray__servos,  // assign(index, value) function pointer
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__resize_function__ServoArray__servos  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_members = {
  "i2cpwm_controller__msg",  // message namespace
  "ServoArray",  // message name
  1,  // number of fields
  sizeof(i2cpwm_controller__msg__ServoArray),
  i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_member_array,  // message members
  i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_init_function,  // function to initialize message memory (memory has to be allocated)
  i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_type_support_handle = {
  0,
  &i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_i2cpwm_controller
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, msg, ServoArray)() {
  i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, msg, Servo)();
  if (!i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_type_support_handle.typesupport_identifier) {
    i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &i2cpwm_controller__msg__ServoArray__rosidl_typesupport_introspection_c__ServoArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
