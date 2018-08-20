project(CUnit C)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(Headers)
add_subdirectory(Sources)


# Package Generator  #######################################################
set(CPACK_GENERATOR TGZ DEB)
set(CPACK_PACKAGE_NAME "cunit")
set(CPACK_PACKAGE_DESCRIPTION "CUnit")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The CUnity fork of the CUnit unit test framework")
set(CPACK_PACKAGE_VERSION_MAJOR "${CUNIT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CUNIT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CUNIT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "CUnity")
set(CPACK_PACKAGE_CONTACT "inorton@gmail.com")
set(CPACK_PACKAGE_FILE_NAME "cunit-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
include (CPack)