#include "queue.h"

#include <stdlib.h>

typedef struct {
    int cap;
    int size;
    int begin;
    int end;
    PsInfo **arr;
} Queue;

void *NewQueue(int capacity) {
    Queue *q = malloc(sizeof(Queue));
    q->arr = malloc(capacity * sizeof(PsInfo*));
    q->cap = capacity;
    q->size = 0;
    q->begin = 0;
    q->end = 0;
    return q;
}

void QueuePush(void *queue, PsInfo *ps) {
    Queue *q = queue;
    q->arr[q->end] = ps;
    q->end = (q->end + 1) % q->cap;
    ++q->size;
}

void QueuePop(void *queue) {
    Queue *q = queue;
    q->begin = (q->begin + 1) % q->cap;
    --q->size;
}

PsInfo *QueueFront(void *queue) {
    return ((Queue*)queue)->arr[((Queue*)queue)->begin];
}

void FreeQueue(void *queue) {
    free(((Queue*)queue)->arr);
    free(queue);
}

int QueueCapacity(void *queue) {
    return ((Queue*)queue)->cap;
}

int QueueSize(void *queue) {
    return ((Queue*)queue)->size;
}

int QueueEmpty(void *queue) {
    return ((Queue*)queue)->size == 0 ? 1 : 0;
}