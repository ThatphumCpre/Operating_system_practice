#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NUM1    4
#define NUM2    40
#define NUMOFTHREADS    3

/* Prototypes */
void *printPrimeThreadCalculation(void *threadid);
void primeCheckerThread(int num1, int num2, int numOfThreads);

int main() {

    /* Thread Prime Checker */
    primeCheckerThread(NUM1, NUM2, NUMOFTHREADS);
    /* Exits the threads */
    pthread_exit(NULL);
    return 0;
}

void *printPrimeThreadCalculation(void *threadid) {
    long tid;
    tid = (long) threadid;
    static int cnt=0; //cnt=count
    int number1 = NUM1+(NUM2-NUM1)*cnt/NUMOFTHREADS;
    int number2 = NUM1+(NUM2-NUM1)*(cnt+1)/NUMOFTHREADS;
    cnt+=1;
    int isPrime, i;

    /* Calculations */
    while (number1 <= number2) {
        /* Assume isPrime is true */
        isPrime = 1;

        for (i = 2; i < number1 && isPrime; i++) {
            if (number1 % i == 0) {
                isPrime = 0;
            }
        }
        if (isPrime == 1) {
            printf("%d ", number1);
        }
        number1++;
    }
    printf("\n");
}

void primeCheckerThread(int num1, int num2, int numOfThreads) {
    /* Create threads */
    pthread_t threads[numOfThreads];
    int rc;
    long t;
    for (t = 0; t < numOfThreads; t++) {
        /* Creates threads */
        rc = pthread_create(&threads[t], NULL, printPrimeThreadCalculation, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }  pthread_join(threads[t],NULL);

    }

}