# generated from rosidl_generator_py/resource/_idl.py.em
# with input from i2cpwm_controller:msg/Position.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Position(type):
    """Metaclass of message 'Position'."""

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
                'i2cpwm_controller.msg.Position')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__position
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__position
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__position
            cls._TYPE_SUPPORT = module.type_support_msg__msg__position
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__position

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Position(metaclass=Metaclass_Position):
    """Message class 'Position'."""

    __slots__ = [
        '_servo',
        '_position',
    ]

    _fields_and_field_types = {
        'servo': 'int16',
        'position': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.servo = kwargs.get('servo', int())
        self.position = kwargs.get('position', int())

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
        if self.servo != other.servo:
            return False
        if self.position != other.position:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def servo(self):
        """Message field 'servo'."""
        return self._servo

    @servo.setter
    def servo(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'servo' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'servo' field must be an integer in [-32768, 32767]"
        self._servo = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'position' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'position' field must be an integer in [-32768, 32767]"
        self._position = value
