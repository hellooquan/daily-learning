#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if(pid==0)
    {
        char buf[128];
        read(fd[0],buf,10);
        printf("from parent:%s\n",buf);

        write(fd[1],"123456",7);

    }
    else if(pid>0)
    {
        write(fd[1],"hi child!",10); 
        usleep(1*1000);
        
        char buf[128];
        read(fd[0],buf,7);
        printf("from child:%s\n",buf);
    }
}