#include "../include/main.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Correct syntax is: %s -f <BinaryFile> -l <recid[,recid]> -d <time> -s <shmid>\n", argv[0]);
        return(1);
    }

    const char* pathname = NULL;
    int startCustomerID = -1;
    int endCustomerID = -1;
    int sleep_time = -1;
    int shm_id = -1;
    getFlagsReader(argc, argv, &pathname, &startCustomerID, &endCustomerID, &sleep_time, &shm_id);

    //printf("Called reader\n");

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
    sem_wait(&(sharedData->rcnt));
    sharedData->r_counter++;
    
    if(sharedData->r_counter == 1)
        sem_wait(&(sharedData->rdwr));

    sem_post(&(sharedData->rcnt));
    sem_post(&(sharedData->addt));
    srand(time(NULL));

    //START OF CS
    printf("Entered CS READER -> ");
    readerWork(pathname, startCustomerID, endCustomerID, sleep_time);

    if(sleep_time > sharedData->maxSleepTime)
        sharedData->maxSleepTime = sleep_time;
        
    sharedData->readers_total++;
    sharedData->Rsleep_total += sleep_time;
    sharedData->recsProcessed += ((endCustomerID - startCustomerID) + 1);
    //END OF CS

    sem_wait(&(sharedData->rcnt));
    sharedData->r_counter--;

    if(sharedData->r_counter == 0)
        sem_post(&(sharedData->rdwr));

    sem_post(&(sharedData->rcnt));

    //detach shared memory's info
    int err = shmdt((void*)sharedData);
    if(err == -1)
    {
        perror("Detaching failed!");
        exit(-1);
    }
    return 0;
}