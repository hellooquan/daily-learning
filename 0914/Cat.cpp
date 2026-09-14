#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class Cat
{
private:
    string _name;
    int _age;
    int _weight;

public:
    Cat(const string &name="jack",int age=2,int weight=10):_name(name),_age(age),_weight(weight)//会有浅拷贝
    {
       cout << "构造成功" << endl;
    }
    void show(void)
    {
        cout << "name:" << _name << " " << "age:" << _age << " " << "weight:" << _weight << " " << endl;
    }
    ~Cat()
    {
        std::cout << "析构Cat成功" << std::endl;
    }
};
int main()
{
    Cat cat1;
    Cat cat2(cat1);
    cat1.show();
    cat2.show();

    Cat cat4=Cat(cat1);
    cat4.show();

    return 0;
}