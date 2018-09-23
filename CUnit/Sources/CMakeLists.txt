project(cunit C)

find_package(Curses)

FILE(GLOB Basic Basic/*.c)
FILE(GLOB Automated Automated/*.c)
FILE(GLOB Framework Framework/*.c)
FILE(GLOB Console Console/*.c)
FILE(GLOB Curses Curses/*.c)
FILE(GLOB Test Test/*.c)
FILE(GLOB CI CI/*.c)

set(cunit_srcs
        ${Basic}
        ${Automated}
        ${CI}
        ${Framework}
        ${Console}
        )

set(cunit_libs "")


if(NOT APPLE AND NOT WIN32)
    if(CURSES_FOUND)
        list(APPEND cunit_srcs ${Curses})
        list(APPEND cunit_libs ${CURSES_LIBRARY})
    else()
        message(WARNING "curses not found - curses support disabled")
    endif(CURSES_FOUND)
endif()


add_library(cunit STATIC
        ${cunit_srcs})
target_link_libraries(cunit PUBLIC cunit_headers)
target_link_libraries(cunit PUBLIC ${cunit_libs})



install(TARGETS cunit
        EXPORT FindCUnit
        LIBRARY DESTINATION lib/cunit
        ARCHIVE DESTINATION lib/cunit
        )
install(EXPORT FindCUnit
        DESTINATION share/cmake/cunit)
export(TARGETS cunit FILE ${CMAKE_BINARY_DIR}/cmake/FindCUnit.cmake)

# for internal test program
add_executable(cunit_test
        ${cunit_srcs}
        ${Test}
        )

target_include_directories(cunit_test PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Framework
        ${CMAKE_CURRENT_LIST_DIR}/Test
        )
target_link_libraries(cunit_test
        cunit_headers
        ${cunit_libs})
set_target_properties(cunit_test
        PROPERTIES COMPILE_FLAGS "-DCUNIT_BUILD_TESTS -DMEMTRACE -DCUNIT_DO_NOT_DEFINE_UNLESS_BUILDING_TESTS")

