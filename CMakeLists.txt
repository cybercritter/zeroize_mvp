cmake_minimum_required(VERSION 3.28)

# Project name
project(zeroize)

# Set C standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_FILES 
    src/main.cpp
)

# Add your source files here
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Enable testing
include(CTest)
enable_testing()

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
add_executable(zeroize_test tests/test_main.cpp)
target_link_libraries(zeroize_test gtest_main)
add_test(NAME zeroize_test COMMAND zeroize_test)

add_subdirectory(src)
add_subdirectory(tests)
