//
// Created by 陈彦骏 on 2019-09-03.
//

#ifndef MYTINYSTL_UNINITIALIZED_H
#define MYTINYSTL_UNINITIALIZED_H

#include <Algorithm>
#include "type_traits.h"
#include "iterator.h"

namespace mystl {

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter _uninitialized_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
    {
        return std::copy(first, last, result);
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter _uninitialized_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
    {
        auto cur = result;
        try {

            for(; first != last; ++first, ++cur)
                mystl::construct(&*cur, *first);

        } catch(...) {
            for(; result != cur; ++result)
                mystl::destroy(&*result);
        }
        return result;
    }

    template <typename InputIter, typename ForwardIter>
    inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        return _uninitialized_copy(first, last, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

    template <typename ForwardIter, typename T>
    inline void _uninitialized_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
    {
        std::fill(first, last, value);
    }

    template <typename ForwardIter, typename T>
    inline void _uninitialized_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type)
    {
        auto cur = first;
        try {
            for(; cur != last; ++cur)
                mystl::construct(&*cur, value);
        } catch(...) {
            for(; first != cur; ++first)
                mystl::destroy(&*first);
        }

    }

    template <typename ForwardIter, typename T>
    inline void uninitialized_fill(ForwardIter first, ForwardIter last, const T& value)
    {
        _uninitialized_fill(first, last, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter _uninitialized_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
    {
        return std::fill_n(first, n, value);
    }

    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter _uninitialized_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
    {
        auto cur = first;
        try {
            for(; n > 0; --n, ++cur)
                mystl::construct(&*cur, value);
        } catch(...) {
            for(; first != cur; ++first)
                mystl::destroy(&*first);
        }
        return cur;
    }

    template <typename ForwardIter, typename Size, typename T>
    inline ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T& value)
    {
        return _uninitialized_fill_n(first, n, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

}

#endif //MYTINYSTL_UNINITIALIZED_H
