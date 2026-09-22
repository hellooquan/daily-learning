#include <iostream>
using namespace std;

class AirCraft
{
public:
    virtual void refuel()const=0;
    virtual void fly()const=0;
};

class Copter:AirCraft
{
    void refuel()const override
    {
    }
};

class Bomber:AirCraft
{

};
int main()
{

}