cmake_minimum_required(VERSION 3.10)
project(MANTruckScenesProject)

# Add subdirectories
add_subdirectory(core)

###########################################################################
##                           BUILD PYTHON BINDINGS                       ##
###########################################################################

if (BUILD_PYBINDS)
  add_subdirectory(python)
endif()

###########################################################################
##                              BUILD EXAMPLES                           ##
###########################################################################

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()