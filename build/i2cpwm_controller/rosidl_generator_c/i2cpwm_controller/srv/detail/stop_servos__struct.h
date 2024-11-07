// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:srv/StopServos.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__STRUCT_H_
#define I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/StopServos in the package i2cpwm_controller.
typedef struct i2cpwm_controller__srv__StopServos_Request
{
  uint8_t structure_needs_at_least_one_member;
} i2cpwm_controller__srv__StopServos_Request;

// Struct for a sequence of i2cpwm_controller__srv__StopServos_Request.
typedef struct i2cpwm_controller__srv__StopServos_Request__Sequence
{
  i2cpwm_controller__srv__StopServos_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__srv__StopServos_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/StopServos in the package i2cpwm_controller.
typedef struct i2cpwm_controller__srv__StopServos_Response
{
  uint8_t structure_needs_at_least_one_member;
} i2cpwm_controller__srv__StopServos_Response;

// Struct for a sequence of i2cpwm_controller__srv__StopServos_Response.
typedef struct i2cpwm_controller__srv__StopServos_Response__Sequence
{
  i2cpwm_controller__srv__StopServos_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__srv__StopServos_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__STOP_SERVOS__STRUCT_H_
