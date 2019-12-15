#include <iostream>
#include "SimpleTimer.h"
#include <vector>
#include "allocator.h"
#include "smart_allocator.h"
#include "simple_allocator.h"
#include "list.h"
#include <string>
#include "list.cpp"
#include <map>

constexpr size_t size_container = 1000;
constexpr size_t size_container_map = 1000000;

template <class T, class Alloc = std::allocator<T>>
void test_vector_alloc_1(std::string msg); 

template <class T, class Alloc = std::allocator<std::pair<const T, T>>>
void test_map_alloc_1(std::string msg);

template <class T, class Alloc = std::allocator<T>>
void test_list_alloc_1(std::string msg); 

template <class T, class Alloc = std::allocator<T>>
void test_vector_alloc_2(std::string msg);

template <class T, class Alloc = std::allocator<std::pair<const T, T>>>
void test_map_alloc_2(std::string msg);

template <class T, class Alloc = std::allocator<T>>
void test_list_alloc_2(std::string msg);

int test();