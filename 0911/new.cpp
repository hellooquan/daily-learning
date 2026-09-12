#include <iostream>

using namespace std;
int main (int argc, char *argv[]) {
    int *p1=new int[10];
    for(int i=0;i<10;i++)
        *(p1+i)=i+1;
    
    for(int i=0;i<10;i++)
        cout << p1[i] << " ";

    cout << endl;

    //int *const ptr;
    //int &ptr;
    return 0;
}
