project(CUnit C)

cmake_minimum_required (VERSION 3.2)

set(CUNIT_DISABLE_TESTS CACHE INTERNAL FALSE)
set(CUNIT_DISABLE_EXAMPLES CACHE INTERNAL FALSE)
if(CMAKE_CROSSCOMPILING)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
endif()

enable_testing()
set(CUNIT_CMAKE_INSTALL yes)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Werror=strict-prototypes")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /WX /wd4996")
endif()

add_subdirectory(CUnit)
if(NOT CUNIT_DISABLE_TESTS)
  add_subdirectory(Tests)
endif()

if(NOT CUNIT_DISABLE_EXAMPLES)
  add_subdirectory(Examples)
endif()
