#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    
    for (int i = 0; i<8; ++i)
    {
        pid = fork();
    pid = fork();
    if (pid == -1)
    {
        //If -1 = error
        fprintf(stderr, "can't fork, error %d\n", errno);

        exit(EXIT_FAILURE);
    }
    }
    if (pid > 0)
    {
        printf("\nParent process pid\n");
    }
    else
    {
        printf("\nChild process pid\n");
    }
}
