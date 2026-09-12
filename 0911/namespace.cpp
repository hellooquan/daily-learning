#include <iostream>

using namespace std;
int y=11;
int t=13;
namespace YY
{
    int y=23;
    namespace TT
    {
        int t=33;
    }
}

void func(void)
{
    cout << "全局变量y=" << y << endl;
    cout << "全局变量t=" << t << endl;
    cout << "YY中的y=" << YY::y << endl;
    cout << "YY中的TT中的t=" << YY::TT::t << endl;
}
int main (int argc, char *argv[]) 
{
    func();

    return 0;
}
