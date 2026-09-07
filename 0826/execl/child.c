#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    for(int n=3;n>0;n--)
    {
        printf("%d秒后退出\n",n);
        sleep(1);
    }
    return 1;
}