#ifndef AIROS_MUTEX_H_
#define AIROS_MUTEX_H_

#include "airos_task.h"

typedef struct _airos_mutex_t
{
    int lock;
    airos_queue_node_t task_nodes;
} airos_mutex_t;

void airos_mutex_init(airos_mutex_t *m);    
void airos_mutex_lock(airos_mutex_t *m);
void airos_mutex_unlock(airos_mutex_t *m);

#endif