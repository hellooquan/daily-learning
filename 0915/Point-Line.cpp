#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
    float _x;
    float _y;
public:
    Point(float x,float y):_x(x),_y(y){}
    float getx(){return _x;}
    float gety(){return _y;}
};

class Line
{
private:
    Point _p1;
    Point _p2;
public:
    Line(Point p1,Point p2):_p1(p1),_p2(p2){}
    Line(float x1,float y1,float x2,float y2):_p1(x1,y1),_p2(x2,y2){}
    float getLength()
    {
        float datax=_p1.getx()-_p2.getx();
        float datay=_p1.gety()-_p2.gety();
        float length;
        return length =sqrt(datax*datax+datay*datay);
    }
};

int main(int argc, char const *argv[])
{
    Line L(1,4,5,7);
    cout << "Line's length is: " << L.getLength() << endl;
    
    return 0;
}
