# MyString.cpp 检查报告(第 2 轮)

> 创建时间:2026-09-21。来源:`routine/0921/MyString.cpp`

**一句话结论**:上一轮的三个问题你已经自己改掉了——深拷贝有了、`return *this;` 有了、output 会判空打 `(空)` 了,三件套(拷贝构造 / 赋值 / 析构)也齐了。现在 `-Wall -Wextra` 零警告、输出 5 行 hello + `(空)`。剩下的三条都藏在"内存"上:赋值前不还旧内存(泄漏)、没挡自赋值(补上 delete 后会 use-after-free)、拷贝/赋值没判空(空对象直接段错误)。

## 一、上一轮的结果(已改对)

| 上一轮的问题 | 现在的状态 |
| --- | --- |
| 拷贝构造、赋值只拷指针(浅拷贝) | 已改成深拷贝(第 17~18 行、第 22~23 行各自 new 一块) |
| `operator=` 缺 `return *this;`(UB) | 已补(第 24 行) |
| `output()` 把 nullptr 喂给 cout | 已改成 `(m_ch ? m_ch : "(空)")`(第 28 行) |
| 没有析构函数 | 已加 `~MyString(){ delete [] m_ch; }`(第 30~33 行) |
| `<string.h>` 没用上 | 已换成 `<cstring>`(第 2 行) |
| 没写 explicit | 已加(第 10 行) |

## 二、必修(这一轮剩下的)

### 1. 第 22 行:赋值前没还掉自己的旧内存 → 每次赋值泄漏一块

定位锚点(第 20 行):`MyString& operator=(const MyString& S)`

`m_ch = new char[...]` 直接把旧指针覆盖掉了,上一块内存再也没人 `delete`。实测(`-fsanitize=address` 自带的泄漏检测):

```
ERROR: LeakSanitizer: detected memory leaks

Direct leak of 6 byte(s) in 1 object(s) allocated from:
    #0 ... in operator new[](unsigned long)
    #1 ... in MyString::MyString(MyString const&) MyString.cpp:17
    #2 ... in main MyString.cpp:38
```

泄漏的正是第 38 行 `MyString s2(s1);` new 出来的那块——被第 43 行 `s2=s1;` 覆盖后没人认领。现在只有 6 字节,程序大了就是成片泄漏,而且编译器一句警告都不给。

原版 vs 正确:

| 第 21~23 行原版 | 正确 |
| --- | --- |
| `{`<br>`m_ch=new char[...];`<br>`strcpy(m_ch,S.m_ch);` | `{`<br>`if (this == &S) return *this;`<br>`delete [] m_ch;`<br>`m_ch = nullptr;`<br>`m_ch=new char[...];`<br>`strcpy(m_ch,S.m_ch);` |

### 2. 补上 `delete [] m_ch;` 之后,第 21 行位置必须有自赋值检查

这两条是连着的:`delete [] m_ch;` 一加上,`s2 = s2;` 就会先把自己的内存还掉,再拿这个已经归还的指针去 `strlen`。

第 45 行你把 `s2=s2;` 注释掉了——它现在是必修 1 的"帮凶":不还旧内存所以不炸,一旦补齐就会炸。实测(照常识只补 `delete [] m_ch;`、不写自赋值检查):

```
ERROR: AddressSanitizer: heap-use-after-free on address 0x706761ae0070
READ of size 2 at 0x706761ae0070 thread T0
    #0 ... in strlen
    #1 ... in MyString::operator=(MyString const&) self.cpp:23
    #2 ... in main self.cpp:46
```

所以赋值的正确顺序是四步,一句都不能少:

1. `if (this == &S) return *this;` —— 自赋值先挡掉
2. `delete [] m_ch;` —— 还掉自己旧的
3. `if (S.m_ch) { m_ch = new char[strlen(S.m_ch)+1]; strcpy(m_ch, S.m_ch); }` —— 判空 + 拷新的
4. `return *this;` —— 返回自己

### 3. 第 17 行 + 第 22 行:拷贝构造和赋值没判空 → 空对象参与拷贝就段错误

定位锚点(第 15 行):`MyString(const MyString& S)`

第 9 行 `MyString()=default;` 造出来的空对象 `m_ch` 是 `nullptr`,而第 17 行、第 22 行都直接 `strlen(S.m_ch)`——`strlen(nullptr)` 是真的去读地址 0。实测:

```
ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000
```

`MyString f(e);`(拿空对象拷贝构造)和 `g = e;`(拿空对象赋值)两条路都崩。你在 output 里已经想到判空了,拷贝构造和赋值这里是同一个道理。

## 三、建议改

| 行号 | 现状 | 问题 |
| --- | --- | --- |
| 第 12 行 | `m_ch=new char[strlen(ch)+1];` | 没判 `ch` 是不是空指针,`MyString s(nullptr);` 同样 `strlen(NULL)` 崩;拷贝构造/赋值补判空时,这里顺手一起补 |
| 第 43~46 行 | `s2=s1; s2.output();` + 注释掉的 `// s2=s2;` | 第 45 行注释掉后,第 46 行的 output 变成了把上一行的结果打第二遍。而自赋值恰恰是必修 2 的现场——修完就把第 45 行打开 |
| 第 47~48 行 | `MyString s4; s4.output();` | 只测了空对象能打印,没测"空对象参与拷贝/赋值"(必修 3 那条路) |

## 四、修正版完整代码 + 实测输出

```cpp
#include <iostream>
#include <cstring>

using namespace std;

class MyString
{
    char* m_ch = nullptr;

public:
    MyString() = default;

    explicit MyString(const char* ch)
    {
        if (ch)
        {
            m_ch = new char[strlen(ch) + 1];
            strcpy(m_ch, ch);
        }
    }

    MyString(const MyString& S)
    {
        if (S.m_ch)
        {
            m_ch = new char[strlen(S.m_ch) + 1];
            strcpy(m_ch, S.m_ch);
        }
    }

    MyString& operator=(const MyString& S)
    {
        if (this == &S) return *this;      // ① 自赋值:先挡掉
        delete [] m_ch;                    // ② 还掉自己旧的
        m_ch = nullptr;
        if (S.m_ch)                        // ③ 判空 + new 一块新的拷过来
        {
            m_ch = new char[strlen(S.m_ch) + 1];
            strcpy(m_ch, S.m_ch);
        }
        return *this;                      // ④ 返回自己
    }

    ~MyString()
    {
        delete [] m_ch;
    }

    void output() const
    {
        cout << (m_ch ? m_ch : "(空)") << '\n';
    }
};

int main()
{
    MyString s1("hello");
    MyString s2(s1);
    MyString s3 = s1;
    MyString s4;
    MyString s5;
    s4 = s1;                // 赋值
    s5 = s4 = s1;           // 链式赋值
    s1.output(); s2.output(); s3.output(); s4.output(); s5.output();
    s2 = s2;                // 自赋值:不能把自己删没了
    s2.output();
    s4 = s1;                // 再赋一次:旧内存要归还,不然泄漏
    s4.output();
    MyString s6;            // 空对象
    s6.output();
    MyString s7(s6);        // 拿空对象做拷贝构造
    s7.output();
    s4 = s6;                // 拿空对象做赋值
    s4.output();
}

```

实测(`g++ -Wall -Wextra -std=c++17`,零警告):

```
hello
hello
hello
hello
hello
hello
hello
(空)
(空)
(空)
```

再挂 `-fsanitize=address -g` 跑一遍:零报错、零泄漏、退出码 0。

## 五、可以直接背下来的结论

1. 赋值运算符是四步:**自赋值检查 → 还旧内存 → 判空后拷新内容 → `return *this`**。少一步就是泄漏或崩溃,编译器都不会提醒你。
2. 只要类里有 `new`,析构、深拷贝构造、深拷贝赋值三个都必须有;而且凡是要 `strlen`/`strcpy` 的地方,都得先问一句"这块指针会不会是空的"。
3. 泄漏和 use-after-free 是同一件事的两面:不 `delete` 就泄漏,`delete` 了不挡自赋值就 use-after-free——所以第 45 行那个被注释掉的 `s2=s2;` 修完必修 2 之后一定要打开。
4. `-Wall -Wextra` 零警告 ≠ 内存正确;这两个货(`LeakSanitizer` / `heap-use-after-free`)只有 `-fsanitize=address` 看得见。
