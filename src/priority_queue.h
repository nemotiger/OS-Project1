#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "sched_context.h"

/* PQueue<PsInfo*> : priority_queue<PsInfo*>
 * Fixed size. If the number of elements in the PQueue exceeds the capcity of PQueue, the behavior is undefined.
 * PsInfo* is only a reference to the actual PsInfo object. This pointer is not reference counted.
 * PQueue does not own the pointers it contains.
 * The behaviors of any illogical manipulations to the PQueue are undefined.
 * Caution: The implementation is not optimized, but the behavior of PQueue is same as prority_queue. 
 */

void *NewPQueue(int capacity, int (*cmp)(const void *lhs, const void *rhs));
void PQueuePush(void *pqueue, PsInfo *ps);
void PQueuePop(void *pqueue);
PsInfo *PQueueFront(void *pqueue);
void FreePQueue(void *pqueue);

int PQueueCapacity(void *pqueue);
int PQueueSize(void *pqueue);
int PQueueEmpty(void *pqueue);


#endif