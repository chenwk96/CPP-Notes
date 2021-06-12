# C++ 面向对象高级编程

侯捷C++面向对象高级编程课程过程中的一些记录，不能称之为笔记。

B站课程连接：

[C++面向对象高级编程(上)-基于对象＆面向对象_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Lb4y1R7fs?p=3&spm_id_from=pageDriver)

[C++面向对象高级编程(下)-兼谈对象模型（完结）_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1ZX4y157Bu?p=2&spm_id_from=pageDriver)

## C++编程简介



## 头文件与类的声明



## 构造函数

1. 变量的初始化、赋值

2. 不带指针的类多半不用写析构函数

3. 函数重载，名称相同的函数在经编译器编译后，实际名称取决于编译器

4. 构造函数可以放在private区，比如：单例模式（singleton），外界只能用一个

   ```c++
   class A {
   public:
       static A& getInstance();
       setup() { ... }
   private:
       A();
       A(const A& rhs);
       ...
   };
   
   A& A::getInstance() {
   	static A a;
       return a;
   }
   
   // A::getInstance().setup();
   ```

   



## 常量成员函数

1. 凡是有可能打破const的行为都是禁止的

2. 成员函数参数列表之后的const被称为成员函数限定符，其作用是将成员函数隐藏的this指针变为了常量指针

   >常量指针表示一个指针指向的变量为常量 `const int *p`
   >
   >指针常量表示该指针自身是一个常量，不可改变，始终指向同一个地址，在定义时必须初始化
   >
   >```
   >int a = 10, b = 20;
   >int *const p = &a;
   >*p = 30; // a = 30
   >```



## 参数传递：pass by value vs. pass by conference(to const)

1. 尽量不用pass by value
2. 传入的值不希望被改变的话就pass by conference to const



## 返回值：return by value vs. return by conference(to const)

1. 尽量return by conference
2. 不要返回局部变量的引用
3. 传递者无需知道接收者是以reference接收

##  友元

1. 自由取得friend的private成员

2. 相同class的各个objects互为friends

   > 自己原来根本没考虑过这个问题，比如类的成员函数以访问该类的另一个对象为参数，并且访问其私有成员



## 操作符重载

1. C++中操作符就是一种函数
2. 两种情况：成员函数和非成员函数



## temp object（临时对象） typename()



## 三大函数（big three）：拷贝构造、拷贝复制、析构

1. 没有自己编写的话，编译器会自己生成默认的，简单的不带指针的默认的一般就够用

2. 在string的构造函数中，侯捷老师讲的好像有点问题，只能在默认函数的声明中定义默认参数的值而不能同时在构造函数的定义中也声明

3. class with pointer members 必须有 **copy ctor** 和 **copy op=**

4. 浅拷贝 & 深拷贝

5. 拷贝赋值时需要先把自己指向的内容释放 

6. ==检测自我赋值（self assignment）==

   ![](https://i.loli.net/2021/06/08/ax94PZk5uRDJAfv.png)



## 所谓stack（栈），所谓heap（堆）

1. static local objects的生命在作用域结束后任然存在，直到整个程序结束

2. global object的生命在整个程序结束之后才结束，其作用域是整个程序

3. heap object的生命在它被deleted之际结束

   ```C++ 
   class Complex {...}
   ...
   {
   	Complex* p = new Complex;
   }
   // 会出现内存泄漏（memory leak）
   // 指针p的生命在作用域结束时结束，但p所指的heap object
   // 仍然存在，作用域之外再也看不到p，也就没有机会delete p
   ```

4. new  先分配内存，在调用ctor； delete先调用dtor，再释放内存

5. 动态分配内存块

6. 内存对齐

7. 指针的大小

   

## String类

1. null, 0, nullptr
2. 链式编程 `return *this`



## 扩展补充：类模板、函数模板、及其他

1. static成员，属于类的，而不是对象。静态成员函数没有this指针，只能处理静态成员变量

2. 静态成员变量一定要在类的外面定义（变量获得内存）

3. 调用静态函数的方式有两种：1. 通过对象调用；2. 通过class name 调

4. ==单例设计模式==

   <img src="https://i.loli.net/2021/06/09/kXQCpG1c52ISPhZ.png" alt="饿汉" style="zoom: 80%;" />

   <img src="https://i.loli.net/2021/06/09/QASosVTczaku3Ux.png" alt="懒汉" style="zoom: 80%;" />

5. namespace



## 组合和继承

1. 复合，表示has-a，构造由内而外，析构由外而内
2. adapter 适配器
3. 委托，delegation，Composition by reference，编译防火墙
4. 写时复制
5. 继承 is-a，构造由内而外，析构由外而内，base class的dtor必须是virtual，否则会出现undefined behavior



## Inheritance with virtual functions

1. 子类继承了父类的成员函数，实际上是继承了父类成员函数的调用权，子类可以调用父类的成员函数

2. 成员函数：

   ![](https://i.loli.net/2021/06/09/UxkPGSTIC9Ep2b1.png)

3. Template Method

4. 继承和复合组合下的构造与析构

5. 观察者设计模式



## 转换函数

1. 没有返回类型，通常都会添上`const`

   ![](https://i.loli.net/2021/06/10/rQanMb7214VsG8J.png)

2. 一个类可以有有多个转换函数，只要合理

3. 转换函数的类型可以是自定义类型



## non-explicit-one-argument ctor

1. argument和parameter有区别

   ![](https://i.loli.net/2021/06/10/iDAHSZctByrTj8u.png)

2. ambiguous，因二义而报错（将转换函数和non-explicit-one-argument ctor两张ppt内容合在一起就会发生ambiguous）



## explicit-one-argument ctor

![](https://i.loli.net/2021/06/10/84jnLFBWPDYHNTO.png)



## pointer-like classes

1. 有关智能指针
2. 有关迭代器



## function-like classes, 所谓仿函数

1. 重载`operator ()`
2. 标准库中有很多仿函数，都有继承一些base classe（unary_functon、binary_function）



## namespace



## class template，类模板



## function templ，函数模板

```c++
template <class T> // template <typename T>
inline
const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}
```



## 成员模板

1. 子类初始化父类，反之不行（向上转型）



## specialization 模板特化



## partial specialization 偏特化

1. 个数上的偏
2. 范围上的偏



## 模板模板参数

很懵



## variadic templates(since C++11) 



## reference

1. 引用底层实现都是指针，但从逻辑角度讲，引用就是别名，类型和引用的类型一样（底层为指针）
2. 引用一定要有初值，之后就无法再改变去重新代表别的东西

> const函数可以被非const对象和const对象调用，如果重载了同名同参数类型的非const函数，非const对象会优先调用非const函数，const对象只会调用const函数，两种函数可共存。



##  对象模型：关于vptr和vtbl

1. 虚函数？
2. 静态绑定、动态绑定

