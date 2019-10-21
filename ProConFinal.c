#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>

int count = 0;
int initial = 10;
int index1 = 0;
const int MAX_BUF_SIZE = 10;
int Prod_Buff[10];

void put(int n)
{
    printf("Count: %d\n", count);
    Prod_Buff[count++] = initial;
    printf("Putting %d in Prod_Buff\n", initial);
           
}

int get()
{
    printf("Count: %d\n", count);
    index1 = count;
    initial = Prod_Buff[--count];
    return initial;
}

void produce()
{
    initial++;
}
void consume()
{
    printf("In consumer sent %d number %d\n", count, get());
}


void* prod_func(void* arg)
{
    while(count >= MAX_BUF_SIZE) {
        put(initial);
        produce();
    }
     pthread_exit(0);
}

void* cons_func(void* arg)
{
    while(count == 0){}
    while(count > 0)
    {
        consume();
    }
    pthread_exit(0);
}

int main()
{
    //Code was provided by Mark Reha in a previous semester.
pthread_t thr_producer_handle;
  pthread_t thr_consumer_handle;

  int th_prod_creat_stat;
  int th_cons_creat_stat;
  int th_join_status;

  /*  Make a producer thread  */
  th_prod_creat_stat = pthread_create(&thr_producer_handle, //pthread_t* thread
                                      NULL,                 //const pthread_attr_r* attr
			   	      prod_func,            //void* (*start_routine)(void*)
			   	      NULL);                //void* arg

  /*  Make a consumer thread  */
  th_cons_creat_stat = pthread_create(&thr_consumer_handle, //pthread_t* thread
                                      NULL,                 //const pthread_attr_r* attr
			   	      cons_func,            //void* (*start_routine)(void*)
			   	      NULL);                //void* arg

  th_join_status = pthread_join(thr_producer_handle, //pthread_t thread
                                NULL);               //void** retval
  th_join_status = pthread_join(thr_consumer_handle, //pthread_t thread
                                NULL);               //void** retval

  printf("Done processing\n");
  return 0;

}
