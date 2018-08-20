project (CUnit_Headers C)


FILE(GLOB headerfiles *.h)

configure_file(CUnit.h.in ${PROJECT_BINARY_DIR}/generated-headers/CUnit.h @ONLY)

add_library(cunit_headers INTERFACE)
target_include_directories(cunit_headers INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated-headers>
        $<INSTALL_INTERFACE:include/cunit>)

target_sources(cunit_headers INTERFACE
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated-headers/CUnit.h>
  $<BUILD_INTERFACE:${headerfiles}>)



install(TARGETS cunit_headers
        EXPORT FindCUnitHeaders
        LIBRARY DESTINATION include/cunit
        ARCHIVE DESTINATION include/cunit
        PUBLIC_HEADER DESTINATION include/cunit
        )
install(FILES ${headerfiles} ${PROJECT_BINARY_DIR}/generated-headers/CUnit.h
        DESTINATION include/cunit
        )

install(EXPORT FindCUnitHeaders
        DESTINATION share/cmake/cunit)
export(TARGETS cunit_headers FILE ${CMAKE_BINARY_DIR}/cmake/FindCUnitHeaders.cmake)