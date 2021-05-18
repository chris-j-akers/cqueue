#include "qdcqueue.h"

QDCQueue* create_queue(const long initial_capacity, const long grow_by) {

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

// Shrink queue simply copies all existing elements into a new queue that has
// been allocated with exactly the right amount of items. Note that all
// operations to create the new queue and copy the items in are QDCQueue's own
// operations.

QDCQueue* shrink_queue(QDCQueue* src) {

    long new_capacity = src->tail - src->head;
    QDCQueue* dest = create_queue(new_capacity, src->grow_by);

    for (int i=src->head; i<src->tail; i++) {
        enqueue(dest, dequeue(src));
    }

    destroy_queue(src);
    return dest;
}

// grow_queue() uses realloc() to add space to the queue. The internal
// implementation of realloc() means there is no guarantee how the operation to
// add more space is performed. It could be added to the end of the current
// pointer chain, or, if there's no room,  new space will have to be allocated
// elsewhere and the existing items copied in.

QDCQueue* grow_queue(QDCQueue* q) {

    long new_capacity = q->capacity + q->grow_by;
    q->queue = realloc(q->queue, sizeof(void*) * new_capacity);
    q->capacity = new_capacity;

    return q;

}

// enqueue() first checks to see if the queue is already at capacity. If it is,
// it calls grow_queue() to expand the available space.

void enqueue(QDCQueue* q, void* item) {

    if (q->tail == q->capacity) {
        q = grow_queue(q);
    }
    
    q->queue[q->tail] = item;
    q->tail++;

}

// dequeue() obviously needs to check there are items in the queue first. It
// returns NULL if not.
//
// Note that dequeue doesn't free any memory, it merely increases the head of
// the queue to the next item. To free memory, shrink_queue must be called.

void* dequeue(QDCQueue* q) {

    if (q->head - q->tail == 0) {
        return NULL;
    }
    
    void* tmp;
    tmp = q->queue[q->head];
    q->head++;
    return tmp;

}

// A peek() operation is usually useful for these types of data structures. To
// what's coming next without actually deqeueing the item.

void* peek(const QDCQueue* q) {

    if (q->head > q->tail) {
        return NULL;
    }

    return q->queue[q->head];
}

