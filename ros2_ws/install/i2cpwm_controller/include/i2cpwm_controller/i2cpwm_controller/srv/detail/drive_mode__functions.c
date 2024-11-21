// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from i2cpwm_controller:srv/DriveMode.idl
// generated code does not contain a copyright notice
#include "i2cpwm_controller/srv/detail/drive_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `mode`
#include "rosidl_runtime_c/string_functions.h"
// Member `servos`
#include "i2cpwm_controller/msg/detail/position__functions.h"

bool
i2cpwm_controller__srv__DriveMode_Request__init(i2cpwm_controller__srv__DriveMode_Request * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__init(&msg->mode)) {
    i2cpwm_controller__srv__DriveMode_Request__fini(msg);
    return false;
  }
  // rpm
  // radius
  // track
  // scale
  // servos
  if (!i2cpwm_controller__msg__Position__Sequence__init(&msg->servos, 0)) {
    i2cpwm_controller__srv__DriveMode_Request__fini(msg);
    return false;
  }
  return true;
}

void
i2cpwm_controller__srv__DriveMode_Request__fini(i2cpwm_controller__srv__DriveMode_Request * msg)
{
  if (!msg) {
    return;
  }
  // mode
  rosidl_runtime_c__String__fini(&msg->mode);
  // rpm
  // radius
  // track
  // scale
  // servos
  i2cpwm_controller__msg__Position__Sequence__fini(&msg->servos);
}

bool
i2cpwm_controller__srv__DriveMode_Request__are_equal(const i2cpwm_controller__srv__DriveMode_Request * lhs, const i2cpwm_controller__srv__DriveMode_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mode), &(rhs->mode)))
  {
    return false;
  }
  // rpm
  if (lhs->rpm != rhs->rpm) {
    return false;
  }
  // radius
  if (lhs->radius != rhs->radius) {
    return false;
  }
  // track
  if (lhs->track != rhs->track) {
    return false;
  }
  // scale
  if (lhs->scale != rhs->scale) {
    return false;
  }
  // servos
  if (!i2cpwm_controller__msg__Position__Sequence__are_equal(
      &(lhs->servos), &(rhs->servos)))
  {
    return false;
  }
  return true;
}

bool
i2cpwm_controller__srv__DriveMode_Request__copy(
  const i2cpwm_controller__srv__DriveMode_Request * input,
  i2cpwm_controller__srv__DriveMode_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__copy(
      &(input->mode), &(output->mode)))
  {
    return false;
  }
  // rpm
  output->rpm = input->rpm;
  // radius
  output->radius = input->radius;
  // track
  output->track = input->track;
  // scale
  output->scale = input->scale;
  // servos
  if (!i2cpwm_controller__msg__Position__Sequence__copy(
      &(input->servos), &(output->servos)))
  {
    return false;
  }
  return true;
}

i2cpwm_controller__srv__DriveMode_Request *
i2cpwm_controller__srv__DriveMode_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Request * msg = (i2cpwm_controller__srv__DriveMode_Request *)allocator.allocate(sizeof(i2cpwm_controller__srv__DriveMode_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(i2cpwm_controller__srv__DriveMode_Request));
  bool success = i2cpwm_controller__srv__DriveMode_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
i2cpwm_controller__srv__DriveMode_Request__destroy(i2cpwm_controller__srv__DriveMode_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    i2cpwm_controller__srv__DriveMode_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
i2cpwm_controller__srv__DriveMode_Request__Sequence__init(i2cpwm_controller__srv__DriveMode_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Request * data = NULL;

  if (size) {
    data = (i2cpwm_controller__srv__DriveMode_Request *)allocator.zero_allocate(size, sizeof(i2cpwm_controller__srv__DriveMode_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = i2cpwm_controller__srv__DriveMode_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        i2cpwm_controller__srv__DriveMode_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
i2cpwm_controller__srv__DriveMode_Request__Sequence__fini(i2cpwm_controller__srv__DriveMode_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      i2cpwm_controller__srv__DriveMode_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

i2cpwm_controller__srv__DriveMode_Request__Sequence *
i2cpwm_controller__srv__DriveMode_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Request__Sequence * array = (i2cpwm_controller__srv__DriveMode_Request__Sequence *)allocator.allocate(sizeof(i2cpwm_controller__srv__DriveMode_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = i2cpwm_controller__srv__DriveMode_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
i2cpwm_controller__srv__DriveMode_Request__Sequence__destroy(i2cpwm_controller__srv__DriveMode_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    i2cpwm_controller__srv__DriveMode_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
i2cpwm_controller__srv__DriveMode_Request__Sequence__are_equal(const i2cpwm_controller__srv__DriveMode_Request__Sequence * lhs, const i2cpwm_controller__srv__DriveMode_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!i2cpwm_controller__srv__DriveMode_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
i2cpwm_controller__srv__DriveMode_Request__Sequence__copy(
  const i2cpwm_controller__srv__DriveMode_Request__Sequence * input,
  i2cpwm_controller__srv__DriveMode_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(i2cpwm_controller__srv__DriveMode_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    i2cpwm_controller__srv__DriveMode_Request * data =
      (i2cpwm_controller__srv__DriveMode_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!i2cpwm_controller__srv__DriveMode_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          i2cpwm_controller__srv__DriveMode_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!i2cpwm_controller__srv__DriveMode_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
i2cpwm_controller__srv__DriveMode_Response__init(i2cpwm_controller__srv__DriveMode_Response * msg)
{
  if (!msg) {
    return false;
  }
  // error
  return true;
}

void
i2cpwm_controller__srv__DriveMode_Response__fini(i2cpwm_controller__srv__DriveMode_Response * msg)
{
  if (!msg) {
    return;
  }
  // error
}

bool
i2cpwm_controller__srv__DriveMode_Response__are_equal(const i2cpwm_controller__srv__DriveMode_Response * lhs, const i2cpwm_controller__srv__DriveMode_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // error
  if (lhs->error != rhs->error) {
    return false;
  }
  return true;
}

bool
i2cpwm_controller__srv__DriveMode_Response__copy(
  const i2cpwm_controller__srv__DriveMode_Response * input,
  i2cpwm_controller__srv__DriveMode_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // error
  output->error = input->error;
  return true;
}

i2cpwm_controller__srv__DriveMode_Response *
i2cpwm_controller__srv__DriveMode_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Response * msg = (i2cpwm_controller__srv__DriveMode_Response *)allocator.allocate(sizeof(i2cpwm_controller__srv__DriveMode_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(i2cpwm_controller__srv__DriveMode_Response));
  bool success = i2cpwm_controller__srv__DriveMode_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
i2cpwm_controller__srv__DriveMode_Response__destroy(i2cpwm_controller__srv__DriveMode_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    i2cpwm_controller__srv__DriveMode_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
i2cpwm_controller__srv__DriveMode_Response__Sequence__init(i2cpwm_controller__srv__DriveMode_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Response * data = NULL;

  if (size) {
    data = (i2cpwm_controller__srv__DriveMode_Response *)allocator.zero_allocate(size, sizeof(i2cpwm_controller__srv__DriveMode_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = i2cpwm_controller__srv__DriveMode_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        i2cpwm_controller__srv__DriveMode_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
i2cpwm_controller__srv__DriveMode_Response__Sequence__fini(i2cpwm_controller__srv__DriveMode_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      i2cpwm_controller__srv__DriveMode_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

i2cpwm_controller__srv__DriveMode_Response__Sequence *
i2cpwm_controller__srv__DriveMode_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__DriveMode_Response__Sequence * array = (i2cpwm_controller__srv__DriveMode_Response__Sequence *)allocator.allocate(sizeof(i2cpwm_controller__srv__DriveMode_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = i2cpwm_controller__srv__DriveMode_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
i2cpwm_controller__srv__DriveMode_Response__Sequence__destroy(i2cpwm_controller__srv__DriveMode_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    i2cpwm_controller__srv__DriveMode_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
i2cpwm_controller__srv__DriveMode_Response__Sequence__are_equal(const i2cpwm_controller__srv__DriveMode_Response__Sequence * lhs, const i2cpwm_controller__srv__DriveMode_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!i2cpwm_controller__srv__DriveMode_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
i2cpwm_controller__srv__DriveMode_Response__Sequence__copy(
  const i2cpwm_controller__srv__DriveMode_Response__Sequence * input,
  i2cpwm_controller__srv__DriveMode_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(i2cpwm_controller__srv__DriveMode_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    i2cpwm_controller__srv__DriveMode_Response * data =
      (i2cpwm_controller__srv__DriveMode_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!i2cpwm_controller__srv__DriveMode_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          i2cpwm_controller__srv__DriveMode_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!i2cpwm_controller__srv__DriveMode_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}