//
// Created by 陈彦骏 on 2019-09-02.
//

#ifndef MYTINYSTL_STREAM_ITERATOR_H
#define MYTINYSTL_STREAM_ITERATOR_H

#include <iostream>

namespace mystl {

    template <typename T, typename Distance = ptrdiff_t>
    class istream_iterator {
    public:
        friend bool operator==(const istream_iterator& x, const istream_iterator& y);
        friend bool operator!=(const istream_iterator& x, const istream_iterator& y);

        typedef input_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        istream_iterator() : stream(&cin), end_marker(false) { }
        istream_iterator(std::istream& s) : stream(&s) { read(); }

        reference operator*() const { return value; }
        pointer operator->() const { return &(operator*()); }
        istream_iterator& operator++() {
            read();
            return *this;
        }

        istream_iterator& operator++(int) {
            read();
            return *this;
        }

    private:
        std::istream* stream;
        T value;
        bool end_marker;
        void read() {
            end_marker = (*stream) ? true : false;
            if(end_marker) *stream >> value;
            end_marker = (*stream) ? true : false;
        }
    };

    template <typename T, typename Distance = ptrdiff_t>
    inline bool operator==(const istream_iterator<T, Distance>& x, const istream_iterator<T, Distance>& y)
    {
        return x.end_marker == y.end_marker;
    }

    template <typename T, typename Distance = ptrdiff_t>
    inline bool operator!=(const istream_iterator<T, Distance>& x, const istream_iterator<T, Distance>& y)
    {
        return x.end_marker != y.end_marker;
    }

    template <typename T>
    class ostream_iterator {
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        ostream_iterator(std::ostream& s) : stream(&s), string(0) { }
        ostream_iterator(std::ostream& s, const char* c) : stream(&s), string(c) { }

        ostream_iterator& operator=(const T& value) {
            *stream << value;
            if(string) *stream << string;
            return *this;
        }

        ostream_iterator& operator*() const noexcept { return *this; }
        ostream_iterator& operator++() const noexcept { return *this; }
        ostream_iterator& operator++(int) const noexcept { return *this; }

    private:
        std::ostream* stream;
        const char* string;
    };


}

#endif //MYTINYSTL_STREAM_ITERATOR_H
