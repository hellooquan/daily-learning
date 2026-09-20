#include <iostream>

constexpr double PI = 3.14159265;
using namespace std;

class Shape
{
    int x_;
    int y_;

public:
    Shape(int x, int y) : x_(x), y_(y) {}
    int getx() const { return x_; }
    int gety() const { return y_; }
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void info() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
    double radius_;

public:
    Circle(double radius, int x = 0, int y = 0)
        : Shape(x, y), radius_(radius)
    {
    }
    double area() const override { return PI * radius_ * radius_; }
    double perimeter() const override { return 2 * PI * radius_; }
    void info() const override
    {
        cout << "我是圆，坐标为(" << getx() << ',' << gety() << ")," << "面积为: " << area() << "," << "周长为: " << perimeter() << '\n';
    }
};

class Rectangle : public Shape
{
    double length_;
    double width_;

public:
    Rectangle(double length, double width, int x = 0, int y = 0)
        : Shape(x, y), length_(length), width_(width)
    {
    }
    double area() const override { return length_ * width_; }
    double perimeter() const override { return 2 * (length_ + width_); }
    void info() const override
    {
        cout << "我是矩形，坐标为(" << getx() << ',' << gety() << ")," << "面积为: " << area() << "," << "周长为: " << perimeter() << '\n';
    }
};

int main()
{
    Shape *c1 = new Circle(3.14, 5, 6);
    c1->info();

    Shape *r1 = new Rectangle(3.2, 3.1, 2, 3);
    r1->info();

    delete c1;
    delete r1;
}