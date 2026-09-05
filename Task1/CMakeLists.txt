cmake_minimum_required(VERSION 3.20)

project(Task1TestsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project code as a library.
# Main.cpp is intentionally NOT included: Google Test supplies its own main().
add_library(task1_lib
    src/Matrix.cpp
    src/RandomGenerator.cpp
    src/IStreamGenerator.cpp
    src/ConstantGenerator.cpp
    src/ZeroGenerator.cpp
    src/Exercise.cpp
    src/ExerciseVariant7.cpp
)

target_include_directories(task1_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Download GoogleTest automatically on the first CMake configure.
include(FetchContent)

# Important for MSVC: use the same CRT mode as the project.
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
