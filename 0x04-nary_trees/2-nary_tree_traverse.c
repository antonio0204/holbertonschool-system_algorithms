#include "nary_trees.h"


/**
 * nary_tree_traverse - walks through an N-ary tree, node by node
 *
 * @root: pointer to the root node of the tree to traverse
 * @action: pointer to a function to execute for each node being traversed,
 *   takes 2 parameters:
 *     node: pointer to the node being traversed
 *     depth: depth of the node being traversed
 *
 * Return: max depth of the tree pointed to by root
 */
size_t nary_tree_traverse(nary_tree_t const *root,
			  void (*action)(nary_tree_t const *node, size_t depth))
{
}
