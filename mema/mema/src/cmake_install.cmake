# Install script for directory: /home/wsh/mema/mema/src

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
   "/home/wsh/mema/bin/include/ChannelList.h;/home/wsh/mema/bin/include/FdChannel.h;/home/wsh/mema/bin/include/MemaBase.h;/home/wsh/mema/bin/include/MemoryPool.h;/home/wsh/mema/bin/include/ThreadPool.h;/home/wsh/mema/bin/include/ListenThread.h;/home/wsh/mema/bin/include/Thread.h;/home/wsh/mema/bin/include/EPoller.h;/home/wsh/mema/bin/include/Poller.h;/home/wsh/mema/bin/include/SocketLink.h;/home/wsh/mema/bin/include/TcpAcceptor.h;/home/wsh/mema/bin/include/TcpConnection.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/wsh/mema/bin/include" TYPE FILE FILES
    "/home/wsh/mema/mema/src/ChannelList.h"
    "/home/wsh/mema/mema/src/FdChannel.h"
    "/home/wsh/mema/mema/src/MemaBase.h"
    "/home/wsh/mema/mema/src/MemoryPool.h"
    "/home/wsh/mema/mema/src/ThreadPool.h"
    "/home/wsh/mema/mema/src/thread/ListenThread.h"
    "/home/wsh/mema/mema/src/thread/Thread.h"
    "/home/wsh/mema/mema/src/poller/EPoller.h"
    "/home/wsh/mema/mema/src/poller/Poller.h"
    "/home/wsh/mema/mema/src/socketopt/SocketLink.h"
    "/home/wsh/mema/mema/src/socketopt/TcpAcceptor.h"
    "/home/wsh/mema/mema/src/socketopt/TcpConnection.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/wsh/mema/bin/lib/libmema_base.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/wsh/mema/bin/lib" TYPE STATIC_LIBRARY FILES "/home/wsh/mema/mema/mema/src/libmema_base.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/wsh/mema/mema/mema/src/thirdparty/gflags/cmake_install.cmake")
  include("/home/wsh/mema/mema/mema/src/base/cmake_install.cmake")
  include("/home/wsh/mema/mema/mema/src/tests/cmake_install.cmake")

endif()

