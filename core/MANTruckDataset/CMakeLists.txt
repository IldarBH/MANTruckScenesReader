cmake_minimum_required(VERSION 3.10)
project(MANTruckDataset)

find_package(PCL 1.14.0 EXACT REQUIRED COMPONENTS common io)

set(SOURCES
    src/MANTruckDataset.cpp
    # Add other source files here
)
set(HEADERS
    include/MANTruckDataset.hpp
    # Add other header files here
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${PCL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
      ${PCL_LIBRARIES}
)

# Installation rules
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# Export the targets for downstream projects
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)