#ifndef MALLOC_H
#define MALLOC_H
#include <iostream>
#include <algorithm>
#define UNUSED(variable) (void)variable

constexpr bool prettu_fun = false;
constexpr size_t size_allocator = 1000000;

template<typename T>
class my_allocator {
public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = my_allocator<U>;
    };

    my_allocator(): m_pool(nullptr), m_size(0), m_capacity(0)  {}

    ~my_allocator() = default;

    template<typename U> 
    my_allocator(const my_allocator<U>&) {}

    T *allocate(std::size_t n, std::size_t new_size = size_allocator) {
        if constexpr(prettu_fun == true) {
          std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;  
        } 
        if (m_pool == nullptr) {
            reserve(std::max(n, new_size));
            // reserve(new_size);
            m_size++;
            return m_pool;
        } else if ( m_size < m_capacity) {
            return m_pool + m_size++;
        } else {
            throw std::bad_alloc();
        }
        if constexpr (prettu_fun == true) {
            std::cout << "m_size " << m_size << std::endl;
            std::cout << "m_capacity: " << m_capacity << std::endl;
        }
    }

    void deallocate(T *p, std::size_t n = 1) {
        if constexpr (prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << "[p = " << p << "]" << "[n = " << n << "]" << std::endl;
            std::cout << "m_size " << m_size << std::endl;
            std::cout << "m_capacity: " << m_capacity << std::endl;
        }
        if (m_size >= n)
            m_size -= n;
        else if (m_capacity >= n) {
            m_size = 0;
        }
        else {
            if constexpr (prettu_fun == true) {
                std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl; 
                std::cout << "m_size " << m_size << std::endl;
                std::cout << "m_capacity: " << m_capacity << std::endl;
            }
            throw std::bad_alloc();
        }

        if (m_size == 0) {
            if constexpr (prettu_fun == true) {
                std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl; 
                std::cout << "m_size " << m_size << std::endl;
                std::cout << "m_capacity: " << m_capacity << std::endl;
            }
            if (m_pool != nullptr) {
                std::free(m_pool);
                m_pool = nullptr;
            }
        } 
        UNUSED(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        if constexpr(prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        if constexpr(prettu_fun == true) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        p->~T();
    }

private:
    pointer m_pool;
    std::size_t m_size;
    std::size_t m_capacity;

    void reserve(std::size_t n) {
        auto p = std::malloc(n * sizeof(T));
        if (p == nullptr) 
            throw std::bad_alloc();
        else {
            m_capacity = n;
            m_pool = reinterpret_cast<T *>(p);
        }
    }
};

#endif
