// Дан набор строк, в каждой строке набор полей, разделенных символами \t
// text1 \t text2 \t text3 \n
//
// Надо:
// 1. Отсортировать в обратном лексиграфическом порядке
// 2. Выдать список адресов первый байт которых равен 1
// 3. Выдать список адресов 1 байт - 46, 2 байт - 70
// 4. Выдать список адресов любо байт = 46


#include "lib.h"
#define USE_PRETTY 1

// Превращаем строчный вариант списка в tuple<char, char, char, char>
// Согласно стандарту для IPv4 и для IPv6 можно пропускать некоторые октеты
// То есть значение 4.6 - это корректная запись ipv4 адреса. 
// Размер вектора list_str м.б. от 2 до 4 октетов
// По стандарту можно ip адрес задавать и одним числом
// Но для простоты на прием будем принимать от 2 до 4 октетов
// ping 8.8 => ping 8.0.0.8
// ping 8.8.8 => ping 8.8.0.8
// ping 8.8.8.8
ipv4_addr_list parse(ipv4_addr_list_str&& list_str) {
	
	ipv4_addr_list list;
	std::vector<unsigned char> octets(4);

	try {
		
		for (auto ip_str : list_str) {
			int m_size = ip_str.size();
			if ((ip_str.size() >= 2) && (ip_str.size() <= 4)) {
				
				for (int i = 0; i < m_size; ++i) {			
			 		int a = std::stoi(ip_str[i]); 
					
				 	if 	( a >= 0 && a <= 255) {
				 		octets[i] = a;
					} else {
						throw std::exception();
					}
				}
				
				switch(m_size) {
					case 2:
						// list.push_back({octets[0], 0, 0, octets[1]});
						list.emplace_back(ipv4_addr{octets[0], 0, 0, octets[1]});
						break;

					case 3:
						// list.push_back({octets[0], octets[1], 0, octets[2]});
						list.emplace_back(ipv4_addr{octets[0], octets[1], 0, octets[2]});
						break;

					case 4:
						// list.push_back({octets[0], octets[1], octets[2], octets[3]});
						list.emplace_back(ipv4_addr{octets[0], octets[1], octets[2], octets[3]});
						break;	
				}			
			} else {
				std::cerr << "error: " << "Число элементов < 2" << std::endl;
				assert(m_size > 1);
			}
		}
	} 
	catch(const std::exception &e) {
        std::cerr << "error: " << __PRETTY_FUNCTION__ << ":" << "Ошибка при разборе ip адреса" << std::endl;
		std::cerr << e.what() << std::endl;
		throw std::exception();
    } 

	return list;
}

// Печать
void print(ipv4_addr_list ip_pool)
{
	// std::cout << ip_pool.size() << std::endl;
	for(auto ip : ip_pool) 
	{ 
        std::cout <<  (int)std::get<0>(ip) << '.' 
        		  <<  (int)std::get<1>(ip) << '.' 
        		  <<  (int)std::get<2>(ip) << '.'
        		  <<  (int)std::get<3>(ip) << std::endl;
    }
}

std::vector<std::string>  split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));
    return r;
}

ipv4_addr_list filterAny(const ipv4_addr_list& ip_pool, int value) {
	ipv4_addr_list list;

	for (auto ip : ip_pool) {
		if (std::get<0>(ip) == value ) 
			list.emplace_back(ip);
		else if (std::get<1>(ip) == value ) 
			list.emplace_back(ip);
		else if (std::get<2>(ip) == value ) 
			list.emplace_back(ip);
		else if (std::get<3>(ip) == value ) 
			list.emplace_back(ip);
	}

	return list;
}
