//
// Created by 陈彦骏 on 2019-09-02.
//

#ifndef MYTINYSTL_REVERSE_ITERATOR_H
#define MYTINYSTL_REVERSE_ITERATOR_H

#include "iterator.h"

namespace mystl {

    template <typename Iterator>
    class reverse_iterator {
    public:
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

        typedef Iterator iterator_type;
        typedef reverse_iterator self;

        reverse_iterator() = default;
        explicit reverse_iterator(iterator_type x) : current(x) { }
        reverse_iterator(const self& x) : current(x.current) { }

        iterator_type base() const { return current; }
        reference operator*() const {
            Iterator temp = current;
            return *--temp;
        }
        pointer operator->() const {
            return &(operator*());
        }

        self& operator++() {
            --current;
            return *this;
        }

        self operator++(int) {
            self temp = *this;
            --current;
            return temp;
        }

        self& operator--() {
            ++current;
            return *this;
        }

        self operator--(int) {
            self temp = *this;
            ++current;
            return temp;
        }

        self operator+(difference_type n) const {
            return self(current - n);
        }

        self& operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        self operator-(difference_type n) const {
            return self(current + n);
        }

        self& operator-=(difference_type n) {
            current += n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

    private:
        Iterator current;
    };

    template <typename Iterator>
    inline bool operator==(const reverse_iterator<Iterator>& lhs, cosnt reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator>
    inline bool operator!=(const reverse_iterator<Iterator>& lhs, cosnt reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
    }

}

#endif //MYTINYSTL_REVERSE_ITERATOR_H
