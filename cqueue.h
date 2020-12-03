#include <stdlib.h>

struct Queue {
    long head;
    long tail;
    long capacity;
    long increments;
    void ** queue;
};
typedef struct Queue Queue;

Queue* create_queue(long init_capacity, long increments);
void destroy_queue(Queue* q);
Queue* resize_queue(Queue* q);
void enqueue(Queue* q, void* item);
void* dequeue(Queue* q);