#include "qdcqueue.h"

QDCQueue* create_queue(long initial_capacity, long grow_by) {

    QDCQueue* q = malloc(sizeof(QDCQueue));
    
    q->head = 0;
    q->tail = 0;
    q->capacity = initial_capacity;
    q->grow_by = grow_by;
    q->queue = malloc(sizeof(void*) * initial_capacity);

    return q;

}

void destroy_queue(QDCQueue* q) {

    free(q->queue);
    free(q);
}

QDCQueue* shrink_queue(QDCQueue* src) {

    long new_capacity = src->tail - src->head;
    QDCQueue* dest = create_queue(new_capacity, src->grow_by);

    for (int i=src->head; i<src->tail; i++) {
        enqueue(dest, dequeue(src));
    }

    destroy_queue(src);
    return dest;
}

QDCQueue* grow_queue(QDCQueue* q) {

    long new_capacity = q->capacity + q->grow_by;
    q->queue = realloc(q->queue, sizeof(void*) * new_capacity);
    q->capacity = new_capacity;

    return q;

}

void enqueue(QDCQueue* q, void* item) {

    if (q->tail == q->capacity) {
        q = grow_queue(q);
    }
    
    q->queue[q->tail] = item;
    q->tail++;

}

void* dequeue(QDCQueue* q) {

    if (q->head > q->tail) {
        return NULL;
    }
    
    void* tmp;
    tmp = q->queue[q->head];
    q->head++;
    return tmp;

}

