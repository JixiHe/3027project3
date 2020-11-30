#include <sys/shm.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <csignal>
#include <cmath>
#include <fstream>

struct SharedValues {
    pthread_mutex_t lock_1{};
    pthread_mutex_t lock_2{};
}SharedValues;

struct SharedValues *counter;
int srand_number = 1;