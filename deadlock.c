#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *lock;

int timerStatus = 0;

// The Child PID if the Parent else the Parent PID if the Child
pid_t pid, otherPid;

/***********************************/

void *timer(void *a) {
	printf("\nTimer thread starting");
	sleep(10);
	if (sem_trywait(lock) != 0) {
		timerStatus = 1;
	}
	return a;
}

void parent() {
	printf("\nParent process running...");
	pthread_t tid1;
	
	// Give child chance to start
	sleep(5);
	
	// See if semaphore used without hanging indefinitely
	if (sem_trywait(lock) != 0) {
		// Create timer thread
		printf("\nParent creating timer thread");
		if (pthread_create(&tid1, NULL, timer, NULL)) {
			printf("\n ERROR creating timer thread");
			exit(1);
		}
		// Join thread back
		printf("\nJoining timer thread");
		if (pthread_join(tid1, NULL)) {
			printf("\n ERROR joining timer thread");
			exit(1);
		}
	}
	
	printf("\nTimer status is %i", timerStatus);
	
	// If still hung, kill child process
	if (timerStatus == 1)
	{
		kill(pid, SIGKILL);
	}
}

void child() {
	printf("\nChild process running...");
	
	// Lock semaphore
	sem_wait(lock);
	
	// Print dots in second intervals (to show it's still running)
	while(1) {
		sleep(1);
		printf(".\n");
	}
	
	// Doesn't stop or reopen semaphore
}

/***********************************/

int main() {
	
	// Initialize binary semaphore
	lock = sem_open("/mysem", O_CREAT, 0644, 1);
	
	// Use fork()
	pid = fork();
	if (pid == -1)
	{
		// Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
		printf("Can't fork, error %d\n", errno);
		exit(EXIT_FAILURE);
	}
	// OK: If fork() returns non zero then the parent process is running else child process is running
	
	if (pid == 0)
	{
		printf("Pid was 0 (running parent)");
		otherPid = pid;
		parent();
	}
	else
	{
		printf("Pid was not 0 (running child)");
		otherPid = getppid();
		child();
	}
	
	// Close semaphore, threads
	sem_close(lock);
	pthread_exit(NULL);
	
	return 0;
}