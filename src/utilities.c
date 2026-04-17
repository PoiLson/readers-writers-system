#include "../include/main.h"

void extractNumbers(const char* str, int* start, int* end)
{
    int count = 0;
    // Iterate through each character in the string
    while (*str)
    {
        // Check if the current character is a digit
        if (isdigit(*str))
        {
            count++;
            // Extract and print the number
            int num = 0;
            while (isdigit(*str))
            {
                num = num * 10 + (*str - '0');
                str++;
            }

            if (*str != '[' && count == 1)
            {
                *start = num;
                *end = num;
                return;
            }

            if(count == 1)
                *start = num;
            else
                *end = num;
        }
        else
        {
            // Move to the next character
            str++;
        }
    }

    return;
}

void getFlagsReader(int argc, char* argv[], const char** filename, int* startCustomerID, int* endCustomerID, int* sleep_time, int* shm_id)
{
    for (int idx = 1; idx < argc; idx++)
    {
        char* argument = argv[idx];

        if (strcmp(argument, "-f") == 0)
        {
            idx++;
            *filename = argv[idx];
        }

        if (strcmp(argument, "-l") == 0)
        {
            idx++;
            *startCustomerID = atoi(argv[idx]);
            if(*startCustomerID <= 0)
            {
                printf("customerID must be equal or greater than 1\n");
                exit(-1);
            }

            extractNumbers(argv[idx], startCustomerID, endCustomerID);

            if(*endCustomerID < *startCustomerID)
            {
                printf("last customerID must be less than first customerID\n");
                exit(-1);
            }
        }

        if (strcmp(argument, "-d") == 0)
        {
            idx++;
            *sleep_time = atoi(argv[idx]);
            if(!(*sleep_time >= 1 && *sleep_time <= 100))
            {
                printf("Sleep time is out of range for reader process, it should be [1, 100] seconds.\n");
                exit(-1);
            }

        }

        if (strcmp(argument, "-s") == 0)
        {
            idx++;
            *shm_id = atoi(argv[idx]);
        }
    }


    if (*filename == NULL)
    {
        printf("No flag for file was inserted!\n");
        exit(-1);
    }


    if ((*startCustomerID) == -1)
    {
        printf("No flag for customer(s) ID('s) was inserted!\n");
        exit(-1);
    }

    if (*sleep_time == -1)
    {
        printf("No flag for sleeping time was inserted!\n");
        exit(-1);
    }

    if (*shm_id == -1)
    {
        printf("No flag for shared memory's ID was inserted!\n");
        exit(-1);
    }

    //check if customerID is valid!
    FILE* cfPtr = fopen(*filename, "rb");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    unsigned int size = 0;
    fseek(cfPtr, 0, SEEK_END);
    size = ftell(cfPtr);
    
    int numOfRecords = size / sizeof(Customer);

    if(*startCustomerID > numOfRecords || *endCustomerID > numOfRecords)
    {
        printf("CustomerID is out of range: [1, %d]!\n", numOfRecords);
        exit(-1);
    }
}

void getFlagsWriter(int argc, char* argv[], const char** filename, int* customerID, int* value, int* sleep_time, int* shm_id)
{

    for (int idx = 1; idx < argc; idx++)
    {
        char* argument = argv[idx];

        if (strcmp(argument, "-f") == 0)
        {
            idx++;
            *filename = argv[idx];
        }

        if (strcmp(argument, "-l") == 0)
        {
            idx++;
            *customerID = atoi(argv[idx]);
            if(*customerID <= 0)
            {
                printf("customerID must be equal or greater than 1\n");
                exit(-1);
            }
        }

        if (strcmp(argument, "-v") == 0)
        {
            idx++;
            *value = atoi(argv[idx]);
        }

        if (strcmp(argument, "-d") == 0)
        {
            idx++;
            *sleep_time = atoi(argv[idx]);
            if(!(*sleep_time >= 1 && *sleep_time <= 10))
            {
                printf("Sleep time is out of range for writer process, it should be [1, 10] seconds.\n");
                exit(-1);
            }

        }

        if (strcmp(argument, "-s") == 0)
        {
            idx++;
            *shm_id = atoi(argv[idx]);
        }
    }


    if (*filename == NULL)
    {
        printf("No flag for file was inserted!\n");
        exit(-1);
    }


    if ((*customerID) == -1)
    {
        printf("No flag for customer(s) ID('s) was inserted!\n");
        exit(-1);
    }

    if (*value == -1)
    {
        printf("No flag for value was inserted!\n");
        exit(-1);
    }

    if (*sleep_time == -1)
    {
        printf("No flag for sleeping time was inserted!\n");
        exit(-1);
    }

    if (*shm_id == -1)
    {
        printf("No flag for shared memory's ID was inserted!\n");
        exit(-1);
    }

    //check if customerID is valid!
    FILE* cfPtr = fopen(*filename, "rb");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    unsigned int size = 0;
    fseek(cfPtr, 0, SEEK_END);
    size = ftell(cfPtr);
    
    int numOfRecords = size / sizeof(Customer);

    if(*customerID > numOfRecords)
    {
        printf("CustomerID is out of range: [1, %d]!\n", numOfRecords);
        exit(-1);
    }
}

void readerWork(const char* pathname, int startIDX, int endIDX, int max_sleep_time)
{
    int rec = startIDX;

    srand(time(NULL));
    int randomNum = 1 + (rand() % max_sleep_time);

    if(startIDX == endIDX)
        printf("Reading ID %d. I will need %d seconds.\n", rec, randomNum);
    else
        printf("Reading IDs [%d - %d]. I will need %d seconds.\n", startIDX, endIDX, randomNum);


    sleep(randomNum);

    while(rec <= endIDX)
    {
        printCustomerwithID(pathname, rec);
        rec++;
    }

    printAverageBalance(pathname, startIDX, endIDX);

    return;
}