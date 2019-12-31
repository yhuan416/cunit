project(CUnit C)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "-Werror -Wall")
endif()

cmake_minimum_required (VERSION 3.2)
enable_testing()
set(CUNIT_CMAKE_INSTALL yes)

add_subdirectory(CUnit)
add_subdirectory(Examples)
