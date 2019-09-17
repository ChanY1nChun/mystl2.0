//
// Created by 陈彦骏 on 2019-07-14.
//

#include "allocator.h"

namespace mystl {

    template <typename T>
    inline allocator::pointer allocator::allocate()
    {
        return static_cast<pointer>(::operator new(sizeof(T)));
    }

    template <typename T>
    inline allocator::pointer allocator::allocate(size_type n)
    {
        if(n == 0)
            return nullptr;
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    template <typename T>
    inline void allocator::deallocate(pointer p)
    {
        if(p == nullptr)
            return;
        ::operator delete(p);
    }

    template <typename T>
    inline void allocator::deallocate(pointer p, size_type n)
    {
        if(p == nullptr || n <= 0)
    }


    template <>
}
