#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1={1,2,3,4,5};
    
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    for(std::vector<int>::iterator it = v1.begin();it!=v1.end();it++)
        std::cout << *it << ' ';

    std::cout <<'\n';
}