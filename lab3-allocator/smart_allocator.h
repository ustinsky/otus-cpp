#ifndef MSMART_ALLOC_H
#define MSMART_ALLOC_H
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include "smart_allocator_node.h"

constexpr bool m_prettu_fun = true;
const size_t m_size_allocator = 10000; // Размер Chunk-а

template<typename T, size_t m_capacity = m_size_allocator>
class smart_allocator {
public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = smart_allocator<U>;
    };

    smart_allocator() {}

    ~smart_allocator() {
        for (auto i : sl) {
            i.~smart_alloc_logic();
        }
    };

    template<typename U> 
    smart_allocator(const smart_allocator<U>&) {}

    T *allocate(std::size_t n = 1) {
        if constexpr(m_prettu_fun == true) {
          std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl; 
          std::cout << "alloc: m_capacity = " << m_capacity << std::endl;  
        } 
        auto p = sl.alloc(n);
        if constexpr(m_prettu_fun == true) {
          std::cout << "smart_alloc: p = "<< p << std::endl;  
        } 
        if (p == nullptr) {
            if constexpr(m_prettu_fun == true) {
                std::cout << "smart_alloc: call bad_alloc" << std::endl;  
                std::cout << "smart_alloc: m_capacity" << m_capacity << std::endl;
            } 
            throw std::bad_alloc();
        } else {
            return p;
        }
    }

    void deallocate(T *p, std::size_t n = 1) {
        if constexpr (m_prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        }
        if (sl.dealloc(p, n) == false) {
            throw std::exception();
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        if constexpr(m_prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        if constexpr(m_prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        p->~T();
    }

private:
    smart_alloc_logic<T, m_capacity> sl;
};

#endif
