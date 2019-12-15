cmake_minimum_required(VERSION 3.2)

message("$ENV{TRAVIS_BUILD_NUMBER} = " $ENV{TRAVIS_BUILD_NUMBER})
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(helloworld VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
# add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli helloworld  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)


target_link_libraries(helloworld_cli PRIVATE
    helloworld
)


if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    # target_compile_options(test_version PRIVATE
    #     /W4
    # )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(test_version PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lex@mapha.org)

include(CPack)

enable_testing()

# add_test(test_version test_version)
# add_custom_command(COMMAND "git submodule add https://github.com/google/googletest.git")
add_subdirectory(googletest)
add_subdirectory(test)