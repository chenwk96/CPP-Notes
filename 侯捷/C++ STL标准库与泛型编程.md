# C++ STL标准库与泛型编程

侯捷C++ STL标准库与泛型编程课程听课过程中的一些记录



## 1. 六大部件

容器（Containers）、分配器（Allocators）、算法（Algorithms）、迭代器（Iterators）、适配器（Adapters）、仿函数（Functors）。



## 2.容器——结构与分类

1. Sequence Containers
   1. Array：大小固定
   2. Vector
   3. Deque
      1. deque
      2. stack<br>不提供迭代器
      3. queue<br>不提供迭代器
   4. List：双向链表
   5. Forward-List：单向链表
2. Associative Containers
   1. Set/Multiset，Unordered Set/Multiset
   2. Map/Multimap，Unordered Map/Multimap
