# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.18)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget spirv-cross-reflect)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target spirv-cross-reflect
add_library(spirv-cross-reflect STATIC IMPORTED)

set_target_properties(spirv-cross-reflect PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "X:/checkouts/SPIRV-Cross"
)

# Import target "spirv-cross-reflect" for configuration "Debug"
set_property(TARGET spirv-cross-reflect APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(spirv-cross-reflect PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "X:/checkouts/SPIRV-Cross/Debug/spirv-cross-reflectd.lib"
  )

# Import target "spirv-cross-reflect" for configuration "Release"
set_property(TARGET spirv-cross-reflect APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(spirv-cross-reflect PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "X:/checkouts/SPIRV-Cross/Release/spirv-cross-reflect.lib"
  )

# Import target "spirv-cross-reflect" for configuration "MinSizeRel"
set_property(TARGET spirv-cross-reflect APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(spirv-cross-reflect PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "X:/checkouts/SPIRV-Cross/MinSizeRel/spirv-cross-reflect.lib"
  )

# Import target "spirv-cross-reflect" for configuration "RelWithDebInfo"
set_property(TARGET spirv-cross-reflect APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(spirv-cross-reflect PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "X:/checkouts/SPIRV-Cross/RelWithDebInfo/spirv-cross-reflect.lib"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
