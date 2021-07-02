#include <iostream>

class A {
public:
    A(int x) : a(x), c(x) {
        std::cout << "构造函数" << std::endl;
    }
    ~A() {
        std::cout << "析构函数" << std::endl;
    }
private:
    int a;
    const int b = 10;
    const int c;
};

