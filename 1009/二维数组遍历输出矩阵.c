#include <stdio.h>

void print_square1(int a,int b,int avl[a][b])
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            printf("%d ",avl[i][j]);
        }
        printf("\n");
    }
}

void print_square2(int *avl,int a,int b)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            printf("%d ",*(avl+i*b+j));
        }
        printf("\n");
    }
}

int main()
{
    int a[][3]={{1,2,3},{4,5,6}};
    print_square1(2,3,a);
    print_square2((int *)a,2,3);
}