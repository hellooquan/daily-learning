#include <iostream>
#include <string>
using namespace std;

enum class termBegin
{
    begin,
    end
};

class School
{
    int _classes;
    string _OAA;
    termBegin _averScore;

public:
    School(int classes, string OAA, termBegin averScore)
        : _classes(classes), _OAA(OAA), _averScore(averScore) {}

    virtual ~School() = default;

    void show() const
    {
        cout << "【School】" << endl;
        cout << "  班级数: " << _classes << endl;
        cout << "  教务处: " << _OAA << endl;
        cout << "  学期: " << (_averScore == termBegin::begin ? "begin" : "end") << endl;
    }
};

class Firm
{
    float _profitRate;
    string _board;
    float _payTaxes;

public:
    Firm(float profitRate, string board, float payTaxes)
        : _profitRate(profitRate), _board(board), _payTaxes(payTaxes) {}

    virtual ~Firm() = default;

    void show() const
    {
        cout << "【Firm】" << endl;
        cout << "  利润率: " << _profitRate << endl;
        cout << "  董事会: " << _board << endl;
        cout << "  纳税额: " << _payTaxes << endl;
    }
};

class Institution : public School, public Firm
{
public:
    Institution(int classes, string OAA, termBegin averScore,
                float profitRate, string board, float payTaxes)
        : School(classes, OAA, averScore),
          Firm(profitRate, board, payTaxes)
    {
    }

    void show() const
    {
        cout << "======= Institution 信息 =======" << endl;
        School::show();   // 显式指定调用哪个基类的 show
        Firm::show();     // 否则会有二义性
        cout << "================================" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Institution yueqian(100, "我是教务处", termBegin::begin,
                        0.5f, "我是董事会", 100.9f);

    yueqian.show();

    return 0;
}