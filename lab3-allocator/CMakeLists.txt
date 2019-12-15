cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)


add_executable(allocator main.cpp )
add_library(allocator_lib test.cpp SimpleTimer.cpp list.cpp )

set_target_properties(allocator allocator_lib  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(allocator_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)


target_link_libraries(allocator PRIVATE
    allocator_lib
)


if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator_lib PRIVATE
        -Wall 
        -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

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