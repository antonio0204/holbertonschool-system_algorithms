#include "graphs.h"

/* fprintf */
#include <stdio.h>
/* memset */
#include <string.h>
/* malloc free */
#include <stdlib.h>
/* bool true false */
#include <stdbool.h>



static int inQueue(BFS_queue_t *queue, vertex_t *v)
{
	BFS_queue_t *temp;

	if (!queue || !v)
		return (0);

	temp = queue;
	while (temp)
	{
		if (temp->v == v)
			return (1);
		temp = temp->next;
	}

	return (0);
}



static void testPrintQueue(BFS_queue_t *queue)
{
	BFS_queue_t *temp;

	temp = queue;
	while (temp && temp->v)
	{
		printf("\t\t\t\tin queue: %s[%lu] depth:%lu\n",
		       temp->v->content, temp->v->index, temp->depth);
		temp = temp->next;
	}
}


static void removeFromQueue(BFS_queue_t **queue)
{
	BFS_queue_t *temp;

	if (!queue || !(*queue))
		return;

	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
}


static BFS_queue_t *addToQueue(BFS_queue_t **queue, size_t depth, vertex_t *next_v)
{
	BFS_queue_t *next_in_q = NULL, *temp;

	if (!queue || !next_v)
		return (NULL);

        next_in_q = malloc(sizeof(BFS_queue_t));
	if (!next_in_q)
		return (NULL);
	next_in_q->v = next_v;
	next_in_q->depth = depth;
        next_in_q->next = NULL;

	if (!(*queue))
		*queue = next_in_q;
	else
	{
		temp = *queue;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = next_in_q;
	}

	return (next_in_q);
}


/**
 * BFS_recursion - recursive helper to breadth_first_traverse; recursively
 *   traverses a graph using the breadth-first algorithm to return its maximum
 *   depth
 *
 * @curr: pointer to the current vertex (starting vertex is abitrary, but
 *   depth_first_traverse expects to start with first vertex in adjacency list)
 * @visited: array of bytes indicating traversal history: if byte at a given
 *   index is non-zero, then the vertex at the same index in the adjacency list
 *   has already been visited
 * @curr_depth: depth of current vertex from the starting node
 * @action: pointer to a function to be called for each visited vertex, takes
 *   the parameters:
 *      v: const pointer to the visited vertex
 *      depth: depth of v, from the starting vertex
 * Return: largest vertex depth, or `curr_depth` on failure
 */
static int BFS_visit(BFS_queue_t **queue, unsigned char *visited,
	      void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *temp_e = NULL;
	vertex_t *curr_v = NULL;
	size_t curr_depth;

	if (!queue || !(*queue) || !(*queue)->v || !visited || !action)
	{
		fprintf(stderr, "BFS_visit: invalid parameters\n");
		return (1);
	}

	curr_v = (*queue)->v;
	curr_depth = (*queue)->depth;

	visited[curr_v->index] = 1;
	action(curr_v, curr_depth);

	removeFromQueue(queue);

	temp_e = curr_v->edges;
	while (temp_e)
	{
		if (!visited[temp_e->dest->index] &&
		    !inQueue(*queue, temp_e->dest))
		{
			if (!addToQueue(queue, curr_depth + 1, temp_e->dest))
				return (1);
		}

		temp_e = temp_e->next;
	}

	testPrintQueue(*queue);

	return (0);
}



/**
 * breadth_first_traverse - walks through a graph using the breadth-first
 *   algorithm
 *
 * @graph: pointer to the graph to traverse. (Traversal must start from the
 *   first vertex in the vertices list.)
 * @action: pointer to a function to be called for each visited vertex, takes
 *   the parameters:
 *      v: const pointer to the visited vertex
 *      depth: depth of v, from the starting vertex
 * Return: biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	unsigned char *visited = NULL;
	BFS_queue_t *queue = NULL;
	size_t depth = 0;

	if (!graph || !action)
	{
		fprintf(stderr, "breadth_first_traverse: invalid parameters\n");
		return (0);
	}

	visited = malloc(sizeof(unsigned char) * graph->nb_vertices);
	if (!visited)
		return (0);
	memset(visited, 0, graph->nb_vertices);

	/* start queue with first vertex in adjacency list */
	addToQueue(&queue, 0, graph->vertices);
	if (!queue)
	{
		fprintf(stderr, "breadth_first_traverse: addToQueue failure\n");
		free(visited);
		return (0);
	}

	while (queue)
	{
	        depth = queue->depth;

		if (BFS_visit(&queue, visited, action) == 1)
		{
			fprintf(stderr, "breadth_first_traverse: BFS_visit failure\n");
			free(visited);
			while (queue)
				removeFromQueue(&queue);
			return (0);
		}

	}

	free(visited);
	return (depth);
}
