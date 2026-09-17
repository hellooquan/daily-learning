#include <iostream>
using namespace std;

template<typename T>
int fun(const T &a1,const T &a2)
{
    return a1*a2;
}

struct Student
{
// private:
    string name_;
    int age_;
public:
    Student(string name,int age):name_(std::move(name)),age_(age){}
    int operator*(const Student &other)const
    {
        return this->age_*other.age_;
    }
};

class Cat
{
    string name_;
    int age_;
public:
    Cat(string name,int age):name_(std::move(name)),age_(age){}
    bool operator>(const Cat &other)const
    {
        return this->age_>other.age_;
    }
    bool operator<(const Cat &other)const
    {
        return this->age_<other.age_;
    }
    bool operator==(const Cat &other)const
    {
        return this->age_==other.age_;
    }
    int operator*(const Cat &other)const
    {
        return this->age_*other.age_;
    }
};

int main(int argc, char const *argv[])
{
    Cat c1("Jack",5);
    Cat c2("Rose",2);

    Student s1("Jack",20);
    Student s2("Rose",19);

    if(c1>c2)
        cout<<"Jace older than Rose"<<endl;
    else if(c1<c2)
        cout<<"Jace younger than Rose"<<endl;
    else if(c1==c2)
        cout<<"Jace is as old as Rose"<<endl;

    cout<<"Jack的年龄乘以Rose的年龄等于"<<fun(c1,c2)<<endl;
    cout<<"Jack的年龄乘以Rose的年龄等于"<<fun(s1,s2)<<endl;

    return 0;
}
