#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>
#include<sys/wait.h>
#include<math.h>
#include<time.h>

FILE* ptr;

void* fun1(void* arg){
    struct timespec t1,t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    float initial_sec = t1.tv_sec;
    long long int initial_nsec = t1.tv_nsec;
    // clockid_t c;
    long int count = 0;
    for(long int i=1;i<pow(2, 32);i++){
        // printf("thread1: %d ", i);
        count++;
    }

    int val=clock_gettime(CLOCK_MONOTONIC, &t2);
    float final_sec = t2.tv_sec;
    long long int final_nsec = t2.tv_nsec;
    // printf("%f\n ",  initial1);

    if(val == -1){
        printf("Exit fun1");
        return NULL;
    }

    float time = (final_sec - initial_sec) + ((final_nsec - initial_nsec)/1e9);

    printf("Time for completion for thread1 is: %f \n", time);
    fprintf(ptr, "1 %f ", time);

    return NULL;
}

void* fun2(void* arg){
    struct timespec t1,t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    float initial_sec = t1.tv_sec;
    long long int initial_nsec = t1.tv_nsec;
    // clockid_t c;
    long int count = 0;
    for(long int i=1;i<pow(2, 32);i++){
        // printf("thread1: %d ", i);
        count++;
    }

    int val=clock_gettime(CLOCK_MONOTONIC, &t2);
    float final_sec = t2.tv_sec;
    long long int final_nsec = t2.tv_nsec;
    // printf("%f\n ",  initial1);

    if(val == -1){
        printf("Exit fun2");
        return NULL;
    }

    float time = (final_sec - initial_sec) + ((final_nsec - initial_nsec)/1e9);

    printf("Time for completion for thread2 is: %f \n", time);
    fprintf(ptr, "2 %f ", time);

    return NULL;
}

void* fun3(void* arg){
    struct timespec t1,t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    float initial_sec = t1.tv_sec;
    long long int initial_nsec = t1.tv_nsec;
    // clockid_t c;
    long int count = 0;
    for(long int i=1;i<pow(2, 32);i++){
        // printf("thread1: %d ", i);
        count++;
    }

    int val=clock_gettime(CLOCK_MONOTONIC, &t2);
    float final_sec = t2.tv_sec;
    long long int final_nsec = t2.tv_nsec;
    // printf("%f\n ",  initial1);

    if(val == -1){
        printf("Exit fun3");
        return NULL;
    }

    float time = (final_sec - initial_sec) + ((final_nsec - initial_nsec)/1e9);

    printf("Time for completion for thread3 is: %f \n", time);
    fprintf(ptr, "3 %f ", time);

    return NULL;
}

int main(){
    if ((ptr = fopen("data.txt", "a")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       return 0;
    }
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;

    int rc = 0;

    struct sched_param param1;
    param1.sched_priority = 90;
    struct sched_param param2;
    param2.sched_priority = 90;
    struct sched_param param3;
    param3.sched_priority = 0;

    pthread_create(&pthread1, NULL, fun1, NULL );
    rc = pthread_setschedparam(pthread1, SCHED_FIFO, &param1);
    if(rc != 0){
        printf("a\n");
        printf("EXIT");
        return 0;
    } 

    pthread_create(&pthread2, NULL, fun2, NULL);
    rc = pthread_setschedparam(pthread2, SCHED_RR, &param2);
    if(rc != 0){
        printf("b\n");
        printf("EXIT");
        return 0;
    }

    pthread_create(&pthread3, NULL, fun3, NULL);  
    rc = pthread_setschedparam(pthread3, SCHED_OTHER, &param3);
    if(rc != 0){
        printf("c\n");
        printf("EXIT");
        return 0;
    }

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    fprintf(ptr, "\n");
    fclose(ptr);

    return 0;
}


// 3 2 0
// Time for completion for thread3 is: 15.890654
// Time for completion for thread1 is: 19.062887
// Time for completion for thread2 is: 19.284075

// 1 1 0
// Time for completion for thread1 is: 18.523016
// Time for completion for thread2 is: 18.612968
// Time for completion for thread3 is: 18.873327

// 2 2 0
// Time for completion for thread3 is: 17.995596
// Time for completion for thread1 is: 18.601091
// Time for completion for thread2 is: 18.643030

// 2 3 0
// Time for completion for thread1 is: 18.267609
// Time for completion for thread3 is: 18.287743
// Time for completion for thread2 is: 18.491421

// 5 5 0
// Time for completion for thread2 is: 18.059784
// Time for completion for thread3 is: 18.242603
// Time for completion for thread1 is: 18.395418

// 90 93 0
// Time for completion for thread3 is: 17.994831
// Time for completion for thread1 is: 18.530396
// Time for completion for thread2 is: 18.542101

// 5 4 0
// Time for completion for thread2 is: 17.652023
// Time for completion for thread3 is: 18.045727
// Time for completion for thread1 is: 18.442139

// 14 15 0
// Time for completion for thread2 is: 17.652023
// Time for completion for thread3 is: 18.045727
// Time for completion for thread1 is: 18.442139

// 70 80 0
// Time for completion for thread1 is: 18.803270
// Time for completion for thread2 is: 18.840014
// Time for completion for thread3 is: 18.877306

// 50 90 0
// Time for completion for thread2 is: 17.249342
// Time for completion for thread1 is: 18.938147
// Time for completion for thread3 is: 19.128164
