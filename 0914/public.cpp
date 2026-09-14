#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class Juxing    
{
private:
    float _length;
    float _width;

public:
    Juxing(float length, float width) : _length(length), _width(width){}
    void area()
    {
        cout << "面积为：" << _length * _width << endl;
    }
    
};
class Zhengfangxing : public Juxing
{
public:
    explicit Zhengfangxing(float side) : Juxing(side,side){}
    void zhengarea()
    {
        cout << "正方形的";
        area();
    }
};
int main(int argc, char const *argv[])
{
    Zhengfangxing z(3);
    z.zhengarea();

    return 0;
}
