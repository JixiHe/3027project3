#include "signal_generator.cpp"
using namespace std;


void signal_catcher_handler(int signal){
    if(signal == SIGINT){
        int detatch = shmdt(counter);
        if (detatch==-1){
            cout<<"fail to detach shared memory"<<endl;
        }
        exit(0);
    }
    if(signal == SIGUSR1){
        cout<<"received SIGSER1!"<<endl;
    }else if(signal == SIGUSR2){
        cout<<"received SIGSER2!"<<endl;
    }
}
void signal_catcher(int n){
    signal(SIGINT,signal_catcher_handler);

    if(n==1){
        signal(SIGUSR1,signal_catcher_handler);
    }if(n==2){
        signal(SIGUSR2,signal_catcher_handler);
    }

}
