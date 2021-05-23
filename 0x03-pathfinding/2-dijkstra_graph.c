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


void dijkstraGraph(dijkstra_vertex_t *d_queue, size_t nb_vertices,
		   const vertex_t *start, const vertex_t *target,
		   size_t dq_head_i, size_t *target_i)
{
	dijkstra_vertex_t dq_head;
	edge_t *temp_e = NULL;
	size_t i;

	if (!d_queue || !start || !target || !target_i)
		return;

	printf("d_queue on entry:\n");
	for (i = dq_head_i; i < nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       d_queue[i].vertex->content,
		       d_queue[i].cml_weight,
		       d_queue[i].path_via ? d_queue[i].path_via->content : NULL);

	dq_head = d_queue[dq_head_i];
	printf("Checking %s, distance from Seattle is %lu\n",
	       dq_head.vertex->content, dq_head.cml_weight);

	for (temp_e = dq_head.vertex->edges; temp_e; temp_e = temp_e->next)
	{
		if (dq_head.path_via && strcmp(temp_e->dest->content,
					       dq_head.path_via->content) == 0)
			continue;
/*
		if (isVertexFinished(d_queue, dq_head_i, temp_e->dest))
			continue;
*/

		for (i = dq_head_i; i < nb_vertices; i++)
		{
			if (strcmp(temp_e->dest->content,
				   d_queue[i].vertex->content) == 0)
			{
				if (dq_head.cml_weight + temp_e->weight <
				    d_queue[i].cml_weight)
				{
					d_queue[i].cml_weight = dq_head.cml_weight + temp_e->weight;
					d_queue[i].path_via = dq_head.vertex;
				}
			}
		}
	}

	qsort((void *)(d_queue + dq_head_i), nb_vertices - dq_head_i,
	      sizeof(dijkstra_vertex_t), compareWeights);

	printf("d_queue on exit:\n");
	for (i = dq_head_i; i < nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       d_queue[i].vertex->content,
		       d_queue[i].cml_weight,
		       d_queue[i].path_via ? d_queue[i].path_via->content : NULL);

	if (strcmp(target->content, dq_head.vertex->content) == 0)
	{
		*target_i = dq_head_i;
		return;
	}

	if (dq_head_i == nb_vertices - 1)
		return;

	dijkstraGraph(d_queue, nb_vertices, start, target,
		      dq_head_i + 1, target_i);
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
	queue_t *path = NULL;

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

	dijkstraGraph(dijkstra_queue, graph->nb_vertices,
		      start, target, 0, &target_i);

	printf("\n\ndijkstra_queue after recursion\n");
	for (i = 0; i < graph->nb_vertices; i++)
		printf("dijkstra_queue[%lu] %s %lu %s\n", i,
		       dijkstra_queue[i].vertex->content,
		       dijkstra_queue[i].cml_weight,
		       dijkstra_queue[i].path_via ? dijkstra_queue[i].path_via->content : NULL);

/*
	{
		free(dijkstra_queue);
		return (NULL);
	}
*/
/* assemble path backwards from dijkstra_queue */
/*
	path = queue_create();
	if (!path)
		return (NULL);

	queue_push_front(path, (void *));

	for (i = 0; i < graph->nb_vertices; i++)
	{
	}
*/
	return (path);
}
