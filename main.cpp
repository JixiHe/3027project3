#include "reporter.cpp"
using namespace std;

#define run_time -1
#define max_process 10000


int main(){
    int shm_id = shmget(IPC_PRIVATE, sizeof(SharedValues), IPC_CREAT | 0666);
    counter = static_cast<struct SharedValues *>(shmat(shm_id, nullptr, 0));



    //create process
    pid_t process[8];
    for(int i=0;i<=8;i++){
        process[i] = fork();

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

        }
        else{
            sleep(1);
        }
        exit(0);
    }
    return 0;
}