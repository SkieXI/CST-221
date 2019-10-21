#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <signal.h>
#include <sys/mman.h>
#include <errno.h>

int MAX = 100;
int TIME_TO_PRINT_NAME = SIGUSR1;
int TIME_TO_GET_NAME = SIGUSR2;

pid_t otherPid;

void SignalHandler (int nSig)
{
    printf("\nIn Handler sig = %d", nSig);
}

sigset_t sigSet;

char *userName = NULL; 

void getValue(char *pDestinationBuffer)
{
    int i;
    for (i = 0; (i < MAX-1) && (*(userName + i) != 0); ++i)
    {
         *(pDestinationBuffer + i) = *(userName + i);
    }
    *(pDestinationBuffer + i) = 0;
}

void putValue(char *pName)
{
    int i;
    for (i = 0; (i < MAX-1) && (*(pName + i) != 0); ++i)
    {
        *(userName + i) = *(pName + i);
    }
    *(userName + i) = 0;
}

void Print_user_name()
{
    int nSig;
    char* tmpBuffer = malloc(MAX * sizeof(char));
    
    sigemptyset(&sigSet);
    sigaddset(&sigSet, TIME_TO_PRINT_NAME);

    for (int i = 0; i < 3; ++i) 
    {
        sigwait(&sigSet, &nSig); 

        printf("\nWakie wakie time for the consumer, signal = %d\n", nSig);

        getValue(tmpBuffer);

        printf("\nThe User Name entered was: %s\n\n", tmpBuffer);
        printf("\nSending signal = %d to the producer", TIME_TO_GET_NAME);
        kill(otherPid, TIME_TO_GET_NAME); 
    }

    
    if (tmpBuffer) 
    {
        free(tmpBuffer);
    }

    _exit('1');
}

void Get_user_name()
{

    int nSig;
    int nLength;
    char* tmpBuffer = malloc(MAX * sizeof(char));  
    sigemptyset(&sigSet);
    sigaddset(&sigSet, TIME_TO_GET_NAME);

    for (int i = 0; i < 3; ++i) 
    {
        printf("Please enter your name: ");

        scanf("%s", tmpBuffer);

        putValue(tmpBuffer);

        kill(otherPid, TIME_TO_PRINT_NAME);
        sigwait(&sigSet, &nSig);
    }

    if (tmpBuffer)
    {
        free(tmpBuffer);
    }
    _exit('1');
}

int main(int argc, char* argv[])
{
    pid_t  pid;
    userName = (char*)mmap(0,MAX * sizeof(char), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    signal(TIME_TO_PRINT_NAME, SignalHandler);
    signal(TIME_TO_GET_NAME, SignalHandler);

    pid = fork();
    if (pid == -1)
    {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0)
    {
        otherPid = getppid(); 
        Get_user_name();
    }
    else
    {
        otherPid = pid;
        Print_user_name();
    }

    sleep(2);

    return 0;
}
