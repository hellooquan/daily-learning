#include <iostream>

using namespace std;

class Student
{
	string name_;
	int id_;
public:
	Student(string name, int id) : name_(std::move(name)), id_(id) {}
	Student operator--(int)
	{
		Student student = *this;
		--id_;
		return student;
	}
	Student operator--()
	{
		--id_;
		return *this;
	}
	void show()const
	{
		cout << name_ << " " << id_ << endl;
	}
	friend ostream &operator<<(ostream &os, const Student &student);
};

ostream &operator<<(ostream &os, const Student &student)
{
	os << student.name_ << " " << student.id_ << endl;
	return os;
}

int main()
{
	Student student1("Tom", 1001);
	Student student2 = student1--;
	Student student3 = --student1;

	cout<<student1<<student2<<student3;
	
	return 0;
}