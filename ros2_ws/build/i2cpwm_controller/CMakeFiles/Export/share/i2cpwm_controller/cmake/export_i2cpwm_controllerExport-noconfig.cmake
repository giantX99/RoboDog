#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "i2cpwm_controller::i2cpwm_controller_lib" for configuration ""
set_property(TARGET i2cpwm_controller::i2cpwm_controller_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(i2cpwm_controller::i2cpwm_controller_lib PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libi2cpwm_controller_lib.so"
  IMPORTED_SONAME_NOCONFIG "libi2cpwm_controller_lib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS i2cpwm_controller::i2cpwm_controller_lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_i2cpwm_controller::i2cpwm_controller_lib "${_IMPORT_PREFIX}/lib/libi2cpwm_controller_lib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
