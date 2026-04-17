#pragma once

typedef struct customer
{
    int customerID; //it always starts from 1
    char lastname[20];
    char firstname[20];
    int balance;
}Customer;

void printCustomer(Customer* customer);
void printCustomers(const char* pathname);
void printCustomerwithID(const char* pathname, int customerID);
void printAverageBalance(const char* pathname, int startIDX, int endIDX);

int existCustomersFile(const char*  pathname);
void changeCustomer(const char* pathname, int customerID, int value, int max_sleep_time);