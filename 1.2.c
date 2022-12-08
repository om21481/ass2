#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>
#include<sys/wait.h>
#include<math.h>
#include<time.h>
#include<sched.h>

int main(){
    struct timespec end; 
    
    struct timespec t1, t2, t3, f1, f2, f3;

    long long int initial1_nsec, initial2_nsec, initial3_nsec, final1_nsec, final2_nsec, final3_nsec;
    long int initial1_sec, initial2_sec, initial3_sec, final1_sec, final2_sec, final3_sec;

    struct sched_param param1;
    param1.sched_priority = 0;
    struct sched_param param2;
    param2.sched_priority = 9;
    struct sched_param param3;
    param3.sched_priority = 1;
    

    clock_gettime(CLOCK_REALTIME, &t1);
    initial1_nsec = t1.tv_nsec;
    initial1_sec = t1.tv_sec;
    
    pid_t pid = fork();
    clock_gettime(CLOCK_REALTIME, &t1);
    initial1_nsec = t1.tv_nsec;
    initial1_sec = t1.tv_sec;
    
    if(pid == 0){
        int val = sched_setscheduler(getpid(), SCHED_OTHER, &param1);
        if(val != 0){
            printf("EXIT1");
            return 0;
        }

        // char temp[10];
        // sprintf(temp, "%d", getpid());

        // char command[100] = "/usr/bin/chrt -r -p 3 ";
        // strcat(command, temp);
        // system(command);
        
        // char comm[] = "/usr/bin/chrt -p ";
        // strcat(comm, temp);
        // system(comm);


        char* comm_[2] = {NULL};
        execvp("./kernel1.sh", comm_);

        clock_gettime(CLOCK_REALTIME, &f1);
        final1_nsec = f1.tv_nsec;
        final1_sec = f1.tv_sec;
    }
    else{
        clock_gettime(CLOCK_REALTIME, &t2);
        initial2_nsec = t2.tv_nsec;
        initial2_sec = t2.tv_sec;

        pid_t pid2 = fork();
        if(pid2 == 0){
            int val = sched_setscheduler(getpid(), SCHED_RR, &param2);
            if(val != 0){
                printf("EXIT2");
                return 0;
            }

            // char temp[10];
            // sprintf(temp, "%d", getpid());

            // char command[100] = "/usr/bin/chrt -f -p 2 ";
            // strcat(command, temp);
            // system(command);
            
            // char comm[] = "/usr/bin/chrt -p ";
            // strcat(comm, temp);
            // system(comm);


            char* comm_[2] = {NULL};
            execvp("./kernel2.sh", comm_);

            clock_gettime(CLOCK_REALTIME, &f2);
            final2_nsec = f2.tv_nsec;
            final2_sec = f2.tv_sec;
        }
        else{
            clock_gettime(CLOCK_REALTIME, &t3);
            initial3_nsec = t3.tv_nsec;
            initial3_sec = t3.tv_sec;

            pid_t pid3 = fork();
            if(pid3 == 0){
                int val = sched_setscheduler(getpid(), SCHED_FIFO, &param3);
                if(val != 0){
                    printf("EXIT3");
                    return 0;
                }
                // char temp[10];
                // sprintf(temp, "%d", getpid());

                // char command[100] = "/usr/bin/chrt -o -p 0 ";
                // strcat(command, temp);
                // system(command);
                
                // char comm[] = "/usr/bin/chrt -p ";
                // strcat(comm, temp);
                // system(comm);


                char* comm_[2] = {NULL};
                execvp("./kernel3.sh", comm_);

                clock_gettime(CLOCK_REALTIME, &f3);
                final3_nsec = f3.tv_nsec;
                final3_sec = f3.tv_sec;
            }
            else{
                while(wait(NULL) > 0){

                }

                printf("\nFor process1: %f \nFor process2: %f \nFor process3: %f\n", (final1_sec - initial1_sec + (final1_nsec - initial1_nsec)/1e9), (final2_sec - initial2_sec + (final2_nsec - initial2_nsec)/1e9), (final3_sec - initial3_sec + (final3_nsec - initial3_nsec)/1e9));
            }
        }
    }
    return 0;
}