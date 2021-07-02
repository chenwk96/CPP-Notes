# README

C++ 一些记录，平时遇见的就直接在readme中记录

## sizeof & strlen()

- `sizeof`属于运算符，不是库函数，其结果在编译时期计算得到，因此不能用来得到动态分配的内存大小，而`strlen`属于库函数，其结果在运行期间计算得到；
- `sizeof`参数可以是任何数据或数据类型，而`strlen`的参数只能是字符指针，且该指针指向结尾为`\0`的字符串。

## const  

### const修饰成员函数

C++会保护const对象不被更新，为了防止类的对象出现意外更新，禁止const对象调用类的非常成员函数。因此，常成员函数为常对象的唯一对外接口。

* const对象只能访问const成员函数，而非const对象可以访问任意的成员函数，包括const成员函数；
* const对象的成员是不能修改的，而通过指针维护的对象是可以修改的；
* const成员函数不可以修改对象的数据，不管对象是否具有const性质。编译时以是否修改成员数据为依据进行检查。

```C++
class A {
public:
    int& getvalue() const {
        // a= 10;		// wrong!
        return a;
    }
private:
    int a;				// 非const成员变量
};
```

* 常成员函数的定义和声明都要含有const关键字
* 一个函数是否含有const关键字可以作为重载函数，const对象默认调用const函数，非const对象默认调用非const函数，如果没有非const函数，也可以调用const函数；
* const函数中不能更新目的对象的任何成员(mutable修饰的变量除外)，以此方法来保证const对象不被修改。
* 如果const成员函数想修改成员变量值，可以用`mutable`修饰目标成员变量。

### const修饰数据成员

类的常数据成员不能在任何函数中被赋值或修改，但**必须在构造函数中使用初始化列表的方式赋初值。**

```C++
class Example{
public:
    Example(int x, int y):a(x),b(y){} //初始化列表方式赋初值
    void print();
    void print() const;
private:
    const int a,b;
    const int c = 10;  
    static const int d = 10;
    static const int f;
};
const int Example::f = 20;
void Example::print() {cout<<"print():"<<a<<ends<<b<<endl;}
void Example::print() const {cout<<"print() const:"<<a<<ends<<b<<endl;}
```

如果为静态常数据成员，由于不属于具体对象，所以不能在构造函数里赋值，仍然应该在类外赋值。特别地，如果静态常量为整数或枚举类型，C++允许在类内定义时指定常量值。

### const修饰类对象

用const修饰的类对象，该对象内的任何成员变量都不能被修改。
因此不能调用该对象的任何非const成员函数，因为对非const成员函数的调用会有修改成员变量的企图。

### static、cosnt比较

**static:**

- static局部变量 将一个变量声明为函数的局部变量，那么这个局部变量在函数执行完成之后不会被释放，而是继续保留在内存中

- static 全局变量 表示一个变量在当前文件的全局内可访问

- static 函数 表示一个函数只能在当前文件中被访问

- static 类成员变量 表示这个成员为全类所共有

- static 类成员函数 表示这个函数为全类所共有，而且只能访问静态成员变量

- static关键字的作用：

  * 函数体内static变量的作用范围为该函数体，该变量的内存只被分配一次，因此其值在下次调用时仍维持上次的值；

    ```C++
    void func() {
        static int a = 1;
        cout << "static a " << a << endl;
        a++;
    }
    
    int main() {
        int a = 10;
        cout << "main a " << a << endl;   // main a 10
        func();							  // static a 1
        a++;
        func();							  // static a 2
        cout << "main a " << a << endl;   // main a 11
        return 0;
    }
    ```

  * 在模块内的static全局变量和函数可以被模块内的函数访问，但不能被模块外其它函数访问；

  * 在类中的static成员变量属于整个类所拥有，对类的所有对象只有一份拷贝；

  * 在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量。

**const**

* 阻止一个变量被改变
* 声明常量指针和指针常量
* const修饰形参，表明它是一个输入参数，在函数内部不能改变其值
* 对于类的成员函数，若指定其为const类型，则表明其是一个常函数，不能修改类的成员变量；
* 对于类的成员函数，有时候必须指定其返回值为const类型，以使得其返回值不为”左值”。

const定义的常量在超出其作用域之后其空间会被释放，而static定义的静态常量在函数执行后不会释放其存储空间。

static表示的是静态的。类的静态成员函数、静态成员变量是和类相关的，而不是和类的具体对象相关的。即使没有具体对象，也能调用类的静态成员函数和成员变量。一般类的静态函数几乎就是一个全局函数，只不过它的作用域限于包含它的文件中。

在C++中，static静态成员变量不能在类的内部初始化。在类的内部只是声明，定义必须在类定义体的外部，通常在类的实现文件中初始化，如：double Account::Rate=2.25;static关键字只能用于类定义体内部的声明中，定义时不能标示为static

在C++中，const成员变量也不能在类定义处初始化，只能通过构造函数初始化列表进行，并且必须有构造函数。

const数据成员只在某个对象生存期内是常量，而对于整个类而言却是可变的。因为类可以创建多个对象，不同的对象其const数据成员的值可以不同。所以不能在类的声明中初始化const数据成员，因为类的对象没被创建时，编译器不知道const数据成员的值是什么。

const数据成员的初始化只能在类的构造函数的初始化列表中进行。要想建立在整个类中都恒定的常量，应该用类中的枚举常量来实现，或者static cosnt。

> 静态存储区：内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。它主要存放静态数据、全局数据和常量。



## 函数名、函数名取地址以及函数指针

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test() {
    printf("1234567\n");
}

int main() {
    printf("0x%x\n", test);  // 0x8048328
    printf("0x%x\n", &test); // 0x8048328
}
```

按照&运算符本来的意义，它要求其操作数是一个对象，但函数名不是对象（函数是一个对象），本来&test是非法的，但很久以前有些编译器已经允许这样做，c/c++标准的制定者出于对象的概念已经有所发展的缘故，也承认了`&tes`t的合法性。

因此，对于`test`和`&test`你应该这样理解，`test`是函数的首地址，它的类型是`void ()`，`&test`表示一个指向函数`test`这个对象的地址，它的类型是`void (*)()`，因此`test`和`&tes`t所代表的地址值是一样的，但类型不一样。test是一个函数，&test表达式的值是一个指针！

这与数组名和数组名首元素地址类似。

在使用函数指针时，如果把函数名作为一个值使用，该函数自动转换成了指针，例如：

```C++
bool lengthCompare(const string&, const string&);

bool (*pf)(const string&, const string&);

pf = lengthCompare;    // pf指向名为lengthComare的函数
pf = &lengthCompare;   // 等价的赋值语句：取地址符是可选的

// 下面三个调用等价
bool b1 = pf("hello", "world");
bool b2 = (*pf)("hello", "world");
bool b2 = lengthCompare("hello", "world");
```

与数组类似，虽然不能定义函数类型的形参，但是形参可以是指向函数的指针。此时，形参看起来是函数类型，实际上却是当成指针使用。

```c++
// 函数声明
void useBigger(const string& s1, const string& s2, bool pf(const string&, const string&));

// 等价声明
void useBigger(const string& s1, const string& s2, bool (*pf)(const string&, const string&)); 

// 调用useBigger
useBigger(s1, s2, lengthCompare);

// 可以用类型别名和decltype简化
typedef bool Func(const string&, const string&);
typedef decltype(lengthCompare) Func2;
typedef bool (*FuncP)(const string&, const string&);
typedef decltype(lengthCompare) *FuncP2;

void useBigger(const string& s1, const string& s2, Func); 
void useBigger(const string& s1, const string& s2, FuncP2); 
```



## new

在C++中提到new，至少可能代表以下三种含义：**new operator**，**operator new**，**placement new**

### new operator

**new operator** 就是 **new** 操作符，不能被重载，也就是我们平常用的new

```c++
class Foo{ ... };
Foo *pf = new Foo;
delete pf;
```

实际做了：

```c++
Foo *pf;
void* buff = operator new(sizeof(Foo));
pf = static_cast<Foo*>(buff);
pf -> Foo::Foo();
```

### operator new

**operator new** 是函数，可以被重载，new operator 调用它用来分配内存，**通过重载它，可以改变 new operator 的功能**，默认有三种：

```C++
void* operator new (std::size_t size) throw (std::bad_alloc); 
void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw(); 
void* operator new (std::size_t size, void* ptr) throw(); 
```

1. 第一种分配size个字节的存储空间，并将对象类型进行内存对齐。如果成功，返回一个非空的指针指向首地址。失败抛出bad_alloc异常。 （`A* a = new A;`调用第一种)
2. 第二种在分配失败时不抛出异常，它返回一个NULL指针。 (`A* a = new(std::nothrow) A;` 调用第二种)
3. 第三种是 **placement new** 版本，它本质上是对 operator new 的重载，定义于#include 中，它不分配内存，调用合适的构造函数在 ptr 所指的地方构造一个对象，之后返回实参指针ptr。

重载 operator new 需要注意以下几点：

1. 重载时，返回类型必须声明为void*
2. 重载时，第一个参数类型必须为表达**要求分配空间的大小**（字节），类型为 **size_t**
3. 重载时，可以带其它参数

### placement new

**placement new** 它实现了**在指定内存地址上用指定类型的构造函数来构造一个对象**的功能，这块指定的地址既可以是栈，又可以是堆，placement 对此不加区分

placement new 的使用步骤如下：

```C++
Copy//1.分配内存
char* buff = new char[ sizeof(Complex) * N ];
memset( buff, 0, sizeof(Foo)*N );
//2.构建对象
Complex* pc = new (buff)Complex;
//3.使用对象
pc->XXXXXX();
//4.析构对象，显式的调用类的析构函数
pc->~Complex();
//5.销毁内存
delete[] buff;
```

上面5个步骤是标准的placement new的使用方法。placement new 是用来实现定位构造的，因此可以实现 new operator 三步操作中的**调用构造函数**这一步（在取得了足够内存空间后，在这块内存空间是上构造一个对象）

上面写的`pc->Complex::Complex(1,2);`这句话并不是一个标准的写法，正确的写法是使用 **placement new**：

```C++
#include <new.h>

int main()
{
    char* buff = new char[ sizeof(Complex) ];
	Complex* pc = new(buff) Complex(1,2);
    ...
}
```



## 对象移动

问题：`vector<string>`在重新分配内存的过程中，从旧内存将元素拷贝到新内存是不必要的，原因是拷贝后对象就立即销毁了，这样的话拷贝是极为低效的。移动而非拷贝对象会大幅的提高性能。

右值引用（rvalue reference），C++新标准为了支持移动操作引入的一种新的引用类型，即必须绑定到右值的引用。

左值有持久的状态，右值要么是字面值常量，要么是在表达式求值的过程中创建的临时对象。即右值引用所引用的对象将要被销毁且该对象没有其他用户，意味着右值引用的代码可以自由地接管所引用的对象的资源。

> 1. 【右值引用只能绑定到一个将要销毁的对象】（这句话在C++ primer p471）
>
> 2.  变量是左值
>
>    ```c++
>    int &&rr1 = 42;
>    int &&rr2 = rr1;   // 错误，表达式rr1是左值
>    // 可以将一个左值显示地转换为对应的右值引用类型
>    int &&r2 = std::move(rr1);
>    ```



### 移动构造函数和移动赋值运算符

移动构造函数的第一个参数是右值引用，移动构造函数必须确保移动后源对象处于一个销毁他是无害的状态。一旦资源完成移动，源对象必须不再指向被移动的资源（这些资源的所有权已经归属新创建的对象）。

```c++
StrVec::StrVec(StrVec &&s) noexcept // 移动操作不应该抛出任何异常
    : elements(s.elements), first_free(s.first_free), cap(s.cap) {
        s.elements = s.first_free = s.caps = nullptr; // 没有这一步，销毁源对象会释放掉移动的内存
    }

StrVec& StrVec::opreator=(StrVec &&rhs) noexcept {
    if (this != rhs) {
        free();			// 释放已有元素
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.caps = nullptr;
    }
    return *this;
}
```

只有当一个类没有定义任何自己版本的拷贝控制函数，且类的每个非static数据成员都可以移动时，编译器才会为他合成移动构造函数或者移动赋值运算符。

```c++
// 编译器会为X和hasX合成移动操作
struct X {
	int i;
    std::string s; // string定义了自己的移动操作
};

struct has {
	X men;   // X 有合成的移动操作
};
```

> 定义了移动构造函数和移动赋值运算符的类必须也要定义自己的拷贝操作，否则，默认的拷贝构造函数和拷贝赋值运算符是默认定义为删除的。



## 智能指针

### shared_ptr

```c++
// shared_ptr 独有操作
make_shared<T>(args);

shared_ptr<T> p(q);		// p是shared_ptr q的拷贝；增加q的引用计数，q中的指针必须能转换为T*

p = q;			// q,p都是shared_ptr，所保存的指针必须能相互转化。
				// 递减p的引用计数，递增q的引用计数；若p的引用计数为0，释放其管理的内存资源

p.unique();		// p.use_count() == 1, 返回true，否则返回false

p.use_count;	// 返回与p共享对象的指针指针数量
```

```c++
// 一个例子
shared_ptr<Foo> factory(T arg) {
    ...
    return make_shared<Foo>(arg);
}

void use_factory(T arg) {
	shared_ptr<Foo> p = factory(arg);
    ...
}// p离开了其作用域，递减其引用计数并检查其是否为0


shared_ptr<Foo> use_factory(T arg) {
	shared_ptr<Foo> p = factory(arg);
    ...
	return p; // 返回p时，引用计数进行递增操作
}// p离开了作用域，但指向的内存不会被释放
```

接收指针参数的智能指针的构造函数是explicit的，因此不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化：

```C++
shared_ptr<int> p1 = new int(1024); // wrong!
shared_ptr<int> p2(new int(1014)); // bingo

shared_ptr<int> clone(int p) {
    return new int(p);  // wrong!
    return shared_ptr<int>(new int(p));
}
```

智能指针定义了一个名为get的函数，它返回一个内置指针，指向智能指针管理的对象。此函数是为了向不能使用智能指针的代码传递一个内置指针，但是使用get返回的指针的代码不能delete此指针。

不能将另一个智能指针绑定到 get 返回的指针上:

```c++
shared_ptr<int> p(new int(42)); // 引用计数为1
int *q = p.get();
{
    // 两个独立的智能指针指向相同的内存
    shared_ptr<int>(q);
}// 程序块结束，q被销毁，指向的内存已经释放
int foo = *p; // 未定义：p指向的内存已经被释放
```

### unique_ptr

与shared_ptr不同，某个时刻只能有一个unique_ptr指向一个给定对象，当unique_ptr被销毁时，它所指向的对象也被销毁。没有类似make_shared的标准库函数返回一个unique_ptr。定义是需要将其绑定到一个new返回的指针上。

```C++
unique_ptr<double> p1;
unique_ptr<double> p2(new double(3.0));
```

一个unique_ptr拥有其指向的对象，其不支持普通的拷贝或赋值操作。

```c++
unqiue_ptr<T> u1;

unique_ptr<T, D> u2;    // u1使用delete释放指针，u2使用一个类型为D的可调用对象来释放指针

unique_ptr<T, D> u(d);  // 空unique_ptr, 指向类型为T的对象，用类型为D的对象d代替delete

u = nullptr;			// 释放u指向的对象，将u置为空

u.release(); 			// u放弃对指针的控制权，返回指针，并将u置空

u.reset();              // 释放u指向的对象

u.reset(q);				// 释放u指向的对象，令u指向q
u.reset(nullptr);
```

虽然不能拷贝或赋值unique_ptr，但可以通过release或reset将指针的所有权从一个（非const）unique_ptr转移给另一个unique_ptr:

```c++
unqiue_ptr<string> p2(p1.release());

unique_ptr<string> p3(new string("text"));
p2.reset(p3.release());
```

不能拷贝unique_ptr有一个例外，可以拷贝或赋值一个将要被销毁的unique_ptr，最常见的就是从函数返回一个unique_ptr

```C++
unique_ptr<int> clone(int p) {
    return unique_ptr<int>(new int(p)); // right! 移动构造
}
```



## lambda 表达式

函数式编程的概念。

C++ 使用了"**[]**"，称为“**lambda引出符**”来形成lambda表达式。

```C++
auto f1 = [](){};  // 相当于空函数，什么都不做

// ( )内声明入口参数
// { }定义函数体
// [ ]内进行变量捕捉 

// lambda 嵌套
auto f2 = [](){
    std::cout << "lambda f2" << std::endl;
    
    auto f3 = [](int x) {
        return x * x;
    };
    
    std::cout << f3(10) << std::endl;
}

// 每个 lambda 表达式都会有一个独特的类型，该类型只有编译器知道，必须要用auto

// "匿名"使用lambda表达式
vector<int> v = {3, 1, 8, 5, 0};
std::cout << *find_if(begin(v), end(v),  // 标准容器里的查找算法
				[](int x) {				 // 匿名lambda表达式，不需要auto赋值
                	return x >= 5;		 // 用作算法的判断条件
            	}
        	  )
     	  << std::endl;
```

**lambda的变量捕获**

* "[=]"表示按值捕获所有变量，表达式内部是值的拷贝，并且不能修改；
* "[&]"表示按引用捕获所有变量，内部以引用的方式使用，可以修改；
* 在"[]"里明确写出外部变量名，指定按值或者按引用捕获。

```C++
int x = 33;

auto f1 = [=]() {
    // x += 10;			// x 只读， 不允许修改
};

autp f2 = [&]() {
    x += 10;
};

auto f3 = [=, &x]() {   // 按引用捕获x，其余用值捕获
  	x += 20;  
};
```

**泛型的lambda**

C++14里，lambda可以实现泛型化

```C++
auto f = [](const auto& x) {    // 参数使用auto声明，泛型化
    return x + x;
};

cout << f(3) << endl;
couy << f(0,618) << endl;

string str = "matrix";
cout << f(str) << endl;
```



