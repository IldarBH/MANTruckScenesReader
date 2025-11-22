enable_testing()
set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

find_package(GTest)

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(
  ${TEST_PROJECT_NAME}
  PRIVATE
    GTest::gtest_main
    ${PROJECT_NAME}
)

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})
