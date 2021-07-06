#include "nary_trees.h"

/* free */
#include <stdlib.h>


/**
 * nary_tree_delete - deallocates an entire N-ary tree
 *
 * @tree: pointer to the parent node
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *temp;

	if (!tree)
		return;

	while (tree->children)
	{
		temp = tree->children;
		tree->children = tree->children->next;
		nary_tree_delete(temp);
	}

	if (tree->content)
		free(tree->content);

	free(tree);
}
