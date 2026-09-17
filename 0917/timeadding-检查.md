# timeadding.cpp 检查报告

> 创建时间:2026-09-17。来源:`routine/0917/timeadding.cpp`

编译:`g++ -std=c++17 -Wall -Wextra` —— 能编过、能跑,下面是跑完的实测结论。

一句话:**进位判断写成了 `>60`,应该是 `>=60`;另外 `operator+` 的签名写成了 `operator+=` 的语义。**

## 一、必修两条

### 1. 第 22 行、第 27 行:`>60` 应改成 `>=60`

```cpp
bool add=false;                                          // 第 21 行:声明了没用
if((this->second_+=other.second_)>60)                    // 第 22 行
{
    this->second_%=60;
    this->minute_++;
}
if((this->minute_+=other.minute_)>60)                     // 第 27 行
{
    this->minute_%=60;
    this->hour_++;
}
```

和正好是 60 时不进位,把非法的 60 直接留在结果里(第 32 行的 `%24` 没这个问题)。

| 输入 | 原版输出 | 正确应为 |
| --- | --- | --- |
| 1:20:30 + 0:0:30 | `1:20:60` | `1:21:0` |
| 1:20:0 + 0:40:0 | `1:60:0` | `2:0:0` |
| 23:59:59 + 0:0:1 | `23:59:60` | `0:0:0` |
| 7:50:30 + 22:30:40 | `6:21:10` | `6:21:10`(蒙对,没撞上 60) |
| 12:45:45 + 11:14:15 | `23:59:60` | `0:0:0` |

`main` 里那对 7:50:30 + 22:30:40 恰好不撞 60,所以看着是对的 —— 这类 bug 只有换一组数据才露头。

### 2. 第 19 行 `Time &operator+(const Time &other)`:是 `operator+=` 的写法,不是 `+`

```cpp
Time &operator+(const Time &other)                       // 第 19 行
{
    ...
    return *this;
}
```

三个后果:

- **`+` 不该改自己**。实测 `t1 + t2` 之后 `t1` 从 `7:50:30` 变成了 `6:21:10`;第 49 行 `Time resultTime = t1+t2;` 之所以打出正确结果,是因为"t1 先被改了,resultTime 再拷一份",属于蒙对
- **少了末尾 `const`**,`const Time` 对象加不了,报:
  `error: passing 'const Time' as 'this' argument discards qualifiers [-fpermissive]`
- **返回 `Time&`** 让 `a + b + c` 变成在同一条链上反复改同一个对象,出错很难查

两种改法,想要哪种就选哪种:

- `+` 的语义(推荐):返回类型去掉 `&`,改成返回新对象,末尾加 `const`
- `+=` 的语义(加到自身上):名字改成 `operator+=`,保留返回引用 —— 就是 cpp-note 第 7 节 `Counter &add(int k)` 那种

## 二、建议改的五处(不影响结果)

| 行号 | 现状 | 问题 |
| --- | --- | --- |
| 14 | `throw "时间格式错误\n";` | 抛的是 `const char*`,不是异常类,要 `catch (const char *)` 才接得住;`main` 里没写 catch,真抛了就是 `terminate`(abort)。建议 `throw std::invalid_argument("时间格式错误");`,消息里也不用带 `\n` |
| 21 | `bool add=false;` | 声明了从头到尾没用,-Wall 报 `unused variable 'add'` |
| 42 | `int main(int argc, char const *argv[])` | 两个参数都没用,-Wextra 报 2 条 `unused parameter`;用不上直接写 `int main()` |
| 35-40 | `ostringstream os; os << ... << endl; cout << os.str();` | 绕了一圈。ostringstream 的价值在"把一段拼成字符串存起来/传出去",不是打印;要换行用 `"\n"` 就好,`endl` 是"换行 + 刷新",对流式对象没必要。更顺的做法是给 Time 写 `operator<<`,以后 `cout << t1` 直接用 |
| 15-17 | 构造函数体里 `hour_=hour;` 赋值 | 统一写成初始化列表 `: hour_(hour), minute_(minute), second_(second)`;`int` 成员性能无所谓,好处是第 13 行的检查抛异常时不会留下"构造了一半"的成员 |

编译警告原文:

```
timeadding.cpp:21:14: warning: unused variable ‘add’ [-Wunused-variable]
timeadding.cpp:42:14: warning: unused parameter ‘argc’ [-Wunused-parameter]
timeadding.cpp:42:32: warning: unused parameter ‘argv’ [-Wunused-parameter]
```

## 三、修正版完整代码

已用 `g++ -std=c++17 -Wall -Wextra` 编过(零警告),上面 5 组输入的结果全部正确,`t1` 算完保持 `7:50:30` 不变,`const Time` 对象也能相加。

```cpp
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

    // + 的语义:只读、不改自己 -> 末尾 const,返回新对象(不加 &)
    Time operator+(const Time &other) const
    {
        int s = second_ + other.second_;
        int m = minute_ + other.minute_ + s / 60;    // 进位一次算完,不用 if + %=
        int h = hour_   + other.hour_   + m / 60;
        return Time(h % 24, m % 60, s % 60);         // 24 小时制回绕
    }

    void showTime() const { cout << "time: " << hour_ << ':' << minute_ << ':' << second_ << "\n"; }
};

int main()
{
    Time t1(7,50,30);
    Time t2(22,30,40);

    t1.showTime();
    t2.showTime();
    Time resultTime = t1 + t2;
    resultTime.showTime();   // 6:21:10,而且 t1 还是 7:50:30
}
```

实测输出:

```
time: 7:50:30
time: 22:30:40
time: 6:21:10
```

## 四、两个可以直接背下来的点

- **判断进位一律用 `>=`**:`>60` 把"正好 60"漏掉,而 60 恰好是最常见的边界(30+30、45+15)
- **`+` 和 `+=` 别写串**:`+` 返回新对象(值、const)、`+=` 改自己(引用、非 const)。看签名就知道是哪个:`Time operator+(const Time &) const` 是 `+`,`Time &operator+=(const Time &)` 是 `+=`
