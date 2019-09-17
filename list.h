//
// Created by 陈彦骏 on 2019-07-15.
//

#ifndef MYTINYSTL_LIST_H
#define MYTINYSTL_LIST_H

#include <new>
#include <initializer_list>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "iterator.h"


namespace mystl {
    template <typename T>
    struct list_node {
        list_node *prev;
        list_node *next;
        T data;
    };

    template <typename T>
    struct list_iterator : public iterator<bidirectional_iterator_tag, T> {
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference;
        typedef list_iterator<T> self;

        link_type _node;

        list_iterator() = default;
        list_iterator(const list_iterator &rhs) : _node(rhs._node) { }
        list_iterator(link_type node) : _node(node) { }

        bool operator==(const self &it) const { return _node == it._node; }
        bool operator!=(const self &it) const { return _node != it._node; }
        reference operator*() const { return (*_node).data; }
        pointer operator->() const { return &(operator*()); }

        self& operator++();
        self operator++(int);
        self& operator--();
        self operator--(int);


    };

    template <typename T>
    typename list_iterator<T>::self& list_iterator<T>::operator++()
    {
        _node = _node->next;
        return *this;
    }

    template <typename T>
    typename list_iterator<T>::self list_iterator<T>::operator++(int)
    {
        self temp = *this;
        ++*this;
        return temp;
    }

    template <typename T>
    typename list_iterator<T>::self& list_iterator<T>::operator--()
    {
        _node = _node->prev;
        return *this;
    }

    template <typename T>
    typename list_iterator<T>::self list_iterator<T>::operator--(int)
    {
        self temp = *this;
        --*this;
        return temp;
    }

    template <typename T>
    struct list_const_iterator : public iterator<bidirectional_iterator_tag, T> {
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference;
        typedef list_const_iterator<T> self;

        link_type _node;

        list_const_iterator() = default;
        list_const_iterator(const list_iterator<T> &rhs) : _node(rhs._node) { }
        list_const_iterator(const list_const_iterator &rhs) : _node(rhs._node) { }
        list_const_iterator(link_type node) : _node(node) { }

        bool operator==(const self &it) const { return _node == it._node; }
        bool operator!=(const self &it) const { return _node != it._node; }
        reference operator*() const { return (*_node).data; }
        pointer operator->() const { return &(operator*()); }

        self& operator++();
        self operator++(int);
        self& operator--();
        self operator--(int);


    };

    template <typename T>
    typename list_const_iterator<T>::self& list_const_iterator<T>::operator++()
    {
        _node = _node->next;
        return *this;
    }

    template <typename T>
    typename list_const_iterator<T>::self list_const_iterator<T>::operator++(int)
    {
        self temp = *this;
        ++*this;
        return temp;
    }

    template <typename T>
    typename list_const_iterator<T>::self& list_const_iterator<T>::operator--()
    {
        _node = _node->prev;
        return *this;
    }

    template <typename T>
    typename list_const_iterator<T>::self list_const_iterator<T>::operator--(int)
    {
        self temp = *this;
        --*this;
        return temp;
    }

    template <typename T>
    class list {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef list_node<T>* link_type;
        typedef const T* const_pointer;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        typedef list_iterator<T> iterator;
        typedef list_const_iterator<T> const_iterator;

        list();
        list(const list &rhs);
        //list(list &&rhs);
        list(size_type n);
        list(size_type n, const value_type &elem);
        list(const_iterator begin, const_iterator end);
        list(std::initializer_list<T> ilist);
        ~list();

        iterator begin() noexcept { return _node->next; }
        iterator begin() const noexcept { return _node->next; }
        const_iterator cbegin() const noexcept { return _node->next; }

        iterator end() noexcept { return _node; }
        iterator end() const noexcept { return _node; }
        const_iterator cend() const noexcept { return _node; }

        bool empty() const noexcept { return _node->next == _node; }
        size_type size() const noexcept { return _size; };

        reference front() noexcept { return *begin(); }
        const_reference front() const noexcept { return *begin(); }

        reference back() noexcept { return *--end(); }
        const_reference back() const noexcept { return *--end(); }

        //bool operator==(const list &lhs, const list &rhs);
        //bool operator!=(const list &lhs, const list &rhs);
        //bool operator<=(const list &lhs, const list &rhs);
        //bool operator>=(const list &lhs, const list &rhs);
        //bool operator<(const list &lhs, const list &rhs);
        //bool operator>(const list &lhs, const list &rhs);

        //list& operator=(const list &rhs);
        //list& operator=(list &&rhs);
        //list& operator=(std::initialized_list<T> ilist);

        //void assign(size_type n, const value_type &elem);
        //void assign(const_iterator begin, const_iterator);
        //void assign(std::initialized_list<T> ilist);

        void push_back(const value_type &elem);
        void pop_back() noexcept;
        void push_front(const value_type &elem);
        void pop_front() noexcept;

        iterator insert(iterator pos, const value_type &elem);
        iterator insert(iterator pos, size_type n, const value_type &elem);
        iterator insert(iterator pos, iterator begin, iterator end);
        iterator insert(iterator pos, std::initializer_list<T> ilist);

        iterator erase(iterator pos) noexcept;
        iterator erase(iterator begin, iterator end) noexcept;
        void remove(const value_type &elem);
        void resize(size_type n);
        void resize(size_type n, const value_type &elem);
        void clear() noexcept;
        void unique();
    private:
        link_type _node;
        size_type _size;
        std::allocator<list_node<T>> _allocator;
        void fill_init(size_type n, const value_type &elem);
        void copy_init(iterator begin, iterator end);
        link_type create_node(const value_type &elem);
        void destroy_node(link_type p);
        void init_empty();

    };

    template <typename T>
    list<T>::list()
    {
        init_empty();
    }

    template <typename T>
    list<T>::list(const list &rhs)
    {
        copy_init(rhs.cbegin(), rhs.cend());
    }

    template <typename T>
    list<T>::list(size_type n)
    {
        fill_init(n, value_type());
    }

    template <typename T>
    list<T>::list(size_type n, const value_type &elem)
    {
        fill_init(n, elem);
    }

    template <typename T>
    list<T>::list(const_iterator begin, const_iterator end)
    {
        copy_init(begin, end);
    }

    template <typename T>
    list<T>::list(std::initializer_list<T> ilist)
    {
        copy_init(ilist.begin(), ilist.end());
    }

    template <typename T>
    list<T>::~list()
    {
        clear();
        destroy_node(_node);
        _node = nullptr;
    }

    template <typename T>
    void list<T>::push_back(const value_type &elem)
    {
        insert(end(), elem);
    }

    template <typename T>
    void list<T>::pop_back() noexcept
    {
        iterator tmp = end();
        erase(--tmp);
    }

    template <typename T>
    void list<T>::push_front(const value_type &elem)
    {
        insert(begin(), elem);
    }

    template <typename T>
    void list<T>::pop_front() noexcept
    {
        erase(begin());
    }


    template <typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, const value_type &elem)
    {
        link_type p = create_node(elem);
        p->prev = pos._node->prev;
        p->next = pos._node;
        (pos._node->prev)->next = p;
        pos._node->prev = p;
        ++_size;
        return static_cast<iterator>(p);
    }

    template <typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, size_type n, const value_type &elem)
    {
        iterator res;
        for(int i = 0; i < n; ++i) {
            iterator first = insert(pos, elem);
            if(i == 0)
                res = first;
        }
        return res;
    }

    template <typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, iterator begin, iterator end)
    {
        iterator res;
        int distance = 0;
        auto tmp = begin;
        while(tmp++ != end)
            ++distance;
        for(auto i = 0; i < distance; ++i) {
            iterator first = insert(pos, *begin);
            if(i == 0)
                res = first;
            ++begin;
        }
        return res;
    }

    template <typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, std::initializer_list<T> ilist)
    {
        iterator beg = (ilist.begin());
        iterator end = (ilist.end());
        return insert(pos, beg, end);
    }

    template <typename T>
    typename list<T>::iterator list<T>::erase(iterator pos) noexcept
    {
        link_type next_node = pos._node->next;
        link_type prev_node = pos._node->prev;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(pos._node);
        --_size;
        return iterator(next_node);
    }

    template <typename T>
    typename list<T>::iterator list<T>::erase(iterator begin, iterator end) noexcept
    {
        link_type before_begin_node = begin._node->prev;
        link_type after_end_node = end._node;
        link_type p = begin._node;
        before_begin_node->next = after_end_node;
        after_end_node->prev = before_begin_node;
        int distance = 0;
        while(begin++ != end)
            ++distance;
        for(auto i = 0; i < distance; ++i) {
            link_type tmp = p;
            p = p->next;
            destroy_node(tmp);
        }
        _size -= static_cast<size_type>(distance);
        return end;
    }

    template <typename T>
    void list<T>::remove(const value_type &elem)
    {
        iterator begin(_node->next);
        iterator end(_node);

        while(begin != end) {
            iterator next = begin;
            ++next;
            if(*begin == elem) {
                erase(begin);
            }
            begin = next;
        }


    }

    template <typename T>
    void list<T>::resize(size_type n)
    {
        resize(n, value_type());
    }

    template <typename T>
    void list<T>::resize(size_type n, const value_type &elem)
    {
        if(_size < n)
            insert(end(), n - _size, elem);
        else if(_size > n) {
            iterator tmp = begin();
            for(int i = 0; i < n; ++i)
                ++tmp;
            erase(tmp, end());
        } else
            return;
    }

    template <typename T>
    void list<T>::clear() noexcept
    {
        link_type cur = _node->next;
        while(cur != _node) {
            link_type tmp = cur;
            cur = cur->next;
            destroy_node(tmp);
        }

        _node->next = _node;
        _node->prev = _node;
        _size = 0;
    }

    template <typename T>
    void list<T>::unique()
    {
        iterator begin(_node->next);
        iterator end(_node);
        if(begin == end)
            return;
        iterator next = begin;
        while(++next != end) {
            if(*begin == *next)
                erase(next);
            else
                begin = next;
            next = begin;
        }
    }


    template <typename T>
    void list<T>::fill_init(size_type n, const value_type &elem)
    {
        init_empty();
        insert(end(), n, elem);
    }

    template <typename T>
    void list<T>::copy_init(iterator begin, iterator end)
    {
        init_empty();
        insert(end(), begin, end);
    }

    template <typename T>
    typename list<T>::link_type list<T>::create_node(const value_type &elem)
    {
        link_type p = _allocator.allocate(1);
        _allocator.construct(&p->data, elem);
        return p;
    }

    template <typename T>
    void list<T>::destroy_node(link_type p)
    {
        _allocator.destroy(p);
        _allocator.deallocate(p,1);
    }

    template <typename T>
    void list<T>::init_empty()
    {
        _node = create_node(value_type());
        _node->next = _node;
        _node->prev = _node;
        _size = 0;
    }



}

#endif //MYTINYSTL_LIST_H
