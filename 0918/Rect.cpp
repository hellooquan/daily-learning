#include <iostream>
using namespace std;

class Rect
{
    int length_;
    int width_;
public:
    Rect(int length, int width): length_(length), width_(width) {}
    void show()
    {
        cout << "length: " << length_ << " width: " << width_ << endl;
    }
    friend Rect &operator+(Rect &rect, int n);
    friend Rect &operator+(int n,Rect &rect);
    friend Rect &operator+(Rect &rect,Rect &other);
    friend Rect &operator-(Rect &rect, int n);
};
Rect &operator+(Rect &rect, int n)
{
    rect.length_ += n;
    rect.width_ += n;
    return rect;
}
Rect &operator+(int n,Rect &rect)
{
    rect.length_ += n;
    rect.width_ += n;
    return rect;
}
Rect &operator+(Rect &rect,Rect &other)
{
    rect.length_ += other.length_;
    rect.width_ += other.width_;
    return rect;
}
Rect &operator-(Rect &rect, int n)
{
    rect.length_ -= n;
    rect.width_ -= n;
    return rect;
}

int main()
{
    Rect r1(1, 2);
    Rect r2(3, 4);
    Rect r3(5, 6);
    Rect r4=9+r1+5+r2+6+r3-7;

    r4.show();

    return 0;
}