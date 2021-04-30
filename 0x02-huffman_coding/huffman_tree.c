/* includes heap.h */
#include "huffman.h"


/**
 * huffman_tree - TBD
 *
 *
 * Sums values in a Huffman tree represented by a
 *   priority queue.
 *
 *     At the outset, the queue should be a Min Binary Heap containing as data
 *   at each node a second untethered node which itself contains symbol data.
 *   The priority queue should be sorted by the frequencies in these nested
 *   node symbols.
 *
 *     Two nodes are extracted from the queue, and then one is inserted. The
 *   new queue node contains a new nested node, with a frequency value the sum
 *   of the two extraced nodes' frequencies. The two extracted nodes are then
 *   linked to the new nested as its children. By iterating this process a
 *   Huffman tree is constructed among the nested nodes.
 *
 * @data: TBD
 * @freq: TBD
 * @size: TBD
 * Return: TBD
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *huff_pq = NULL;
	binary_tree_node_t *huff_tree = NULL;

	if (!data || !freq || size == 0)
		return (NULL);

	huff_pq = huffman_priority_queue(data, freq, size);
	if (!huff_pq)
		return (NULL);

	/* extraction/summing/insertion cycles in queue until one node left */
	while (huff_pq->root &&
	       (huff_pq->root->left || huff_pq->root->right))
	{
		if (huffman_extract_and_insert(huff_pq) == 1)
		{
			heap_delete(huff_pq, freeNestedNode);
			return (NULL);
		}
	}

	huff_tree = (binary_tree_node_t *)(huff_pq->root->data);
	heap_delete(huff_pq, NULL);

	return (huff_tree);
}
