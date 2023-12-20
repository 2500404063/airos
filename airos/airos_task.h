#ifndef AIROS_TASK_H_

#include "airos_config.h"
#include "airos_queue.h"

#define AIROS_TASK_READY (0)
#define AIROS_TASK_SUSPEND (1)
#define AIROS_TASK_SLEEP (2)

#define AIROS_TASK_NOFPU (0)
#define AIROS_TASK_FPU (1)

typedef void (*task_func_t)(void);
typedef void* addr_t;

typedef struct _airos_task_t
{
    addr_t *sp;             // stack pointer(must be the first)
    task_func_t entry;      // task function entry pointer
    unsigned char id;       // task id
    unsigned char status;   // task status
    unsigned char priority; // task priority
    unsigned char sleep;    // sleep count
} airos_task_t;

void airos_task_init();
void airos_task_create(airos_task_t *task,
					   airos_queue_node_t *task_node,
					   addr_t *stack,
					   task_func_t entry,
					   unsigned char id,
					   unsigned char priority);

void airos_task_sleep(airos_queue_node_t *task_node, unsigned long tick_delay);
void airos_task_suspend(airos_queue_node_t *task_node);
void airos_task_resume(airos_queue_node_t *task_node);
void airos_task_enable_schedule();
void airos_task_disable_schedule();
void airos_task_schedule();

#endif
