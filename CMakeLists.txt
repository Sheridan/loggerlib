cmake_minimum_required(VERSION 3.18)
project(loggerlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(CMAKE_BUILD_TYPE "Build type" Release)

message("Configuring as " ${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE STREQUAL Debug)
   set(CMAKE_VERBOSE_MAKEFILE ON)
   set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
   set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
   add_definitions(-DLL_DEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

set(LL_HEADERS
  src/clogger.h
  src/cloggerbase.h
  src/clogstring.h
  src/clogpriority.h
  )

set(LL_SOURCES
  src/clogger.cpp
  src/cloggerbase.cpp
  src/clogstring.cpp
  src/clogpriority.cpp
  )

include_directories(
  src
  test
  )

add_library(logger SHARED ${LL_HEADERS} ${LL_SOURCES})

add_executable(lltest test/main.h test/main.cpp)
target_link_libraries(lltest PUBLIC logger cpptools stdc++fs)
