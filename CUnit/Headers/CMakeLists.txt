project (CUnit_Headers C)

set (VERSION 2.2)
set (RELEASE cunity)

FILE(GLOB headerfiles *.h)

configure_file(CUnit.h.in ${PROJECT_BINARY_DIR}/generated-headers/CUnit.h @ONLY)

add_library(cunit_headers INTERFACE)
target_include_directories(cunit_headers INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}"
  "${PROJECT_BINARY_DIR}/generated-headers"
  )
target_sources(cunit_headers INTERFACE
  "${PROJECT_BINARY_DIR}/generated-headers"
  ${headerfiles})

