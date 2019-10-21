#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


sem_t* Test; //Test = 1
sem_t* Demo; //Demo = 2


void  signalHandler1(int signum)
{
    printf("Caught Signal: %d\n",signum);
    printf("     Exit Child Process.\n");
    sem_post(semaphore);
    _exit(0);
}

void  parent()
{
    printf("Parent Prime.\n");
    exit(0);
}
void Test()
{
    printf("Child 1.\n");

    sem_wait(lock);
    sem_post(lock);
    exit(0);
}
void Demo()
{
    printf("Child 2.\n");

    sem_wait(lock);
    sem_post(lock);
    exit(0);
}

int main() {

    Test = (sem_t*)mmap(0,sizeof(sem_t), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(Test, 1,1);
    Demo = (sem_t*)mmap(0,sizeof(sem_t), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(Demo,1,1);

    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        printf("Something went horribly wrong, but nothing is dead.");
    }
    else
    {
        printf("Starting pidding.");
    }
    if( pid == 0)
    {
        printf("Child ID: %d", getpid());
        Test();
    }
    else
    {
        printf("Parent ID: %d", getpid());

    }
    pid = fork();
    if ( pid == 0)
    {
        printf("Child ID: %d", getpid());
        Test();
    }
    else
    {
        printf("Parent ID: %d", getpid());
        parent();
    }
    printf("Something Lived?\n");

    sem_destory(&Test);
    sem_destory(&Demo);
    return 0;

}