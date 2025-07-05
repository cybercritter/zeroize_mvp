cmake_minimum_required(VERSION 3.28)

# Project name
project(zeroize_app)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

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
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

include(CodeCoverage)
append_coverage_compiler_flags()

set(SRC_Z_FILES src/zeroize.c)
add_library(zeroize STATIC ${SRC_Z_FILES})
target_include_directories(zeroize PUBLIC include)

# Add your source files here
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} zeroize)

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}
)

# Enable testing
enable_testing()
include(CTest)

SETUP_TARGET_FOR_COVERAGE_LCOV(
  NAME coverage_report # Name for the custom target
  EXECUTABLE zeroize_test -j16 # Name of your test executable
  DEPENDENCIES zeroize # Ensure test executable is built first
  # Optional: Add EXCLUDE_DIRS or EXCLUDE_FILES for specific paths to ignore
)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include(GoogleTest)

# Example test
# print_message(STATUS "Adding test executable: ${PROJECT_SOURCE_DIR}/build/zeroize_test")
add_executable(zeroize_test tests/test_main.cpp tests/test_zeroize.cpp)
target_link_libraries(zeroize_test gtest_main zeroize)
target_include_directories(zeroize_test PRIVATE tests include)


set(BINARY_DIR ${CMAKE_BINARY_DIR})
# Set the output directory for the test executable
set_target_properties(zeroize_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BINARY_DIR}
) 
# Discover tests
# This will automatically find all tests in the zeroize_test executable
# and register them with CTest.
# It assumes that you have defined tests using the GoogleTest framework.
gtest_discover_tests(zeroize_test)

add_subdirectory(src)
add_subdirectory(tests)
