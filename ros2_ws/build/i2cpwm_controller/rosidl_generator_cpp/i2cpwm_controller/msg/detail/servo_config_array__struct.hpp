// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from i2cpwm_controller:msg/ServoConfigArray.idl
// generated code does not contain a copyright notice

#ifndef I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_HPP_
#define I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'servos'
#include "i2cpwm_controller/msg/detail/servo_config__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__i2cpwm_controller__msg__ServoConfigArray __attribute__((deprecated))
#else
# define DEPRECATED__i2cpwm_controller__msg__ServoConfigArray __declspec(deprecated)
#endif

namespace i2cpwm_controller
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoConfigArray_
{
  using Type = ServoConfigArray_<ContainerAllocator>;

  explicit ServoConfigArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ServoConfigArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _servos_type =
    std::vector<i2cpwm_controller::msg::ServoConfig_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<i2cpwm_controller::msg::ServoConfig_<ContainerAllocator>>>;
  _servos_type servos;

  // setters for named parameter idiom
  Type & set__servos(
    const std::vector<i2cpwm_controller::msg::ServoConfig_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<i2cpwm_controller::msg::ServoConfig_<ContainerAllocator>>> & _arg)
  {
    this->servos = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__i2cpwm_controller__msg__ServoConfigArray
    std::shared_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__i2cpwm_controller__msg__ServoConfigArray
    std::shared_ptr<i2cpwm_controller::msg::ServoConfigArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoConfigArray_ & other) const
  {
    if (this->servos != other.servos) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoConfigArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoConfigArray_

// alias to use template instance with default allocator
using ServoConfigArray =
  i2cpwm_controller::msg::ServoConfigArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace i2cpwm_controller

#endif  // I2CPWM_CONTROLLER__MSG__DETAIL__SERVO_CONFIG_ARRAY__STRUCT_HPP_