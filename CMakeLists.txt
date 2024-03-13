# Minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Project name
project(MyProject)

# Find Boost Unit Test framework
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Add the executable target
add_executable(MyExecutable Main.cpp)

# Link against Boost Unit Test framework
target_link_libraries(MyExecutable Boost::unit_test_framework)
