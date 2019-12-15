#include "test.h"

template <class T, class Alloc = std::allocator<T>>
void test_vector_alloc_1(std::string msg) {
	std::cout << "=============================================================" << std::endl;
	std::cout << "vector with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("Vector Create");
	auto v = std::vector<T, Alloc>{};
    v.reserve(size_container);
    for (size_t i = 0; i < size_container; ++i) {
        v.emplace_back(T(i));
    }
    timer.stop();

    timer.start("VectorShow");
    int sum = 0; 
    for (auto i: v) {
        sum += i;
        // std::cout << i << std::endl;
    }
}

template <class T, class Alloc = std::allocator<std::pair<const T, T>>>
void test_map_alloc_1(std::string msg) {
	std::cout << "=============================================================" << std::endl;
	std::cout << "map with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("Map Create");
	auto m = std::map<int, int, std::less<T>, Alloc>{};
    for (size_t i = 0; i < size_container_map; ++i) {
        m[i] = i;
    }

    timer.stop();
    SimpleTimer timer2("Map Select");
    int sum = 0;
    for (size_t i = 0; i < size_container_map; ++i) {
        sum += m[i];
    }
    std::cout << "sum:" << sum << std::endl;
}

template <class T, class Alloc = std::allocator<T>>
void test_list_alloc_1(std::string msg) {
	
	std::cout << "=============================================================" << std::endl;
	std::cout << "list with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("List Create");
	linked_list<int, Alloc> L;
	
	L.print();
    for (int i = 0; i < 500; ++i ) {
		L.emplace_back(i);
	}
    L.move_front();
	L.curr() = 5;
	L.move_next();
	L.curr() = 6;
	L.move_next();
    // L.insert(7);
    std::cout << L.curr() << std::endl;
    timer.stop();

    SimpleTimer timer2("List Print");
    L.print();
    std::cout << "size:" << L.size() << std::endl;
    timer2.stop();
    L.clear();
    L.emplace_back(1);
    L.emplace_back(2);
    L.emplace_back(3);
    L.print();
    std::cout << "size:" << L.size() << std::endl;
}

template <class T, class Alloc = std::allocator<T>>
void test_vector_alloc_2(std::string msg) {
	std::cout << "=============================================================" << std::endl;
	std::cout << "vector with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("Vector Create");
	auto v = std::vector<T, Alloc>{};
    v.reserve(size_container);
    for (size_t i = 0; i < size_container; ++i) {
        v.emplace_back(T(i));
    }
    timer.stop();

    timer.start("VectorShow");
    v.erase(v.begin() + 15);
    v.insert(v.begin() + 10, 15);
    int sum = 0;
    for (auto i: v) {
        sum += i;
        // std::cout << i << std::endl;
    }
}

template <class T, class Alloc = std::allocator<std::pair<const T, T>>>
void test_map_alloc_2(std::string msg) {
	std::cout << "=============================================================" << std::endl;
	std::cout << "map with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("Map Create");
	auto m = std::map<int, int, std::less<T>, Alloc>{};
    for (size_t i = 0; i < size_container_map; ++i) {
        m[i] = i * i;
    }

    timer.stop();
    SimpleTimer timer2("Map Select");
    m.erase(m.begin());
    m[12] = 18;
    int sum = 0;
    for (size_t i = 0; i < size_container_map; ++i) {
        sum += m[i];
    }
    std::cout << "sum:" << sum << std::endl;
}

template <class T, class Alloc = std::allocator<T>>
void test_list_alloc_2(std::string msg) {
	
	std::cout << "=============================================================" << std::endl;
	std::cout << "list with " + msg + " alloc" << std::endl;
	std::cout << "=============================================================" << std::endl;
	SimpleTimer timer("List Create");
	linked_list<int, Alloc> L;
	
	L.print();
    for (int i = 0; i < 500; ++i ) {
		L.emplace_back(i);
	}
    L.move_front();
	L.curr() = 5;
	L.move_next();
	L.curr() = 6;
	L.move_next();
    L.insert(7);
    L.move_next();
    L.erase();
    L.insert(8);
    std::cout << L.curr() << std::endl;
    timer.stop();

    SimpleTimer timer2("List Print");
    L.print();
    std::cout << "size:" << L.size() << std::endl;
    timer2.stop();
    L.clear();
    L.emplace_back(1);
    L.emplace_back(2);
    L.emplace_back(3);
    L.print();
    std::cout << "size:" << L.size() << std::endl;
}

int test() {
    // Вектора
    test_vector_alloc_1<int>("Standard");
    test_vector_alloc_1<int, simple_allocator<int>>("Simple");
    test_vector_alloc_1<int, my_allocator<int>>("My");
    test_vector_alloc_1<int, smart_allocator<int>>("Smart");
    
    // Map
    test_map_alloc_1<int>("Std");
    test_map_alloc_1<int, simple_allocator<std::pair<const int, int>>>("Simple");
    test_map_alloc_1<int, my_allocator<std::pair<const int, int>>>("My");
    test_map_alloc_1<int, smart_allocator<std::pair<const int, int>>>("Smart");
	
    // Свой список
    test_list_alloc_1<int>("Std");
    test_list_alloc_1<int, simple_allocator<int>>("Simple");
    test_list_alloc_1<int, my_allocator<int>>("My");
    test_list_alloc_1<int, smart_allocator<int>>("Smart");

    // Тестирование с передислокации и удалением и вставкой элементов
    // Аллокатор "My" не участвует - т.к. он не предназначен для операции insert и delete элементов 
    // структур данных. Его выделение памяти происходит линейно. Он не может освободить
    // произвольный элемент памяти. Также при передислокации он работает не правильно.
    // Такая модель не подходит для решения таких задач.

    // Вектора
    test_vector_alloc_2<int>("Standard");
    test_vector_alloc_2<int, simple_allocator<int>>("Simple");
    test_vector_alloc_2<int, smart_allocator<int>>("Smart");
    
    // Map
    test_map_alloc_2<int>("Std");
    test_map_alloc_2<int, simple_allocator<std::pair<const int, int>>>("Simple");
    test_map_alloc_2<int, smart_allocator<std::pair<const int, int>>>("Smart");
	
    // Свой список
    test_list_alloc_2<int>("Std");
    test_list_alloc_2<int, simple_allocator<int>>("Simple");
    test_list_alloc_2<int, smart_allocator<int>>("Smart");

	return 0;
}