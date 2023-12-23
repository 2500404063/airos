#include "airos_context.h"

/*
This is used to record the values in context.
usage:
airos_context_t background;
void task(){
    airos_context_t ctx;
    airos_context_init(&ctx);
    airos_context_add(&ctx, &background)
    while(1){
        airos_context_t *ctx2 = airos_context_get_begin(&background, 0);
        ctx2.val
        airos_context_get_end(ctx2);
    }
}
*/

#define SCHEDULE_PLACE() airos_task_schedule()

void airos_context_init(airos_context_t *ctx)
{
    ctx->nxt_ctx = ctx;
    ctx->pre_ctx = ctx;
    ctx->key = 0;
    ctx->ready = 0;
}

void airos_context_add(airos_context_t *ctx, airos_context_t *parent)
{
    airos_context_t *parent_next_node = parent->nxt_ctx;
    parent->nxt_ctx = ctx;
    ctx->pre_ctx = parent;
    if (parent_next_node != parent)
    {
        ctx->nxt_ctx = parent_next_node;
        parent_next_node->pre_ctx = ctx;
    }
}

void airos_context_set(airos_context_t *ctx, unsigned long key, void *val)
{
    while (ctx->ready == 1)
    {
        SCHEDULE_PLACE();
    }
    ctx->key = key;
    ctx->val = val;
    ctx->ready = 1;
}

airos_context_t *airos_context_get_begin(airos_context_t *ctx, unsigned long key)
{
    // get to head
    while (ctx->pre_ctx != ctx)
    {
        ctx = ctx->pre_ctx;
    }
    while (ctx->nxt_ctx != ctx)
    {
        if (ctx->key == key)
        {
            while (ctx->ready == 0)
            {
                /* code */
            }
            return ctx;
        }
    }
}

void airos_context_get_end(airos_context_t *ctx)
{
    ctx->ready = 0;
}