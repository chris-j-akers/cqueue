#include <stdlib.h>

struct QDCQueue {

    // Points to the next item to be dequeued

    long head;

    // Points to the next slot available for an item to be enqueued.

    long tail;

    // The number of items that fit into the queue. When a queue is first
    // created, this is specified by the user. If the queue autogrows, this will
    // be automatically updated.

    long capacity;

    // The QDCQueue will autogrow if it runs out of space. The users sets how
    // much the queue shold grow by (how many items) when it does.

    long grow_by;

    // The actual queue data. A chain of void pointers.

    void ** queue;
};
typedef struct QDCQueue QDCQueue;

// Initialise and destroy operations

QDCQueue* create_queue(const long initial_capacity, const long grow_by);
void destroy_queue(QDCQueue* q);

// Housekeeping operations

QDCQueue* grow_queue(QDCQueue* q);
QDCQueue* shrink_queue(QDCQueue* src);

// Operations

void enqueue(QDCQueue* q, void* item);
void* dequeue(QDCQueue* q);
void* peek(const QDCQueue* q);