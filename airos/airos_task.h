#ifndef AIROS_TASK_H_
#define AIROS_TASK_H_

#include "airos_config.h"
#include "airos_queue.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define AIROS_TASK_READY (0)
#define AIROS_TASK_SUSPEND (1)
#define AIROS_TASK_SLEEP (2)
#define AIROS_TASK_MUTED (3)

#define AIROS_TASK_NOFPU (0)
#define AIROS_TASK_FPU (1)

    typedef void (*task_func_t)(void);
    typedef void *addr_t;

    typedef struct _airos_task_t
    {
        addr_t *sp; // stack pointer(must be the first)
        addr_t *_sp;
        task_func_t entry;      // task function entry pointer
        unsigned char status;   // task status
        unsigned char priority; // task priority
        unsigned short sleep;   // sleep count
    } airos_task_t;

   extern airos_queue_node_t task_queue_ready[AIROS_PRIORITY_MAX];
   extern airos_queue_node_t task_queue_suspend;
   extern airos_queue_node_t task_queue_sleep;

   extern airos_task_t *cur_task;
   extern airos_task_t *pre_task;
   extern airos_queue_node_t *cur_task_node;
   extern airos_queue_node_t *pre_task_node;

    void airos_task_init();
    void airos_task_create(airos_queue_node_t *task_node, task_func_t entry, unsigned long stack_size, unsigned char priority);
    void airos_task_destory(airos_queue_node_t *task_node);
    void airos_task_sleep(airos_queue_node_t *task_node, unsigned long tick_delay);
    void airos_task_suspend(airos_queue_node_t *task_node);
    void airos_task_resume(airos_queue_node_t *task_node);
    void airos_task_enable_schedule();
    void airos_task_disable_schedule();
    void airos_task_schedule();

#ifdef __cplusplus
}
#endif

#endif
