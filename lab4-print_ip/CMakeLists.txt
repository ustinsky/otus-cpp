cmake_minimum_required(VERSION 3.2)

message("$ENV{TRAVIS_BUILD_NUMBER} = " $ENV{TRAVIS_BUILD_NUMBER})
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.1)
endif()
find_package(GTest REQUIRED)
find_package (Threads REQUIRED)


add_executable(print_ip main.cpp)
add_executable(print_test print_ip.h test.cpp)

target_link_libraries(print_test ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(print_ip print_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror"
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lex@mapha.org)

include(CPack)

enable_testing()

add_test(test print_test)

