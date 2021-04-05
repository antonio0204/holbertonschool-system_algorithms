#include "graphs.h"


/**
 * graph_add_edge - adds an edge between two vertices in an existing graph
 *
 * @graph: pointer to the graph to which edge is added
 * @src: string identifying the starting vertex in the connection
 * @dest: string identifying the ending vertex in the connection
 * @type: type of edge, valid values are:
 *          UNIDIRECTIONAL: only one edge is created from src to dest
 *          BIDIRECTIONAL: two edges created: from src to dest AND dest to src
 * Return: 0 on success, or 1 on failure
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
}
