#define BOOST_TEST_MODULE test_parse

#include "../lib.h"
#include <vector>
#include <iostream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_parse)

    // Error IP address 1
    BOOST_AUTO_TEST_CASE(test_split_err_ip)
    {
        auto  v = split("8.4.vasya.123", '.');
        BOOST_TEST_MESSAGE("v[0]: " << v.at(0));
        BOOST_CHECK( (v.size() == 4 ) && ( v.at(0) == "8") && ( v.at(1) == "4") && ( v.at(2) == "vasya") && ( v.at(3) == "123"));
        
    }

    BOOST_AUTO_TEST_CASE(test_parse_err_ip1)
    {
        BOOST_TEST_MESSAGE("IP адрес 8.4.vasya.123 - Должен вызвать исключение");
        try {
            auto v = split("8.4.vasya.123", '.');
            auto lst = parse(ipv4_addr_list_str{v});
            BOOST_CHECK( false );
        } 
        catch (const std::exception &e) {
            BOOST_TEST_MESSAGE("\n");
            BOOST_CHECK( true );
        }
    }

    // Error IP address 2
    BOOST_AUTO_TEST_CASE(test_split_err_ip2)
    {
        auto  v = split("8.4.258.123", '.');
        BOOST_TEST_MESSAGE("v[0]: " << v.at(0));
        BOOST_CHECK( (v.size() == 4 ) && ( v.at(0) == "8") && ( v.at(1) == "4") && ( v.at(2) == "258") && ( v.at(3) == "123"));
        
    }

    BOOST_AUTO_TEST_CASE(test_parse_err_ip2)
    {
        BOOST_TEST_MESSAGE("IP адрес 8.4.vasya.123 - Должен вызвать исключение");
        try {
            auto v = split("8.4.258.123", '.');
            auto lst = parse(ipv4_addr_list_str{v});
            BOOST_CHECK( false );
        }
        catch (const std::exception &e) {
            BOOST_TEST_MESSAGE("\n");
            BOOST_CHECK( true );
        }
    }

    // 2 position
    BOOST_AUTO_TEST_CASE(test_split_2pos)
    {
        auto  v = split("8.4", '.');
        BOOST_TEST_MESSAGE("v[0]: " << v.at(0));
        BOOST_CHECK( (v.size() == 2 ) && ( v.at(0) == "8") && ( v.at(1) == "4"));
    }

    BOOST_AUTO_TEST_CASE(test_parse_2pos)
    {
        auto v = split("8.4", '.');
        auto lst = parse(ipv4_addr_list_str{v});
        BOOST_CHECK(lst.size() == 1);
    }


    // 3 position

    BOOST_AUTO_TEST_CASE(test_split_3pos)
    {
        auto  v = split("8.4.2", '.');
        BOOST_TEST_MESSAGE("v[0]: " << v.at(0));
        BOOST_CHECK( (v.size() == 3 ) && ( v.at(0) == "8") && ( v.at(1) == "4") && ( v.at(2) == "2"));
    }

    BOOST_AUTO_TEST_CASE(test_split_4pos)
    {
        auto v = split("8.4.2", '.');
        auto lst = parse(ipv4_addr_list_str{v});
        BOOST_CHECK(lst.size() == 1);
    }

    // 4 position

    BOOST_AUTO_TEST_CASE(test_parse_3pos)
    {
        auto  v = split("8.4.2.1", '.');
        BOOST_TEST_MESSAGE("v[0]: " << v.at(0));
        BOOST_CHECK( (v.size() == 4 ) && ( v.at(0) == "8") && ( v.at(1) == "4") && ( v.at(2) == "2") && ( v.at(3) == "1"));
    }

    BOOST_AUTO_TEST_CASE(test_parse_4pos)
    {
        auto v = split("8.4.2.1", '.');
        auto lst = parse(ipv4_addr_list_str{v});
        BOOST_CHECK(lst.size() == 1);
    }

}