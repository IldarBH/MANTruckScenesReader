cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME_PYTHON MANTruckDatasetPy)
set(PROJECT_VERSION 0.1.0)

find_package(pybind11 REQUIRED)

###########################################################################
##                            BUILD LIBRIARY                             ##
###########################################################################

pybind11_add_module(${PROJECT_NAME_PYTHON}
  src/py_bindings.cpp
)
target_link_libraries(${PROJECT_NAME_PYTHON}
  PRIVATE
    MANTruckDataset
)
set_target_properties(${PROJECT_NAME_PYTHON}
  PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

###########################################################################
##                             INSTALL LIBRIARY                          ##
###########################################################################
# Install Python extension module to Python site-packages
install(
  TARGETS ${PROJECT_NAME_PYTHON}
  LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES}
)
install(
  FILES "${CMAKE_CURRENT_SOURCE_DIR}/stubs/MANTruckDatasetPy.pyi"
  DESTINATION ${PYTHON_SITE_PACKAGES}
)