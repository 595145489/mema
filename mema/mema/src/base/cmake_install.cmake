# Install script for directory: /home/wsh/mema/mema/src/base

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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/wsh/mema/bin/include/base/Buffer.h;/home/wsh/mema/bin/include/base/FileUtil.h;/home/wsh/mema/bin/include/base/ListBuffer.h;/home/wsh/mema/bin/include/base/Log.h;/home/wsh/mema/bin/include/base/MutexLock.h;/home/wsh/mema/bin/include/base/Socket.h;/home/wsh/mema/bin/include/base/ThreadBase.h;/home/wsh/mema/bin/include/base/Timer.h;/home/wsh/mema/bin/include/base/WriteBuffer.h;/home/wsh/mema/bin/include/base/coding.h;/home/wsh/mema/bin/include/base/noncopyable.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/wsh/mema/bin/include/base" TYPE FILE FILES
    "/home/wsh/mema/mema/src/base/Buffer.h"
    "/home/wsh/mema/mema/src/base/FileUtil.h"
    "/home/wsh/mema/mema/src/base/ListBuffer.h"
    "/home/wsh/mema/mema/src/base/Log.h"
    "/home/wsh/mema/mema/src/base/MutexLock.h"
    "/home/wsh/mema/mema/src/base/Socket.h"
    "/home/wsh/mema/mema/src/base/ThreadBase.h"
    "/home/wsh/mema/mema/src/base/Timer.h"
    "/home/wsh/mema/mema/src/base/WriteBuffer.h"
    "/home/wsh/mema/mema/src/base/coding.h"
    "/home/wsh/mema/mema/src/base/noncopyable.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/wsh/mema/bin/base/lib/libmema_base_lib.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/wsh/mema/bin/base/lib" TYPE STATIC_LIBRARY FILES "/home/wsh/mema/mema/mema/src/base/libmema_base_lib.a")
endif()

