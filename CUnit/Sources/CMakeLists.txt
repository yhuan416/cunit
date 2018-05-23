project(cunit C)

find_package(Curses)

FILE(GLOB Basic Basic/*.c)
FILE(GLOB Automated Automated/*.c)
FILE(GLOB Framework Framework/*.c)
FILE(GLOB Console Console/*.c)
FILE(GLOB Curses Curses/*.c)
FILE(GLOB Test Test/*.c)

set(cunit_srcs
        ${Basic}
        ${Automated}
        ${Framework}
        ${Console})

set(cunit_libs "")


if(CURSES_FOUND)
    list(APPEND cunit_srcs ${Curses})
    list(APPEND cunit_libs ${CURSES_LIBRARY})
else()
    message(WARNING "curses not found - curses support disabled")
endif(CURSES_FOUND)


add_library(cunit-static STATIC
        ${cunit_srcs})
target_link_libraries(cunit-static cunit_headers ${cunit_libs})
set_target_properties(cunit-static PROPERTIES OUTPUT_NAME cunit)

add_library(cunit SHARED
        ${cunit_srcs})
target_link_libraries(cunit cunit_headers ${cunit_libs})


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

