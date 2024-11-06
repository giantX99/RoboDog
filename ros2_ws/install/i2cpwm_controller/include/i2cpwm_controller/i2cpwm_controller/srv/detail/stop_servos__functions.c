// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from i2cpwm_controller:srv/StopServos.idl
// generated code does not contain a copyright notice
#include "i2cpwm_controller/srv/detail/stop_servos__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
i2cpwm_controller__srv__StopServos_Request__init(i2cpwm_controller__srv__StopServos_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
i2cpwm_controller__srv__StopServos_Request__fini(i2cpwm_controller__srv__StopServos_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
i2cpwm_controller__srv__StopServos_Request__are_equal(const i2cpwm_controller__srv__StopServos_Request * lhs, const i2cpwm_controller__srv__StopServos_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
i2cpwm_controller__srv__StopServos_Request__copy(
  const i2cpwm_controller__srv__StopServos_Request * input,
  i2cpwm_controller__srv__StopServos_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

i2cpwm_controller__srv__StopServos_Request *
i2cpwm_controller__srv__StopServos_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Request * msg = (i2cpwm_controller__srv__StopServos_Request *)allocator.allocate(sizeof(i2cpwm_controller__srv__StopServos_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(i2cpwm_controller__srv__StopServos_Request));
  bool success = i2cpwm_controller__srv__StopServos_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
i2cpwm_controller__srv__StopServos_Request__destroy(i2cpwm_controller__srv__StopServos_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    i2cpwm_controller__srv__StopServos_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
i2cpwm_controller__srv__StopServos_Request__Sequence__init(i2cpwm_controller__srv__StopServos_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Request * data = NULL;

  if (size) {
    data = (i2cpwm_controller__srv__StopServos_Request *)allocator.zero_allocate(size, sizeof(i2cpwm_controller__srv__StopServos_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = i2cpwm_controller__srv__StopServos_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        i2cpwm_controller__srv__StopServos_Request__fini(&data[i - 1]);
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
i2cpwm_controller__srv__StopServos_Request__Sequence__fini(i2cpwm_controller__srv__StopServos_Request__Sequence * array)
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
      i2cpwm_controller__srv__StopServos_Request__fini(&array->data[i]);
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

i2cpwm_controller__srv__StopServos_Request__Sequence *
i2cpwm_controller__srv__StopServos_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Request__Sequence * array = (i2cpwm_controller__srv__StopServos_Request__Sequence *)allocator.allocate(sizeof(i2cpwm_controller__srv__StopServos_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = i2cpwm_controller__srv__StopServos_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
i2cpwm_controller__srv__StopServos_Request__Sequence__destroy(i2cpwm_controller__srv__StopServos_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    i2cpwm_controller__srv__StopServos_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
i2cpwm_controller__srv__StopServos_Request__Sequence__are_equal(const i2cpwm_controller__srv__StopServos_Request__Sequence * lhs, const i2cpwm_controller__srv__StopServos_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!i2cpwm_controller__srv__StopServos_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
i2cpwm_controller__srv__StopServos_Request__Sequence__copy(
  const i2cpwm_controller__srv__StopServos_Request__Sequence * input,
  i2cpwm_controller__srv__StopServos_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(i2cpwm_controller__srv__StopServos_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    i2cpwm_controller__srv__StopServos_Request * data =
      (i2cpwm_controller__srv__StopServos_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!i2cpwm_controller__srv__StopServos_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          i2cpwm_controller__srv__StopServos_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!i2cpwm_controller__srv__StopServos_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
i2cpwm_controller__srv__StopServos_Response__init(i2cpwm_controller__srv__StopServos_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
i2cpwm_controller__srv__StopServos_Response__fini(i2cpwm_controller__srv__StopServos_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
i2cpwm_controller__srv__StopServos_Response__are_equal(const i2cpwm_controller__srv__StopServos_Response * lhs, const i2cpwm_controller__srv__StopServos_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
i2cpwm_controller__srv__StopServos_Response__copy(
  const i2cpwm_controller__srv__StopServos_Response * input,
  i2cpwm_controller__srv__StopServos_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

i2cpwm_controller__srv__StopServos_Response *
i2cpwm_controller__srv__StopServos_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Response * msg = (i2cpwm_controller__srv__StopServos_Response *)allocator.allocate(sizeof(i2cpwm_controller__srv__StopServos_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(i2cpwm_controller__srv__StopServos_Response));
  bool success = i2cpwm_controller__srv__StopServos_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
i2cpwm_controller__srv__StopServos_Response__destroy(i2cpwm_controller__srv__StopServos_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    i2cpwm_controller__srv__StopServos_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
i2cpwm_controller__srv__StopServos_Response__Sequence__init(i2cpwm_controller__srv__StopServos_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Response * data = NULL;

  if (size) {
    data = (i2cpwm_controller__srv__StopServos_Response *)allocator.zero_allocate(size, sizeof(i2cpwm_controller__srv__StopServos_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = i2cpwm_controller__srv__StopServos_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        i2cpwm_controller__srv__StopServos_Response__fini(&data[i - 1]);
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
i2cpwm_controller__srv__StopServos_Response__Sequence__fini(i2cpwm_controller__srv__StopServos_Response__Sequence * array)
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
      i2cpwm_controller__srv__StopServos_Response__fini(&array->data[i]);
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

i2cpwm_controller__srv__StopServos_Response__Sequence *
i2cpwm_controller__srv__StopServos_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  i2cpwm_controller__srv__StopServos_Response__Sequence * array = (i2cpwm_controller__srv__StopServos_Response__Sequence *)allocator.allocate(sizeof(i2cpwm_controller__srv__StopServos_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = i2cpwm_controller__srv__StopServos_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
i2cpwm_controller__srv__StopServos_Response__Sequence__destroy(i2cpwm_controller__srv__StopServos_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    i2cpwm_controller__srv__StopServos_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
i2cpwm_controller__srv__StopServos_Response__Sequence__are_equal(const i2cpwm_controller__srv__StopServos_Response__Sequence * lhs, const i2cpwm_controller__srv__StopServos_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!i2cpwm_controller__srv__StopServos_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
i2cpwm_controller__srv__StopServos_Response__Sequence__copy(
  const i2cpwm_controller__srv__StopServos_Response__Sequence * input,
  i2cpwm_controller__srv__StopServos_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(i2cpwm_controller__srv__StopServos_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    i2cpwm_controller__srv__StopServos_Response * data =
      (i2cpwm_controller__srv__StopServos_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!i2cpwm_controller__srv__StopServos_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          i2cpwm_controller__srv__StopServos_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!i2cpwm_controller__srv__StopServos_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
