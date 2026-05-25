find_package(fmt REQUIRED)

# Put binaries in cpp build dir
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

# Find all .cpp files in this directory and subdirectories
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Filter out CMake internal files and build directory files
list(FILTER CPP_FILES EXCLUDE REGEX ".*CMakeFiles.*")
list(FILTER CPP_FILES EXCLUDE REGEX "${CMAKE_CURRENT_BINARY_DIR}.*")

# Create an executable for each .cpp file
foreach(SOURCE_FILE ${CPP_FILES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
  if(NOT TARGET ${EXECUTABLE_NAME})
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt)
  endif()
endforeach()
