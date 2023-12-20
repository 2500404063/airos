#include "airos_queue.h"

void airos_queue_node_init(airos_queue_node_t *node, void *val)
{
	node->nextNode = node;
	node->preNode = node;
	node->value = val;
}

void airos_queue_add_next(airos_queue_node_t *parent_node, airos_queue_node_t *node)
{
	airos_queue_node_t *parent_node_next = parent_node->nextNode;
	parent_node->nextNode = node;
	node->preNode = parent_node;
	if (parent_node_next != parent_node)
	{
		node->nextNode = parent_node_next;
		parent_node_next->preNode = node;
	}
}

void airos_queue_add_pre(airos_queue_node_t *parent_node, airos_queue_node_t *node)
{
	airos_queue_node_t *parent_node_pre = parent_node->preNode;
	parent_node->preNode = node;
	node->nextNode = parent_node;
	if (parent_node_pre != parent_node)
	{
		node->preNode = parent_node_pre;
		parent_node_pre->nextNode = node;
	}
}

void airos_queue_add_line_tail(airos_queue_node_t *parent_node, airos_queue_node_t *node)
{
	while (parent_node->nextNode != parent_node)
	{
		parent_node = parent_node->nextNode;
	}
	airos_queue_add_next(parent_node, node);
}

void airos_queue_add_line_head(airos_queue_node_t *parent_node, airos_queue_node_t *node)
{
	while (parent_node->preNode != parent_node)
	{
		parent_node = parent_node->preNode;
	}
	airos_queue_add_pre(parent_node, node);
}

void airos_queue_add_round_tail(airos_queue_node_t *parent_node, airos_queue_node_t *node)
{
	airos_queue_node_t *parent_node_pre = parent_node->preNode;
	parent_node->preNode = node;
	node->nextNode = parent_node;
	node->preNode = parent_node_pre;
	parent_node_pre->nextNode = node;
}

void airos_queue_remove_node(airos_queue_node_t *node)
{
	if (node->nextNode == node)
	{
		node->preNode->nextNode = node->preNode;
		node->preNode = node;
	}
	else if (node->preNode == node)
	{
		node->nextNode->preNode = node->nextNode;
		node->nextNode = node;
	}
	else
	{
		node->preNode->nextNode = node->nextNode;
		node->nextNode->preNode = node->preNode;
		node->preNode = node;
		node->nextNode = node;
	}
}

void airos_queue_remove_line_tail(airos_queue_node_t *node)
{
	while (node->nextNode != node)
	{
		node = node->nextNode;
	}
	node->preNode->nextNode = node->preNode;
	node->preNode = node;
}

void airos_queue_remove_line_head(airos_queue_node_t *node)
{
	while (node->preNode != node)
	{
		node = node->preNode;
	}
	node->nextNode->preNode = node->nextNode;
	node->nextNode = node;
}

void airos_queue_remove_line_all(airos_queue_node_t *node)
{
	while (node->preNode != node)
	{
		node = node->preNode;
	}
	while (node->nextNode != node)
	{
		airos_queue_node_t *nextNode = node->nextNode;
		nextNode->preNode = nextNode;
		node->nextNode = node;
		node = nextNode;
	}
}

void airos_queue_convert_to_line(airos_queue_node_t *head_node)
{
	head_node->preNode->nextNode = head_node->preNode;
	head_node->preNode = head_node;
}

void airos_queue_convert_to_round(airos_queue_node_t *node)
{
	airos_queue_node_t *head_node = node;
	airos_queue_node_t *tail_node = node;
	while (head_node->preNode != head_node)
	{
		head_node = head_node->preNode;
	}
	while (tail_node->nextNode != tail_node)
	{
		tail_node = tail_node->nextNode;
	}
	head_node->preNode = tail_node;
	tail_node->nextNode = head_node;
}

airos_queue_node_t *airos_queue_at(airos_queue_node_t *head_node, unsigned long pos)
{
	for (int i = 0; i < pos; ++i)
	{
		head_node = head_node->nextNode;
	}
	return head_node;
}
