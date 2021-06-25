# C++ STL标准库与泛型编程

侯捷C++ STL标准库与泛型编程课程听课过程中的一些记录。附带《STL源码剖析》一些记录



## 1. 六大部件

容器（Containers）、分配器（Allocators）、算法（Algorithms）、迭代器（Iterators）、适配器（Adapters）、仿函数（Functors）。



## 2. 容器——结构与分类

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



## 3. 基础：操作符重载/模板

泛化，特化，偏特化



## 4. 分配器 allocators

分配器一层一层调用下去最后是`malloc,free`，会带来额外开销

GNU C 2.9分配器采用了内存池技术，到了4.9版本取消了这种设计。

这一章节需进一步学习内存管理

SGI中的空间配置器与标准不同，其不叫allocator而是alloc。虽然SGI也定义了一个名为allocator的配置器，但SGI从未使用，也不建议使用，只是在C++的`::opreator new`和`::operator delete`做了一层封装

### SGI 的`std::alloc`

一般习C++内存操作和释放操作惯使用：

```c++
class Foo{ ... };
Foo* pf = new Foo;
delete pf;
```

`new`其实内含两个阶段的操作：1. 调用`::opreator new`配置内存；2. 调用`Foo::Foo()`构造对象内容。`delete`同理，先析构后释放。

为了精密分工，STL allocator将这两阶段操作分开，内存操作与释放：`alloc::allocate()`，`alloc::deallocate()`。对象构造与析构：`::construct()`，`::destory()`。



## 5. 容器，结构与分类

<img src="https://i.loli.net/2021/06/23/RuZ7pkQbH2LjWNF.png" style="zoom:70%;" />

### 5.1 list

Iterator是一个聪明的指针，除了vector和array外Iterator都是一个class，才能设计出聪明的动作，如`++`，`--`。Iterator会模拟指针的操作，里面会有大量的操作符重载。

c++语言规格，prefix：`++i`，重载时不需要参数，postfix：`i++`，重载时需要参数。
