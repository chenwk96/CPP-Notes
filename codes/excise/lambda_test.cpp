#include <iostream>

using namespace std;

int main() {
    int n = 10;

    /*
    auto func = [](int x) {
        cout << x * x << endl;
    };
    */
   
    auto func = [=](int x) {
        // "捕获"外部变量
        cout << x * n << endl;
    };
    func(3);
    return 0;
}