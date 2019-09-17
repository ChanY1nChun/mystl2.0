//
// Created by 陈彦骏 on 2019-09-13.
//

#ifndef MYTINYSTL_PRIORITY_QUEUE_H
#define MYTINYSTL_PRIORITY_QUEUE_H

#include "functional.h"
#include "vector.h"

namespace mystl {

    template <typename T, typename Sequence = vector<T>,
                    typename Compare = less<typename Sequence::value_type>> //只是写了接口，还没有实现comp的底层函数
    class priority_queue {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;

        priority_queue() : c() { }
        explicit priority_queue(const Compare& x) : c(), comp(x) { }

        template <typename InputIter>
        priority_queue(InputIter first, InputIter last) : c(first, last)
        {
            make_heap(c.begin(), c.end());
        }

        bool empty() const noexcept { return c.empty(); }
        size_type size() const noexcept { return c.size(); }
        const_reference top() const noexcept { return c.front(); }
        void push(const value_type& x)
        {
            c.push_back(x);
            push_heap(c.begin(), c.end());
        }

        void pop()
        {
            pop_heap(c.begin(), c.end());
            c.pop_back();
        }

    private:
        Sequence c;
        Compare comp; //没有用到

    };

}

#endif //MYTINYSTL_PRIORITY_QUEUE_H
