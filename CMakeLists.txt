cmake_minimum_required(VERSION 3.14)
project(Hospital CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

file(GLOB LIBRARY_SOURCES CONFIGURE_DEPENDS Library/src/*.cpp)
add_library(HospitalLibrary STATIC ${LIBRARY_SOURCES})
target_include_directories(HospitalLibrary PUBLIC Library/include)

add_executable(HospitalConsole Console/src/main.cpp)
target_link_libraries(HospitalConsole PRIVATE HospitalLibrary)

option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS GoogleTests/*.cpp)
    add_executable(HospitalGoogleTests ${TEST_SOURCES})
    target_link_libraries(HospitalGoogleTests PRIVATE HospitalLibrary GTest::gtest_main)

    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(HospitalGoogleTests)
endif()
