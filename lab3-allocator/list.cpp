#include <iostream>
#include "list.h"

using namespace std;

template <class T, class Alloc>
linked_list<T, Alloc>::linked_list() {
	// m_root = new list_elem<T>();
	m_root = m_new();
	m_root->m_next = m_root;
	m_root->m_prev = m_root;
	m_curr = m_root;
}

template<class T, class Alloc>
void linked_list<T,Alloc>::m_delete(list_elem<T> *p, size_t n) {
	if ((m_root != nullptr) && (p != nullptr)) {
		std::allocator_traits<Alloc>::destroy(m_alloc_data, p);
    	std::allocator_traits<ElemAlloc>::deallocate(m_alloc_elem, p, n);
	}
}

template <class T, class Alloc>
template <class... Args>
list_elem<T>* linked_list<T, Alloc>::m_new(Args&&... args) {
	auto p = std::allocator_traits<ElemAlloc>::allocate(m_alloc_elem, 1);
    std::allocator_traits<Alloc>::construct(m_alloc_data, p, std::forward<Args>(args)...);
    return p;
}


template <class T, class Alloc>
template <class... Args>
void linked_list<T, Alloc>::emplace_back(Args&&... args) {
	// list_elem<T>* elem = new list_elem<T>();
	// elem->m_data = val;
	auto elem = m_new(std::forward<Args>(args)...);

	auto m_cur = m_root->m_prev;
	elem->m_prev = m_cur;
	elem->m_next = m_root;
	m_cur->m_next = elem;

	m_root->m_prev = elem;
}

// Печать списка
template <class T, class Alloc>
void linked_list<T, Alloc>::print(){
	auto m_cur = m_root->m_next;

	while (m_cur != m_root) {
		cout << m_cur->m_data << ' ';
		m_cur = m_cur->m_next;
	}
	cout << endl;
	// std::cout << "alloc_size" << m_alloc_elem.get_size() << std::endl;
}

// Перемещает текущий элемент на первый элемент списка
template <class T, class Alloc>
void linked_list<T, Alloc>::move_front(){
	m_curr = m_root->m_next;
}

// // Перемещает текущий элемент на последний элемент
template <class T, class Alloc>
void linked_list<T, Alloc>::move_back(){
	m_curr = m_root->m_prev;
}

// // Перемещает текущий элемент на следующий элемент
template <class T, class Alloc>
void linked_list<T, Alloc>::move_next(){
	m_curr = m_curr->m_next;
}

// // Перемещает текущий элемент на предыдущий элемент
template <class T, class Alloc>
void linked_list<T, Alloc>::move_prev(){
	m_curr = m_curr->m_prev;
}

// // Возвращает ссылку на поле m_data текущего элемента
template <class T, class Alloc>
T& linked_list<T, Alloc>::curr(){
	return m_curr->m_data;
}

// Вставка элементов в список. В позицию определенную m_curr
template <class T, class Alloc>
template <class... Args>
void linked_list<T, Alloc>::insert(Args&&... args) {
	auto elem = m_new(std::forward<Args>(args)...);

	list_elem<T>* elem_prev = m_curr->m_prev;
	elem->m_next = m_curr;
	elem->m_prev = elem_prev;
	m_curr->m_prev = elem;
	elem_prev->m_next = elem;

	m_curr = elem;
}

//
// Удаление элементов
template <class T, class Alloc>
void linked_list<T, Alloc>::erase(){
	list_elem<T>* cur = m_curr;
	if (m_curr != m_root) {
		m_curr->m_prev->m_next = m_curr->m_next;
		m_curr->m_next->m_prev = m_curr->m_prev;
		m_curr = m_curr->m_next;
		m_delete(cur);
	}
}


// Размер списка
template <class T, class Alloc>
size_t linked_list<T, Alloc>::size() {
	size_t m_size = 0;
	auto cur = m_root->m_next;

	while(cur != m_root) {
		++m_size;
		cur = cur->m_next;
	}

	return m_size;
}

// Удаляет из списка все элементы, освобождая занимаемую память
template <class T, class Alloc>
void linked_list<T, Alloc>::clear(){
	// std::cout << "clear" << std::endl;
	auto cur = m_root->m_prev;
	while (cur != m_root) {
		cur = cur->m_prev;
		// std::cout << cur->m_next->m_data << " " << cur->m_data << " m_prev: " << cur->m_prev->m_data << " m_next: " << cur->m_next->m_data << std::endl;
		m_delete(cur->m_next);
	}

	m_root->m_next = m_root;
	m_root->m_prev = m_root;
	m_curr = m_root;
}

// Деструктор, должен освободить всю выделенную память, включая m_root
template <class T, class Alloc>
linked_list<T, Alloc>::~linked_list() {
	clear();
	m_delete(m_root, 1);
} 




