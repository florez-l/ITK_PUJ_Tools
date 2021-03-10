## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

cmake_minimum_required(VERSION 3.0)
project(ITK_PUJ_Tools VERSION 1.0.0.1)

# -- Force c++17
set(CMAKE_CXX_STANDARD 17)

# -- Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif(EXISTS "${CMAKE_SOURCE_DIR}/.git")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS
    "Setting build type to '${default_build_type}' as none was specified."
    )
  set(
    CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE
    )
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

# -- Do not allow to build inside the source tree
if(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})
  message(FATAL_ERROR "Building in the source tree is not allowed.")
endif(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})

# -- Where to put targets (executables and libs)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
mark_as_advanced(
  CMAKE_BACKWARDS_COMPATIBILITY
  EXECUTABLE_OUTPUT_PATH
  LIBRARY_OUTPUT_PATH
  )

# -- ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# -- Tools
set(_tools ConvertImage ExtractSeries)
foreach(_t ${_tools})
  add_executable(${_t} ${_t}.cxx)
  target_link_libraries(${_t} ${ITK_LIBRARIES})
endforeach()

## eof - $RCSfile$
