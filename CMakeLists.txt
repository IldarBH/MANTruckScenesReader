cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesProject)

# Add subdirectories
add_subdirectory(core)

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()