__SCHEDULER_HEADER = sched_internal.h sched_context.h queue.h priority_queue.h ps_info.h 
__SCHEDULER_SOURCE = scheduler.c sched_internal queue.c priority_queue.c 
__SCHED_POLICY_HEADER = fifo.h sjf.h psjf.h round_robin.h sched_policy.h
__SCHED_POLICY_SOURCE = fifo.c sjf.c psjf.c round_robin.c

SCHEDULER_HEADER = $(addprefix src/, $(__SCHEDULER_HEADER))
SCHEDULER_SOURCE = $(addprefix src/, $(__SCHEDULER_SOURCE))
SCHED_POLICY_HEADER = $(addprefix src/sched_policy/, $(__SCHED_POLICY_HEADER))
SCHED_POLICY_SOURCE = $(addprefix src/sched_policy/, $(__SCHED_POLICY_SOURCE))

ALL = $(SCHEDULER_HEADER) $(SCHEDULER_SOURCE) $(SCHED_POLICY_HEADER) $(SCHED_POLICY_SOURCE) \
      src/myservice.h src/process.c

all: $(ALL)
	gcc -std=c11 -Isrc/ -o scheduler $(SCHEDULER_SOURCE) $(SCHED_POLICY_SOURCE)
	gcc -std=c11 -Isrc/ -o process src/process.c 