#include "print_ip.h"



int main() {
	char c = -1;
	print_ip(char(-1));

	print_ip(c);
	print_ip(5);
	print_ip(short(0));
	print_ip(int(2130706433));
	print_ip(long(8875824491850138409));
	print_ip(int(140000302));
	print_ip(std::string("1.2.3.4"));
	print_ip("1.2.3.4");
	print_ip(std::vector<int>{1,2,3,4});
	print_ip(std::list<int>{1,2,3,4});
	print_ip(std::list<char>{1,2,3,4});
	
	print_ip(std::tuple<int, int, int, int, int, int, int, int, int, int>{1,2,3,4,5,6,7,8,9,10});
	print_ip(std::tuple<u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char>{1,2,3,4,5,6,7,8,9,10});
	print_ip(std::tuple<long int, long int, long int, long int>{8875824491850138409,8875824491850138410,8875824491850138411,8875824491850138412});
	print_ip(std::tuple<u_char, u_char, u_char, u_char>{1,2,3,4});
	print_ip(std::tuple<uint8_t, uint32_t, uint8_t> {1, 2, 3});
	print_ip(std::tuple<u_char, u_char, int, u_char>{4,5,6,7});



   	return 0;
}