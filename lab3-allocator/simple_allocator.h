#include "list.h"

#include <iostream>
#include <vector>
#include <map>

#define USE_PRETTY 1
#define M_DEBUG false
#define UNUSED(variable) (void)variable

template<typename T>
struct simple_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = simple_allocator<U>;
    };

    simple_allocator() = default;
    ~simple_allocator() = default;

    template<typename U> 
    simple_allocator(const my_allocator<U>&) {}

    T *allocate(std::size_t n) {
        if constexpr (M_DEBUG) {
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        }
        
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        if constexpr (M_DEBUG) {
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        }
        std::free(p);
        UNUSED(n);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        if constexpr (M_DEBUG) {
            std::cout << __PRETTY_FUNCTION__ << "[p = " << p << "]" << std::endl;
        }
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        if constexpr (M_DEBUG) {
            std::cout << __PRETTY_FUNCTION__ << "[p = " << p << "]" << std::endl;
        }
        p->~T();
    }
};


