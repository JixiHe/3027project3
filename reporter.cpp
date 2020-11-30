#include "signal_catcher.cpp"
using namespace std;

int current_process_number;

struct timespec timeSIGUSR1;
double timeSumSIGUSR1;

struct timespec timeSIGUSR2;
double timeSumSIGUSR2;

void reporter_handler(int sig){
    if(sig==SIGUSR1){
        clock_gettime(CLOCK_REALTIME,&timeSIGUSR1);

    }else if(sig==SIGUSR2){
        clock_gettime(CLOCK_REALTIME,&timeSIGUSR2);

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
        // report every 10 processes
        if(current_process_number==10){
            pthread_mutex_lock(&counter->lock_1);
            pthread_mutex_lock(&counter->lock_2);

        }
    }
}