#include <iostream>

int main() {
    int a = 10;
    const int& ref_a = a;
    int b = 1;
    // ref_a = b;  // wrong

    int* ptr = &a;
    const int* ptr1 = &a;
    ptr1 = &b;

    std::cout << ref_a << std::endl;
}