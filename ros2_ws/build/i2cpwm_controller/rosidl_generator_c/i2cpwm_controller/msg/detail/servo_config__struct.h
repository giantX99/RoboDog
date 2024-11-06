// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:msg/ServoConfig.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG__STRUCT_H_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ServoConfig in the package i2cpwm_controller.
/**
  * the ServoConfig message is used to assign specific configuration
  * data to a servo. the data is needed to normalize servos to
  * common values to isolate variations from the rest of the user's
  * robot motion code. 
 */
typedef struct i2cpwm_controller__msg__ServoConfig
{
  int16_t servo;
  int16_t center;
  int16_t range;
  int16_t direction;
} i2cpwm_controller__msg__ServoConfig;

// Struct for a sequence of i2cpwm_controller__msg__ServoConfig.
typedef struct i2cpwm_controller__msg__ServoConfig__Sequence
{
  i2cpwm_controller__msg__ServoConfig * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__msg__ServoConfig__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG__STRUCT_H_
