cmake_minimum_required (VERSION 3.5)
set(CUNIT_VERSION_MAJOR 3)
set(CUNIT_VERSION_MINOR 0)
set(CUNIT_VERSION_PATCH 0)
set(CUNIT_VERSION "${CUNIT_VERSION_MAJOR}.${CUNIT_VERSION_MINOR}.${CUNIT_VERSION_PATCH}")
set(CUNIT_RELEASE cunity)

if (MSVC)
    # force assert() to work on release mode windows
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /UNDEBUG")
    message(STATUS "CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")
endif()

add_subdirectory(CUnit)
add_subdirectory(Examples)