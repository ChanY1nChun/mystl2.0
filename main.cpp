#include <iostream>
#include <functional>

#include "vector.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "rb_tree.h"
#include "functional.h"
#include "allocator.h"
#include "alloc.h"
#include "heap.h"
#include "priority_queue.h"

template <typename T>
void PrintVec(typename mystl::vector<T>::const_iterator begin, typename mystl::vector<T>::const_iterator end)
{
    for(auto i = begin; i != end; ++i)
        std::cout << *i << " " ;
    std::cout << std::endl;
}

template <typename T>
void PrintVecInfo(const mystl::vector<T> &vec)
{
    std::cout << "empty: " << std::boolalpha << vec.empty() << std::endl;
    std::cout << "size: " << vec.size() << std::endl;
    std::cout << "capacity: " << vec.capacity() << std::endl;
}

template <typename T>  //测试默认构造函数
void test1Vec()
{
    mystl::vector<int> my_vec;
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
}

template <typename T>  //测试拷贝构造函数
void test2Vec()
{
    mystl::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    mystl::vector<int> my_vec(vec);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
}

template <typename T> //测试利用默认构函数生产一个大小为n的vector
void test3Vec()
{
    mystl::vector<int> my_vec(3);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
}

template <typename T> //测试建立一个大小为n的vector，每个元素的值都为elem
void test4Vec()
{
    mystl::vector<int> my_vec(4, 2);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
}

template <typename T> //测试建立一个vector， 以区间【beg, end)作为元素初值
void test5Vec()
{
    mystl::vector<int> vec(4, 2);
    mystl::vector<int> my_vec(vec.cbegin(), vec.cend());
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
}

template <typename T> //测试C++11,以初值列ilist的元素作为初值
void test6Vec()
{
    mystl::vector<int> my_vec{1,2,3,4};
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
}

template <typename T> //测试push_back() pop_back()
void test7Vec()
{
    mystl::vector<int> my_vec{1,2,3,4,5};
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(6);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(7);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(8);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(9);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(10);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.push_back(11);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
    my_vec.pop_back();
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo(my_vec);
}

template <typename T> //测试 reserve() shrink_to_fit()
void test8Vec()
{
    mystl::vector<int> my_vec{1,2,3,4};
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.reserve(10);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.shrink_to_fit();
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
}

template <typename T> //测试 resize() erase() clear()
void test9Vec()
{
    mystl::vector<int> my_vec{1,2,3,4};
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.resize(5);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.erase(my_vec.end() - 1);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.clear();
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);
    my_vec.resize(3);
    PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    PrintVecInfo<int>(my_vec);

}

template <typename T> //测试 insert()
void test10Vec()
{
    mystl::vector<int> my_vec{1,2,3,4};
    //PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    //PrintVecInfo<int>(my_vec);
    my_vec.insert(my_vec.end(), 5);
    //PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    //PrintVecInfo<int>(my_vec);
    my_vec.insert(my_vec.end(), 4);
    //PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    //PrintVecInfo<int>(my_vec);
    my_vec.insert(my_vec.end(), 3, 4);
    //PrintVec<int>(my_vec.cbegin(), my_vec.cend());
    //PrintVecInfo<int>(my_vec);
    mystl::vector<int> vec{1,2,3};
    //my_vec.insert(vec.end(), {5,6,7,8,1,1,1});
    my_vec.insert(vec.end(), my_vec.begin(), my_vec.end());
    PrintVec<int>(vec.cbegin(), vec.cend());
    PrintVecInfo<int>(vec);
    PrintVec<int>(vec.cbegin(), vec.cend());
    PrintVecInfo<int>(vec);
}

template <typename T>
void PrintList(typename mystl::list<T>::const_iterator begin, typename mystl::list<T>::const_iterator end)
{
    for(auto i = begin; i != end; ++i)
        std::cout << *i << " " ;
    std::cout << std::endl;
}

template <typename T>
void PrintListInfo(const mystl::list<T> &list)
{
    std::cout << "empty: " << std::boolalpha << list.empty() << std::endl;
    std::cout << "size: " << list.size() << std::endl;
}

template <typename T> //测试 front() back() push_front() push_back() pop_front() pop_back()
void test1List()
{
    mystl::list<T> my_list;
    my_list.push_back(2);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

    my_list.push_back(3);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

    my_list.push_front(1);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

    std::cout <<  "front: " << my_list.front() << std::endl;
    std::cout << "back: " << my_list.back() << std::endl;

    my_list.pop_front();
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

    my_list.pop_back();
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

    my_list.pop_back();
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
}

template <typename T> //测试 insert() erase()
void test2List()
{
    mystl::list<T> my_list;
    mystl::list<T> my_list2;
    my_list2.push_back(2);
    my_list2.push_back(3);
    my_list.insert(my_list.end(), 2);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.insert(my_list.end(), 3, 3);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.insert(my_list.begin(), my_list2.begin(), my_list2.end());
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.erase(my_list.begin());
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.erase(my_list.begin(), my_list.end());
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
}

template <typename T> //测试 remove() resize() clear() unique()
void test3List()
{
    mystl::list<T> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.remove(2);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.push_back(2);
    my_list.push_back(2);
    my_list.unique();
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.resize(5);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.resize(2);
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);
    my_list.clear();
    PrintList<int>(my_list.cbegin(), my_list.cend());
    PrintListInfo<int>(my_list);

}

template <typename T>
void test1stack()
{
    mystl::stack<T, mystl::vector<T>> my_stack;
    my_stack.push(1);
    my_stack.push(3);
    my_stack.push(5);
    my_stack.push(7);

    std::cout << my_stack.size() << std::endl;
    std::cout << my_stack.top() << std::endl;

    my_stack.pop();
    std::cout << my_stack.top() << std::endl;
    my_stack.pop();
    std::cout << my_stack.top() << std::endl;
    my_stack.pop();
    std::cout << my_stack.top() << std::endl;
    my_stack.pop();
    std::cout << my_stack.top() << std::endl;
}

template <typename T>
void test1queue()
{
    mystl::queue<T> my_queue;
    my_queue.push(1);
    my_queue.push(3);
    my_queue.push(5);
    my_queue.push(7);

    std::cout << my_queue.size() << std::endl;
    std::cout << my_queue.front() << std::endl;

    my_queue.pop();
    std::cout << my_queue.front() << std::endl;
    my_queue.pop();
    std::cout << my_queue.front() << std::endl;
    my_queue.pop();
    std::cout << my_queue.front() << std::endl;
    my_queue.pop();
    std::cout << my_queue.front() << std::endl;
}

/*template <typename T>
void test1rbtree()
{
    mystl::rb_tree<T, T, std::identity<T>, std::less<T>> my_tree;
}*/


void functional() {
    using std::cout;
    using std::endl;
    using namespace mystl;
    using std::boolalpha;
    cout << plus<int>()(3, 5) << endl;
    cout << minus<int>()(3, 5) << endl;
    cout << multiplies<int>()(3, 5) << endl;
    cout << divides<int>()(3, 5) << endl;
    cout << modulus<int>()(3, 5) << endl;
    cout << negate<int>()(5) << endl;

    cout << boolalpha << equal_to<int>()(3, 5) << endl;
    cout << boolalpha << not_equal_to<int>()(3, 5) << endl;
    cout << boolalpha << greater<int>()(3, 5) << endl;
    cout << boolalpha << greater_equal<int>()(3, 5) << endl;
    cout << boolalpha << less<int>()(3, 5) << endl;
    cout << boolalpha << less_equal<int>()(3, 5) << endl;

    cout << boolalpha << logical_and<int>()(1, 0) << endl;
    cout << boolalpha << logical_or<int>()(1, 0) << endl;
    cout << boolalpha << logical_not<int>()(0) << endl;

}

void test_allocator()
{
    class test {
    public:
        test(int* i) : i_(i) {
            std::cout << "test ctor" << std::endl;
        }

        ~test() {
            std::cout << "test dctor and i_ = " << *i_ << std::endl;
        }
    private:
        int* i_;
    };
    mystl::allocator<test> _alloc;
    auto ptr = _alloc.allocate();
    _alloc.construct(ptr, new int(3));
    _alloc.destroy(ptr);
    _alloc.deallocate(ptr);
}

void test_alloc()
{
    class test {
    public:
        test(int* i) : i_(i) {
            std::cout << "test ctor" << std::endl;
        }

        ~test() {
            std::cout << "test dctor and i_ = " << *i_ << std::endl;
        }
    private:
        int* i_;
    };
    //mystl::alloc _alloc;
    test* ptr = static_cast<test*>(mystl::alloc::allocate(sizeof(test)));
    mystl::construct(ptr, new int(3));
    mystl::destroy(ptr);
    mystl::alloc::deallocate(ptr, sizeof(test));
}

void test_heap()
{
    mystl::vector<int> ivec{0,1,2,3,4,8,9,3,5};
    mystl::make_heap(ivec.begin(), ivec.end());
    std::for_each(ivec.begin(), ivec.end(), [](const int i) { std::cout << i << ' '; });
    std::cout << std::endl;

    ivec.push_back(7);
    mystl::push_heap(ivec.begin(), ivec.end());
    std::for_each(ivec.begin(), ivec.end(), [](const int i) { std::cout << i << ' '; });
    std::cout << std::endl;

    mystl::pop_heap(ivec.begin(), ivec.end());
    std::cout << ivec.back() << std::endl;
    ivec.pop_back();
    std::for_each(ivec.begin(), ivec.end(), [](const int i) { std::cout << i << ' '; });
    std::cout << std::endl;

    mystl::sort_heap(ivec.begin(), ivec.end());
    std::for_each(ivec.begin(), ivec.end(), [](const int i) { std::cout << i << ' '; });
    std::cout << std::endl;

}

void test_priority_queue()
{
    mystl::vector<int> vec{0,1,2,3,4,8,9,3,5};
    mystl::priority_queue<int> pq(vec.begin(), vec.end());
    std::cout << "size = " << pq.size() << std::endl;
    for(int i = 0; i < pq.size(); ++i)
        std::cout << pq.top() << ' ';
    std::cout << std::endl;
    while(!pq.empty()) {
        std::cout << pq.top() << ' ';
        pq.pop();
    }
}

int main() {
    //test1Vec<int>();
    //test2Vec<int>();
    //test3Vec<int>();
    //test4Vec<int>();
    //test5Vec<int>();
    //test6Vec<int>();
    //test7Vec<int>();
    //test8Vec<int>();
    //test9Vec<int>();
    //test10Vec<int>();
    //test1List<int>();
    //test2List<int>();
    //test3List<int>();
    //test1stack<int>();
    //test1queue<int>();
    //test1rbtree<int>();
    //functional();
    //test_allocator();
    //test_alloc();
    //test_heap();
    test_priority_queue();
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}