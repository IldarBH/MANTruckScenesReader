cmake_minimum_required(VERSION 3.10)
project(MANTruckDataset)
set(PROJECT_VERSION 0.1.0)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common io)

###########################################################################
##                            BUILD LIBRIARY                             ##
###########################################################################

set(HEADERS
  include/MANTruckDataset/Sensor.hpp
  include/MANTruckDataset/Lidar.hpp
  include/MANTruckDataset/MANTruckDataset.hpp
  # Add other header files here
)
set(SOURCES
  src/MANTruckDataset/MANTruckDataset.cpp
  # Add other source files here
)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${PCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    ${PCL_LIBRARIES}
)

###########################################################################
##                             INSTALL LIBRIARY                          ##
###########################################################################

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
          COMPONENT libraries
)
install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION include
    COMPONENT headers
)
install(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${PROJECT_NAME}Targets.cmake"
  DESTINATION lib/cmake/${PROJECT_NAME}
  COMPONENT headers
)
###########################################################################
##                   CREATE / INSTALL CMAKE CONFIGS                      ##
###########################################################################

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
# Install the config and version files
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)