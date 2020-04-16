project(CUnit C)

cmake_minimum_required (VERSION 3.2)
enable_testing()
set(CUNIT_CMAKE_INSTALL yes)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Werror=strict-prototypes")
endif()

add_subdirectory(CUnit)
add_subdirectory(Tests)
add_subdirectory(Examples)
