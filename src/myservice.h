#ifndef MYSERVICE_H_
#define MYSERVICE_H_

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/time.h>

inline void get_nstime(struct timespec *time) {
    syscall(333, time);
}

inline void log_pslifetime(struct timespec *tv_start) {
    syscall(334, tv_start);
}

#endif