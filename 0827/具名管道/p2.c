#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    if(mkfifo("fifo",0666)==-1)
    {
        perror("mkfifo failed");
    }

    int fd=open("fifo",O_RDONLY);
    if(fd==-1)
    {
        perror("open fifo failed");
        exit(1);
    }

    char buf[1024];
    while(1)
    {
        bzero(buf,sizeof(buf));
        if(read(fd,buf,sizeof(buf))==0)
            break;
        printf("from parent:%s",buf);    
    }
    
    return 0;
}
