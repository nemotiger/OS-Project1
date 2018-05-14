#include <stdlib.h>
#include <signal.h>
#include "myservice.h"

struct timespec tv_start;

void LogProcessLifeTime() {
    log_pslifetime(&tv_start);
}

int main(int argc, char **argv) {

    get_nstime(&tv_start);
    raise(SIGSTOP);
    atexit(LogProcessLifeTime);

    int exec_time = atoi(argv[1]);
    volatile unsigned long i; 

    for(int t = 0; t < exec_time; ++t) {
        for(i = 0; i < 1000000UL; ++i);
    }

    return 0;
}