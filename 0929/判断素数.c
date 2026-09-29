#include <stdio.h>
#include <stdbool.h>

bool isPrime(int a)
{
    bool flag = true;
    for (int i = 2; i <= a / 2; i++)
    {
        if (a % i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
int main()
{
    int a = 100;
    printf("%d%s\n", a, isPrime(a) ? "是素数" : "不是素数");

    return 0;
}