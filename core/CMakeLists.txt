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
)
set(SOURCES
  src/MANTruckDataset/MANTruckDataset.cpp
)
add_library(${PROJECT_NAME} 
  SHARED 
    ${SOURCES} 
    ${HEADERS}
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${PCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${PCL_LIBRARIES}
)
set_target_properties(${PROJECT_NAME} 
  PROPERTIES 
  VERSION ${PROJECT_VERSION}
  CMAKE_CXX_STANDARD 20
  CMAKE_CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF
  PUBLIC_HEADER "${HEADERS}"
)

###########################################################################
##                             INSTALL LIBRIARY                          ##
###########################################################################

include(GNUInstallDirs)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE "${PROJECT_NAME}Targets.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

###########################################################################
##                   CREATE / INSTALL CMAKE CONFIGS                      ##
###########################################################################

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Install the config and version files
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)