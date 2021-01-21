#include <stdlib.h>

struct QDCQueue {
    long head;
    long tail;
    long capacity;
    long increments;
    void ** queue;
};
typedef struct QDCQueue QDCQueue;

QDCQueue* create_queue(long init_capacity, long increments);
QDCQueue* shrink_queue(QDCQueue* src);
void destroy_queue(QDCQueue* q);
QDCQueue* resize_queue(QDCQueue* q);
void enqueue(QDCQueue* q, void* item);
void* dequeue(QDCQueue* q);