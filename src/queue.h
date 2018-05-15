#ifndef QUEUE_H_
#define QUEUE_H_

#include "sched_context.h"

/* Queue<PsInfo*>
 * Fixed size. If the number of elements in the queue exceeds the capcity of queue, the behavior is undefined.
 * PsInfo* is only a reference to the actual Psinfo object. This pointer is not reference counted.
 * Queue does not own the pointers it contains.
 * The behaviors of any illogical manipulations to the queue are undefined. 
 */

void *NewQueue(int capacity);
void QueuePush(void *queue, PsInfo *ps);
void QueuePop(void *queue);
PsInfo *QueueFront(void *queue);
void FreeQueue(void *queue);

int QueueCapacity(void *queue);
int QueueSize(void *queue);
int QueueEmpty(void *queue);


#endif