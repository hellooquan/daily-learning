#include <iostream>
#include <cstring>

using namespace std;

class MyString
{
    char *m_ch = nullptr;

public:
    MyString() = default;

    explicit MyString(const char *ch)
    {
        if (ch)
        {
            m_ch = new char[strlen(ch) + 1];
            strcpy(m_ch, ch);
        }
    }

    // 拷贝构造函数(深拷贝)
    MyString(const MyString &S)
    {
        if (S.m_ch)
        {
            m_ch = new char[strlen(S.m_ch) + 1];
            strcpy(m_ch, S.m_ch);
        }
    }

    // 赋值构造函数(深拷贝)
    MyString &operator=(const MyString &S)
    {
        if (this == &S)
            return *this;
        char *tmp = m_ch;
        if (S.m_ch)
        {
            try
            {
                m_ch = new char[strlen(S.m_ch) + 1];
            }
            catch (const exception &e)
            {
                std::cerr << e.what() << '\n';
                return *this;
            }
            strcpy(m_ch, S.m_ch);
            delete[] tmp;
        }
        else
        {
            delete[] m_ch;
            m_ch = nullptr;
        }
        return *this;
    }

    ~MyString()
    {
        delete[] m_ch;
    }

    const char *c_str() const { return m_ch ? m_ch : "(null)"; }
    const char *addr() const { return m_ch; }
    void setChar(size_t idx, char c)
    {
        if (m_ch && idx < strlen(m_ch))
            m_ch[idx] = c;
    }
};

int main()
{
    cout << "========== 1. new 出一个对象 ==========" << endl;
    MyString *p1 = new MyString("hello");
    cout << "p1: " << p1->c_str() << "  addr=" << (void *)p1->addr() << endl;

    cout << "\n========== 2. 用 p1 拷贝构造出 p2 ==========" << endl;
    MyString *p2 = new MyString(*p1);
    cout << "p2: " << p2->c_str() << "  addr=" << (void *)p2->addr() << endl;

    cout << "\n========== 3. 验证独立性：改 p2 不影响 p1 ==========" << endl;
    p2->setChar(0, 'H');   // p2: "Hello"
    cout << "修改后 p1 = " << p1->c_str() << endl;
    cout << "修改后 p2 = " << p2->c_str() << endl;

    cout << "\n========== 4. 用指针做拷贝赋值 ==========" << endl;
    MyString *p3 = new MyString("world");
    cout << "赋值前 p3 = " << p3->c_str() << ", addr = " << (void *)p3->addr() << endl;
    *p3 = *p1;  
    cout << "赋值后 p3 = " << p3->c_str() << ", addr = " << (void *)p3->addr() << endl;

    cout << "\n========== 5. 释放堆对象 ==========" << endl;
    delete p1;
    delete p2;
    delete p3;

    return 0;
}