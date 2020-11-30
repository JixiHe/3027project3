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

void generator(){
    signal(SIGINT,generator_handler);

    srand(srand_number);

}


