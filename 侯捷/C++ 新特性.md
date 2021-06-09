# C++ 新特性

侯捷C++新特性课程学习中的一些记录



## Variadic Templates

数量不定的模板参数，可以方便地完成recursive function call、recursive inheritance。



## Spaces in Template Expressions

```c++
vector<list<int> >; // ok in each C++ version
vector<list<int>>;  // ok since C++11
```



