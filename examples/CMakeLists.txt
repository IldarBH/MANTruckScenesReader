cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesReader)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common io)
find_package(MANTruckDataset)

add_executable(example src/example.cpp)
target_include_directories(example 
  PRIVATE 
    ${PCL_INCLUDE_DIRS})
target_link_libraries(example 
  PRIVATE 
    ${PCL_LIBRARIES})