#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int i;

    // Modulus operator (%) was used so the value only changes from 0-7

    for (i = 0; i<8; ++i)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    {
        if (i > 8) pid = fork(); // Don't have to have {} for single statement
        if (pid == -1)
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("\t%d", i%8);
    }
}
