#include <iostream>

using namespace std;

class Car
{
private:
    enum level{high,medium,low} mass;
    float maxSpeed;
public:
    void move(){cout << "Car is moving" << endl;}
    void maintain(){cout << "Car is maintaining" << endl;}
};

class ElectroMobile:public Car
{

};

class FlyCar:public Car
{

};
int main(int argc, char const *argv[])
{

    return 0;
}
