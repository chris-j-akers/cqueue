#include <stdlib.h>

struct QDCQueue {
    long head;
    long tail;
    long capacity;
    long grow_by;
    void ** queue;
};
typedef struct QDCQueue QDCQueue;

/* Intialise & Destroy */

QDCQueue* create_queue(const long initial_capacity, const long grow_by);
void destroy_queue(QDCQueue* q);

/* Housekeeping */

QDCQueue* grow_queue(QDCQueue* q);
QDCQueue* shrink_queue(QDCQueue* src);

/* Operations */

void enqueue(QDCQueue* q, void* item);
void* dequeue(QDCQueue* q);
void* peek(const QDCQueue* q);