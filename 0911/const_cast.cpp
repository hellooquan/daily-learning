#include <iostream>

int main()
{
          int  i = 6;
	const int *p = &i; // 常目标指针p，不可修改目标

    // ×: 试图修改常指针的目标，错误！
    // *p = 8;

	// √: 去除 const 特性后，可以修改其目标
	*(const_cast<int *>(p)) = 8;



    // ×: 试图扩大权限，错误！
    // int *k = p;
        
	// √: 去除 const 特性后，可赋值给普通指针 k 
	int *k = const_cast<int *>(p);
}