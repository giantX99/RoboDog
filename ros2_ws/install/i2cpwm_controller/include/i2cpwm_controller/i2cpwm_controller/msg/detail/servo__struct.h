// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from i2cpwm_controller:msg/Servo.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__STRUCT_H_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Servo in the package i2cpwm_controller.
/**
  * the Servo message is commonly used message in this package to
  * assign a value to a specific servo. the purpose of the value is
  * dependent on the topic or service being called
 */
typedef struct i2cpwm_controller__msg__Servo
{
  int16_t servo;
  float value;
} i2cpwm_controller__msg__Servo;

// Struct for a sequence of i2cpwm_controller__msg__Servo.
typedef struct i2cpwm_controller__msg__Servo__Sequence
{
  i2cpwm_controller__msg__Servo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} i2cpwm_controller__msg__Servo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO__STRUCT_H_
