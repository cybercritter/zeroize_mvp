cmake_minimum_required(VERSION 3.28)

# Project name
project(zeroize_app)

# Set C standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_FILES 
    src/main.cpp
    src/Object.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

set(SRC_Z_FILES src/zeroize.c)
add_library(zeroize STATIC ${SRC_Z_FILES})
target_include_directories(zeroize PUBLIC include)

# Add your source files here
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} zeroize)

# Enable testing
enable_testing()
include(CTest)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Example test
# print_message(STATUS "Adding test executable: ${PROJECT_SOURCE_DIR}/build/zeroize_test")
add_executable(zeroize_test tests/test_main.cpp tests/test_zeroize.cpp)
target_link_libraries(zeroize_test gtest_main zeroize)
target_include_directories(zeroize_test PRIVATE tests include)


include(GoogleTest)

# Discover tests
# This will automatically find all tests in the zeroize_test executable
# and register them with CTest.
# It assumes that you have defined tests using the GoogleTest framework.
gtest_discover_tests(zeroize_test)

add_subdirectory(src)
add_subdirectory(tests)
