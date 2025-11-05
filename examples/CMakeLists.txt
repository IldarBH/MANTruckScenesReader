cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesReader)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common io)

add_executable(samples src/samples.cpp)
target_include_directories(samples 
  PRIVATE 
    ${PCL_INCLUDE_DIRS}
    MANTruckDataset
)
target_link_libraries(samples 
  PRIVATE 
    ${PCL_LIBRARIES}
    MANTruckDataset
)

add_executable(sensors src/sensors.cpp)
target_include_directories(sensors 
  PRIVATE 
    ${PCL_INCLUDE_DIRS}
    MANTruckDataset
)
target_link_libraries(sensors 
  PRIVATE 
    ${PCL_LIBRARIES}
    MANTruckDataset
)