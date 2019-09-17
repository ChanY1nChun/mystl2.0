//
// Created by 陈彦骏 on 2019-07-16.
//

#ifndef MYTINYSTL_STACK_H
#define MYTINYSTL_STACK_H


#include "iterator.h"
#include "list.h"

namespace mystl {

    template <typename T, typename Container = mystl::list<T>>
    class stack {
    public:
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;
        typedef Container container_type;

        stack() = default;
        ~stack() = default;

        bool empty() const noexcept { return _container.empty(); }
        size_type size() const noexcept { return _container.size(); }
        void push(const value_type &elem) { _container.push_back(elem); }
        void pop() { _container.pop_back(); }
        reference top() { return _container.back(); }
        const_reference top() const { return _container.back(); };

    private:
        container_type _container;
    };
}

#endif //MYTINYSTL_STACK_H
