cmake_minimum_required(VERSION 3.18)
project(loggerlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CMAKE_BUILD_TYPE "Build type" Release)

message("Configuring as " ${CMAKE_BUILD_TYPE})
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
   set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
   set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    add_definitions(-DLL_DEBUG)
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

set(LL_HEADERS
  src/clogger.h
  src/tools/tools_fs.h
  src/tools/tools_string.h
  )

set(LL_SOURCES
  src/clogger.cpp
  src/tools/tools_fs.cpp
  src/tools/tools_string.cpp
  )

include_directories(
  src
  src/defines
  src/tools
  test
  )

add_library(logger SHARED ${LL_HEADERS} ${LL_SOURCES})

add_executable(lltest test/lltest.cpp)
target_link_libraries(lltest PUBLIC logger stdc++fs)
