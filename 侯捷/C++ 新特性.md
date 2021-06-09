# C++ 新特性

侯捷C++新特性课程学习中的一些记录



## Variadic Templates

数量不定的模板参数，可以方便地完成recursive function call、recursive inheritance。



## Spaces in Template Expressions

```c++
vector<list<int> >; // ok in each C++ version
vector<list<int>>;  // ok since C++11
```



## nullptr and std::nullter_t



## auto

1. Using auto is <u>especially useful where the type is a pretty long and/or complicated expression.</u>



## Uniform Initialization



## Initializer list



## explicit

告诉编译器不要自作聪明，要明确地调用构造函数，不要隐式转换

![](https://i.loli.net/2021/06/09/MSwgbzCWIYsJZR8.png)

在C++11 中，explicit for ctors taking more than one argument



## range-based for statement



## =default, =delete

1. 如果自行定义一个ctor，编译器就不会自动生成default ctor
2. 如果强行加上`=default`，就可以重新获得并使用default ctor
3. 拷贝构造函数，复制函数只能有一个，强行加上`=default`会报错
4. 一般函数不能加上`=default`，但能加上`=delete`
5. `=delete`可用于任何函数身上



## Alias Template