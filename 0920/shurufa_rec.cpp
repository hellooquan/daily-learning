// 文件输入法:把 file.txt 里的 拼音=>"候选字", 读进 map,然后循环查询
// 数据格式样例:  a=>"啊阿呵吖嗄腌锕錒",
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    ifstream file("file.txt");        // 相对路径跟"启动目录"走,不是跟可执行文件所在目录走
    if (!file.is_open())              // 打开失败是静默的,必须自己查
    {
        cout << "open file error" << endl;
        return 1;                     // 出错给非 0 退出码,外面脚本才看得出来
    }

    map<string, string> zidian;
    string line;
    while (getline(file, line))       // 循环条件就用 getline 的返回值,别写 while (!file.eof())
    {
        istringstream ss(line);       // 每一行单独一个内存流,在这行里面切字段
        string key, value;

        // 一行拆开看:   a  =>  "  啊阿呵吖嗄腌锕錒  "  ,
        //               ↑       ↑                    ↑
        //         读到'='为止  读到第一个'"'为止   读到第二个'"'为止(后面的逗号不读)
        getline(ss, key, '=');        // → "a"
        getline(ss, value, '"');      // → ">"   这一趟只是把 "=>" 当垃圾扔掉
        getline(ss, value, '"');      // → "啊阿呵吖嗄腌锕錒"   覆盖 value,拿到真值

        zidian[key] = value;          // file.txt 格式统一,不额外校验;要校验就先判断
                                      // line.find("=>\"") != string::npos
    }
    file.close();                     // 可省略:出了作用域析构时会自动 close

    string input;
    while (cin >> input && input != "exit")   // 先读再判断;读失败(Ctrl-D)自动退出,不会死循环
    {
        auto it = zidian.find(input);          // 用 find,不能用 zidian[input]
        if (it != zidian.end())                // 找不到时 operator[] 会悄悄插入一个空值,
            cout << it->second << endl;        // 打出来就是空行,看不出是"没这个词"
        else
            cout << "no such word" << endl;
    }

    return 0;
}
