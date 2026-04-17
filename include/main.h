#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>

#define FTOK_PATHNAME   "textname.txt"
#define FTOK_PRJ_ID     299454
#define SHM_SIZE        2048

#include "customer.h"
#include "utilities.h"

typedef struct
{
    //semaphore needs
    int r_counter;
    sem_t rcnt;
    sem_t rdwr;
    sem_t addt;

    //for statistics needs
    int readers_total;
    int Rsleep_total;
    int writers_total;
    int Wsleep_total;
    int maxSleepTime; //find the maximum among readers/writers
    int recsProcessed;

}SharedData;