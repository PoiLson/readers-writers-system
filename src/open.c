#include "../include/main.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Correct syntax is: %s <BinaryFile>\n", argv[0]);
        return(1);
    }

    key_t theKey;

    theKey = ftok(FTOK_PATHNAME, FTOK_PRJ_ID);
    if(theKey == -1){
        perror("ftok failed: ");
        return(-1);
    }

    //allocates a System V shared memory segment
    int shm_id = shmget(theKey, SHM_SIZE, 0666 | IPC_CREAT | IPC_EXCL);
    if(theKey == -1)
    {
        perror("shmget failed: ");
        return(-1);
    }

    printf("%d", shm_id);

    SharedData* sharedData = (SharedData*)shmat(shm_id, (void*)0, 0);
    if(sharedData == (SharedData*)-1)
    {
        perror("Attachment failed");
        exit(-1);
    }

    //initialize reader counter and semaphores
    sharedData->r_counter = 0;
    sem_init(&(sharedData->addt), 1, 1);
    sem_init(&(sharedData->rcnt), 1, 1);
    sem_init(&(sharedData->rdwr), 1, 1);

    //initialize statitstics data
    sharedData->readers_total = 0;
    sharedData->Rsleep_total = 0;
    sharedData->writers_total = 0;
    sharedData->Wsleep_total = 0;
    sharedData->maxSleepTime = 0;
    sharedData->recsProcessed = 0;

    int err = shmdt((void*)sharedData);
    if(err == -1)
    {
        perror("Detaching failed!");
        exit(-1);
    }
    return 0;
}