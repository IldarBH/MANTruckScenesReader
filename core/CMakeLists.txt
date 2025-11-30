cmake_minimum_required(VERSION 3.10)
project(MANTruckDataset)
set(PROJECT_VERSION 0.1.0)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common io)

###########################################################################
##                            BUILD LIBRIARY                             ##
###########################################################################

# Automatically collect headers from include directory
file(GLOB_RECURSE HEADERS 
  "${CMAKE_CURRENT_SOURCE_DIR}/include/MANTruckDataset/*.hpp"
)
add_library(${PROJECT_NAME} 
  SHARED
    ${HEADERS}
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${PCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
    ${PCL_LIBRARIES}
)
set_target_properties(${PROJECT_NAME} 
  PROPERTIES 
  LINKER_LANGUAGE CXX
  VERSION ${PROJECT_VERSION}
  CMAKE_CXX_STANDARD 20
  CMAKE_CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF
  PUBLIC_HEADER "${HEADERS}"
)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG_BUILD)
endif()

###########################################################################
##                               BUILD TESTS                             ##
###########################################################################

if (BUILD_TESTING)
  add_subdirectory(test)
endif()

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