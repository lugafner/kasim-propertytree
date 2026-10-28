cmake_minimum_required(VERSION 3.14)
project(propertytree VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(propertytree
    src/PropertyTree.cpp
    src/PropertyNode.cpp
)
target_include_directories(propertytree PUBLIC include)

# Tests — only built when configured as the top-level project, so the
# test targets and their FetchContent dependencies (doctest) are not
# pulled in when the library is consumed via add_subdirectory / submodule.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  enable_testing()
  add_subdirectory(tests)
endif()