cmake_minimum_required(VERSION 3.20)

project(Task1TestsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(task1_lib
    src/Matrix.cpp
    src/RandomGenerator.cpp
    src/IStreamGenerator.cpp
    src/ConstantGenerator.cpp
    src/ZeroGenerator.cpp
    src/Exercise.cpp
    src/Task1.cpp
    src/Task2.cpp
)

target_include_directories(task1_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Task1Tests
    tests/Tests.cpp
)

target_link_libraries(Task1Tests
    PRIVATE
        task1_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Task1Tests)
