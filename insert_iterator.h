//
// Created by 陈彦骏 on 2019-09-02.
//

#ifndef MYTINYSTL_INSERT_ITERATOR_H
#define MYTINYSTL_INSERT_ITERATOR_H

#include "iterator.h"

namespace mystl {
    //定义尾后插入迭代器
    template <typename Container>
    class back_insert_iterator {
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit back_insert_iterator(Container& x) : container(&x) { }

        back_insert_iterator& operator=(const typename Container::value_type& value) {
            container->push_back(value);
            return *this;
        }

        back_insert_iterator& operator*() const noexcept { return *this; }
        back_insert_iterator& operator++() const noexcept { return *this; }
        back_insert_iterator& operator++(int) const noexcept { return *this; }

    private:
        Container* container;
    };

    //辅助函数，外部调用这个函数进行尾后插入
    template <typename Container>
    inline back_insert_iterator<Container> back_inserter(Container& x)
    {
        return back_insert_iterator<Container>(x);
    }



    //定义头部插入迭代器
    template <typename Container>
    class front_insert_iterator {
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit front_insert_iterator(Container& x) : container(&x) { }

        front_insert_iterator& operator=(const typename Container::value_type value) {
            container->push_front(value);
            return *this;
        }

        front_insert_iterator& operator*() const noexcept { return *this; }
        front_insert_iterator& operator++() const noexcept { return *this; }
        front_insert_iterator& operator++(int) const noexcept { return *this; }

    private:
        Container* container;
    };

    //辅助函数，外部调用这个函数进行头部插入，只用于提供push_front函数的容器如list，deque
    template <typename Container>
    inline front_insert_iterator<Container> front_inserter(Container& x)
    {
        return front_insert_iterator<Container>(x);
    }

    //定义插入迭代器
    template <typename Container>
    class insert_iterator {
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        insert_iterator(Container& x, typename Container::iterator it)
            : container(&x), iter(it) { }

        insert_iterator& operator=(const typename Container::value_type& value) {
            iter = container->insert(iter, value);
            ++iter;
            return *this;
        }

        insert_iterator& operator*() const noexcept { return *this; }
        insert_iterator& operator++() const noexcept { return *this; }
        insert_iterator& operator++(int) const noexcept { return *this; }


    private:
        Container* container;
        typename Container::iterator iter;
    };

    template <typename Container, typename Iterator>
    inline insert_iterator<Container> inserter(Container& x, Iterator it)
    {
        typedef typename Container::iterator iter;
        return insert_iterator<Container>(x, static_cast<iter>(it));
    }


}

#endif //MYTINYSTL_INSERT_ITERATOR_H
