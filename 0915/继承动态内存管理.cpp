#include <iostream>
#include <cstring>
using namespace std;

class Person
{
    char *_name;

public:
    Person(const char *name = nullptr)
    {
        if (name != nullptr)
        {
            _name = new char[strlen(name) + 1];   // 必须 +1,给结尾的 '\0' 留一格
            strcpy(_name, name);
        }
        else
            _name = nullptr;
    }

    // 【原错】原来写的是 Person(Person &r):少了 const,const 对象和函数返回的临时对象都拷不了
    Person(const Person &r)
    {
        if (r._name != nullptr)
        {
            // 【原错】原来少了 + 1:strcpy 连结尾的 '\0' 一起写,只申请 strlen 字节就会多写 1 字节到堆块外面
            _name = new char[strlen(r._name) + 1];
            strcpy(_name, r._name);
        }
        else
            _name = nullptr;
    }

    // 【原错】原来写的是 Person &operator=(Person &r),少了 const
    Person &operator=(const Person &r)
    {
        // 【原错】原来没有这一段:没判自赋值,而赋值里第一句就是 delete[] _name,
        //         碰上 s2 = s2 就在读已经释放的内存(ASAN: heap-use-after-free)
        if (this == &r)
            return *this;

        // 【原错】原来是先 delete[] _name 再申请:这里改成先把新数据准备好,成功之后再删旧的
        char *tmp = nullptr;
        if (r._name != nullptr)
        {
            tmp = new char[strlen(r._name) + 1];
            strcpy(tmp, r._name);
        }
        delete[] _name;
        _name = tmp;

        return *this;
    }

    // 【原错】原来没有 virtual:Base *p = new Derived; delete p; 时派生类析构不跑,派生类的堆成员泄漏
    virtual ~Person() { delete[] _name; }

    void show() const
    {
        // 【原坑】原来直接 cout << _name:传 nullptr 时不崩,但会把 cout 变成失败状态,之后所有输出静默消失
        cout << "姓名: " << (_name ? _name : "(空)") << ",";
    }
};

class Student : public Person
{
    char *_id;

public:
    Student(const char *name, const char *id = nullptr)
        : Person(name)
    {
        if (id != nullptr)
        {
            _id = new char[strlen(id) + 1];
            strcpy(_id, id);
        }
        else
            _id = nullptr;
    }

    // 【原错】原来是 Student(Student &r):少了 const(基类 r._id 那半的 +1 也漏了,下面补了)
    Student(const Student &r)
        : Person(r)                                // 基类那半交给基类的拷贝构造
    {
        if (r._id != nullptr)
        {
            // 【原错】原来少了 + 1,同基类
            _id = new char[strlen(r._id) + 1];
            strcpy(_id, r._id);
        }
        else
            _id = nullptr;
    }

    // 【原错】原来是 Student &operator=(Student &r),少了 const(原来也没判自赋值)
    Student &operator=(const Student &r)
    {
        if (this == &r)                            // 【原错】这行是补的:派生类这半也要判自赋值
            return *this;

        Person::operator=(r);                      // 必须显式调用,不写这句基类的成员就漏拷贝了
        // 【原错】原来这里也是先 delete[] _id 再申请(和基类同一个毛病)
        delete[] _id;
        if (r._id != nullptr)
        {
            // 【原错】原来少了 + 1
            _id = new char[strlen(r._id) + 1];
            strcpy(_id, r._id);
        }
        else
            _id = nullptr;

        return *this;
    }

    ~Student() { delete[] _id; }

    void show() const
    {
        Person::show();
        // 【原坑】原来直接 cout << _id,同基类:nullptr 会把 cout 弄成失败状态
        cout << "学号: " << (_id ? _id : "(空)") << endl;
    }
};

int main(int argc, char const *argv[])
{
    Student s1("Jack", "100");
    s1.show();

    Student s2(s1);      // 拷贝构造
    s2.show();

    s2 = s1;             // 拷贝赋值
    s2.show();

    s1 = s1;             // 自赋值
    s1.show();

    Student s3("Tom");   // id 是默认值 nullptr
    s3.show();
    cout << "上面这行之后输出还在:说明流没被搞坏" << endl;

    Person *p = new Student("Amy", "202");
    p->show();           // show() 不是虚函数,走的是基类版本,只打印姓名
    cout << endl;
    delete p;            // 有虚析构,派生类那半才会一起释放

    return 0;
}
