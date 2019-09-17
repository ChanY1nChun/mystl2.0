//
// Created by 陈彦骏 on 2019-07-16.
//

#ifndef MYTINYSTL_QUEUE_H
#define MYTINYSTL_QUEUE_H

#include "list.h"

namespace mystl {

    template <typename T, typename Container = list<T>>
    class queue {
    public:
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;
        typedef Container container_type;

        queue() = default;
        ~queue() = default;

        bool empty() const noexcept { return _container.empty(); }
        size_type size() const noexcept { return _container.size(); }
        reference front() { return _container.front(); }
        const_reference front() const { return _container.front(); }
        reference back() { return _container.back(); }
        const_reference back() const { return _container.back(); }

        void push(const value_type &elem) { _container.push_back(elem); }
        void pop() { _container.pop_front(); }
    private:
        container_type _container;
    };
}

#endif //MYTINYSTL_QUEUE_H
