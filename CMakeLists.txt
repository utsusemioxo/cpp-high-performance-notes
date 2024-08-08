cmake_minimum_required(VERSION 3.20)

# Project name
project(my_testbed)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(benchmark_example benchmark_main.cpp)

add_executable(test_example test_main.cpp)

set(BENCHMARK_ENABLE_TESTING NO)

include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.5
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip

)

FetchContent_MakeAvailable(benchmark googletest)

target_link_libraries(benchmark_example benchmark::benchmark)
target_link_libraries(test_example GTest::gtest GTest::gtest_main)

add_custom_target(run_tests COMMAND test_example)
