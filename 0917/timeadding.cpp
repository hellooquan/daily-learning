#include <iostream>
#include <stdexcept>
using namespace std;

class Time
{
    int hour_;
    int minute_;
    int second_;

public:
    Time(int hour, int minute, int second)
        : hour_(hour), minute_(minute), second_(second)
    {
        if (hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0)
            throw invalid_argument("时间格式错误");
    }
    Time operator+(const Time &other) const
    {
        int s = second_ + other.second_;
        int m = minute_ + other.minute_ + s / 60;
        int h = hour_ + other.hour_ + m / 60;
        if (h >= 24)
            cout << "过了一天，到了第二天的" << h % 24 << "小时" << '\n';
        return Time(h % 24, m % 60, s % 60);
    }
    void showTime() const
    {
        cout << "time: " << hour_ << ':' << minute_ << ':' << second_ << '\n';
    }
};
int main()
{
    Time t1(7, 50, 30);
    Time t2(22, 30, 40);

    t1.showTime();
    t2.showTime();
    Time resultTime = t1 + t2;
    resultTime.showTime();

    return 0;
}
