#include <iostream>
using namespace std;

class A
{
public:
    int x;
    void fa(){cout << __LINE__ << endl;}
};

class B : public A
{
public:
    int y;
    void fb(){cout << __LINE__ << endl;}
};

int main(int argc, char const *argv[])
{
    B b;
    A *pa = &b; // 将基类指针 pa 指向子类对象是安全的、可行的
    A &ra = b;  // 将基类引用 ra 指向子类对象是安全的、可行的

    pa->x = 100; // 可以访问对象b中的x
    pa->fa();    // 可以访问对象b中的fa()

    /*
    pa->y = 100; // 不可以访问对象b中的y，因为pa只能访问子类对象中的基类部分
    pa->fb();    // 不可以访问对象b中的fb()，因为pa只能访问子类对象中的基类部分
    */

    return 0;
}
