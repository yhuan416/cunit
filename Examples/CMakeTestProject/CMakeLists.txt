cmake_minimum_required(VERSION 3.5)

find_package(CUnit MODULE REQUIRED)
find_package(CUnitHeaders MODULE REQUIRED)



add_executable(test-program test-program.c)
target_link_libraries(test-program cunit)