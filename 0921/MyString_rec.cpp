#include <iostream>
#include <cstring>

using namespace std;

class MyString
{
    char* m_ch = nullptr;                  // 对象自己拥有的一块内存

public:
    MyString() = default;                  // 空对象:m_ch 仍是 nullptr

    explicit MyString(const char* ch)      // explicit:挡住 "hello" 悄悄隐式转换
    {
        if (ch)                            // 传空指针就保持空对象
        {
            m_ch = new char[strlen(ch) + 1];   // +1 是给结尾的 '\0' 留位置
            strcpy(m_ch, ch);
        }
    }

    MyString(const MyString& S)            // 深拷贝:自己再 new 一块,不共用
    {
        if (S.m_ch)
        {
            m_ch = new char[strlen(S.m_ch) + 1];
            strcpy(m_ch, S.m_ch);
        }
    }

    MyString& operator=(const MyString& S)
    {
        if (this == &S) return *this;      // 自赋值:先挡掉,否则下面会把自己先 delete 了
        delete[] m_ch;                     // 先还掉自己旧的内存
        m_ch = nullptr;
        if (S.m_ch)                        // 再照 S 的样子 new 一块(和拷贝构造同一套活)
        {
            m_ch = new char[strlen(S.m_ch) + 1];
            strcpy(m_ch, S.m_ch);
        }
        return *this;                      // 少了这句就是 UB
    }

    ~MyString()                            // 有 new 就必须有 delete(三法则)
    {
        delete[] m_ch;
    }

    void output() const
    {
        cout << (m_ch ? m_ch : "(空)") << '\n';   // nullptr 不能直接喂给 cout
    }
};

int main()
{
    MyString s1("hello");
    MyString s2(s1);        // 拷贝构造
    MyString s3 = s1;       // 拷贝构造(不是赋值)
    MyString s4;            // 空对象
    s4 = s1;                // 这才是赋值运算符
    MyString s5;
    s5 = s4 = s1;           // 链式赋值,靠 return *this 才成立
    MyString s6;

    s1.output(); s2.output(); s3.output(); s4.output(); s5.output();
    s4 = s4;                // 自赋值,不能把自己删没了
    s4.output();
    s6.output();
}
