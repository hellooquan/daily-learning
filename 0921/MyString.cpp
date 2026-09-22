#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
    char *m_ch=nullptr;
public:
    MyString()=default;
    explicit MyString(const char* ch)
    {
        m_ch=new char[strlen(ch)+1];
        strcpy(m_ch,ch);
    }
    MyString(const MyString& S)
    {
        m_ch=new char[strlen(S.m_ch)+1];
        strcpy(m_ch,S.m_ch);
    }
    MyString& operator=(const MyString& S)
    {
        m_ch=new char[strlen(S.m_ch)+1];
        strcpy(m_ch,S.m_ch);
        return *this;
    }
    void output()const
    {
        cout<<(m_ch?m_ch:"(空)")<<'\n';
    }
    ~MyString()
    {
        delete [] m_ch;
    }
};
int main()
{
    MyString s1("hello");
    MyString s2(s1);
    MyString s3=s1;
    s1.output();
    s2.output();
    s3.output();
    s2=s1;
    s2.output();
    // s2=s2;
    s2.output();
    
}