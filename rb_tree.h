//
// Created by 陈彦骏 on 2019-07-18.
//

#ifndef MYTINYSTL_RB_TREE_H
#define MYTINYSTL_RB_TREE_H

namespace mystl {
    typedef bool _rb_tree_color_type;
    const _rb_tree_color_type _rb_tree_red = false;
    const _rb_tree_color_type _rb_tree_black = true;

    template <typename T>
    struct _rb_tree_node {
        typedef _rb_tree_color_type color_type;
        typedef _rb_tree_node* link_type;
        typedef T value_type;

        color_type color;
        link_type parent;
        link_type left;
        link_type right;
        value_type value_field;

        //static link_type minimum(link_type x);
        //static link_type maximum(link_type x);
    };

   /* template <typename T>
    typename _rb_tree_node::link_type _rb_tree_node::minimum(typename link_type x)
    {
        while(x != nullptr)
            x = x->left;
        return x;
    }

    template <typename T>
    typename _rb_tree_node::link_type _rb_tree_node::maximum(typename link_type x)
    {
        while(x != nullptr)
            x = x->right;
        return x;
    }*/


    template <typename T>
    struct _rb_tree_iterator {
        typedef bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef _rb_tree_iterator<T> iterator;
        typedef _rb_tree_iterator self;
        typedef _rb_tree_node<T>* link_type;

        _rb_tree_iterator() = default;
        _rb_tree_iterator(link_type x) { node = x; }
        _rb_tree_iterator(const iterator &rhs) { node = rhs.node; }
        //_rb_tree_iterator(const const_iterator &rhs) { node = rhs.node; }

        reference operator*() const { return node->value_field; }
        pointer operator->() const { return &(operator*()); }
        self& operator++();
        self operator++(int);
        self& operator--();
        self operator--(int);

        link_type node;

        void increment();
        void decrement();


    };

    template <typename T>
    inline typename _rb_tree_iterator<T>::self& _rb_tree_iterator<T>::operator++()
    {
        increment();
        return *this;
    }

    template <typename T>
    inline typename _rb_tree_iterator<T>::self _rb_tree_iterator<T>::operator++(int)
    {
        self tmp = *this;
        increment();
        return tmp;
    }

    template <typename T>
    inline typename _rb_tree_iterator<T>::self& _rb_tree_iterator<T>::operator--()
    {
        decrement();
        return *this;
    }

    template <typename T>
    inline typename _rb_tree_iterator<T>::self _rb_tree_iterator<T>::operator--(int)
    {
        self tmp = *this;
        decrement();
        return tmp;
    }

    template <typename T>
    void _rb_tree_iterator<T>::increment()
    {
        if(node->right != nullptr) {
            node = node->right;
            while(node->left != nullptr)
                node = node->left;
        } else {
            link_type y = node->parent;
            while(node == y->right) {
                node = y;
                y = y->parent;
            }

            if(node->right != y)
                node = y;
        }
    }

    template <typename T>
    void _rb_tree_iterator<T>::decrement()
    {
        if(node->color == _rb_tree_red && node->parent->parent == node)
            node = node->right;
        else if(node->left != nullptr) {
            link_type y = node->left;
            while(y->right != nullptr)
                y = y->right;
            node = y;
        } else {
            link_type y = node->parent;
            while(node == y->left) {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }


    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    class rb_tree {
    public:
        typedef _rb_tree_node<Value> _rb_tree_node;
        typedef _rb_tree_node* link_type;
        typedef _rb_tree_color_type color_type;
        typedef Key key_type;
        typedef Value value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef _rb_tree_iterator<Value> iterator;

        rb_tree(const Compare &comp = Compare())
            : node_count(0), key_compare(comp) { init(); }

        ~rb_tree() { clear(); put_node(header); }

        Compare key_comp() const { return key_compare; }
        iterator begin() const { return leftmost(); }
        iterator end() const { return header; }

        bool empty() const { return node_count == 0; }
        size_type size() const { return node_count; }

        std::pair<iterator, bool> insert_unique(const value_type &elem);
        iterator insert_equal(const value_type &elem);

        iterator find(const key_type &elem);

    private:
        size_type node_count;
        link_type header;
        Compare key_compare;
        std::allocator<_rb_tree_node> _allocator;

        void init();
        link_type get_node();
        void put_node(link_type p);
        link_type create_node(const value_type &elem);
        link_type clone_node(link_type p);
        void destroy_node(link_type p);
        void clear();

        link_type& root() const { return header->parent; }
        link_type& leftmost() const { return header->left; }
        link_type& rightmost() const { return header->right; }

        iterator _insert(link_type node, link_type node_parent, const value_type &elem);
    };

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    std::pair<typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator, bool>
        rb_tree<Key, Value, KeyOfValue, Compare>::insert_unique(const value_type &elem)
    {
        link_type y = header;
        link_type x = root();
        bool comp = true;
        while(x != nullptr) {
            y = x;
            comp = key_compare(KeyOfValue()(elem), KeyOfValue()(x->value_field));
            x = comp ? x->left : x->right;
        }

        iterator j(y);
        if(comp) {
            if(j == begin())
                return { _insert(x, y, elem), true };
            else
                --j;
        }

        if(key_compare(KeyOfValue(j->value_field), KeyOfValue(elem)))
            return { _insert(x, y, elem), true };

        return { j, false };
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator
        rb_tree<Key, Value, KeyOfValue, Compare>::insert_equal(const value_type &elem)
    {
        link_type y = header;
        link_type x = root();
        while(x != nullptr) {
            y = x;
            x = key_compare(KeyOfValue()(elem), KeyOfValue()(x->value_field)) ? x->left : x->right;
        }

        return _insert(x, y, elem);
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator rb_tree<Key, Value, KeyOfValue, Compare>::find(const key_type &elem)
    {
        link_type y = header;
        link_type x = root();

        while(x != nullptr) {
            if(!key_compare(KeyOfValue()(x), elem))
                y = x, x = x->left;
            else
                x = x->right;
        }

        iterator j(y);
        return (j == end() || key_compare(elem, KeyOfValue()(j->value_field)) ? end() : j);
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    void rb_tree<Key, Value, KeyOfValue, Compare>::init()
    {
        header = get_node();
        header->color = _rb_tree_red;

        root() = nullptr;
        leftmost() = header;
        rightmost() = header;
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    inline typename rb_tree<Key, Value, KeyOfValue, Compare>::link_type rb_tree<Key, Value, KeyOfValue, Compare>::get_node()
    {
        return _allocator.allocate(1);
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    inline void rb_tree<Key, Value, KeyOfValue, Compare>::put_node(link_type p)
    {
        _allocator.deallocate(p, 1);
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    typename rb_tree<Key, Value, KeyOfValue, Compare>::link_type rb_tree<Key, Value, KeyOfValue, Compare>::create_node(const value_type &elem)
    {
        link_type tmp;
        try {
            tmp = get_node();
            _allocator.construct(tmp, elem);
        } catch(...) {
            put_node(tmp);
            tmp = nullptr;
            throw;
        }

        return tmp;
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    typename rb_tree<Key, Value, KeyOfValue, Compare>::link_type rb_tree<Key, Value, KeyOfValue, Compare>::clone_node(link_type p)
    {
        link_type tmp = create_node(p->value_field);
        tmp->color = p->color;
        tmp->left = nullptr;
        tmp->right = nullptr;

        return tmp;
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    inline void rb_tree<Key, Value, KeyOfValue, Compare>::destroy_node(link_type p)
    {
        _allocator.destroy(p);
        put_node(p);
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    void rb_tree<Key, Value, KeyOfValue, Compare>::clear()
    {
        
    }

    template <typename Key, typename Value, typename KeyOfValue, typename Compare>
    typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator
        rb_tree<Key, Value, KeyOfValue, Compare>::_insert(link_type node, link_type node_parent, const value_type &elem)
    {
        link_type x = node;
        link_type y = node_parent;
        link_type z;

        if(y == header || x != nullptr || key_compare(KeyOfValue()(elem), KeyOfValue()(y->value_field))) {
            z = create_node(elem);
            y->left = z;
            if(y == header) {
                root() = z;
                rightmost() = z;
            } else if(y == leftmost())
                leftmost() = z;
        } else {
            z = create_node(elem);
            y->right = z;
            if(y == rightmost())
                rightmost() = z;
        }

        z->parent = y;
        z->left = nullptr;
        z->right = nullptr;

        _rb_tree_rebalance(z, header->parent);
        ++node_count;
        return static_cast<iterator>(z);
    }

    template <typename T>
    inline void _rb_tree_rebalance(_rb_tree_node<T>* node, _rb_tree_node<T>*& root)
    {
        node->color = _rb_tree_red;
        while(node != root && node->parent->color == _rb_tree_red) {
            if(node->parent == node->parent->parent->left) {
                _rb_tree_node<T>* y = node->parent->parent->right;
                if(y != nullptr && y->color == _rb_tree_red) {
                    node->parent->color = _rb_tree_black;
                    y->color = _rb_tree_black;
                    node->parent->parent->color = _rb_tree_red;
                    node = node->parent->parent;
                } else {
                    if(node == node->parent->right) {
                        _rb_tree_rotate_left(node->parent, root);
                    }
                    node->color = _rb_tree_black;
                    node->parent->color = _rb_tree_red;
                    _rb_tree_rotate_right(node->parent, root);
                }
            } else {
                _rb_tree_node<T>* y = node->parent->parent->left;
                if(y != nullptr && y->color == _rb_tree_red) {
                    node->parent->color = _rb_tree_black;
                    y->color = _rb_tree_black;
                    node->parent->parent->color = _rb_tree_red;
                    node = node->parent->parent;
                } else {
                    if(node == node->parent->left) {
                        _rb_tree_rotate_right(node->parent, root);
                    }
                    node->color = _rb_tree_black;
                    node->parent->color = _rb_tree_black;
                    _rb_tree_rotate_left(node->parent, root);
                }
            }
        }

        root->color = _rb_tree_black;
    }

    template <typename T>
    inline void _rb_tree_rotate_left(_rb_tree_node<T>* node, _rb_tree_node<T>*& root)
    {
        _rb_tree_node<T>* y = node->right;
        node->right = y->left;
        if(y->left != nullptr)
            y->left->parent = node;
        y->parent = node->parent;
        if(node == root)
            root = y;
        else if(node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;

        y->left = node;
        node->parent = y;
    }

    template <typename T>
    inline void _rb_tree_rotate_right(_rb_tree_node<T>* node, _rb_tree_node<T>*& root)
    {
        _rb_tree_node<T>* y = node->left;
        node->left = y->right;
        if(y->right != nullptr)
            y->right->parent = node;
        y->parent = node->parent;
        if(node == root)
            root = y;
        else if(node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;

        y->right = node;
        node->parent = y;
    }
}

#endif //MYTINYSTL_RB_TREE_H
