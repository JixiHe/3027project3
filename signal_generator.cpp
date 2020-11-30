#include "main.h"
using namespace std;

void generator_handler(int signal){
    if(signal == SIGINT){
        int detatch = shmdt(counter);
        if(detatch==-1){
            cout<<"fail to detach shared memory"<<endl;
        }
    }
    exit(0);
}
double rand_gengerate(double min, double max){
    int ran = rand();
    double random_number = (fmod((double)ran,max*100)+min*100);
    return random_number/100;
}

[[noreturn]] void generator(){
    signal(SIGINT,generator_handler);

    srand(srand_number);
    int x = 0;
    while (true){
        x++;
        double rand = rand_gengerate(0.0,1.0);
        if (rand<0.5){
            pthread_mutex_lock(&counter->lock_1);
            counter->sentSIGUSR1++;
            pthread_mutex_unlock(&counter->lock_1);
            kill(0,SIGUSR1);
        }else if (rand>=0.5){
            pthread_mutex_lock(&counter->lock_2);
            counter->sentSIGUSR2++;
            pthread_mutex_unlock(&counter->lock_2);
            kill(0,SIGUSR2);
        }
        struct timespec t{};
        t.tv_sec = 0;
        t.tv_nsec = rand_gengerate(0.01,0.1)*1000000000L;
        nanosleep(&t,nullptr);
    }
}


