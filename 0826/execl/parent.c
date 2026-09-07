#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int status;

    while(1)
    {
        if(waitpid(-1, &status, WNOHANG)<=0)
            printf("wait\n");
        else
            break;
        usleep(100*1000);    
    }

    if (WIFEXITED(status))
    {
        return 0;
    }

}