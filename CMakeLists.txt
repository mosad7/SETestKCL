CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
project(SETestKCL)

##############################################################################
# Release number
#-----------------------------------------------------------------------------
set(SETestKCL_VERSION_MAJOR 1)
set(SETestKCL_VERSION_MINOR 0)
set(SETestKCL_VERSION_PATCH 0)

##############################################################################
# Configured header files
#-----------------------------------------------------------------------------
configure_file(
  "${PROJECT_SOURCE_DIR}/SETestKCLConfig.h.in"
  "${PROJECT_BINARY_DIR}/SETestKCLConfig.h")
  
  INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

##############################################################################
# Build type and platform target
#-----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS “Setting build type to ‘Release’ as none was specified.”)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING “Choose the type of build” FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
               STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

if(APPLE)
	set(CMAKE_OSX_ARCHITECTURES "x86_64")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

##############################################################################
# SETestKCL options 
#-----------------------------------------------------------------------------
option(Build_GUI_App "Build GUI App" OFF)

##############################################################################
# Locations for source files, and runtime and shared libraries
#-----------------------------------------------------------------------------
ADD_SUBDIRECTORY(src)






