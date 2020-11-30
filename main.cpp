#include "reporter.cpp"
using namespace std;

#define run_time -1
#define max_process 10000
bool check_if_max(){
    int total = counter->sentSIGUSR1 + counter->sentSIGUSR2;
    if(total>=max_process){
        return true;
    }
    return false;
}

int main(){
    int shm_id = shmget(IPC_PRIVATE, sizeof(SharedValues), IPC_CREAT | 0666);
    counter = static_cast<struct SharedValues *>(shmat(shm_id, nullptr, 0));



    //create 8 process
    pid_t process[8];
    for(int i=0;i<=8;i++){
        process[i] = fork();
        if(process[i]==-1){
            cout << "error forking" << endl;
        }
        if(process[i]==0){
            if(i<2) {
                cout << "creating sig_1 Handler" << endl;
                signal_catcher(1);
            }else if(2<=i && i<4){
                cout << "creating sig_2 Handler" << endl;
                signal_catcher(2);
            } else if(i == 4) {
                cout << "Creating reporter" << endl;
                reporter(1);
            }
            else if(i > 4 && i < 8) {
                cout << "Creating signal generator" << endl;
                generator();
            }
            if(i == 7) {
                waitpid(process[i], nullptr, 0);
            }
        }
        else{
            if(i==8){
                while (true) {
                    if (check_if_max()) {
                        for (int x = 0; x < 8; x++) {
                            kill(process[x], SIGINT);
                        }
                        sleep(2);
                        cout << counter->sentSIGUSR1 << " " << counter->receivedSIGUSR1 << endl;
                        cout << counter->sentSIGUSR2 << " " << counter->receivedSIGUSR2 << endl;

                        int detatch = shmdt(counter);
                        if (detatch == -1) {
                            cout << "failded to detach shared memory" << endl;
                        }
                        exit(0);
                    }
                }
            }
            sleep(1);
        }
    }
    return 0;
}}