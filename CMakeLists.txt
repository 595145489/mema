cmake_minimum_required (VERSION 3.10) 

# IF(NOT ${CMAKE_BUILD_TYPE} EQUAL "Relese") 
#     set(DCMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
# ENDIF()
set(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_STANDARD 17)

# SET (CMAKE_C_COMPILER "/usr/bin/clang")
# SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
# SET (CMAKE_AR      "/usr/bin/llvm-ar")
# SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
# SET (CMAKE_NM      "/usr/bin/llvm-nm")
# SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
# SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

# SET(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++17")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -O0 -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

SET(MEMA_BUILD_TESTS "ON")

#给项目命名
PROJECT(mema)

add_subdirectory(mema)

