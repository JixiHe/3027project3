#include <sys/shm.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <csignal>
#include <cmath>
#include <fstream>

struct SharedValues {
    int sentSIGUSR1=0;
    int sentSIGUSR2=0;
    int receivedSIGUSR1=0;
    int receivedSIGUSR2=0;
    pthread_mutex_t lock_1{};
    pthread_mutex_t lock_2{};
}SharedValues;

struct SharedValues *counter;
int srand_number = 1;