#include "../include/main.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Correct syntax is: %s -f <BinaryFile> -l <recid[,recid]> -v <value> -d <time> -s <shmid>\n", argv[0]);
        return(1);
    }

    const char* pathname = NULL;
    int customerID = -1;
    int value = -1;
    int sleep_time = -1;
    int shm_id = -1;
    getFlagsWriter(argc, argv, &pathname, &customerID, &value, &sleep_time, &shm_id);

    // printf("Called writer\n");

    if(existCustomersFile(pathname)<=0)
    {
        return(-1);
    }

    SharedData* sharedData = (SharedData*)shmat(shm_id, (void*)0, 0);
    if(sharedData == (SharedData*)-1)
    {
        perror("Attaching failed!");
        exit(-1);
    }

    sem_wait(&(sharedData->addt));
    sem_wait(&(sharedData->rdwr));

    //START OF CS
    printf("Entered CS WRITER -> ");
    changeCustomer(pathname, customerID, value, sleep_time);
    printCustomerwithID(pathname, customerID);
    if(sleep_time > sharedData->maxSleepTime)
        sharedData->maxSleepTime = sleep_time;

    sharedData->writers_total++;
    sharedData->Wsleep_total += sleep_time;
    sharedData->recsProcessed++;
    //END OF CS

    sem_post(&(sharedData->rdwr));
    sem_post(&(sharedData->addt));

    //detach shared memory's info
    int err = shmdt((void*)sharedData);
    if(err == -1)
    {
        perror("Detaching failed!");
        exit(-1);
    }
    return 0;
}