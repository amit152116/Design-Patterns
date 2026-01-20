cmake_minimum_required(VERSION 3.8)
project(Design_patterns)

# Set C++17 as standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)

# Ensure build files go to build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Find all .cpp files in the project directory and subdirectories
file(GLOB_RECURSE CPP_FILES "${CMAKE_SOURCE_DIR}/*.cpp"
     "${CMAKE_SOURCE_DIR}/**/*.cpp")

# Find all header files
file(GLOB_RECURSE header_files "${CMAKE_SOURCE_DIR}/*.h"
     "${CMAKE_SOURCE_DIR}/*.hpp" "${CMAKE_SOURCE_DIR}/**/*.h"
     "${CMAKE_SOURCE_DIR}/**/*.hpp")

# Filter out CMake internal files and build directory files
list(FILTER CPP_FILES EXCLUDE REGEX ".*CMakeFiles.*")
list(FILTER CPP_FILES EXCLUDE REGEX "${CMAKE_BINARY_DIR}.*")

# Create an executable for each .cpp file
foreach(SOURCE_FILE ${CPP_FILES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
  if(NOT TARGET ${EXECUTABLE_NAME})
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    if(${EXECUTABLE_NAME} STREQUAL "builder")
      target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt)
    endif()
  endif()
endforeach()
