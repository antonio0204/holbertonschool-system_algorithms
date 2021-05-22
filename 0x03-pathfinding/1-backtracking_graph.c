#include "pathfinding.h"


/**
  * backtracking_graph - searches for the first path from a starting point to
  *   a target point in a graph
  *
  * @graph: pointer to the graph to traverse
  * @start: pointer to starting vertex
  * @target: pointer to target vertex
  * Return: returns a queue in which each node is a `char *` corresponding to a
  *   vertex, forming a path from start to target, or NULL on failure
  */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	if (!graph || !start || !target)
		return (NULL);
}