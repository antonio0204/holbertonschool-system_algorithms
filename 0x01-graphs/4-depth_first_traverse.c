#include "graphs.h"


/**
 * depth_first_traverse - walks through a graph using the depth-first algorithm
 *
 * @graph: pointer to the graph to traverse. (Traversal must start from the
 *   first vertex in the vertices list.)
 * @action: pointer to a function to be called for each visited vertex
 * @v: parameter to `action`: const pointer to the visited vertex
 * @depth: parameter to `action`: depth of v, from the starting vertex
 * Return: biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
}
