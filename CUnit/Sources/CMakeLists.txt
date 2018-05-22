project(cunit C)

find_package(Curses)

FILE(GLOB Basic Basic/*.c)
FILE(GLOB Automated Automated/*.c)
FILE(GLOB Framework Framework/*.c)
FILE(GLOB Console Console/*.c)
FILE(GLOB Curses Curses/*.c)


add_library(cunit STATIC
  ${Basic}
  ${Automated}
  ${Framework}
  ${Console}
  )

if(CURSES_FOUND)
  target_sources(cunit PUBLIC ${Curses})
  target_link_libraries(cunit ${CURSES_LIBRARY})
else()
message(WARNING "curses not found - curses support disabled")
endif(CURSES_FOUND)

target_link_libraries(cunit cunit_headers)
