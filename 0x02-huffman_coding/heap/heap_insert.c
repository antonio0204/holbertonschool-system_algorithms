#include "heap.h"
/* malloc free */
#include <stdlib.h>


/**
 * BTQueuePush - adds member to rear of a bt_node_queue_t SLL
 *
 * @queue: pointer to head of bt_node_queue_t queue
 * @node: pointer to a node in a binary tree
 * Return: pointer to new node in queue, or NULL on failure
 */
bt_node_queue_t *BTQueuePush(bt_node_queue_t **queue, binary_tree_node_t *node)
{
	bt_node_queue_t *temp, *new = NULL;

	if (!queue || !node)
		return (NULL);

	new = malloc(sizeof(bt_node_queue_t));
	if (!new)
		return (NULL);
	new->node = node;
	new->next = NULL;

	if (!*queue)
		*queue = new;
	else
	{
		temp = *queue;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = new;
	}

	return (new);
}


/**
 * BTQueueAdvance - deletes first member of a bt_node_queue_t SLL
 *
 * @queue: pointer to head of bt_node_queue_t queue
 */
void BTQueueAdvance(bt_node_queue_t **queue)
{
	bt_node_queue_t *temp;

	if (!queue || !*queue)
		return;

	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
}


/**
 * BTQueueClear - deletes all members of a bt_node_queue_t SLL
 *
 * @queue: pointer to head of bt_node_queue_t queue
 */
void BTQueueClear(bt_node_queue_t **queue)
{
	if (!queue)
		return;

	while (*queue)
		BTQueueAdvance(queue);
}


/**
 * binaryTreeCompleteInsert - uses queue to insert new leaves into a binary
 *   tree in level order, keeping tree complete
 *
 * @root: pointer to root node of heap to traverse
 * @data: pointer to value to store in the new node
 * Return: pointer to the new node, or NULL on failure
 */
binary_tree_node_t *binaryTreeCompleteInsert(binary_tree_node_t *root,
					     void *data)
{
	binary_tree_node_t *new = NULL;
	bt_node_queue_t *queue = NULL;

	if (!root)
		return (NULL);

	queue = BTQueuePush(&queue, root);
	if (!queue)
		return (NULL);

	while (queue)
	{
		if (queue->node->left && queue->node->right)
		{
			if (!BTQueuePush(&queue, queue->node->left) ||
			    !BTQueuePush(&queue, queue->node->right))
			{
				BTQueueClear(&queue);
				return (NULL);
			}

			BTQueueAdvance(&queue);
		}
		else
		{
			new = binary_tree_node(queue->node, data);
			if (!new)
				return (NULL);

			if (!queue->node->left)
				queue->node->left = new;
			else
				queue->node->right = new;

			BTQueueClear(&queue);
		}
	}

	return (new);
}


/**
 * heap_insert - inserts a value into a Min Binary Beap
 *
 * @heap: pointer to a binary heap profile
 * @data: pointer containing data to store in the inserted node
 * Return: pointer to the inserted node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new = NULL, *temp = NULL;
	void *swap;

	/* NULL heap must return error, as no data_cmp provided */
	if (!heap)
		return (NULL);

	/* no heap, start new tree */
	if (!(heap->root))
	{
		new = binary_tree_node(NULL, data);
		if (!new)
			return (NULL);
		heap->root = new;
		heap->size++;
		return (new);
	}

	/* find next available leaf position in level order */
	new = binaryTreeCompleteInsert(heap->root, data);
	if (!new)
		return (NULL);
	heap->size++;

	/* sort data towards root if *(temp->data) < *(temp->parent->data) */
	temp = new;
	while (temp && temp->parent && heap->data_cmp &&
	       heap->data_cmp(temp->data, temp->parent->data) < 0)
	{
		swap = temp->data;
		temp->data = temp->parent->data;
		temp->parent->data = swap;
		temp = temp->parent;
	}

	return (temp);
}
