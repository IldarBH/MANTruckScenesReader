cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesReader)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common visualization)

add_executable(man_dataset src/man_dataset.cpp)
target_include_directories(man_dataset 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PCL_INCLUDE_DIRS}
)
target_link_libraries(man_dataset 
  PRIVATE 
    MANTruckDataset
    ${PCL_LIBRARIES}
)