//
// Created by 陈彦骏 on 2019-07-14.
//


#include "vector.h"

namespace mystl {

    template <typename T>
    vector<T>::vector(const vector &vec) //拷贝构造函数
    {
        range_init(vec.begin(), vec.end());
    }

    template <typename T>
    vector<T>::vector(size_type n) //利用默认构函数生产一个大小为n的vector
    {
        fill_init(n, value_type());
    }

    template <typename T>
    vector<T>::vector(size_type n, const value_type &elem) //建立一个大小为n的vector，每个元素的值都为elem
    {
        fill_init(n, elem);
    }

    template <typename T>
    vector<T>::vector(iterator beg, iterator end) //建立一个vector， 以区间【beg, end)作为元素初值
    {
        range_init(beg, end);
    }

    template <typename T>
    vector<T>::vector(std::initializer_list<value_type> ilist) //C++11,以初值列ilist的元素作为初值
    {
        range_init(ilist.begin(), ilist.end());
    }

    /*template <typename T>
    vector(vector &&vec); //移动构造函数*/

    /*template <typename T>
    vector<T>::~vector()  //析构函数
    {
        range_destroy(begin(), end(), capacity());
        _begin = _end = _cap = nullptr;
    }*/

    /*template <typename T>
    vector<T>& vector<T>::operator=(const vector &rhs) //拷贝赋值运算符
    {
        if(this == rhs)
            return *this;

        vector temp(rhs);

    }*/
    //vector& operator=(std::initializer_list<value_type> ilist);

    /*template <typename T>
    void assign(size_type n, const value_type &elem);

    template <typename T>
    void assign(iterator beg, iterator end);

    template <typename T>
    void assign(std::initializer_list<value_type> ilist);

    template <typename T>
    void swap(vector &vec) noexcept;*/

    template <typename T>
    void vector<T>::reserve(size_type n)
    {
        if(n <= capacity())
            return;

        auto new_begin = _allocator.allocate(n);
        auto new_end = new_begin;

        auto old_size = size();
        auto new_size = n;

        try {
            new_end = std::uninitialized_copy(_begin, _end, new_begin);
        } catch(...) {
            range_destroy(new_begin, new_end, new_size);
            throw;
        }
            range_destroy(_begin, _end, capacity());
            _begin = new_begin;
            _end = new_end;
            _cap = _begin + new_size;
    }

    template <typename T>
    void vector<T>::shrink_to_fit()
    {
        reinsert(size());
    }

    /*template <typename T>
    bool operator==(const vector &lhs, const vector &rhs);

    template <typename T>
    bool operator!=(const vector &lhs, const vector &rhs);

    template <typename T>
    bool operator<(const vector &lhs, const vector &rhs);

    template <typename T>
    bool operator>(const vector &lhs, const vector &rhs);

    template <typename T>
    bool operator<=(const vector &lhs, const vector &rhs);

    template <typename T>
    bool operator>=(const vector &lhs, const vector &rhs);*/

    template <typename T>
    void vector<T>::push_back(const value_type &elem)
    {
        if(_end != _cap) {
            _allocator.construct(_end++, elem);
        } else
            reallocate_insert(_end, elem);
    }

    /*template <typename T>
    void push_back(value &&elem);*/

    template <typename T>
    void vector<T>::pop_back() noexcept
    {
        if(empty())
            return;
        _allocator.destroy(--_end);
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::insert(const_iterator pos, const value_type &elem)
    {
        return insert(pos, 1, elem);
    }

    /*template <typename T>
    iterator insert(const_iterator pos, value_type &&elem);*/

    template <typename T>
    typename vector<T>::iterator vector<T>::insert(const_iterator pos, size_type n, const value_type &elem)
    {
        return fill_insert(pos, n, elem);
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::insert(const_iterator pos, iterator beg, iterator end)
    {
        return copy_insert(pos, beg, end);
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
    {
        return insert(pos, ilist.begin(), ilist.end());
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::erase(const_iterator pos)
    {
        if(pos + 1 != end())
            std::copy(pos + 1, _end, pos);
        --_end;
        _allocator.destroy(_end);
        return pos;

    }

    template <typename T>
    typename vector<T>::iterator vector<T>::erase(const_iterator beg, const_iterator end)
    {
        iterator i = std::copy(end, _end, beg);
        _allocator.destroy(i, _end);
        _end = _end - (end - beg);
        return beg;
    }

    template <typename T>
    void vector<T>::resize(size_type n)
    {
        resize(n, value_type());
    }

    template <typename T>
    void vector<T>::resize(size_type n, const value_type &elem)
    {
        if(size() < n) {
            insert(_end, size() - n, elem);
        } else if(size() > n) {
            erase(_begin + n, _end);
        } else
            return;
    }

    template <typename T>
    void vector<T>::clear() noexcept
    {
        erase(_begin, _end);
    }

    template <typename T>
    void vector<T>::fill_init(size_type n, const value_type &elem)
    {
        if(n <= 16)
            init_space(n, 16);
        else
            init_space(n, 2 * n);
        std::uninitialized_fill_n(_begin, n, elem);
    }

    template <typename T>
    void vector<T>::range_init(iterator begin, iterator end)
    {
        size_type n;
        if(end - begin <= 16)
            n = 16;
        else
            n = end - begin;

        init_space(n, 2 * n);
        std::uninitialized_copy(begin, end, _begin);
    }

    template <typename T>
    void vector<T>::init_space(size_type size, size_type cap)
    {
        try {
            _begin = _allocator.allocate(cap);
            _end = _begin + size;
            _cap = _begin + cap;
        } catch (...) {
            _begin = nullptr;
            _end = nullptr;
            _cap = nullptr;
            throw;
        }
    }

    /*template <typename T>
    void vector<T>::try_init()
    {
        try {
            _begin = _allocator.allocate(16);
            _end = _begin;
            _cap = _begin + 16;
        } catch (...) {
            _begin = nullptr;
            _end = nullptr;
            _cap = nullptr;
            throw;
        }
    }*/

   /* template <typename T>
    void vector<T>::range_destroy(iterator begin, iterator end, size_type n)
    {
        _allocator.destroy(begin, end);
        _allocator.deallocate(begin, n);
    }*/

    template <typename T>
    void vector<T>::copy_insert(iterator pos, iterator beg, iterator end)
    {
        auto n = end - beg;
        if(n == 0)
            return pos;

        if(_cap - _end >= n) {
            const auto elem_after = _end - pos;
            auto old_end = _end;
            if(elem_after > n) {
                std::uninitialized_copy(_end - n, _end, _end);
                _end += n;
                std::copy_backward(pos, old_end - n, old_end);
                std::copy(beg, end, pos);
            } else {
                auto mid = beg;
                std::advance(beg, elem_after);
                _end = std::uninitialized_copy(mid, end, _end);
                _end = std::uninitialized_copy(pos, old_end, _end);
                std::copy(beg, elem_after, pos);
            }
        } else {
            const size_type old_size = size();
            const size_type new_size = old_size + old_size >= n ? old_size : n;

            iterator new_begin = _allocator.allocate(new_size);
            iterator new_end = new_begin;

            try {
                new_end = std::uninitialized_copy(_begin, pos, new_begin);
                new_end = std::uninitialized_copy(beg, end, new_end);
                new_end = std::uninitialized_copy(pos, _end, new_end);
            } catch(...) {
                range_destroy(new_begin, new_end, new_size);
                throw;
            }

            range_destroy(_begin, _end, capacity());
            _begin = new_begin;
            _end = new_end;
            _cap = _begin + new_size;
        }
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::fill_insert(iterator pos, size_type n, const value_type &elem)
    {
        if(n == 0)
            return pos;

        value_type temp(elem);
        if(_cap - _end >= n) {

            size_type after_elem = _end - pos;
            iterator old_end = _end;
            if(after_elem > n) {
                std::uninitialized_copy(_end - n, _end, _end);
                _end += n;
                std::copy_backward(pos, old_end - n, old_end);
                std::fill(pos, pos + n, temp);
            } else {
                std::uninitialized_fill_n(_end, n - after_elem, temp);
                _end += after_elem;
                std::uninitialized_copy(pos, old_end, _end);
                std::fill(pos, old_end, temp);
            }
        } else {
            const size_type old_size = size();
            const size_type new_size = old_size + old_size >= n ? old_size : n;

            iterator new_begin = _allocator.allocate(new_size);
            iterator new_end = new_begin;

            try {
                new_end = std::uninitialized_copy(_begin, pos, new_begin);
                new_end = std::uninitialized_fill_n(new_begin, n, temp);
                new_end = std::uninitialized_copy(pos, _end, new_end);
            } catch(...) {
                range_destroy(new_begin, new_end, new_size);
                throw;
            }
                range_destroy(_begin, _end, capacity());
                _begin = new_begin;
                _end = new_end;
                _cap = new_begin + new_size;
        }

        return pos;
    }

    template <typename T>
    void vector<T>::reinsert(size_type n)
    {
        auto new_begin = _allocator.allocate(n);
        auto new_end = new_begin;
        auto old_size = size();
        auto new_size = n;

        try {
            new_end = std::uninitialized_copy(_begin, _end, new_begin);
        } catch(...) {
            range_destroy(new_begin, new_end, new_size);
            throw;
        }

        range_destroy(_begin, _end, capacity());
        _begin = new_begin;
        _end = new_end;
        _cap = new_begin + new_size;
    }

    template <typename T>
    void vector<T>::reallocate_insert(iterator pos, const value_type &elem)
    {
        const size_type old_size = size();
        const size_type new_size = old_size != 0 ? 2 * old_size : 1;
        auto new_begin = _allocator.allocate(new_size);
        auto new_end = new_begin;

        try {
            new_end = std::uninitialized_copy(_begin, _end, new_begin);
            _allocator.construct(new_end, elem);
            ++new_end;
        } catch(...) {
            range_destroy(new_begin, new_end, new_size);
            throw;
        }

        range_destroy(_begin, _end, capacity());
        _begin = new_begin;
        _end = new_end;
        _cap = new_begin + new_size;
    }

}