#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tutorial-qdmi-device" for configuration "Release"
set_property(TARGET tutorial-qdmi-device APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tutorial-qdmi-device PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libtutorial-qdmi-device.so"
  IMPORTED_SONAME_RELEASE "libtutorial-qdmi-device.so"
  )

list(APPEND _cmake_import_check_targets tutorial-qdmi-device )
list(APPEND _cmake_import_check_files_for_tutorial-qdmi-device "${_IMPORT_PREFIX}/lib/libtutorial-qdmi-device.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
