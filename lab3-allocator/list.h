#ifndef MLIST_H
#define MLIST_H
#include <memory>
#include "allocator.h"

template <class T, class U> 
struct my_allocator_add {};

template <template<class> class Alloc, class U, class T> 
struct my_allocator_add<Alloc<T>, U> {
	using type = Alloc<U>;
};

template <class T>
class list_elem {
public:
	template<class ...Args>
	list_elem(Args&&... args) noexcept: 
		m_next(nullptr), 
		m_prev(nullptr),
		m_data(std::forward<Args>(args)...) {}

	list_elem<T>* m_next;
	list_elem<T>* m_prev;
	T m_data;
};

template <class T, class Alloc = std::allocator<T>>
class linked_list {
public:
	using ElemAlloc = typename my_allocator_add<Alloc, list_elem<T>>::type;

	linked_list();

	template<class... Args>
	void emplace_back(Args&&... args); 

	// Печать списка
	void print();

	// Перемещает текущий элемент на первый элемент списка
	void move_front();

	// Перемещает текущий элемент на последний элемент
	void move_back();

	// Перемещает текущий элемент на следующий элемент
	void move_next();

	// Перемещает текущий элемент на предыдущий элемент
	void move_prev();

	// Возвращает ссылку на поле m_data текущего элемента
	T& curr();

	// Вставка элементов в список
	template <class... Args>
	void insert(Args&&... args);

	// Удаление текущего элемента
	void erase();

	// Размер списка
	size_t size();

	// Удаляет из списка все элементы, освобождая занимаемую память
	void clear();

	// Деструктор, должен освободить всю выделенную память, включая m_root
	~linked_list(); 

private: 
	// Создание элемента через аллокатор
	template <class... Args>
	list_elem<T>* m_new(Args&&... args);

	// Удаление  
 	void m_delete(list_elem<T>* p, size_t n = 1); 
	
	// Аллокаторы
	Alloc 	  m_alloc_data;
	ElemAlloc m_alloc_elem;

	// Указатели на следующий и предыдущие элементы
	list_elem<T> *m_root;
	list_elem<T> *m_curr;
};

#endif