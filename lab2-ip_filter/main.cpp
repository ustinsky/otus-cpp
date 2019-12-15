// Дан набор строк, в каждой строке набор полей, разделенных символами \t
// text1 \t text2 \t text3 \n
//
// Надо:
// 1. Выбрать text1 и разбить его по октетам (разделитель точка)
// 2. Отсортировать в обратном лексиграфическом порядке
// 3. Выдать список адресов первый байт которых равен 1
// 4. Выдать список адресов 1 байт - 46, 2 байт - 70
// 5. Выдать список адресов где в любом месте байт = 46

#include "lib.h"

template<int N>
ipv4_addr_list filter(const ipv4_addr_list& ip_pool, int value);

// int main(int argc, char const *argv[]) 
int main() 
{
    try 
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string>  v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        ipv4_addr_list m_ip_pool = parse(std::move(ip_pool));
        std::sort(m_ip_pool.begin(), m_ip_pool.end(), std::greater<ipv4_addr>());
        print(m_ip_pool);
        
        ipv4_addr_list m_filtered_ip1 = filter(m_ip_pool, 1);
        print(m_filtered_ip1);
		auto m_filtered_ip2 = filter(m_ip_pool, 46, 70);
		print(m_filtered_ip2);
		auto m_filtered_ip3 = filterAny(m_ip_pool, 46);
		print(m_filtered_ip3);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}