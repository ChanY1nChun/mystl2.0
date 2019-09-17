//
// Created by 陈彦骏 on 2019-09-03.
//

#ifndef MYTINYSTL_CONSTRUCT_H
#define MYTINYSTL_CONSTRUCT_H

#include <new>

#include "iterator.h"

namespace mystl {

    template <typename T>
    void construct(T* ptr)
    {
        ::new ((void*) ptr) T();
    }

    template <typename T1, typename T2>
    void construct(T1* ptr, const T2& value)
    {
        ::new ((void*) ptr) T1(value);
    }



    template <typename T>
    void destroy_one(T*, std::true_type)
    { }

    template <typename T>
    void destroy_one(T* ptr, std::false_type)
    {
        if(ptr != nullptr)
            ptr->~T();
    }

    template <typename T>
    void destroy(T* ptr)
    {
        destroy_one(ptr, std::is_trivially_destructible<T>{});
    }

    template <typename ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::true_type)
    { }

    template <typename ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
    {
        for(; first != last; ++first)
            destroy(&*first);
    }



    template <typename ForwardIter>
    void destroy(ForwardIter first, ForwardIter last)
    {
        destroy_cat(first, last, std::is_trivially_destructible<typename iterator_traits<ForwardIter>::value_type>{});
    }



}

#endif //MYTINYSTL_CONSTRUCT_H
