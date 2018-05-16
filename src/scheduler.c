#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>

#include "sched_internal.h"

static int PsInfo_Cmp(const void *lhs, const void *rhs) {
    if(((const PsInfo*)lhs)->ready_time < ((const PsInfo*)rhs)->ready_time)
        return -1;
    else if(((const PsInfo*)lhs)->ready_time == ((const PsInfo*)rhs)->ready_time)
        return 0;
    else 
        return 1;
}

int main() {
    #ifdef _DEBUG
    printf("PID=%d\n", getpid());
    #endif

    struct sched_param sched_max_priority;
    sched_max_priority.sched_priority = sched_get_priority_max(SCHED_RR);
    sched_setscheduler(0, SCHED_RR, &sched_max_priority);

    cpu_set_t cpu0, cpu1;
    CPU_ZERO(&cpu0);
    CPU_ZERO(&cpu1);
    CPU_SET(0, &cpu0);
    CPU_SET(1, &cpu1);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpu0);

    int n_ps;
    char policy[5];
    scanf("%s", policy);
    scanf("%d", &n_ps);

    PsInfo *ps = malloc(n_ps * sizeof(PsInfo));
    for(int i = 0; i < n_ps; ++i) {
        scanf("%s%d%d", ps[i].name, &ps[i].ready_time, &ps[i].exec_time);
        ps[i].pid = -1;
    }

    qsort(ps, n_ps, sizeof(PsInfo), PsInfo_Cmp);

    void *sched_ctx = InitScheduler(policy, ps, n_ps);

    int n_term = 0; /* number of terminated process */
    int time = 0;

    int next_start_idx = 0;
    int prev_terminated;
    pid_t running = -1, next;

    while(n_term < n_ps) {

        while(ps[next_start_idx].ready_time == time) {
            pid_t pid;
            if((pid = fork()) == 0) {
                char argv1[20];
                sprintf(argv1, "%d", ps[next_start_idx].exec_time);
                execl("./process", "./process", argv1, (char*)NULL);
            }
            else {
                sched_setscheduler(pid, SCHED_RR, &sched_max_priority);
                sched_setaffinity(pid, sizeof(cpu_set_t), &cpu1);
                waitpid(pid, NULL, WUNTRACED);
                printf("%s %d\n", ps[next_start_idx].name, pid);
                ps[next_start_idx].pid = pid;

                #ifdef _DEBUG
                printf("START %s, PID=%d, TIME=%d\n", ps[next_start_idx].name, ps[next_start_idx].pid, time);
                #endif

                ++next_start_idx;
            }
        }

        next = SchedNextPs(sched_ctx, &prev_terminated);
        if(prev_terminated) {
            #ifdef _DEBUG
            printf("[EXIT] %d, TIME=%d\n", running, time);
            #endif

            ++n_term;
            waitpid(running, NULL, 0);
            running = -1;
        }
        if(next >= 0) {
            if(running < 0) {
                #ifdef _DEBUG
                printf("[RUN] %d, TIME=%d\n", next, time);
                #endif
                kill(next, SIGCONT);
                running = next;
            }
            else if(next != running) {
                #ifdef _DEBUG
                printf("[STOP] %d, TIME=%d\n", running, time);
                printf("[RUN] %d, TIME=%d\n", next, time);
                #endif
                kill(running, SIGSTOP);
                kill(next, SIGCONT);
                running = next;
            }
        }
        
        for(volatile unsigned long i = 0; i < 1000000UL; ++i);
        
        ++time;
    }
    
    FreeScheduler(sched_ctx);
    free(ps);

    return 0;
}