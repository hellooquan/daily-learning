#include <iostream>
using namespace std;

class Student
{
    string _name;
    float _grade;
    static int _count;
    static float totalScore;
    static float averScore;
public:
    Student(string name,float grade):_name(name),_grade(grade) 
    {
        _count++;
        totalScore+=_grade;
        averScore=totalScore/_count;
    }
    static void printAverScore()
    {
        cout<<"平均成绩为："<<averScore<<endl;
    }
    static void printCount()
    {
        cout<<"学生人数为："<<_count<<endl;
    }
};

int Student::_count=0;
float Student::totalScore=0.0f;
float Student::averScore=0.0f;
int main() {
    Student s1("张三", 90.0);
    Student s2("李四", 80.0);
    Student s3("王五", 70.0);
    Student::printAverScore(); // 输出平均成绩
    Student::printCount(); // 输出学生人数
 
}