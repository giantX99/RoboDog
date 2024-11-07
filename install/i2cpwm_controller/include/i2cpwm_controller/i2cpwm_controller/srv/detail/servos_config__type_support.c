// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from i2cpwm_controller:srv/ServosConfig.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "i2cpwm_controller/srv/detail/servos_config__rosidl_typesupport_introspection_c.h"
#include "i2cpwm_controller/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "i2cpwm_controller/srv/detail/servos_config__functions.h"
#include "i2cpwm_controller/srv/detail/servos_config__struct.h"


// Include directives for member types
// Member `servos`
#include "i2cpwm_controller/msg/servo_config.h"
// Member `servos`
#include "i2cpwm_controller/msg/detail/servo_config__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  i2cpwm_controller__srv__ServosConfig_Request__init(message_memory);
}

void i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_fini_function(void * message_memory)
{
  i2cpwm_controller__srv__ServosConfig_Request__fini(message_memory);
}

size_t i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__size_function__ServosConfig_Request__servos(
  const void * untyped_member)
{
  const i2cpwm_controller__msg__ServoConfig__Sequence * member =
    (const i2cpwm_controller__msg__ServoConfig__Sequence *)(untyped_member);
  return member->size;
}

const void * i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_const_function__ServosConfig_Request__servos(
  const void * untyped_member, size_t index)
{
  const i2cpwm_controller__msg__ServoConfig__Sequence * member =
    (const i2cpwm_controller__msg__ServoConfig__Sequence *)(untyped_member);
  return &member->data[index];
}

void * i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_function__ServosConfig_Request__servos(
  void * untyped_member, size_t index)
{
  i2cpwm_controller__msg__ServoConfig__Sequence * member =
    (i2cpwm_controller__msg__ServoConfig__Sequence *)(untyped_member);
  return &member->data[index];
}

void i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__fetch_function__ServosConfig_Request__servos(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const i2cpwm_controller__msg__ServoConfig * item =
    ((const i2cpwm_controller__msg__ServoConfig *)
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_const_function__ServosConfig_Request__servos(untyped_member, index));
  i2cpwm_controller__msg__ServoConfig * value =
    (i2cpwm_controller__msg__ServoConfig *)(untyped_value);
  *value = *item;
}

void i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__assign_function__ServosConfig_Request__servos(
  void * untyped_member, size_t index, const void * untyped_value)
{
  i2cpwm_controller__msg__ServoConfig * item =
    ((i2cpwm_controller__msg__ServoConfig *)
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_function__ServosConfig_Request__servos(untyped_member, index));
  const i2cpwm_controller__msg__ServoConfig * value =
    (const i2cpwm_controller__msg__ServoConfig *)(untyped_value);
  *item = *value;
}

bool i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__resize_function__ServosConfig_Request__servos(
  void * untyped_member, size_t size)
{
  i2cpwm_controller__msg__ServoConfig__Sequence * member =
    (i2cpwm_controller__msg__ServoConfig__Sequence *)(untyped_member);
  i2cpwm_controller__msg__ServoConfig__Sequence__fini(member);
  return i2cpwm_controller__msg__ServoConfig__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_member_array[1] = {
  {
    "servos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller__srv__ServosConfig_Request, servos),  // bytes offset in struct
    NULL,  // default value
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__size_function__ServosConfig_Request__servos,  // size() function pointer
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_const_function__ServosConfig_Request__servos,  // get_const(index) function pointer
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__get_function__ServosConfig_Request__servos,  // get(index) function pointer
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__fetch_function__ServosConfig_Request__servos,  // fetch(index, &value) function pointer
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__assign_function__ServosConfig_Request__servos,  // assign(index, value) function pointer
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__resize_function__ServosConfig_Request__servos  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_members = {
  "i2cpwm_controller__srv",  // message namespace
  "ServosConfig_Request",  // message name
  1,  // number of fields
  sizeof(i2cpwm_controller__srv__ServosConfig_Request),
  i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_member_array,  // message members
  i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_type_support_handle = {
  0,
  &i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_i2cpwm_controller
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Request)() {
  i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, msg, ServoConfig)();
  if (!i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_type_support_handle.typesupport_identifier) {
    i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &i2cpwm_controller__srv__ServosConfig_Request__rosidl_typesupport_introspection_c__ServosConfig_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "i2cpwm_controller/srv/detail/servos_config__rosidl_typesupport_introspection_c.h"
// already included above
// #include "i2cpwm_controller/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "i2cpwm_controller/srv/detail/servos_config__functions.h"
// already included above
// #include "i2cpwm_controller/srv/detail/servos_config__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  i2cpwm_controller__srv__ServosConfig_Response__init(message_memory);
}

void i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_fini_function(void * message_memory)
{
  i2cpwm_controller__srv__ServosConfig_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_member_array[1] = {
  {
    "error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(i2cpwm_controller__srv__ServosConfig_Response, error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_members = {
  "i2cpwm_controller__srv",  // message namespace
  "ServosConfig_Response",  // message name
  1,  // number of fields
  sizeof(i2cpwm_controller__srv__ServosConfig_Response),
  i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_member_array,  // message members
  i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_type_support_handle = {
  0,
  &i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_i2cpwm_controller
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Response)() {
  if (!i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_type_support_handle.typesupport_identifier) {
    i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &i2cpwm_controller__srv__ServosConfig_Response__rosidl_typesupport_introspection_c__ServosConfig_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "i2cpwm_controller/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "i2cpwm_controller/srv/detail/servos_config__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_members = {
  "i2cpwm_controller__srv",  // service namespace
  "ServosConfig",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_Request_message_type_support_handle,
  NULL  // response message
  // i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_Response_message_type_support_handle
};

static rosidl_service_type_support_t i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_type_support_handle = {
  0,
  &i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_i2cpwm_controller
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig)() {
  if (!i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_type_support_handle.typesupport_identifier) {
    i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, i2cpwm_controller, srv, ServosConfig_Response)()->data;
  }

  return &i2cpwm_controller__srv__detail__servos_config__rosidl_typesupport_introspection_c__ServosConfig_service_type_support_handle;
}
