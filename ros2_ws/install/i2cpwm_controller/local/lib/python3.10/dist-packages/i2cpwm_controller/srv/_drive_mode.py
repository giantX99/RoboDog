# generated from rosidl_generator_py/resource/_idl.py.em
# with input from i2cpwm_controller:srv/DriveMode.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DriveMode_Request(type):
    """Metaclass of message 'DriveMode_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('i2cpwm_controller')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'i2cpwm_controller.srv.DriveMode_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__drive_mode__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__drive_mode__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__drive_mode__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__drive_mode__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__drive_mode__request

            from i2cpwm_controller.msg import Position
            if Position.__class__._TYPE_SUPPORT is None:
                Position.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DriveMode_Request(metaclass=Metaclass_DriveMode_Request):
    """Message class 'DriveMode_Request'."""

    __slots__ = [
        '_mode',
        '_rpm',
        '_radius',
        '_track',
        '_scale',
        '_servos',
    ]

    _fields_and_field_types = {
        'mode': 'string',
        'rpm': 'float',
        'radius': 'float',
        'track': 'float',
        'scale': 'float',
        'servos': 'sequence<i2cpwm_controller/Position>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['i2cpwm_controller', 'msg'], 'Position')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', str())
        self.rpm = kwargs.get('rpm', float())
        self.radius = kwargs.get('radius', float())
        self.track = kwargs.get('track', float())
        self.scale = kwargs.get('scale', float())
        self.servos = kwargs.get('servos', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.mode != other.mode:
            return False
        if self.rpm != other.rpm:
            return False
        if self.radius != other.radius:
            return False
        if self.track != other.track:
            return False
        if self.scale != other.scale:
            return False
        if self.servos != other.servos:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mode' field must be of type 'str'"
        self._mode = value

    @builtins.property
    def rpm(self):
        """Message field 'rpm'."""
        return self._rpm

    @rpm.setter
    def rpm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rpm' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rpm' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rpm = value

    @builtins.property
    def radius(self):
        """Message field 'radius'."""
        return self._radius

    @radius.setter
    def radius(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'radius' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'radius' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._radius = value

    @builtins.property
    def track(self):
        """Message field 'track'."""
        return self._track

    @track.setter
    def track(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'track' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'track' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._track = value

    @builtins.property
    def scale(self):
        """Message field 'scale'."""
        return self._scale

    @scale.setter
    def scale(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'scale' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'scale' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._scale = value

    @builtins.property
    def servos(self):
        """Message field 'servos'."""
        return self._servos

    @servos.setter
    def servos(self, value):
        if __debug__:
            from i2cpwm_controller.msg import Position
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Position) for v in value) and
                 True), \
                "The 'servos' field must be a set or sequence and each value of type 'Position'"
        self._servos = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_DriveMode_Response(type):
    """Metaclass of message 'DriveMode_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('i2cpwm_controller')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'i2cpwm_controller.srv.DriveMode_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__drive_mode__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__drive_mode__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__drive_mode__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__drive_mode__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__drive_mode__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DriveMode_Response(metaclass=Metaclass_DriveMode_Response):
    """Message class 'DriveMode_Response'."""

    __slots__ = [
        '_error',
    ]

    _fields_and_field_types = {
        'error': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.error = kwargs.get('error', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.error != other.error:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def error(self):
        """Message field 'error'."""
        return self._error

    @error.setter
    def error(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'error' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'error' field must be an integer in [-32768, 32767]"
        self._error = value


class Metaclass_DriveMode(type):
    """Metaclass of service 'DriveMode'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('i2cpwm_controller')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'i2cpwm_controller.srv.DriveMode')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__drive_mode

            from i2cpwm_controller.srv import _drive_mode
            if _drive_mode.Metaclass_DriveMode_Request._TYPE_SUPPORT is None:
                _drive_mode.Metaclass_DriveMode_Request.__import_type_support__()
            if _drive_mode.Metaclass_DriveMode_Response._TYPE_SUPPORT is None:
                _drive_mode.Metaclass_DriveMode_Response.__import_type_support__()


class DriveMode(metaclass=Metaclass_DriveMode):
    from i2cpwm_controller.srv._drive_mode import DriveMode_Request as Request
    from i2cpwm_controller.srv._drive_mode import DriveMode_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
