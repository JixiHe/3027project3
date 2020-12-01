#include "signal_catcher.cpp"
using namespace std;

int current_process_number;

struct timespec timeSIGUSR1;
double timeSumSIGUSR1;

struct timespec timeSIGUSR2;
double timeSumSIGUSR2;

void reporter_handler(int sig){
    if(sig==SIGINT){
        int detatch = shmdt(counter);
        if (detatch == -1) {
            cout << "failded to detach shared memory" << endl;
        }
        exit(0);
    }
    if(sig==SIGUSR1){
        clock_gettime(CLOCK_REALTIME,&timeSIGUSR1);
        timeSumSIGUSR1 = timeSumSIGUSR1 + timeSIGUSR1.tv_sec + timeSIGUSR2.tv_nsec;
        timeSumSIGUSR1 /= 1000000000L;
    }else if(sig==SIGUSR2){
        clock_gettime(CLOCK_REALTIME,&timeSIGUSR2);
        timeSumSIGUSR2 = timeSumSIGUSR2 + timeSIGUSR2.tv_sec + timeSIGUSR2.tv_nsec;
        timeSumSIGUSR2 /= 1000000000L;
    }
}

[[noreturn]] void reporter(int n){
    unblock_signal(SIGUSR1);
    unblock_signal(SIGUSR2);
    unblock_signal(SIGINT);
    signal(SIGINT,reporter_handler);
    signal(SIGUSR1,reporter_handler);
    signal(SIGUSR2,reporter_handler);

    while(true){
        pause();
        ofstream f;

        f.open("output.txt",ios::app);

        time_t now = time(0);
        tm *ltm = localtime(&now);

        current_process_number++;
        if(current_process_number==10){// report every 10 processes
            pthread_mutex_lock(&counter->lock_1);
            pthread_mutex_lock(&counter->lock_2);

            current_process_number=0;//set counter to 0
            double average_time_1 = timeSumSIGUSR1/10.0;
            double average_time_2 = timeSumSIGUSR2/10.0;

            f<<"SIGUSR1: Sent "<<counter->sentSIGUSR1<<" Received "<<counter->receivedSIGUSR1
             <<" current time: "<<ltm->tm_hour<<ltm->tm_min<<ltm->tm_sec<<" Average interval: "<< average_time_1<<endl;

            f<<"SIGUSR2: Sent "<<counter->sentSIGUSR2<<" Received "<<counter->receivedSIGUSR2
             <<" current time: "<<ltm->tm_hour<<ltm->tm_min<<ltm->tm_sec<<" Average interval: "<< average_time_2<<endl;

            average_time_1 = 0;
            average_time_2 = 0;

            timeSumSIGUSR1 = 0;
            timeSumSIGUSR2 = 0;

            pthread_mutex_unlock(&counter->lock_1);
            pthread_mutex_unlock(&counter->lock_2);
        }
    }
}