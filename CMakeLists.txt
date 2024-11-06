cmake_minimum_required(VERSION 3.29)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(test VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(test_cli main.cpp
        lib.cpp
        lib.h
        test_version.cpp
        lib.cpp)
add_library(test lib.cpp
        lib.cpp
        lib.h
        test_version.cpp
        lib.cpp
        lib.cpp)
set_executable(test_version test_version.cpp)

set_target_properties(test_cli test test_version PROPERTIES
    CXX_STANDART 14
    CXX_STARNDART_REQUIRED ON
)
target_include_directories(test
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_tests_properties(test_version PROPERTIES
    COMPILE_DEFENITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(test_cli PRIVATE
    test
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    test
)

if (MSVC)
    target_compile_options(test_cli PRIVATE
        /W4
    )
    target_compile_options(test PRIVATE
    /W4
    )
    target_compile_options(test_version PRIVATE
    /W4
    )
else ()
    target_compile_options(test_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif ()

install(TARGETS test_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPack)

enable_testing()

add_test(test_version test_version)