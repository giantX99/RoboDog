// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:srv/ServosConfig.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__STRUCT_H_
#define I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'servos'
#include "i2cpwm_controller/msg/detail/servo_config__struct.h"

/// Struct defined in srv/ServosConfig in the package i2cpwm_controller.
typedef struct i2cpwm_controller__srv__ServosConfig_Request
{
  i2cpwm_controller__msg__ServoConfig__Sequence servos;
} i2cpwm_controller__srv__ServosConfig_Request;

// Struct for a sequence of i2cpwm_controller__srv__ServosConfig_Request.
typedef struct i2cpwm_controller__srv__ServosConfig_Request__Sequence
{
  i2cpwm_controller__srv__ServosConfig_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__srv__ServosConfig_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/ServosConfig in the package i2cpwm_controller.
typedef struct i2cpwm_controller__srv__ServosConfig_Response
{
  int16_t error;
} i2cpwm_controller__srv__ServosConfig_Response;

// Struct for a sequence of i2cpwm_controller__srv__ServosConfig_Response.
typedef struct i2cpwm_controller__srv__ServosConfig_Response__Sequence
{
  i2cpwm_controller__srv__ServosConfig_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__srv__ServosConfig_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__SRV__DETAIL__SERVOS_CONFIG__STRUCT_H_
