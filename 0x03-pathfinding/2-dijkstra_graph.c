#include "pathfinding.h"
/* malloc free qsort */
#include <stdlib.h>
/* printf */
#include <stdio.h>
/* strcmp strdup */
#include <string.h>

/* ULONG_MAX */
#include <limits.h>


typedef struct dijkstra_vertex_s {
	vertex_t *vertex;
	size_t cml_weight;
	vertex_t *path_via;
} dijkstra_vertex_t;




int isVertexFinished(const dijkstra_vertex_t *D_queue, size_t Dq_head_i, const vertex_t *vertex)
{
	size_t i;

	if (!D_queue || !vertex)
		return (0);

	for (i = 0; i < Dq_head_i; i++)
	{
		if (strcmp(vertex->content, D_queue[i].vertex->content) == 0)
			return (1);
	}

	return (0);
}


int compareWeights(const void *param1, const void *param2)
{
	dijkstra_vertex_t *D_vert1 = NULL, *D_vert2 = NULL;

	if (!param1 && !param2)
		return (0);
	if (param1 && !param2)
		return (1);
	if (!param1 && param2)
		return (-1);

	D_vert1 = (dijkstra_vertex_t *)param1;
	D_vert2 = (dijkstra_vertex_t *)param2;

	/* stabilize sort by using pointer values as tiebreaker? */

	if (D_vert1->cml_weight > D_vert2->cml_weight)
		return (1);
	else if (D_vert1->cml_weight < D_vert2->cml_weight)
		return (-1);
	else if (param1 > param2)
		return (1);
	else if (param1 < param2)
		return (-1);

	return (0);
}


int dijkstraGraph(dijkstra_vertex_t *D_queue, size_t nb_vertices,
		  const vertex_t *start, const vertex_t *target,
		  size_t *target_i)
{
	static size_t Dq_head_i;
	dijkstra_vertex_t Dq_head;
	edge_t *temp_e = NULL;
	size_t i;

	if (!D_queue || !start || !target || !target_i)
		return (0);

	printf("D_queue on entry:\n");
	for (i = Dq_head_i; i < nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       D_queue[i].vertex->content,
		       D_queue[i].cml_weight,
		       D_queue[i].path_via ? D_queue[i].path_via->content : NULL);

	Dq_head = D_queue[Dq_head_i];
	printf("Checking %s, distance from Seattle is %lu\n",
	       Dq_head.vertex->content, Dq_head.cml_weight);

	for (temp_e = Dq_head.vertex->edges; temp_e; temp_e = temp_e->next)
	{
		if (Dq_head.path_via && strcmp(temp_e->dest->content,
					       Dq_head.path_via->content) == 0)
			continue;
/*
		if (isVertexFinished(D_queue, Dq_head_i, temp_e->dest))
			continue;
*/

		for (i = Dq_head_i; i < nb_vertices; i++)
		{
			if (strcmp(temp_e->dest->content,
				   D_queue[i].vertex->content) == 0)
			{
				if (Dq_head.cml_weight + temp_e->weight <
				    D_queue[i].cml_weight)
				{
					D_queue[i].cml_weight = Dq_head.cml_weight + temp_e->weight;
					D_queue[i].path_via = Dq_head.vertex;
				}
			}
		}
	}

	/* add current to "finished" section */
	Dq_head_i++;
	qsort((void *)(D_queue + Dq_head_i), nb_vertices - Dq_head_i,
	      sizeof(dijkstra_vertex_t), compareWeights);

	printf("D_queue on exit:\n");
	for (i = Dq_head_i; i < nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       D_queue[i].vertex->content,
		       D_queue[i].cml_weight,
		       D_queue[i].path_via ? D_queue[i].path_via->content : NULL);

	(void)target_i;
	return (0);
}



/**
  * dijkstra_graph - searches for the shortest path from a starting point to a
  *   target point in a graph, based on edge weights
  *
  * @graph: pointer to the graph to traverse
  * @start: pointer to starting vertex
  * @target: pointer to target vertex
  * Return: returns a queue in which each node is a `char *` corresponding to a
  *   vertex, forming a path from start to target, or NULL on failure
  */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
        dijkstra_vertex_t *dijkstra_queue = NULL;
	vertex_t *temp_v = NULL;
	size_t i, target_i;

	if (!graph || !graph->nb_vertices || !graph->vertices ||
	    !start || !target)
		return (NULL);

	dijkstra_queue = malloc(sizeof(dijkstra_vertex_t) * graph->nb_vertices);
	if (!dijkstra_queue)
		return (NULL);

	for (i = 0, temp_v = graph->vertices; i < graph->nb_vertices;
	     i++, temp_v = temp_v->next)
	{
		dijkstra_queue[i].vertex = temp_v;

		if (strcmp(start->content, temp_v->content) == 0)
			dijkstra_queue[i].cml_weight = 0;
		else
			dijkstra_queue[i].cml_weight = ULONG_MAX;

		if (strcmp(target->content, temp_v->content) == 0)
			target_i = i;

		dijkstra_queue[i].path_via = NULL;
	}

	qsort((void *)dijkstra_queue, graph->nb_vertices,
	      sizeof(dijkstra_vertex_t), compareWeights);
/*
	for (i = 0; i < graph->nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       dijkstra_queue[i].vertex->content,
		       dijkstra_queue[i].cml_weight,
		       dijkstra_queue[i].path_via ? dijkstra_queue[i].path_via->content : NULL);
*/
	if (!dijkstraGraph(dijkstra_queue, graph->nb_vertices,
			   start, target, &target_i))
	{
		free(dijkstra_queue);
		return (NULL);
	}

/*
  assemble path backwards from dijkstra_queue
	path = queue_create();
	if (!path)
		return (NULL);

	return (path);
*/
	return (NULL);
}
