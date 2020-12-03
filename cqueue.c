#include "cqueue.h"

Queue* create_queue(long init_capacity, long increments) {

    Queue* q = malloc(sizeof(Queue));
    q->head = 0;
    q->tail = 0;
    q->capacity = init_capacity;
    q->increments = increments;
    q->queue = malloc(sizeof(void*) * init_capacity);

}

void destroy_queue(Queue* q) {

    free(q->queue);
    free(q);
}

Queue* resize_queue(Queue* q) {

    long new_size = q->capacity + q->increments;
    q->queue = realloc(q->queue, sizeof(void*) * new_size);
    q->capacity = new_size;
    return q;

}

void enqueue(Queue* q, void* item) {

    if (q->tail == q->capacity) {
        q = resize_queue(q);
    }
    q->queue[q->tail] = item;
    q->tail++;

}

void* dequeue(Queue* q) {

    if (q->head > q->tail) {
        return NULL;
    }
    void* tmp;
    tmp = q->queue[q->head];
    q->head++;
    return tmp;

}

