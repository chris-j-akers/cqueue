#include <stdlib.h>

struct QDCQueue {
    long head;
    long tail;
    long capacity;
    long grow_by;
    void ** queue;
};
typedef struct QDCQueue QDCQueue;

QDCQueue* create_queue(long initial_capacity, long grow_by);
void destroy_queue(QDCQueue* q);

QDCQueue* grow_queue(QDCQueue* q);
QDCQueue* shrink_queue(QDCQueue* src);

void enqueue(QDCQueue* q, void* item);
void* dequeue(QDCQueue* q);