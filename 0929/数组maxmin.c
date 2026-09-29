#include <stdio.h>

int main()
{
    int a[6]={5,1,3,4,2,6};
    int max=a[0];
    int min=a[0];
    for (int i=1;i<=5;i++)
    {
        if(max<a[i]) max=a[i];
        if(min>a[i]) min=a[i];
    }

    printf("max:%d,min:%d\n",max,min);

    return 0;
}