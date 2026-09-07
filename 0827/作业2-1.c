#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    pipe(fd);

    pid_t pid=fork();

    if(pid==0)
    {
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        execl("/usr/bin/wc","wc","-w",NULL);
    }
    else if(pid >0)
    {
        dup2(fd[1],STDOUT_FILENO);
        execl("/usr/bin/ls","ls","/etc",NULL);
    }
    
    return 0;
}
