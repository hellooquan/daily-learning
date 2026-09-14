#include <iostream>
using namespace std;

#ifdef DONE
// 一个简易除法器，返回 a ÷ b 的结果
float divider(float a, float b)
{
    // 当除数b为0时，抛出异常！
    if(b == 0)
        throw "除数不可为零";
    
    return a/b;
}

int main(void)
{
    float a,b;

    // 从键盘获取被除数a和除数b，并输出结果
    while(1)
    {
        cin >> a >> b;
        cout << divider(a, b) << endl;
    }
    return 0;
}
#endif

// 一个简易除法器，返回 a ÷ b 的结果
float divider(float a, float b)
{
    // 当除数b为0时，抛出一个字符串异常
    if(b == 0)
        throw "除数不可为零";
    
    return a/b;
}

int main(void)
{
    float a,b;
    float ans; // ans = a ÷ b

    // 从键盘获取被除数a和除数b，并输出结果
    while(1)
    {
        cin >> a >> b;

        // 试图执行 a÷b
        try{
            ans = divider(a, b);
        }
        catch(const char * &e)
        {
            // 发生了异常
            cout << e << endl;
            break;
        }

        // 输出运算结果
        cout << ans << endl;
    }
    return 0;
}
