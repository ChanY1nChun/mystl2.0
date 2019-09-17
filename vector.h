//
// Created by 陈彦骏 on 2019-07-14.
//

#ifndef MYTINYSTL_VECTOR_H
#define MYTINYSTL_VECTOR_H

#include <new>
#include <initializer_list>
#include <algorithm>
#include <memory>


namespace mystl {

    template <typename T>
    class vector {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        vector() { try_init(); } //默认构造函数
        vector(const vector &vec); //拷贝构造函数
        vector(size_type n); //利用默认构函数生产一个大小为n的vector
        vector(size_type n, const value_type &elem); //建立一个大小为n的vector，每个元素的值都为elem
        vector(const_iterator beg, const_iterator end); //建立一个vector， 以区间【beg, end)作为元素初值
        vector(std::initializer_list<value_type> ilist); //C++11,以初值列ilist的元素作为初值
        //vector(vector &&vec); //移动构造函数
        ~vector();//析构函数

        //vector& operator=(const vector &rhs);
        //vector& operator=(std::initializer_list<value_type> ilist);
        //void assign(size_type n, const value_type &elem);
        //void assign(iterator beg, iterator end);
        //void assign(std::initializer_list<value_type> ilist);
        //void swap(vector &vec) noexcept;

        bool empty() const noexcept { return cend() == cbegin() ? true : false; }
        size_type size() const noexcept { return cend() - cbegin(); }
        size_type capacity() const noexcept { return static_cast<size_type>(_cap - _begin); }
        void reserve(size_type n);
        void shrink_to_fit();

        //bool operator==(const vector &lhs, const vector &rhs);
        //bool operator!=(const vector &lhs, const vector &rhs);
        //bool operator<(const vector &lhs, const vector &rhs);
        //bool operator>(const vector &lhs, const vector &rhs);
        //bool operator<=(const vector &lhs, const vector &rhs);
        //bool operator>=(const vector &lhs, const vector &rhs);

        reference operator[](size_type n) { return *(begin() + n); }
        const_reference operator[](size_type n) const { return *(cbegin() + n); }
        reference at(size_type n) { return *(begin() + n); }
        const_reference at(size_type n) const { return *(cbegin() + n); }
        reference front() { return *begin(); }
        const_reference front() const { return *cbegin(); }
        reference back() { return *(end() - 1); }
        const_reference back() const { return *(cend() - 1); }

        iterator begin() noexcept { return _begin; }
        const_iterator begin() const noexcept { return _begin; }
        const_iterator cbegin() const noexcept { return _begin;}

        iterator end() noexcept { return _end; }
        const_iterator end() const noexcept { return _end; }
        const_iterator cend() const noexcept { return _end; }

        void push_back(const value_type &elem);
        //void push_back(value &&elem);
        void pop_back() noexcept;
        iterator insert(iterator pos, const value_type &elem);
        //iterator insert(const-iterator pos, value_type &&elem);
        iterator insert(iterator pos, size_type n, const value_type &elem);
        void insert(iterator pos, iterator beg, iterator end);
        void insert(iterator pos, std::initializer_list<value_type> ilist);

        iterator erase(iterator pos);
        iterator erase(iterator beg, iterator end);
        void resize(size_type n);
        void resize(size_type n, const value_type &elem);
        void clear() noexcept;


    private:
        iterator _begin;
        iterator _end;
        iterator _cap;
        std::allocator<T> _allocator;

        void fill_init(size_type n, const value_type &elem);
        void range_init(const_iterator begin, const_iterator end);
        void init_space(size_type size, size_type cap);
        void try_init();
        void range_destroy(iterator begin, iterator end, size_type n);
        void copy_insert(iterator pos, iterator beg, iterator end);
        iterator fill_insert(iterator pos, size_type n, const value_type &elem);
        void reinsert(size_type n);
        void reallocate_insert(iterator pos, const value_type &elem);
    };


    template <typename T>
    vector<T>::vector(const vector &vec) //拷贝构造函数
    {
        range_init(vec.cbegin(), vec.cend());
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
    vector<T>::vector(const_iterator beg, const_iterator end) //建立一个vector， 以区间【beg, end)作为元素初值
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

    template <typename T>
    vector<T>::~vector()  //析构函数
    {
        range_destroy(begin(), end(), capacity());
        _begin = _end = _cap = nullptr;
    }

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
    typename vector<T>::iterator vector<T>::insert(iterator pos, const value_type &elem)
    {
        return insert(pos, 1, elem);
    }

    /*template <typename T>
    iterator insert(const_iterator pos, value_type &&elem);*/

    template <typename T>
    typename vector<T>::iterator vector<T>::insert(iterator pos, size_type n, const value_type &elem)
    {
        return fill_insert(pos, n, elem);
    }

    template <typename T>
    void vector<T>::insert(iterator pos, iterator beg, iterator end)
    {
        copy_insert(pos, beg, end);
    }

    template <typename T>
    void vector<T>::insert(iterator pos, std::initializer_list<value_type> ilist)
    {
        iterator beg = const_cast<iterator>(ilist.begin());
        iterator end = const_cast<iterator>(ilist.end());
        copy_insert(pos, beg, end);
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::erase(iterator pos)
    {
        if(pos + 1 != end())
            std::copy(pos + 1, _end, pos);
        --_end;
        _allocator.destroy(_end);
        return pos;

    }

    template <typename T>
    typename vector<T>::iterator vector<T>::erase(iterator beg, iterator end)
    {
        iterator i = std::copy(end, _end, beg);
        while(i != _end)
        _allocator.destroy(i++);
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
            insert(_end, n - size(), elem);
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
    void vector<T>::range_init(const_iterator begin,const_iterator end)
    {
        size_type n;
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

    template <typename T>
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
    }

     template <typename T>
     void vector<T>::range_destroy(iterator begin, iterator end, size_type n)
     {
         auto temp = begin;
         if(temp != end)
            _allocator.destroy(temp++);
         _allocator.deallocate(begin, n);
     }

    template <typename T>
    void vector<T>::copy_insert(iterator pos, iterator beg, iterator end)
    {
        auto n = end - beg;
        if(n == 0)
            return;

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
                std::copy(beg, mid, pos);
            }
        } else {
            const size_type old_size = size();
            const size_type new_size = (old_size + n) * 2;

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
        auto xpos = pos - _begin;
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
                _end += n - after_elem;
                std::uninitialized_copy(pos, old_end, _end);
                _end += after_elem;
                std::fill(pos, old_end, temp);
            }
        } else {
            const size_type old_size = size();
            const size_type new_size = (old_size + n) * 2;


            iterator new_begin = _allocator.allocate(new_size);
            iterator new_end = new_begin;

            try {
                new_end = std::uninitialized_copy(_begin, pos, new_begin);
                new_end = std::uninitialized_fill_n(new_end, n, temp);
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

        return _begin + xpos;
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
        if(_end < _cap)
            return;
        const size_type old_size = size();
        const size_type new_size = 2 * old_size;
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

#endif //MYTINYSTL_VECTOR_H
