#include <iostream>
using namespace std;

#define fun(x,y)\
{\
    int tmp=x;\
    cout<<x<<' '<<y<<endl;\
}

int main()
{
   fun(1,2);
   double a=3.14000;
   cout << a <<'\n';
}