/* includes heap.h */
#include "huffman.h"
/* free */
#include <stdlib.h>


/**
 * symbolCompare - TBD
 *
 * @p1: TBD
 * @p2: TBD
 * Return: Positive if frequency 1 is greater, 0 if same values, or negative if
 *   frequency 2 is greater
 */
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


/**
 * nestedSymbolCompare - TBD
 *
 * @p1: TBD
 * @p2: TBD
 * Return: Positive if frequency 1 is greater, 0 if same values, or negative if
 *   frequency 2 is greater
 */
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


/**
 * freeSymbol - meant to be used as free_data parameter to binaryTreeDelete or
 *   heap_delete; frees memory allocated for a symbol_t struct
 *
 * @p: void pointer intended to be cast into symbol_t pointer
 */
void freeSymbol(void *p)
{
	free((symbol_t *)p);
}


/**
 * huffman_priority_queue - Creates a priority queue for use in building a
 *   Huffman Tree.
 *
 *   Each node in the returned heap contains as its `data` a pointer to the
 *     corresponding position in the Huffman Tree, a second Min Binary Heap
 *     which at first mirrors the queue tree structure. As values are
 *     extracted, summed and reinserted into the Huffman Tree, this priority
 *     queue will serve to keep track of how many operations remain in to
 *     reach the final form of the Huffman Tree.
 *
 * @data: array of characters to store in Huffman tree
 * @freq: frequency of appearance of character at each corresponding index
 *   in `data`
 * @size: amount of members in both `data` and `freq`
 * Return: heap_t containing priority queue that refers to an unsummed Huffman
 *   Tree, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *ht_root = NULL, *ht_node = NULL, *pq_node = NULL;
	heap_t *priority_queue = NULL;
	symbol_t *symbol = NULL;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = heap_create(nestedSymbolCompare);
	if (!priority_queue)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		/* Huffman tree is without heap_t wrapper at this stage */
		ht_node = heapInsert(&ht_root, symbolCompare, symbol);
		/* priority_queue has heap_t wrapper */
		pq_node = heap_insert(priority_queue, ht_node);

		if (!symbol || !ht_node || !pq_node)
		{
			binaryTreeDelete(ht_root, freeSymbol);
			heap_delete(priority_queue, NULL);
			return (NULL);
		}

		priority_queue->size++;
	}

	return (priority_queue);
}
