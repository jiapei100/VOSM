# --------------------------------------------------------------
# Top level VOSM project
# --------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

# Add Include, Library path here
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# must go before the project command
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
set(BUILD_EXAMPLES ON CACHE BOOL "Build examples" FORCE)
if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()


project(vosm CXX C)


find_library(BOOST_FILESYSTEM_LIB boost_filesystem $ENV{BOOST_FILESYSTEM_LIB})
find_library(BOOST_REGEX_LIB boost_regex $ENV{BOOST_REGEX_LIB})
find_library(BOOST_SYSTEM_LIB boost_system $ENV{BOOST_SYSTEM_LIB})
#find_library(OPENCV_CORE_LIB opencv_core $ENV{OPENCV_CORE_LIB})
#find_library(OPENCV_IMGPROC_LIB opencv_imgproc $ENV{OPENCV_IMGPROC_LIB})
#find_library(OPENCV_IMGPROC_LIB opencv_imgproc $ENV{OPENCV_IMGCODECS_LIB})
#find_library(OPENCV_HIGHGUI_LIB opencv_highgui $ENV{OPENCV_HIGHGUI_LIB})
#find_library(OPENCV_FEATURES2D_LIB opencv_features2d $ENV{OPENCV_FEATURES2D_LIB})
#find_library(OPENCV_OBJDETECT_LIB opencv_objdetect $ENV{OPENCV_OBJDETECT_LIB})
#find_library(OPENCV_IMGPROC_LIB opencv_imgproc $ENV{OPENCV_ML_LIB})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_subdirectory(modules)
add_subdirectory(samples)
