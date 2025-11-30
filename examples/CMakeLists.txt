cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesReader)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common visualization)
add_executable(samples src/samples.cpp)

add_executable(scenes src/scenes.cpp)
target_include_directories(scenes 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(scenes 
  PRIVATE 
    MANTruckDataset
)

target_include_directories(samples 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(samples 
  PRIVATE 
    MANTruckDataset
)

add_executable(data_samples src/data_samples.cpp)
target_include_directories(data_samples 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(data_samples 
  PRIVATE 
    MANTruckDataset
)

add_executable(sensors src/sensors.cpp)
target_include_directories(sensors 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sensors 
  PRIVATE 
    MANTruckDataset
)

add_executable(data_parsing src/data_parsing.cpp)
target_include_directories(data_parsing 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(data_parsing 
  PRIVATE 
    MANTruckDataset
)

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