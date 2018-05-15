#include "priority_queue.h"

#include <stdlib.h>

typedef struct {
    int cap;
    int end;
    int sorted;
    PsInfo **arr;
    int (*cmp)(const void *lhs, const void *rhs);
} PQueue;

void *NewPQueue(int capacity, int (*cmp)(const void *lhs, const void *rhs)) {
    PQueue *q = malloc(sizeof(PQueue));
    q->arr = malloc(capacity * sizeof(PsInfo*));
    q->cap = capacity;
    q->end = 0;
    q->sorted = 1;
    q->cmp = cmp;
    return q;
}

void PQueuePush(void *pqueue, PsInfo *ps) {
    PQueue *q = pqueue;
    q->arr[q->end++] = ps;
    q->sorted = 0;
}

void PQueuePop(void *pqueue) {
    PQueue *q = pqueue;
    if(!q->sorted)
        qsort(q->arr, q->end, sizeof(PsInfo*), q->cmp);
    q->arr[0] = q->arr[--q->end];
    q->sorted = 0;
}

PsInfo *PQueueFront(void *pqueue) {
    PQueue *q = pqueue;
    if(!q->sorted)
        qsort(q->arr, q->end, sizeof(PsInfo*), q->cmp);
    q->sorted = 1;
    return q->arr[0];
}

void FreePQueue(void *pqueue) {
    free(((PQueue*)pqueue)->arr);
    free(pqueue);
}

int PQueueCapacity(void *pqueue) {
    return ((PQueue*)pqueue)->cap;
}

int PQueueSize(void *pqueue) {
    return ((PQueue*)pqueue)->end;
}

int PQueueEmpty(void *pqueue) {
    return ((PQueue*)pqueue)->end == 0 ? 1 : 0;
}