enable_testing()

find_package(GTest)

add_executable(hello_test src/main.cpp)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
