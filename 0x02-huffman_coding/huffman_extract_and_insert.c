/* includes heap.h */
#include "huffman.h"
/* free */
#include <stdlib.h>


/**
 * huffman_extract_and_insert - Sums values in a Huffman tree represented by a
 *   priority queue.
 *
 *     At the outset, the queue should be a Min Binary Heap separate from the
 *   Huffman tree, but matching its structure 1:1 and containing as its data a
 *   pointer to the node at each corresponding location in the Huffman tree.

 *     Two nodes are extracted from the Huffman tree, and then become the
 *   children of a newly inserted node containing the sum of their values. The
 *   nodes in the queue representing the two extracted nodes in the tree are
 *   also extracted from the queue, but the node inserted into the queue
 *   representing the sum node in the tree has no children in the queue. Thus
 *   for every successful return of this function the Huffman tree grows by 1
 *   node and the priority queue shrinks by 1 node.
 *
 * @priority_queue: pointer to Min Binary Heap which acts as a priority queue
 *   by representing each node of a second Min Binary Heap
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *H_tree = NULL;
        void *extract1 = NULL, *extract2 = NULL;
	size_t freq_sum;

	if (!priority_queue || !priority_queue->data_cmp ||
	    !priority_queue->root || !priority_queue->root->data)
		return (1);

	H_tree = priority_queue->root->data;

	

	return (0);
}
