#include <iostream>
#include <string>

using namespace std;

class Kitty
{
public:
    Kitty(int weight, string sex, string color) : _weight(weight), _sex(sex), _color(color) {}
    void eat()
    {
        cout << "The kitty is eating" << endl;
    }
    void sleep()
    {
        cout << "The kitty is sleeping" << endl;
    }
    void actingCute()
    {
        cout << "The kitty is being cute" << endl;
    }
    void info()
    {
        cout << "Weight : " << _weight << " kg" << endl;
        cout << "Sex    : " << _sex << endl;
        cout << "Color  : " << _color << endl;
    }

private:
    int _weight;
    string _sex;
    string _color;
};

int main(int argc, char const *argv[])
{
    Kitty cat1={15,"male","black"};
    Kitty cat2(10,"female","white");

    cout << "-----cat1 info-----" << endl;
    cat1.info();
    cout << "-------------------" << endl;

    cout << "-----cat2 info-----" << endl;
    cat2.info();
    cout << "-------------------" << endl;

    return 0;
}