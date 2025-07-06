
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
set(CMAKE_BUILD_TYPE Debug)

set(SRC_FILES
    src/main.cpp
    src/Object.cpp
)


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
include(GoogleTest)

# Example test
# print_message(STATUS "Adding test executable: ${PROJECT_SOURCE_DIR}/build/zeroize_test")
add_executable(zeroize_test tests/test_main.cpp tests/test_zeroize.cpp)
target_link_libraries(zeroize_test gtest_main zeroize)
target_include_directories(zeroize_test PRIVATE tests include)
target_compile_options(zeroize_test PRIVATE -Wall -Wextra -Wpedantic -Werror -fprofile-arcs -ftest-coverage)
target_compile_options(zeroize_test PRIVATE -coverage)
target_link_options(zeroize_test PRIVATE -fprofile-arcs -ftest-coverage)


# Discover tests
# This will automatically find all tests in the zeroize_test executable
# and register them with CTest.
# It assumes that you have defined tests using the GoogleTest framework.
gtest_discover_tests(zeroize_test)


include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
  NAME coverage_report
  EXECUTABLE ctest -j 4 --output-on-failure
  # The EXECUTABLE command runs the tests and generates coverage data.
  DEPENDENCIES zeroize
  EXCLUDE_FROM_ALL TRUE
)

set(COVERAGE_EXCLUDES 'external_dependencies/*')

# # Add a custom target to generate the coverage report
# add_custom_target(coverage_report ALL
#   COMMAND lcov -capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info
#   COMMAND lcov --remove coverage.info '/usr/*' '*/googletest/*'
#   COMMAND lcov --remove coverage.info '*/tests/*' '*/src/zeroize.c' '*/src/Object.cpp'
#   COMMAND genhtml coverage.info --output-directory coverage_report
#   VERBATIM
#   USES_TERMINAL
#   # The WORKING_DIRECTORY is set to the binary directory to ensure that the lcov command
#   # can find the coverage data files generated during the build.
#   # This is important for the lcov command to work correctly.
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#   COMMENT "Generating coverage report"
# )

add_dependencies(coverage_report zeroize_test
  # This ensures that the coverage report is generated after the tests are built.
  # The zeroize_test target must be built before generating the coverage report.
  zeroize
  # This ensures that the zeroize library is built before generating the coverage report.)
)

# Add subdirectories for source and tests
# This allows for better organization of the project structure.
# You can create a src directory for your source files and a tests directory for your test files
add_subdirectory(src)
add_subdirectory(tests)
