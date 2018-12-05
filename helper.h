#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECS 1000
#define NANOSECS 1000000
#define SEC_TO_MISECS 1000000
#define NANOSEC_TO_MISECS 1000 
uint64_t time_elapsed(struct timespec start, struct timespec end) {
    uint64_t diff =  SECS * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / NANOSECS;  
    return diff;
}

uint64_t time_elapsed_misec(struct timespec start, struct timespec end) {
    uint64_t diff =  SEC_TO_MISECS * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / NANOSEC_TO_MISECS;  
    return diff;
}
