#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) 
{
    if(n<=1)
    {
        return false;
    }
    bool is=true;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            is=false;
            break;
        }
    }
    return is;
}

int main() 
{
    int count=0;
    for(int i=1;i<=100;i++)
    {
        if(is_prime(i))
        {
            printf("%d ",i);
            count++;
        }
    }
    printf("\nTotal prime numbers between 1 and 100: %d\n",count);
    return 0;
}