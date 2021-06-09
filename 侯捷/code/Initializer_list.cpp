#include <iostream>
#include <vector>

using namespace std;

int main() {
    int i;
    int j{};
    int* p;
    int* q{};

    cout << i << " " << j << " " << p << " " << q << endl;

    int x1(5.3);
    int x2 = 5.3;
    int x3{5.0};

    int x4 = {5.3};

    char c1{7};
    char c2{99999};

    vector<int> v1 {1, 2, 4, 5};
    vector<int> v2 {1, 2.3, 4, 5.6};

    for (auto& elem : v2) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}