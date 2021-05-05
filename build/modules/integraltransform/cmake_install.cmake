# Install script for directory: /media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/integraltransform/libvosm_integraltransform.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvosm_integraltransform.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vosm" TYPE FILE FILES
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_CohenDaubechiesFeauveau.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Coiflets.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Daubechies.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_DiscreteFIRMeyer.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_DiscreteWavelet.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Gabor.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Gauss.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Haar.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_IntegralTransform.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_ReverseBiorthogonal.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_STFT.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_Symlets.h"
    "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/modules/integraltransform/include/VO_WindowFunc.h"
    )
endif()

