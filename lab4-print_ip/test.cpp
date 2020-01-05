#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>
#include "print_ip.h"
#include <sstream>

/*! 
    \brief Тестирование print_ip: передача строки
*/
TEST(print_ip, string) {
    std::ostringstream m_ostring;
    print_ip("1.1.1.1", false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "1.1.1.1");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи целочисленный переменной: знаковый char
*/
TEST(print_ip, signed_char) {
    std::ostringstream m_ostring;
    print_ip(char(-1), false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "255");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи целочисленный переменной: short 
*/
TEST(print_ip, short) {
    std::ostringstream m_ostring;
    print_ip(short(0), false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "0.0");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи целочисленный переменной: int
*/
TEST(print_ip, int) {
    std::ostringstream m_ostring;
    print_ip(int(2130706433), false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "127.0.0.1");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи целочисленный переменной: long
*/
TEST(print_ip, long) {
    std::ostringstream m_ostring;
    print_ip(long(8875824491850138409), false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "123.45.67.89.101.112.131.41");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи контейнера: vector
*/
TEST(print_ip, vector) {
    std::ostringstream m_ostring;
    print_ip(std::vector<u_char>{2,3,4,5}, false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "2.3.4.5");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи контейнера: list
*/
TEST(print_ip, list) {
    std::ostringstream m_ostring;
    print_ip(std::list<u_char>{3,4,5,6}, false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "3.4.5.6");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи tuple
*/
TEST(print_ip, tuple1) {
    std::ostringstream m_ostring;
    print_ip(std::tuple<u_char, u_char, u_char, u_char>{4,5,6,7}, false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "4.5.6.7");
}

/*! 
    \brief Тестирование print_ip: Тестирование передачи tuple - Разные типы
*/
TEST(print_ip, tuple2) {
    std::ostringstream m_ostring;
    print_ip(std::tuple<u_char, u_char, int, u_char>{4,5,6,7}, false, m_ostring);

    EXPECT_EQ(m_ostring.str(), "4.5.0.0.0.6.7");
}

/*! 
    \brief Запуск процесса тестирования
*/
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

