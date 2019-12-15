cmake_minimum_required(VERSION 3.2) 

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)


add_executable(ip_filter main.cpp)
add_library(ip_filter_lib lib.cpp)

set_target_properties(ip_filter ip_filter_lib  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)


target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lex@mapha.org)

include(CPack)

enable_testing()

# add_test(test_parse test_parse)
# add_custom_command(COMMAND "git submodule add https://github.com/google/googletest.git")
# add_subdirectory(googletest)
add_subdirectory(test)