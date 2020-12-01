#include "signal_generator.cpp"
using namespace std;

void block_signal(int signal){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    int sig_return = sigprocmask(SIG_BLOCK,&sigset,NULL);
    if(sig_return!=0){
        cout<<errno<<endl;
    }
}

void unblock_signal(int signal){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    int sig_return = sigprocmask(SIG_UNBLOCK,&sigset,NULL);
    if(sig_return!=0){
        cout<<errno<<endl;
    }
}

void signal_catcher_handler(int signal){
    if(signal == SIGINT){
        int detatch = shmdt(counter);
        if (detatch==-1){
            cout<<"failded to detach shared memory"<<endl;
        }
        exit(0);
    }
    if(signal == SIGUSR1){
        cout<<"received SIGSER1!"<<endl;
    }else if(signal == SIGUSR2){
        cout<<"received SIGSER2!"<<endl;
    }
}

[[noreturn]] void signal_catcher(int n){
    unblock_signal(SIGINT);
    signal(SIGINT,signal_catcher_handler);

    if(n==1){
        unblock_signal(SIGUSR1);
        signal(SIGUSR1,signal_catcher_handler);
    }if(n==2){
        unblock_signal(SIGUSR2);
        signal(SIGUSR2,signal_catcher_handler);
    }
    while(true){
        pause();
        if(n==1) {
            pthread_mutex_lock(&counter->lock_1);
            counter->receivedSIGUSR1++;
            pthread_mutex_unlock(&counter->lock_1);
        }
        if(n==2){
            pthread_mutex_lock(&counter->lock_2);
            counter->receivedSIGUSR2++;
            pthread_mutex_unlock(&counter->lock_2);
        }
    }
}
