#ifndef AIROS_CONTEXT_H_
#define AIROS_CONTEXT_H_

#include "airos_queue.h"
#include "airos_task.h"

typedef struct _airos_context_t
{
    struct _airos_context_t *pre_ctx;
    struct _airos_context_t *nxt_ctx;
    unsigned short ready;
    unsigned short key;
    void *val;
} airos_context_t;

void airos_context_init(airos_context_t *ctx);
void airos_context_add(airos_context_t *ctx, airos_context_t *parent);
void airos_context_set(airos_context_t *ctx, unsigned long key, void *val);
airos_context_t *airos_context_get_begin(airos_context_t *ctx, unsigned long key);
void airos_context_get_end(airos_context_t *ctx);

#endif