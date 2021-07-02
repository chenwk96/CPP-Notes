#include <iostream>

using namespace std;

int main() {
    int a[5] = {0,1,2,3,4};
    char str[] = "hello world";
    cout << "cout a " << a << endl;
    cout << "cout &a " << &a << endl;
    cout << "cout &a[0] " << &a[0] << endl; 
    // cout << "cout a++ " << a++ << endl; // error: lvalue required as increment operand
    cout << "cout a + 1 "  << a + 1 << endl;
    cout << "cout *(a + 1) " << *(a + 1) << endl;

    cout << "sizeof(a): " << sizeof(a) << endl;
    cout << "\n";
    cout << "str " << str << endl;
    cout << "&str " << &str << endl;
    cout << "sizeof(str): " << sizeof(str) << endl;
    cout << "str[1] " << str[1] << endl;
    cout << "&str[1] " << &str[1] << endl;
    
    const char *str1 = "hello world";
    cout << "str1 " << str1 << endl;
    cout << "sizeof(str1): " << sizeof(str1) << endl;
    cout << "str1[1] " << str1[1] << endl;
    cout << "&str1[1] " << &str1[1] << endl;
    return 0;
}