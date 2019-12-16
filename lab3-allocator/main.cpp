#include "test.h"

int factorial(int n) {
    if ( n == 0 )
        return 1; 
    else {
        return n * factorial(n - 1);
    }
}


int main() {
    // return test();

    test();

    // Map
    auto m = std::map<int, int>{};
    for (size_t i = 0; i < 10; ++i) {
        m[i] = factorial(i);
    }

    auto m2 = std::map<int, int, std::less<int>, smart_allocator<std::pair<const int, int>>>{};
    for (size_t i = 0; i < 10; ++i) {
        m2[i] = i;
    }

    // Вывод значений
    for (auto v: m) {
        std::cout << v.first << " " << v.second << std::endl;
    }

    std::cout << std::endl;

    for (auto v: m) {
        std::cout << v.first << " " << v.second << std::endl;
    }

    std::cout << std::endl;


    // List
    linked_list<int> l1;
    for (int i = 0; i < 10; ++i ) {
		l1.emplace_back(i);
	}
    
    linked_list<int, smart_allocator<int>> l2;
    for (int i = 0; i < 10; ++i ) {
		l2.emplace_back(i);
	}

    // Вывод значений
    l1.move_front();
    l2.move_front();

    for (int i = 0; i < 10; ++i) {
        std::cout << l1.curr() << std::endl;
        l1.move_next();
    } 

    std::cout << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << l2.curr() << std::endl;
        l2.move_next();
    } 

    return 0;
}