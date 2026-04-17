#include "../include/main.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Correct syntax is: %s <MemoryID> <BinaryFile>\n", argv[0]);
        return(1);
    }

    int shm_id = atoi(argv[1]);

    SharedData* sharedData = (SharedData*)shmat(shm_id, (void*)0, 0);
    if(sharedData == (SharedData*)-1)
    {
        perror("Attaching failed!");
        exit(-1);
    }

    //print the statistics
    printf("->The total number of readers is: %d\n", sharedData->readers_total);
    printf("->The total number of writers is: %d\n", sharedData->writers_total);

    if(sharedData->readers_total == 0)
        printf("->The average sleeping time for readers was: ---\n");
    else
        printf("->The average sleeping time for readers was: %.2f\n", ((float)sharedData->Rsleep_total/sharedData->readers_total));
    

    if(sharedData->writers_total == 0)
        printf("->The average sleeping time for writers was: ---\n");
    else
        printf("->The average sleeping time for writers was: %.2f\n", ((float)sharedData->Wsleep_total/sharedData->writers_total));
    
    
    printf("->The maximum waiting time was: %d\n", sharedData->maxSleepTime);
    printf("->Total number of records processed: %d\n", sharedData->recsProcessed);
    
    //destroy the semaphores
    sem_destroy(&(sharedData->addt));
    sem_destroy(&(sharedData->rcnt));
    sem_destroy(&(sharedData->rdwr));

    //detach shared memory's info
    int err = shmdt((void*)sharedData);
    if(err == -1)
    {
        perror("Detaching failed!");
        exit(-1);
    }

    //and destroy shared memory segment
    err = shmctl(shm_id, IPC_RMID, 0);
    if(err == -1)
    {
        perror("Destroying segment failed!");
        exit(-1);
    }

    return 0;
}