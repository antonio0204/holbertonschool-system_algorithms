/* includes heap.h */
#include "huffman.h"
/* free */
#include <stdlib.h>

#include <stdio.h>

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));

int symbolCompare(void *p1, void *p2)
{
	symbol_t *sym1, *sym2;
	size_t freq1, freq2;

	sym1 = (symbol_t *)p1;
	sym2 = (symbol_t *)p2;

	freq1 = sym1 ? sym1->freq : 0;
	freq2 = sym2 ? sym2->freq : 0;

	return (freq1 - freq2);
}

int nestedSymbolCompare(void *p1, void *p2)
{
        binary_tree_node_t *node1, *node2;
	symbol_t *sym1, *sym2;
	size_t freq1, freq2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;

	sym1 = node1 ? (symbol_t *)(node1->data) : NULL;
	sym2 = node2 ? (symbol_t *)(node2->data) : NULL;

	freq1 = sym1 ? sym1->freq : 0;
	freq2 = sym2 ? sym2->freq : 0;

	return (freq1 - freq2);
}


void freeSymbol(void *p)
{
	free((symbol_t *)p);
}

/**
 * nested_print - Prints a symbol structure stored in a nested node
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: Number of bytes written in buffer
 */
int char_freq_print(char *buffer, void *data)
{
    symbol_t *symbol;
    int length;

    symbol = (symbol_t *)data;
    length = sprintf(buffer, "(%c/%lu)", symbol->data, symbol->freq);
    return (length);
}



/**
 * huffman_priority_queue - creates a priority queue (Min Binary Heap of ASCII
 *   characters sorted by frequency of appearance) for the Huffman coding
 *   algorithm
 *
 * @data:
 * @freq:
 * @size:
 * Return:
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = NULL;
	binary_tree_node_t *huffman_tree = NULL,
		*ht_node = NULL, *pq_node = NULL/*, *bt1 = NULL*/;
	symbol_t *symbol = NULL/*, *s1 = NULL*/;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

        priority_queue = heap_create(nestedSymbolCompare);
	if (!priority_queue)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		/* huffman_tree is without heap_t wrapper at this stage */
		ht_node = BTCompleteInsert(huffman_tree, symbol);
		ht_node = minHeapSiftUp(ht_node, symbolCompare);
		/* priority_queue has heap_t wrapper as usual */
		pq_node = heap_insert(priority_queue, ht_node);
/*
		printf("symbol @ %p data:%c freq:%lu\n",
		       (void *)symbol, symbol ? symbol->data : 0, symbol ? symbol->freq : 0);
		printf("ht_node @ %p ht_node->data @ %p ht_node->data->data:%c ht_node->data->freq:%lu\n",
		       (void *)ht_node,
		       ht_node ? (void *)(ht_node->data) : NULL,
		       (ht_node && ht_node->data) ? ((symbol_t *)(ht_node->data))->data : 0,
		       (ht_node && ht_node->data) ? ((symbol_t *)(ht_node->data))->freq : 0);

		printf("pq_node @ %p pq_node->data @ %p pq_node->data->data @%p\n",
		       (void *)pq_node,
		       pq_node ? (void *)(pq_node->data) : NULL,
		       (pq_node && pq_node->data) ? (void *)(((binary_tree_node_t *)(pq_node->data))->data) : NULL);

		if (pq_node && pq_node->data && ((binary_tree_node_t *)(pq_node->data))->data)
		{
			printf("pq_node->data->data->data:%c pq_node->data->data->freq:%lu\n",
			       ((symbol_t *)(((binary_tree_node_t *)(pq_node->data))->data))->data,
			       ((symbol_t *)(((binary_tree_node_t *)(pq_node->data))->data))->freq);
		}
*/
		if (!huffman_tree)
			huffman_tree = ht_node;

		if (!symbol || !ht_node || !pq_node)
		{
			BTDelete(huffman_tree, freeSymbol);
			heap_delete(priority_queue, NULL);
			return (NULL);
		}

		priority_queue->size++;
	}
/*
	binary_tree_print(huffman_tree, char_freq_print);
*/
	return (priority_queue);
}
