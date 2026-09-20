#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream o1;
    o1.open("hello.txt");

    o1 << "Hello World!" << endl;
    o1 << "This is a test." << endl;

    o1.close();

    return 0;
}