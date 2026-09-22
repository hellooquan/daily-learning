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
            tmp = nullptr;
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

    void output() const
    {
        cout << (m_ch ? m_ch : "(空)") << '\n';
    }
};
