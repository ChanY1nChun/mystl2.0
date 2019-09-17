//
// Created by 陈彦骏 on 2019-07-14.
//

#ifndef MYTINYSTL_ALLOCATOR_H
#define MYTINYSTL_ALLOCATOR_H


#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

#include "construct.h"

namespace mystl {

    template <typename T>
    class allocator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        allocator() = default;
        ~allocator() = default;
        allocator(const allocator&) = delete;

        pointer allocate();
        pointer allocate(size_type n);

        void deallocate(pointer p);
        void deallocate(pointer p, size_type n);

        void construct(pointer p);
        void construct(pointer p, const T &value);

        void destroy(pointer p);
        void destroy(pointer start, pointer end);

    };

    template <typename T>
    T* allocator<T>::allocate()
    {
        return static_cast<T*>(::operator new (sizeof (T)));
    }

    template <typename T>
    T* allocator<T>::allocate(size_type n)
    {
        return static_cast<T*>(::operator new (n * sizeof(T)));
    }

    template <typename T>
    void allocator<T>::deallocate(T* ptr)
    {
        if(ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <typename T>
    void allocator<T>::deallocate(T* start, size_type n)
    {
        if(start == nullptr)
            return;
        ::operator delete(start);
    }

    template <typename T>
    void allocator<T>::construct(T* ptr)
    {
        mystl::construct(ptr);
    }

    template <typename T>
    void allocator<T>::construct(T* ptr, const T& value)
    {
        mystl::construct(ptr, value);
    }

    template <typename T>
    void allocator<T>::destroy(T* ptr)
    {
        mystl::destroy(ptr);
    }

    template <typename T>
    void allocator<T>::destroy(T* start, T* end)
    {
        mystl::destroy(start, end);
    }

}

#endif //MYTINYSTL_ALLOCATOR_H
