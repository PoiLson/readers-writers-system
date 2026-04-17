#include "../include/main.h"

void printCustomer(Customer* customer)
{
    printf("\t%d, %s, %s, %d\n",
        customer->customerID, customer->lastname,
        customer->firstname, customer->balance);
}

void printCustomers(const char* pathname)
{
    FILE* cfPtr = fopen(pathname, "rb");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    unsigned int size = 0;
    fseek(cfPtr, 0, SEEK_END);
    size = ftell(cfPtr);
    
    int numOfRecords = size / sizeof(Customer);

    printf("file %s, contains %d records:\n", pathname, numOfRecords);

    rewind(cfPtr);
    for(int idx = 0; idx < numOfRecords; idx++)
    {
        Customer customer; 
        fread(&customer, sizeof(Customer), 1, cfPtr);
        printCustomer(&customer);
    }

    fclose(cfPtr);
}

void printCustomerwithID(const char* pathname, int customerID)
{
    FILE* cfPtr = fopen(pathname, "rb");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    fseek(cfPtr, (customerID - 1)*sizeof(Customer), SEEK_SET);
    Customer myRec;
    fread(&myRec, sizeof(Customer), 1, cfPtr);

    printCustomer(&myRec);
    fclose(cfPtr);
}

void printAverageBalance(const char* pathname, int startIDX, int endIDX)
{
    FILE* cfPtr = fopen(pathname, "rb");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    int rec = startIDX;
    int counter = (endIDX - startIDX) + 1;
    int sumBalances = 0;

    Customer myRec;

    while(rec <= endIDX)
    {
        fseek(cfPtr, (rec - 1)*sizeof(Customer), SEEK_SET);
        fread(&myRec, sizeof(Customer), 1, cfPtr);

        sumBalances += myRec.balance;

        rec++; //they are continuously
    }

    if(counter == 0)
        printf("Average Balance for [%d]: %d\n", startIDX, sumBalances);
    else
        printf("Average Balance for [%d, %d]: %.2f\n", startIDX, endIDX, (float)sumBalances/counter);

    fclose(cfPtr);
}

int existCustomersFile(const char*  pathname)
{
    FILE *cfPtr = NULL; 

    if(pathname == NULL)
    {
        printf("CustomerFile cannot by NULL\n");
        return 0;
    }

    cfPtr = fopen(pathname, "rb");
    if (cfPtr == NULL)
    {
        perror("CustomerFile cannot be opened");
        return 0;
    }


    fseek(cfPtr, 0, SEEK_END);
    long int lSize = ftell(cfPtr);

    //have at least one customer
    if(lSize == 0 || lSize < sizeof(Customer))
    {
        printf("Invalid CustomerFile. Size too small\n");
        fclose(cfPtr);
        return 0;
    }



    fclose(cfPtr);
    return 1;
}

void changeCustomer(const char* pathname, int customerID, int value, int max_sleep_time)
{
    FILE* cfPtr = fopen(pathname, "rb+");

    if(cfPtr == NULL)
    {
        perror("fopen failed due to");
        exit(-1);
    }

    Customer myRec;

    fseek(cfPtr, (customerID - 1)*sizeof(Customer), SEEK_SET);
    fread(&myRec, sizeof(Customer), 1, cfPtr);
    
    printf("Change customer (ID:%d, Name= '%s, %s'), with  balance = %d.\n", myRec.customerID, myRec.lastname, myRec.firstname, myRec.balance);
    
    srand(time(NULL));
    int randomNum = 1 + (rand() % max_sleep_time);
    
    if(value > 0)
        printf("\tI will add %d units to its balance. I will need %d seconds...\n", value, randomNum);
    else
        printf("\tI will remove %d units to its balance. I will need %d seconds...\n", abs(value), randomNum);

    myRec.balance  += value;
    sleep(randomNum);

    fseek(cfPtr, (customerID - 1)*sizeof(Customer), SEEK_SET);
    int ret = fwrite(&myRec, sizeof(Customer), 1, cfPtr);

    if(ret <= 0)
    {
        perror("fwrite failed");
        exit(-1);
    }


    fclose(cfPtr);
}