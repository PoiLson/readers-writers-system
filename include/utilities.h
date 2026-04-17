#pragma once

void extractNumbers(const char* str, int* start, int* end);
void getFlagsReader(int argc, char* argv[], const char** filename, int* startCustomerID, int* endCustomerID, int* sleep_time, int* shm_id);
void getFlagsWriter(int argc, char* argv[], const char** filename, int* customerID, int* value, int* sleep_time, int* shm_id);
void readerWork(const char* pathname, int startIDX, int endIDX, int max_sleep_time);