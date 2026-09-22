#include <iostream>
using namespace std;

template <typename T>
class Aipoint
{
    T *p;
public:
    Aipoint()
    {
        p=new T;
    }
    ~Aipoint()
    {
        delete p;
    }
public:
    T operator*() 
    {
        return *p;
    }
};
int main()
{
    Aipoint<int> ptr;
    // *ptr  *(ptr.p)
    cout << "*ptr="<<*ptr<<endl;
}