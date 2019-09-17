cmake_minimum_required(VERSION 3.14)
project(MyTinySTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyTinySTL main.cpp vector.h list.h stack.h queue.h deque.h rb_tree.h insert_iterator.h reverse_iterator.h stream_iterator.h functional.h construct.h alloc.h uninitialized.h type_traits.h heap.h priority_queue.h)