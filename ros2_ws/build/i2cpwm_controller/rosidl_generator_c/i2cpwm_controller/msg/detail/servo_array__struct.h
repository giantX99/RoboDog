// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:msg/ServoArray.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_ARRAY__STRUCT_H_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_ARRAY__STRUCT_H_

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
#include "i2cpwm_controller/msg/detail/servo__struct.h"

/// Struct defined in msg/ServoArray in the package i2cpwm_controller.
/**
  * the ServoArray message is commonly used message in this package to
  * handle multiple assignments of values to servos. the purpose of
  * the value is dependent on the topic or service being called
 */
typedef struct i2cpwm_controller__msg__ServoArray
{
  i2cpwm_controller__msg__Servo__Sequence servos;
} i2cpwm_controller__msg__ServoArray;

// Struct for a sequence of i2cpwm_controller__msg__ServoArray.
typedef struct i2cpwm_controller__msg__ServoArray__Sequence
{
  i2cpwm_controller__msg__ServoArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__msg__ServoArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_ARRAY__STRUCT_H_
