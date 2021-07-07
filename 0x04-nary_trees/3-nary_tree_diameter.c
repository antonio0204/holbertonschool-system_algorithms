#include "nary_trees.h"

/* malloc free */
#include <stdlib.h>
/* fprintf */
#include <stdio.h>


/**
 * _nary_tree_diameter - finds the diameter of an N-ary tree via DFS and
 *   bottom up dynamic programming
 *
 * @root: pointer to the root node of the tree to measure
 * @depth: depth of recursion frame, or current `root` from true root
 * @diameter: pointer to current maximum diameter, modified by reference
 *
 * Return: pointer to struct with first and second max depths of descendant
 *   nodes, or NULL on failure
 */
size_t _nary_tree_diameter(nary_tree_t const *root, size_t depth,
			   size_t *diameter)
{
	size_t *child_depths = NULL, i, max_depth_1, max_depth_2, node_diam;
	nary_tree_t *temp;

	if (!diameter)
		fprintf(stderr, "_nary_tree_diameter: NULL diameter\n");
	if (!root || !diameter)
		return (0);

	max_depth_1 = max_depth_2 = depth;
	if (root->nb_children)
	{
		child_depths = malloc(sizeof(size_t) * root->nb_children);
		if (!child_depths)
		{
			fprintf(stderr,
				"_nary_tree_diameter: malloc failure\n");
			return (0);
		}

		for (temp = root->children, i = 0;
		     temp && i < root->nb_children;
		     temp = temp->next, i++)
			child_depths[i] = _nary_tree_diameter(temp, depth + 1,
							      diameter);

		for (i = 0; i < root->nb_children; i++)
		{
			if (child_depths[i] > max_depth_1)
				max_depth_1 = child_depths[i];
			else if (child_depths[i] > max_depth_2)
				max_depth_2 = child_depths[i];
		}

		free(child_depths);
	}

	node_diam = (max_depth_1 - depth) + (max_depth_2 - depth) + 1;
	if (node_diam > *diameter)
		*diameter = node_diam;
	return (max_depth_1);
}


/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 *
 * @root: pointer to the root node of the tree to measure
 *
 * Return: diameter of the tree pointed to by root, or 0 on failure
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	_nary_tree_diameter(root, 0, &diameter);

	return (diameter);
}
