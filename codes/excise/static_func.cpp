#include <iostream>

using namespace std;

void func() {
    static int a = 1;
    cout << "static a " << a << endl;
    a++;
}

int main() {
    int a = 10;
    cout << "main a " << a << endl;
    func();
    a++;
    func();
    cout << "main a " << a << endl;
    return 0;
}