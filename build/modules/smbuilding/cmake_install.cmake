# Install script for directory: /media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/media/jiapei/Data/Downloads/computervision/VOSM/build/modules/smbuilding/libvosm_smbuilding.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_smbuilding.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vosm" TYPE FILE FILES
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_AAMBasic.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_AAMForwardIA.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_AAMInverseIA.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_AFM.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_ASMLTCs.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_ASMNDProfiles.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_AXM.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Edge.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Ellipse.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_FacePart.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_FaceParts.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_FeatureModel.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Point2DDistributionModel.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Profile.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Profiles.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Shape.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Shape2DInfo.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_ShapeFace.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_ShapeModel.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Texture.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_TextureModel.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Triangle2D.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_Triangle2DStructure.h"
    "/media/jiapei/Data/Downloads/computervision/VOSM/modules/smbuilding/include/VO_WarpingPoint.h"
    )
endif()

