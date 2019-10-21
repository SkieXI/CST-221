#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <signal.h>
#include <sys/mman.h>
#include <errno.h>

int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

pid_t otherPid;

sigset_t sigSet;

struct CIRCULAR_BUFFER
{
    int count;         
    int lower;       
    int upper;     
    int buffer[100];
};
struct CIRCULAR_BUFFER *buffer = NULL;

void sleepAndWait()
{
    int nSig;

    printf("Sleeping...........\n");
    
    sigwake;
    //PUT METHOD HERE THAT WAKES THINGS UP.
    printf("Awoken\n");
}

void wakeupOther()
{
    
}

int getValue()
{
    // TODO: Get a value from the Circular Buffer and adjust where to read from next
    int value = buffer.buffer[buffer.lower];
    buffer.lower  = buffer.lower - 1;
    buffer.upper = buffer.upper - 1;
    return value;

void putValue(struct CIRCULAR_BUFFER* buffer, int value)
{
    // TODO: Write to the next available position in the Circular Buffer and adjust where to write next
    buffer.buffer[buffer.upper] = value;
    buffer.upper = buffer.upper + 1;
    buffer.lower = buffer.lower + 1;
}

void consumer()
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);

    printf("Running Consumer Process.....\n");

    int item;

    while(1) {
        if(buffer.count == 0)
            sleepAndWait();
        item = getValue();
        buffer.count = buffer.count - 1;
        if(buffer.count == MAX - 1)
            wakeupOther();
        print(item);
    }
    _exit(1);
}
void producer()
{
    int value = 0;

    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);

    printf("Running Producer Process.....\n");

    while(1) 
    {
        if(buffer.count == MAX) 
            sleepAndWait();
        putValue(buffer, value);
        buffer.count = buffer.count + 1;
        if(buffer.count == 1)
            wakeupOther();
    }
    _exit(1);
}

int main(int argc, char* argv[])
{
    pid_t  pid;

    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;

    pid = fork();
    if (pid == -1)
    {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        otherPid = getppid();
        producer();
    }
    else
    {
        otherPid = pid;
        consumer();
    }
    return 0;
}
