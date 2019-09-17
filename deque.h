//
// Created by 陈彦骏 on 2019-07-17.
//

#ifndef MYTINYSTL_DEQUE_H
#define MYTINYSTL_DEQUE_H

#include "iterator.h"

namespace mystl {

    template <typename T, size_t BufSiz>
    struct deque_iterator : public mystl::iterator<random_access_iterator_tag, T> {
        typedef size_t size_type;
        typedef value_type** map_pointer;
        typedef value_type* value_pointer;
        typedef deque_iterator self;
        typedef deque_iterator<T, BufSize> iterator;
        typedef deque_iterator<const T, BufSize> const_iterator;

        value_pointer cur;
        value_pointer first;
        value_pointer last;
        map_pointer node;

        deque_iterator() noexcept : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) { }
        deque_iterator(const iterator &rhs)
            : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) { }

        deque_iterator(const const_iterator &rhs)
                : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) { }

        static size_t buffer_size() { return deque_buf_size(BufSiz, sizeof(T)) ; }

        size_type deque_buf_size(size_type n, size_type sz);
        void set_node(map_pointer new_node);

        reference operator*() const { return *cur; }
        pointer operator->() const { return &(operator*()); }
        difference_type operator-(const self &rhs);
        self& operator++();
        self operator++(int);
        self& operator--();
        self operator--(int);
        self& operator+=(difference_type n);
        self operator+(difference_type n) const;
        self& operator-=(difference_type n);
        self operator-(difference_type n) const;
        reference operator[](difference_type) const;

        bool operator==(const self &rhs) const { return cur == rhs.cur; }
        bool operator!=(const self &rhs) const { return !(*this == rhs); }
        bool operator<(const self &rhs) const { return node == rhs.node ? (cur < rhs.cur) : (node < rhs.node); }
        bool operator<=(const self &rhs) const { return !(rhs < *this); }
        bool operator>(const self &rhs) const { return rhs < *this; }
        bool operator>=(const self &rhs) const { return !(*this < rhs); }
    };

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::size_type deque_iterator<T, BufSiz>::deque_buf_size(size_type n, size_type sz)
    {
        return n != 0 ? n : (sz < 512 ? static_cast<size_type>(512 / sz) : static_cast<size_type>(1));
    }

    template <typename T, size_t BufSiz>
    void deque_iterator<T, BufSiz>::set_node(map_pointer new_node)
    {
        node = new_node;
        first = *node;
        last = first + static_cast<difference_type>(buffer_size());
    }



    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::difference_type deque_iterator<T, BufSiz>::operator-(const self &rhs)
    {
        return static_cast<difference_type>(buffer_size()) * (node - rhs.node - 1) + (cur - first) + ( rhs.last - rhs.cur);
    }

    template <typename T, size_t BufSiz>
    typename deque_iterator<T, BufSiz>::self& deque_iterator<T, BufSiz>::operator++()
    {
        ++cur;
        if(cur == last) {
            set_node(node + 1);
            cur = first;
        }

        return *this;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::self deque_iterator<T, BufSiz>::operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    template <typename T, size_t BufSiz>
    typename deque_iterator<T, BufSiz>::self& deque_iterator<T, BufSiz>::operator--()
    {
        if(cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::self deque_iterator<T, BufSiz>::operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    template <typename T, size_t BufSiz>
    typename deque_iterator<T, BufSiz>::self& deque_iterator<T, BufSiz>::operator+=(difference_type n)
    {
        difference_type offset = n + (cur - first);
        if(offset >= 0 && offset < static_cast<difference_type>(buffer_size()))
            cur += n;
        else {
            difference_type node_offset =
                    offset > 0 ? offset / static_cast<difference_type>(buffer_size())
                        : -static_cast<difference_type>((-offset - 1) / buffer_size()) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * static_cast<difference_type>(buffer_size()));
        }

        return *this;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::self deque_iterator<T, BufSiz>::operator+(difference_type n) const
    {
        self tmp = *this;
        return tmp += n;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::self& deque_iterator<T, BufSiz>::operator-=(difference_type n)
    {
        return *this += -n;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::self deque_iterator<T, BufSiz>::operator-=(difference_type n) const
    {
        self tmp = *this;
        return tmp -= n;
    }

    template <typename T, size_t BufSiz>
    inline typename deque_iterator<T, BufSiz>::reference deque_iterator<T, BufSiz>::operator[](difference_type) const
    {
        return *(*this + n);
    }

    template<typename T, size_t BufSiz = 0>
    class deque {
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef pointer* map_pointer;
        typedef const pointer* const_map_pointer;

        typedef deque_iterator<T, BufSiz> iterator;
        typedef deque_iterator<const T, BufSiz> const_iterator;
        typedef deque self;

        deque() { fill_init(0, value_type()); }
        explicit deque(size_type n) { fill_init(n, value_type()); }
        deque(size_type n, const value_type &elem) { fill_init(n, value_type(elem)); }

        iterator begin() noexcept { return _begin; }
        const_iterator begin() const noexcept { return _begin; }
        const_iterator cbegin() const noexcept { return _begin; }

        iterator end() noexcept { return _end; }
        const_iterator end() const noexcept { return _end; }
        const_iterator cend() const noexcept { return _end; }

        size_type size() const noexcept { return _end - _begin; }
        bool empty() const noexcept { return _end == _begin; }

        reference front() { return *_begin; }
        const_reference front() const { return *_begin; }
        reference back() { return *--_end; }
        const_reference back() const { return *--_end; }

        reference operator[](size_type n) { return _begin[n]; }
        const_reference operator[](size_type n) const { return _begin[n]; }
        reference at(size_type n);
        const_reference at(size_type n) const;

        void push_back(const value_type &elem);
        void push_front(const value_type &elem);
        void pop_back();
        void pop_front();
        void clear();
        iterator erase(iterator pos);
        iterator erase(iterator begin, iterator end);
        iterator insert(iterator pos, const value_type &elem);
    private:
        iterator _begin;
        iterator _end;
        map_pointer _map;
        size_type _map_size;
        std::allocator<T> _allocator;
        std::allocator<pointer> _map_allocator;

        void fill_init(size_type n, const value_type &elem);
        void map_init(size_type n);
        void create_buffer(map_pointer start, map_pointer finish);
        void destroy_buffer(map_pointer start, map_pointer finish);
        void push_back_aux(const value_type &elem);
        void push_front_aux(const value_type &elem);
        void pop_back_aux();
        void pop_front_aux();
        void insert_aux(iterator pos, const value_type &elem);
        void reserve_map_at_back(size_type nodes_to_add = 1);
        void reserve_map_at_front(size_type nodes_to_add = 1);
        void reallocate_map(size_type nodes_to_add, bool add_at_front);
    };

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::push_back(const value_type &elem)
    {
        if(_end.cur != _end.last - 1) {
            _allocator.construct(_end.cur, elem);
            ++_end.cur;
        } else
            push_back_aux(elem);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::push_front(const value_type &elem)
    {
        if(_begin.cur != _begin.first) {
            _allocator.construct(--_begin.cur, elem);
        } else
            push_front_aux(elem);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::pop_back()
    {
        if(_end.cur != _end.first) {
            --_end.cur;
            _allocator.destroy(_end.cur);
        } else
            pop_back_aux();
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::pop_front()
    {
        if(_begin.cur != _begin.last - 1) {
            _allocator.destroy(_begin.cur++);
        } else
            pop_front_aux();
    }


    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::insert_aux(iterator pos, const value_type &elem)
    {
        auto index = pos - _begin;
        if(index < size() / 2) {
            push_front(front());
            iterator front1 = _begin;
            ++front1;
            iterator front2 = front1;
            ++front2;
            pos = _begin + index;
            iterator pos1 = pos;
            ++pos1;
            std::copy(front2, pos1, front1);
        } else {
            push_back(back());
            iterator back1 = _end;
            --back1;
            iterator back2 = back1;
            --back2;
            pos = _begin + index;
            std::copy_backward(pos, back2, back1);
        }

        *pos = elem;
        return pos;
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::clear()
    {
        for(map_pointer node = _begin.node + 1; node < _end.node; ++node) {
            for(pointer p = *node, auto distance = buffer_size(); distance > 0; --distance)
                _allocator.destroy(p++);
            destroy_buffer(node, node);
        }

        if(_begin.node != _end.node) {
            for(pointer p = _begin.cur, auto distance = _begin.last - _begin.cur; distance > 0; --distance)
                _allocator.destroy(p++);

            for(pointer p = _end.cur, auto distance = _end.cur - _end.first; distance > 0; --distance)
                _allocator.destroy(--p);
            destroy_buffer(_end.node, _end.node);
        } else {
            for(pointer p = _begin.cur, auto distance = _end - _begin; distance > 0; --distance)
                _allocator.destroy(p++);
        }

        _end = _begin;
    }

    template <typename T, size_t BufSiz>
    typename deque<T, BufSiz>::iterator deque<T, BufSiz>::erase(iterator pos)
    {
        iterator next = pos;
        ++next;
        auto index = pos - _begin;
        if(index < (size() >> 1)) {
            std::copy_backward(_begin, pos, next);
            pop_front();
        } else {
            std::copy(next, _end, pos);
            pop_back();
        }

        return _begin + index;
    }

    template <typename T, size_t BufSiz>
    typename deque<T, BufSiz>::iterator deque<T, BufSiz>::erase(iterator begin, iterator end)
    {
        if(_begin == begin && _end == end) {
            clear();
            return _end;
        } else {
            auto n = end - begin;
            auto elems_before = begin - _begin;
            if(elems_before < (size() - n) / 2) {
                std::copy_backward(_begin, begin, end);
                iterator new_begin = _begin + n;
                for(pointer p = _begin.cur , auto distance = begin - _begin; distance > 0; --distance)
                    _allocator.destroy(p++);
                for(map_pointer cur = _begin.node; cur < new_begin.node; ++cur)
                    _allocator.deallocate(*cur, buffer_size());
                _begin = new_begin;
            } else {
                std::copy(end, _end, begin);
                iterator new_end = _end - n;
                for(pointer p = new_end.cur, auto distance = _end - new_end; distance > 0; --distance)
                    _allocator.destroy(p++);
                for(map_pointer cur = new_end.node + 1; cur <= _end.node; ++cur)
                    _allocator.deallocate(*cur, buffer_size());
                _end = new_end;
            }

            return _begin + elems_before;
        }
    }

    template <typename T, size_t BufSiz>
    typename deque<T, BufSiz>::iterator deque<T, BufSiz>::insert(iterator pos, const value_type &elem)
    {
        if(pos.cur == _begin.cur) {
            push_front(elem);
            return _begin;
        } else if(pos.cur == _end.cur) {
            push_back(elem);
            iterator tmp = _end;
            --tmp;
            return tmp;
        } else
            return insert_aux(pos, elem);
    }


    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::fill_init(size_type n, const value_type &elem)
    {
        _begin = _end = _map = nullptr;
        _map_size = 0;
        map_init(n);
        map_point cur;

        if(n != 0) {
            for(cur = _begin.node; cur < _end.node; ++cur)
                std::uninitialized_fill(*cur, *cur + buffer_size(), elem);
            std::uninitialized_fill(_end.first, _end.last, elem);
        }

    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::map_init(size_type n)
    {
        size_type number_nodes = n / buffer_size() + 1;
        _map_size = 8 > number_nodes + 2 ? 8 : number_nodes + 2;

        try {
           _map = _map_allocator.allocate(_map_size);
        }  catch(...) {
            _map = nullptr;
            _map_size = 0;
            throw;
        }

       map_pointer nstart = _map + (_map_size - number_nodes) / 2;
       map_pointer nfinish = nstart + nfinish - 1;

       try {
           create_buffer(nstart, nfinish);
       } catch(...) {
           _map_allocator.deallocate(_map, _map_size);
           _map = nullptr;
           _map_size = 0;
           throw;
       }

       _begin.set_node(nstart);
       _end.set_node(nfinish);
       _begin.cur = _begin.first;
       _end.cur = _end.first + number_nodes % buffer_size();
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::create_buffer(map_pointer start, map_pointer finish)
    {
        map_pointer cur;
        try {
            for (cur = start; cur <= finish; ++cur)
                *cur = _allocator.allocate(buffer_size());
        } catch(...) {
            while(cur != start) {
                --cur;
                _allocator.deallocate(*cur, buffer_size());
                *cur = nullptr;
            }
            throw;
        }
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::destroy_buffer(map_pointer start, map_pointer finish)
    {
        map_pointer cur;
        for(cur = start; cur <= finish; ++cur)
            _allocator.deallocate(*cur,buffer_size());
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::push_back_aux(const value_type &elem)
    {
        reserve_map_at_back();
        create_buffer(_end.node + 1, _end.node + 1);
        _allocator.construct(_end.cur, elem);
        _end.set_node(_end.node + 1);
        _end.cur = _end.first;
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::push_front_aux(const value_type &elem)
    {
        reserve_map_at_front();
        create_buffer(_begin.node - 1, _begin.node - 1);
        _begin.set_node(_begin.node - 1);
        _begin.cur = _begin.last - 1;
        _allocator.construct(_begin.cur, elem);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::pop_back_aux()
    {
        destroy_buffer(_end.node, _end.node);
        _end.set_node(_end.node - 1);
        _end.cur = _end.last - 1;
        _allocator.destroy(--_end.cur);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::pop_front_aux()
    {
        _allocator.destroy(_begin.cur);
        destroy_buffer(_begin.node, _begin.node);
        _begin.set_node(_begin.node + 1);
        _begin.cur = _begin.first;
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::reserve_map_at_back(size_type nodes_to_add = 1)
    {
        if(nodes_to_add + 1 > _map_size - (_end.node - map))
            reallocate_map(nodes_to_add, false);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::reserve_map_at_front(size_type nodes_to_add = 1)
    {
        if(nodes_to_add > _begin.node - map)
            reallocate_map(nodes_to_add, true);
    }

    template <typename T, size_t BufSiz>
    void deque<T, BufSiz>::reallocate_map(size_type nodes_to_add, bool add_at_front)
    {
        size_type old_num_nodes = _end.node - _begin.node + 1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;

        map_pointer new_begin;
        if(_map_size > 2 * new_num_nodes) {
            new_begin = _map + (_map_size - new_num_nodes) / 2
                    + (add_at_front ? nodes_to_add : 0);
            if(new_begin < _begin.node)
                std::copy(_begin.node, _end.node + 1, new_begin);
            else
                std::copy_backward(_begin.node, _end.node + 1, new_begin + old_num_nodes);
        } else {
            size_type new_map_size = _map_size + (_map_size > nodes_to_add + 2 ? _map_size : nodes_to_add + 2);
            try {
                map_pointer new_map = _map_allocator.allocate(new_map_size);
                new_begin = new_map + (new_map_size - new_num_nodes) / 2
                        + (add_at_front ? nodes_to_add : 0);
            } catch(...) {
                new_map = nullptr;
                new_map_size = 0;
                throw;
            }

            _map_allocator.deallocate(_map, _map_size);
            _map = new_map;
            _map_size = new_map_size;
        }

        _begin.set_node(new_begin);
        _end.set_node(new_begin + old_num_nodes - 1);
    }

}

#endif //MYTINYSTL_DEQUE_H
