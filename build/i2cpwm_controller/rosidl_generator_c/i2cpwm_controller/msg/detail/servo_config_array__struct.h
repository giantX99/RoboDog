// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:msg/ServoConfigArray.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_H_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_H_

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

/// Struct defined in msg/ServoConfigArray in the package i2cpwm_controller.
/**
  * the ServoConfigArray message is used to handle multiple assignments
  * of config data to servos. the data is needed to normalize servos to
  * common values to isolate variations from the rest of the user's
  * robot motion code. 
 */
typedef struct i2cpwm_controller__msg__ServoConfigArray
{
  i2cpwm_controller__msg__ServoConfig__Sequence servos;
} i2cpwm_controller__msg__ServoConfigArray;

// Struct for a sequence of i2cpwm_controller__msg__ServoConfigArray.
typedef struct i2cpwm_controller__msg__ServoConfigArray__Sequence
{
  i2cpwm_controller__msg__ServoConfigArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__msg__ServoConfigArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_H_
