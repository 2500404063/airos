#ifndef AIROS_QUEUE_H_
#define AIROS_QUEUE_H_

typedef struct _airos_queue_node_t
{
	void *value;
	struct _airos_queue_node_t *preNode;
	struct _airos_queue_node_t *nextNode;
} airos_queue_node_t;

void airos_queue_node_init(airos_queue_node_t *node, void *val);

void airos_queue_add_next(airos_queue_node_t *parent_node, airos_queue_node_t *node);

void airos_queue_add_pre(airos_queue_node_t *parent_node, airos_queue_node_t *node);

void airos_queue_add_line_tail(airos_queue_node_t *parent_node, airos_queue_node_t *node);

void airos_queue_add_line_head(airos_queue_node_t *parent_node, airos_queue_node_t *node);

void airos_queue_add_round_tail(airos_queue_node_t *parent_node, airos_queue_node_t *node);

void airos_queue_remove_node(airos_queue_node_t *node);

void airos_queue_remove_line_tail(airos_queue_node_t *node);

void airos_queue_remove_line_head(airos_queue_node_t *node);

void airos_queue_remove_line_all(airos_queue_node_t *node);

void airos_queue_convert_to_line(airos_queue_node_t *head_node);

void airos_queue_convert_to_round(airos_queue_node_t *node);

airos_queue_node_t *airos_queue_at(airos_queue_node_t *head_node, unsigned long pos);

#endif
