# Install script for directory: /home/jiapei/Downloads/computervision/VOSM/modules/integraltransform

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/jiapei/Downloads/computervision/VOSM/build/modules/integraltransform/libvosm_integraltransform.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vosm" TYPE FILE FILES
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_STFT.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Coiflets.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_DiscreteFIRMeyer.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_IntegralTransform.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_DiscreteWavelet.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Symlets.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Haar.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Gauss.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Gabor.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_WindowFunc.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_ReverseBiorthogonal.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_CohenDaubechiesFeauveau.h"
    "/home/jiapei/Downloads/computervision/VOSM/modules/integraltransform/include/VO_Daubechies.h"
    )
endif()

