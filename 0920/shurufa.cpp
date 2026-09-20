#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

// 1.啊2.阿3.呵4.吖5.嗄6.腌
// 1.锕
void printValue(string str)
{
    str.pop_back();
    for()
}
int main()
{
    ifstream file("file.txt");
    if (!file.is_open())
    {
        cout << "open file error" << endl;
        return 0;
    }
    string line;
    map<string, string> zidian;
    while (getline(file, line))
    {
        istringstream ss(line);
        string key, value;

        getline(ss,key,'=');
        getline(ss,value,'"');
        getline(ss,value,'"');

        zidian[key] = value;
    }
    file.close();
    // for (auto &p : zidian)
    //     cout << p.first << " => " << p.second << endl;
    string input;
    while (cin >> input && input != "exit")
    {
        auto it = zidian.find(input);
        if (it != zidian.end())
            cout << it->second << endl;
        else
            cout << "no such word" << endl;
    }

    return 0;
}