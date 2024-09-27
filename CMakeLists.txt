cmake_minimum_required(VERSION 3.16)
project(LogLib LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add an executable or library as needed
add_library(LogLib SHARED src/Log.cpp src/Log.hpp)

# Specify include directories for the library
target_include_directories(LogLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS LogLib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
