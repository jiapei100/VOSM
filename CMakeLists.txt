# --------------------------------------------------------------
# Top level OpenCV project
# --------------------------------------------------------------
if(CMAKE_GENERATOR MATCHES Xcode AND XCODE_VERSION VERSION_GREATER 4.3)
  cmake_minimum_required(VERSION 2.8.8)
elseif(IOS)
  cmake_minimum_required(VERSION 2.8.0)
else()
  cmake_minimum_required(VERSION 2.6.3)
endif()

if(POLICY CMP0017)
  cmake_policy(SET CMP0017 NEW)
endif()

if(POLICY CMP0022)
  cmake_policy(SET CMP0022 OLD)
endif()

# must go before the project command
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()

project(vosm CXX C)


find_library(BOOST_FILESYSTEM_LIB boost_filesystem $ENV{BOOST_FILESYSTEM_LIB})
find_library(BOOST_REGEX_LIB boost_regex $ENV{BOOST_REGEX_LIB})
find_library(BOOST_SYSTEM_LIB boost_system $ENV{BOOST_SYSTEM_LIB})
find_library(OPENCV_CORE_LIB opencv_core $ENV{OPENCV_CORE_LIB})
find_library(OPENCV_IMGPROC_LIB opencv_imgproc $ENV{OPENCV_IMGPROC_LIB})
find_library(OPENCV_HIGHGUI_LIB opencv_highgui $ENV{OPENCV_HIGHGUI_LIB})
find_library(OPENCV_FEATURES2D_LIB opencv_features2d $ENV{OPENCV_FEATURES2D_LIB})
find_library(OPENCV_OBJDETECT_LIB opencv_objdetect $ENV{OPENCV_OBJDETECT_LIB})
find_library(OPENCV_LEGACY_LIB opencv_legacy $ENV{OPENCV_LEGACY_LIB})
