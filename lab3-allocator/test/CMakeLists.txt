cmake_minimum_required(VERSION 3.8)

set(bTest boostTest)

set(Sources_bTest 
    test-alloc.cpp 
)

add_executable(${bTest} ${Sources_bTest})

set_target_properties(${bTest} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(${bTest}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${bTest} PRIVATE
        /W4
    )
else ()
    target_compile_options(${bTest} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(
    ${bTest}
    ${Boost_LIBRARIES}
    allocator_lib
)


target_include_directories(
    ${bTest}
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/..
)

add_test(
    Name ${bTest}
    COMMAND ${bTest}
)