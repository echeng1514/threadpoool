#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "threadpool.h"

#define QUEUESIZE 2
#define MAXPOOL 30
#define MINPOOL 10

void func(void *args)
{
    int num = *(int *)args;
    printf("workerThread[%ld] is working. NUM = %d\n", pthread_self(), num);
    sleep(1);
}


int main()
{
    ThreadPool *pool = NULL;
    int i;
    int *count = NULL;
    /*创建线程池*/
    pool = threadPoolCreate(MINPOOL, MAXPOOL, QUEUESIZE);
    for (i = 0; i < QUEUESIZE; i++) {
        /*args需要堆内存*/
        count = (int*)malloc(sizeof(int));
        *count = i + QUEUESIZE;
        threadPoolAdd(pool, func, (void *)count);
    }
    sleep(30);

    threadPoolDestroy(pool);
    return 1;
}
