#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <array>
#include <type_traits>
#include <cstring>
#include <typeinfo>

/*! 
    \brief Шаблонная функция print_ip для целочисленных значений
    \param T - целочисленный тип (int, short, long, char)
    \param ip - значение ip адреса заданное числом
    \param flag_bool - определяет печать в конце разделитель строки (true) или нет (false). По умолчанию печатать.
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/

template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(T ip, bool flag_line = true, std::ostream& m_stream = std::cout) {
	constexpr size_t m_size_type = sizeof(T);
	
	// // for
	// for (auto i = m_size_type; i > 0 ; --i) {
	// 	m_stream << ((ip >> (8 * (i - 1))) & 0xff) <<  ( i !=  1 ? "." : "");
	// }
	
	// memcpy - 2-ое решение
	std::array<unsigned char, m_size_type> bytes;	
	std::memcpy(bytes.data(), &ip, m_size_type);
	
	for(auto i = m_size_type - 1; i > 0; --i) {
        m_stream << std::to_string(bytes.at(i)) << ".";
    }	
	m_stream  << std::to_string(bytes.at(0));

    if (flag_line)
		m_stream << std::endl;
}

/*! 
    \brief Шаблонная функция print_ip для Векторов и списков
    \param T - тип элемента заданный вектором (std::vector) или списком (std::list)
    \param cont - значение ip адреса заданное вектором или списком. 
    \param flag_bool - определяет печать в конце разделитель строки (true) или нет (false). По умолчанию печатать.
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/
template<class T>
typename std::enable_if<std::is_same<T, std::vector <typename T::value_type> >::value
					   || std::is_same<T, std::list <typename T::value_type> >::value>::type 
print_ip(T cont, bool flag_line = true, std::ostream& m_stream = std::cout) {
// 
	// последний элемент. После него точка не нужна
	auto prev = --(cont.end()); 

	// Проходимся циклом
	for (auto curr = cont.begin(); curr != cont.end(); ++curr) {
		m_stream << std::to_string(*curr) << (curr != prev ? "." : "");
	}
	if (flag_line)
		m_stream << std::endl;
}


/*! 
    \brief Шаблонная функция print_ip для строк
    \param str - значение ip адреса заданное строкой. 
    \param flag_bool - определяет печать в конце разделитель строки (true) или нет (false). По умолчанию печатать.
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/
void print_ip(std::string str, bool flag_line = true, std::ostream& m_stream = std::cout) {
	m_stream << str;
	if (flag_line)
		m_stream << std::endl;
}


// Для tuple

/*! 
    \brief Рекурсивная шаблонная функция ip_iterator::print_ip_tuple

    \detail Рекурсивная шаблонная функция ip_iterator::print_ip_tuple предназначена для
            "раскручивания" всех переданных параметров tuple и формирования строки ip адреса 
    \param N - количество переданных параметров(типов) tuple.
    \param Args - типы элементов tuple
    \param tup - значение ip адреса заданное в виде std::tuple<Args...> 
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/

template <int N, typename ...Args>
struct ip_iterator {
	static void print_ip_tuple(const std::tuple<Args...>& tup, std::ostream& m_stream = std::cout) {
		ip_iterator<N - 1, Args ...>::print_ip_tuple(tup, m_stream);
		m_stream << ".";
		print_ip(std::get<N>(tup), false, m_stream);
	}
};

/*! 
    \brief Рекурсивная шаблонная функция ip_iterator::print_ip_tuple для последнего элемента

    \detail Рекурсивная шаблонная функция ip_iterator::print_ip_tuple предназначена для
            "раскручивания" всех переданных параметров tuple и формирования строки ip адреса 
    \param Args - типы элементов tuple
    \param tup - значение ip адреса заданное в виде std::tuple<Args...> 
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/
template<typename ...Args>
struct ip_iterator<0, Args...> {
	static void print_ip_tuple(const std::tuple<Args...>& tup, std::ostream& m_stream = std::cout) {
		print_ip(std::get<0>(tup), false, m_stream);
	}	
};


/*! 
    \brief Шаблонная функция print_ip для tuple
    \param Args - типы элементов tuple
    \param ip - значение ip адреса заданное вектором или списком. 
    \param flag_bool - определяет печать в конце разделитель строки (true) или нет (false). По умолчанию печатать.
    \param m_stream - поток вывода (По умолчанию std::cout)
    \return Ничего не возвращает. Печатает в поток значение ip адреса
*/
template<typename ...Args>
void print_ip(std::tuple<Args...> ip, bool flag_line = true, std::ostream& m_stream = std::cout) {
	constexpr int tuple_size = std::tuple_size<std::tuple<Args...>>::value; 
	ip_iterator<tuple_size - 1, Args...>::print_ip_tuple(ip, m_stream);
	if (flag_line)
        m_stream << std::endl;
}