#define BOOST_TEST_MODULE test_parse

#include <iostream>
#include "../SimpleTimer.h"
#include <vector>
#include <numeric>
#include "../allocator.h"
#include "../smart_allocator.h"
#include "../simple_allocator.h"
#include "../list.h"
#include <string>
#include "../list.cpp"
#include <map>
#include <algorithm>

#include <boost/test/unit_test.hpp>

const int size_test = 100;
const int size_container = 1000;

template <class Alloc = std::allocator<int>>
void test_vector() {

    std::array<int64_t, size_test> time, time2;
	SimpleTimer timer("Vector Create", false);
    
    for (int i = 0; i < size_test; ++i) {
        auto v = std::vector<int, Alloc>{};
        timer.start("start");
        v.reserve(2 * size_container);
        for (size_t i = 0; i < size_container; ++i) {
            v.emplace_back(i);
        }
        time[i] = timer.stop();
    
        timer.start("Vector Use");
        int sum = 0; 
        for (auto i: v) {
            sum += i;
        }
        time2[i] = timer.stop();
    }

    std::cout << "Среднее время создания вектора: " << (std::accumulate(time.begin(), time.end(), 0) / (double) size_test) << std::endl;
    std::cout << "Среднее время сложения вектора: " << (std::accumulate(time2.begin(), time2.end(), 0) / (double) size_test) << std::endl;
}

template <class Alloc = std::allocator<int>>
void test_map() {
    std::array<int64_t, size_test> time, time2;
	SimpleTimer timer("Map Create", false);
    
    for (int j = 0; j < size_test; ++j) {
        auto m = std::map<int, int, std::less<int>, Alloc>{};
        for (size_t i = 0; i < size_container; ++i) {
            m[i] = i * i;
        }

        time[j] = timer.stop();
        timer.start("Map Select");
        int sum = 0;
        for (size_t i = 0; i < size_container; ++i) {
            sum += m[i];
        }
        time2[j] = timer.stop();
    }

    std::cout << "Среднее время создания map: " << (std::accumulate(time.begin(), time.end(), 0) / (double) size_test) << std::endl;
    std::cout << "Среднее время сложения map: " << (std::accumulate(time2.begin(), time2.end(), 0) / (double) size_test) << std::endl;
}

template <class Alloc = std::allocator<int>>
void test_list() {
    std::array<int64_t, size_test> time, time2;
	SimpleTimer timer("Map Create", false);
    
    for (int j = 0; j < size_test; ++j) {
	    linked_list<int, Alloc> L;

        for (int i = 0; i < 500; ++i ) {
		    L.emplace_back(i);
	    }
        time[j] = timer.stop();

        timer.start("List Print");
        L.move_front();
        auto tmp_size = L.size();
        for (size_t i = 0; i < tmp_size; ++i) {
            L.curr();
            L.move_next();
        }
        time2[j] = timer.stop();
    }

    std::cout << "Среднее время создания list: " << (std::accumulate(time.begin(), time.end(), 0) / (double) size_test) << std::endl;
    std::cout << "Среднее время сложения list: " << (std::accumulate(time2.begin(), time2.end(), 0) / (double) size_test) << std::endl;
}

BOOST_AUTO_TEST_SUITE(test_alloc)

    // Работа с вектором: Standard Allocator
    BOOST_AUTO_TEST_CASE(test_vector_standard)
    {
        std::cout << "Vector: Standart allocator" << std::endl;
        try {
            test_vector();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        }
        
    }


    // Работа с вектором: Simple Allocator
    BOOST_AUTO_TEST_CASE(test_vector_simple)
    {
        std::cout << "Vector: Simple allocator" << std::endl;
        try {
            test_vector<simple_allocator<int>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        }
        
        
    }

    // Работа с вектором: My Allocator
    BOOST_AUTO_TEST_CASE(test_vector_myalloc)
    {
        std::cout << "Vector: My allocator" << std::endl;
        try {
            test_vector<my_allocator<int>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        }
        
    }

    // Работа с вектором: Smart Allocator
    BOOST_AUTO_TEST_CASE(test_vector_smart)
    {
        std::cout << "Vector: Smart allocator" << std::endl;
        try {
            test_vector<smart_allocator<int, 20000 >>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        }
        
    }


    // Работа с map: Standard Allocator
    BOOST_AUTO_TEST_CASE(test_map_standard)
    {
        std::cout << "Map: Standard allocator" << std::endl;
        try {
            test_map();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        }    
    }

    // Работа с map: Simple Allocator
    BOOST_AUTO_TEST_CASE(test_map_simple)
    {
        std::cout << "Map: Simple allocator" << std::endl;
        try {
            test_map<simple_allocator<std::pair<const int, int>>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }

    // Работа с map: My Allocator
    BOOST_AUTO_TEST_CASE(test_map_myalloc)
    {
        std::cout << "Map: My allocator" << std::endl;
        try {
            test_map<my_allocator<std::pair<const int, int>>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }

    // Работа с map: Smart Allocator
    BOOST_AUTO_TEST_CASE(test_map_smart)
    {
        std::cout << "Map: Smart allocator" << std::endl;
        try {
            test_map<smart_allocator<std::pair<const int, int>>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }

    // Работа с Linked_List: Standard Allocator
    BOOST_AUTO_TEST_CASE(test_list_standard)
    {
        std::cout << "List: Standard allocator" << std::endl;
        try {
            test_list();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
    }

    // Работа с Linked_List: Simple Allocator
    BOOST_AUTO_TEST_CASE(test_list_simple)
    {
        std::cout << "List: Simple allocator" << std::endl;
        try {
            test_list<simple_allocator<int>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }

    // Работа с Linked_List: My Allocator
    BOOST_AUTO_TEST_CASE(test_list_myalloc)
    {
        std::cout << "List: My allocator" << std::endl;
        try {
            test_list<my_allocator<int>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }

    // Работа с Linked_List: Smart Allocator
    BOOST_AUTO_TEST_CASE(test_list_smart)
    {
        std::cout << "List: Smart allocator" << std::endl;
        try {
            test_list<smart_allocator<int>>();
            BOOST_CHECK( true );
        }
        catch (const std::exception &) {
            BOOST_CHECK( false );
        } 
        
    }


}