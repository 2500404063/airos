#include "airos_mutex.h"

void airos_mutex_init(airos_mutex_t *m)
{
    m->lock = 0;
    airos_queue_node_init(&m->task_nodes, 0);
}

void airos_mutex_lock(airos_mutex_t *m)
{
    if (m->lock == 0)
    {
        m->lock = 1;
    }
    else
    {
        cur_task->status = AIROS_TASK_MUTED;
        airos_queue_remove_node(cur_task_node);
        airos_queue_add_next(&m->task_nodes, cur_task_node);
        airos_task_schedule();
    }
}

void airos_mutex_unlock(airos_mutex_t *m)
{
    if (m->lock == 0)
        return;
    m->lock = 0;
    airos_queue_node_t *task_node = &m->task_nodes;
    while (task_node->nextNode != task_node)
    {
        task_node = task_node->nextNode;
        airos_task_resume(task_node);
    }
}