#include "airos_task.h"

airos_queue_node_t task_queue_ready[PRIORITY_MAX];
airos_queue_node_t task_queue_suspend;
airos_queue_node_t task_queue_sleep;

airos_task_t *cur_task;
airos_task_t *pre_task;
airos_queue_node_t *cur_task_node;
airos_queue_node_t *pre_task_node;

static int schedule_enable = 0;

inline static void airos_task_cpu_setup()
{
    // Set SystemTick and PendSV priority
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
    SysTick_Config(84000000 / 100);
}

inline static void airos_disable_irq()
{
    __disable_irq();
}

inline static void airos_enable_irq()
{
    __enable_irq();
}

inline static void airos_trigger_pendsv()
{
    SCB->ICSR |= 1 << 28;
}

inline void airos_task_enable_schedule()
{
    schedule_enable = 1;
}

inline void airos_task_disable_schedule()
{
    schedule_enable = 0;
}

void airos_task_init()
{
    for (unsigned char i = 0; i < PRIORITY_MAX; i++)
    {
        airos_queue_node_init(task_queue_ready + i, 0);
    }
    airos_queue_node_init(&task_queue_suspend, 0);
    pre_task = 0;
    pre_task_node = 0;
    cur_task = 0;
    cur_task_node = 0;
    airos_task_cpu_setup();
}

void airos_task_create(airos_queue_node_t *task_node, unsigned char id, task_func_t entry, unsigned long stack_size, unsigned char priority)
{
    // allocate
    airos_task_t *task = (airos_task_t *)malloc(sizeof(airos_task_t));
    addr_t *stack = (addr_t *)malloc(sizeof(addr_t) * stack_size);

    // init structure
    airos_queue_node_init(task_node, task);
    task->entry = entry;
    task->id = id;
    task->_sp = stack;
    task->status = AIROS_TASK_READY;
    task->priority = priority;
    // init stack
    stack = stack + sizeof(addr_t) * stack_size;
    *(--stack) = (void *)0x01000000; // XPSR
    *(--stack) = (void *)entry;      // r15(pc)
    *(--stack) = (void *)0x14;       // R14(LR)
    *(--stack) = (void *)0x12;       // R12
    *(--stack) = (void *)0x03;       // R3
    *(--stack) = (void *)0x02;       // R2
    *(--stack) = (void *)0x01;       // R1
    *(--stack) = (void *)0x0;        // R0
    // user regs
    *(--stack) = (void *)0x11; // R11
    *(--stack) = (void *)0x10; // R10
    *(--stack) = (void *)0x09; // R9
    *(--stack) = (void *)0x08; // R8
    *(--stack) = (void *)0x07; // R7
    *(--stack) = (void *)0x06; // R6
    *(--stack) = (void *)0x05; // R5
    *(--stack) = (void *)0x04; // R4
    // fpu regs
    for (int i = 0; i < 32; i++)
    {
        *(--stack) = (void *)0x00; // S0-S31
    }
    task->sp = stack;
    airos_queue_node_t *node = task_queue_ready + priority;
    if (node->value == 0)
        node->value = task_node;
    else
        airos_queue_add_round_tail(node->value, task_node);
}

void airos_task_destory(airos_queue_node_t *task_node)
{
    if (task_node == cur_task_node)
    {
        return;
    }
    airos_queue_remove_node(task_node);
    airos_task_t *task = (airos_task_t *)task_node->value;
    free(task->_sp);
    free(task);
}

void airos_task_sleep(airos_queue_node_t *task_node, unsigned long tick_delay)
{
    if (task_node == 0)
        task_node = cur_task_node;
    airos_task_t *task = (airos_task_t *)task_node->value;
    task->sleep = tick_delay;
    task->status = AIROS_TASK_SLEEP;
    airos_queue_remove_node(task_node);
    airos_queue_add_next(&task_queue_sleep, task_node);
    airos_task_schedule();
}

void airos_task_suspend(airos_queue_node_t *task_node)
{
    airos_disable_irq();
    if (task_node == 0)
        task_node = cur_task_node;
    airos_task_t *task = (airos_task_t *)task_node->value;
    task->status = AIROS_TASK_SUSPEND;
    airos_queue_remove_node(task_node);
    airos_queue_add_next(&task_queue_suspend, task_node);
    airos_task_schedule();
}

void airos_task_resume(airos_queue_node_t *task_node)
{
    airos_disable_irq();
    if (task_node == 0)
        task_node = cur_task_node;
    airos_task_t *task = (airos_task_t *)task_node->value;
    // recover
    task->status = AIROS_TASK_READY;
    airos_queue_remove_node(task_node);
    airos_queue_node_t *node = task_queue_ready + task->priority;
    if (node->value == 0)
        node->value = task_node;
    else
        airos_queue_add_round_tail(node, task_node);
    airos_enable_irq();
}

void airos_task_schedule()
{
    int flag_task_changed = 0;
    airos_queue_node_t *task_node;
    airos_disable_irq();
    if (schedule_enable == 0)
        return;
    // schedule by priority, the lower priority the higher level;
    for (int i = 0; i < PRIORITY_MAX; i++)
    {
        airos_queue_node_t *task_node_priority = task_queue_ready + i;
        if (task_node_priority->value == 0)
        {
            continue;
        }
        else if (cur_task == 0)
        {
            pre_task_node = cur_task_node;
            pre_task = cur_task;
            cur_task_node = (airos_queue_node_t *)task_node_priority->value;
            cur_task = (airos_task_t *)cur_task_node->value;
            flag_task_changed = 1;
            break;
        }
        else if (cur_task->priority == i)
        {
            // the same priority(TODO: the same task)
            pre_task_node = cur_task_node;
            pre_task = cur_task;
            cur_task_node = cur_task_node->nextNode;
            cur_task = (airos_task_t *)cur_task_node->value;
            flag_task_changed = 1;
            break;
        }
        else
        {
            pre_task_node = cur_task_node;
            pre_task = cur_task;
            cur_task_node = (airos_queue_node_t *)task_node_priority->value;
            cur_task = (airos_task_t *)cur_task_node->value;
            flag_task_changed = 1;
            break;
        }
    }
    // Slept tasks
    // Skip the head because its value is empty.
    task_node = &task_queue_sleep;
    while (task_node->nextNode != task_node)
    {
        task_node = task_node->nextNode;
        airos_task_t *task = (airos_task_t *)task_node->value;
        if (--task->sleep == 0)
        {
            // recover
            task->status = AIROS_TASK_READY;
            airos_queue_remove_node(task_node);
            airos_queue_node_t *node = task_queue_ready + task->priority;
            if (node->value == 0)
                node->value = task_node;
            else
                airos_queue_add_round_tail(node, task_node);
        }
    }
    if (flag_task_changed == 1)
    {
        airos_trigger_pendsv();
    }
    airos_enable_irq();
}

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