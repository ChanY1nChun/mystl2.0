//
// Created by 陈彦骏 on 2019-09-04.
//

#ifndef MYTINYSTL_HEAP_H
#define MYTINYSTL_HEAP_H

#include "iterator.h"

namespace mystl {

    template <typename RandomAccessIter, typename Distance, typename T>
    void _push_heap(RandomAccessIter first, Distance holeIndex, Distance topIndex, T value)
    {
        Distance parent = (holeIndex - 1) / 2;
        while(holeIndex > topIndex && *(first + parent) < value) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <typename RandomAccessIter, typename Distance, typename T>
    inline void _push_heap_aux(RandomAccessIter first, RandomAccessIter last, Distance*, T*)
    {
        _push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
    }

    template <typename RandomAccessIter>
    inline void push_heap(RandomAccessIter first, RandomAccessIter last)
    {
        _push_heap_aux(first, last, distance_type(first), value_type(first));
    }

    template <typename RandomAccessIter, typename Distance, typename T>
    void _adjust_heap(RandomAccessIter first, Distance holeIndex, Distance len, T value)
    {
        Distance topIndex = holeIndex;
        Distance secondChild = 2 * holeIndex + 2;
        while(secondChild < len) {
            if(*(first + secondChild) < *(first + (secondChild - 1)))
                --secondChild;
            *(first + holeIndex) = *(first + secondChild);
            holeIndex = secondChild;
            secondChild = 2 * secondChild + 2;
        }
        if(secondChild == len) {
            *(first + holeIndex) = *(first + (secondChild - 1));
            holeIndex = secondChild - 1;
        }
        _push_heap(first, holeIndex, topIndex, value);
    }

    template <typename RandomAccessIter, typename T, typename Distance>
    inline void _pop_heap(RandomAccessIter first, RandomAccessIter last, RandomAccessIter result, T value, Distance*)
    {
        *result = *first;
        _adjust_heap(first, Distance(0), Distance(last - first), value);
    }

    template <typename RandomAccessIter, typename T>
    inline void _pop_heap_aux(RandomAccessIter first, RandomAccessIter last, T*)
    {
        _pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
    }

    template <typename RandomAccessIter>
    inline void pop_heap(RandomAccessIter first, RandomAccessIter last)
    {
        _pop_heap_aux(first, last, value_type(first));
    }





    template <typename RandomAccessIter>
    void sort_heap(RandomAccessIter first, RandomAccessIter last)
    {
        while(last - first > 1)
            pop_heap(first, last--);
    }

    template <typename RandomAccessIter, typename T, typename Distance>
    void _make_heap(RandomAccessIter first, RandomAccessIter last, T*, Distance*)
    {
        if(last - first < 2)
            return;
        Distance len = last - first;
        Distance parent = (len - 2) / 2;
        while(true) {
            _adjust_heap(first, parent, len, T(*(first + parent)));
            if(parent == 0)
                return;
            --parent;
        }
    }

    template <typename RandomAccessIter>
    inline void make_heap(RandomAccessIter first, RandomAccessIter last)
    {
        _make_heap(first, last, value_type(first), distance_type(first));
    }





}

#endif //MYTINYSTL_HEAP_H
