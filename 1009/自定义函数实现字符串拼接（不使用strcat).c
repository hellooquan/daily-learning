#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addstr(char *str1,char *str2,int len1,int len2)
{
    int len= len1+len2+1;
    char *str=(char *)malloc(len*sizeof(char));
    if(str==NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for(int i=0;i<len1;i++)
    {
        str[i]=str1[i];
    }
    for(int i=0;i<len2;i++)
    {
        str[len1+i]=str2[i];
    }
    str[len-1]='\0';
    return str;
}

int main()
{
    char *str1="Hello, ";
    char *str2="World!";
    char *s=addstr(str1,str2,strlen(str1),strlen(str2));
    if(s!=NULL)
    {
        printf("%s\n",s);
        free(s);
    }
}