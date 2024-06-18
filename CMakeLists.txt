cmake_minimum_required(VERSION 3.12)
project(loggerlib)
project(loggerlib VERSION 0.2.3)

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

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_executable(lltest test/main.h test/main.cpp)
  target_link_libraries(lltest PUBLIC logger cpptools stdc++fs)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

include(GNUInstallDirs)

install(TARGETS logger
  EXPORT loggerTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
)

install(EXPORT loggerTargets
  FILE loggerTargets.cmake
  NAMESPACE logger::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  @ONLY
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
