#include <iostream>
using namespace std;

struct Counter {
    int n = 0;
    Counter &add(int k) { n += k; return *this; }   // 返回 *this 的引用:支持链式调用
};

int main(int argc, char const *argv[])
{
    Counter c;
    c.add(1).add(2);
    cout << "c.n: " << c.n << endl;

    return 0;
}
