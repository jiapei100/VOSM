# Install script for directory: /home/jiapei/Downloads/computervision/VOSM/samples/testsmfitting

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting"
         RPATH "/usr/local/lib:/usr/local/cuda-7.5/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/jiapei/Downloads/computervision/VOSM/build/samples/testsmfitting/vo_testsmfitting")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting"
         OLD_RPATH "/usr/local/lib:/usr/local/cuda-7.5/lib64:/home/jiapei/Downloads/computervision/VOSM/build/modules/common:/home/jiapei/Downloads/computervision/VOSM/build/modules/smbuilding:/home/jiapei/Downloads/computervision/VOSM/build/modules/featureextraction:/home/jiapei/Downloads/computervision/VOSM/build/modules/integraltransform:/home/jiapei/Downloads/computervision/VOSM/build/modules/cvcommon:/home/jiapei/Downloads/computervision/VOSM/build/modules/comalgs:/home/jiapei/Downloads/computervision/VOSM/build/modules/ensembletraining:/home/jiapei/Downloads/computervision/VOSM/build/modules/smfitting:"
         NEW_RPATH "/usr/local/lib:/usr/local/cuda-7.5/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/vo_testsmfitting")
    endif()
  endif()
endif()

