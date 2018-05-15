#ifndef QUEUE_H_
#define QUEUE_H_

#include "sched_context.h"

/* Queue<PsInfo_Sched*>
 * Fixed size. If the number of elements in the queue exceeds the capcity of queue, the behavior is undefined.
 * PsInfo_Sched* is only a reference to the actual Psinfo_Sched object. This pointer is not reference counted.
 * Do not directly push the pointer obtained from malloc or other memory allocation functions into this queue. 
 * Always keep a copy of the original pointer.
 * The behaviors of any illogical manipulations to the queue are undefined. 
 */

void *NewQueue(int capacity);
void QueuePush(void *queue, PsInfo_Sched *ps);
void QueuePop(void *queue);
PsInfo_Sched *QueueFront(void *queue);
void FreeQueue(void *queue);

int QueueCapacity(void *queue);
int QueueSize(void *queue);
int QueueEmpty(void *queue);


#endif