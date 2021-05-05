# Install script for directory: /media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/samples/testsmfitting

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmainx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting"
         RPATH "/usr/local/lib:/usr/local/cuda/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/samples/testsmfitting/testsmfitting")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting"
         OLD_RPATH "/usr/local/lib:/usr/local/cuda/lib64:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/common:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/smbuilding:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/featureextraction:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/integraltransform:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/cvcommon:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/comalgs:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/ensembletraining:/media/lvision/Seagate1/OpenSource/ComputerVision/VOSM/build/modules/smfitting:"
         NEW_RPATH "/usr/local/lib:/usr/local/cuda/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/testsmfitting")
    endif()
  endif()
endif()

