#ifndef IP_ADDR_LIB
#define IP_ADDR_LIB

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>

using ipv4_addr 			= std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>;
using ipv4_addr_list_str 	= std::vector<std::vector<std::string>>;
using ipv4_addr_list  		= std::vector<ipv4_addr>;

// Превращаем строчный вариант списка в tuple
ipv4_addr_list parse(ipv4_addr_list_str&& list_str);

// Печать
void print(ipv4_addr_list ip_pool);

// Разбить строку на подстроки по разделителю
std::vector<std::string>  split(const std::string &str, char d);

// Фильтрация элементов
template<int N = 0>
ipv4_addr_list filter(const ipv4_addr_list& ip_pool) {
	return ip_pool;
}

template<int N = 0, class ...Args>
ipv4_addr_list filter(const ipv4_addr_list& ip_pool, int value, Args ...args) {
	ipv4_addr_list list;

	for (auto ip : ip_pool) {
		if (std::get<N>(ip) == value ) 
			list.emplace_back(ip);
	}

	return filter<N+1>(list, std::forward<Args>(args)...);
}

ipv4_addr_list filterAny(const ipv4_addr_list& ip_pool, int value);

#endif