#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

//just copy and past this later on.
//Prototype things.
//void producer(int a, int b);

void producer(void);
void consumer(void);

struct CIRCULAR_BUFFER;
{
    int count;
    int lower;
    int upper;
    char buffer[100];
}
struct CIRCULAR_BUFFER *buffer = NULL;
//Code from example


int main()
{
    pid_t pid;
    pid_t otherPid;
    pid = fork();
    
    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;
    char buffer[100];
    
    pid = fork();
    //getppid = Get the process ID of the calling process's parent.
    printf("\npartent = %d\n", getppid()); //%d = int | %s = string | %c = caracter 
    if(pid)
    {
        //
        otherPid = pid;
        producer();
        //printf("\nIn Partent pid = %d\n", otherPid());
    }
    else //child
    {
        otherPid = getppid();
        printf("\nIn Child other pid = %d\n", otherPid);
    }
    return 0;
}
    
    void consumer(void)
    {
        int nSig;
        sigemptyset(&sigSet);
        sigaddset(&sigSet, SIGUSR1);
        while(1)
        {
            sigwait(&sigSet, &nSig);
            printf("\nyou typed %s", buffer->buffer);
            //(input != 'q');
        }
    }
    
    void producer(void)
    {
        char input;
        //printf("\nIn Partent pid = %d\n", otherPid());
        char* pinput = &input;
        pinput = '0';
        printf("\nPlease enter characters. And by characters, I mean q.\n");
        do
        {
        scanf("%c", input); //  & = address or a pointer.
        //put your putValue;
        //This is imclement.
        buffer->buffer[buffer->count++] = input;
        
        printf("\nYou typed in %c", input);
        }
        while (input != "q");
        {
            buffer->buffer[buffer->count] = 0; //NULL terminte the bufer.
            
            printf("\nYou typed %s", buffer->buffer);
        }
    }
