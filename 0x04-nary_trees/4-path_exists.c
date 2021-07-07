#include "nary_trees.h"

/* strncmp strlen */
#include <string.h>
/* fprintf */
#include <stdio.h>


/**
 * _path_exists - checks if a path exists in an N-ary tree, as confirmed by
 *   checking node content
 *
 * @root: pointer to the root node
 * @path: path to test, represented by a NULL terminated array of strings:
 *   each string at a given index would correspond to the content of a node
 *   at that depth
 * @path_i: current recursion frame / nodes from true root / index in path
 *
 * Return: 1 if contiguous sequence of nodes with content matching `path`
 *   strings in order, or 0 on failure
 */
int _path_exists(nary_tree_t const *root, char const * const *path,
		 size_t path_i)
{
	nary_tree_t *temp;

	if (!root || !root->content || path == NULL)
	{
		fprintf(stderr, "_path_exists: NULL parameter\n");
		return (0);
	}

	/* no segfault protection in glibc strncmp or strlen for NULL inputs */
	if (strncmp(root->content, path[path_i],
		    strlen(root->content) + 1) != 0)
		return (0);

	if (path[path_i + 1] == NULL)
		return (1);

	for (temp = root->children; temp; temp = temp->next)
	{
		if (_path_exists(temp, path, path_i + 1))
			return (1);
	}

	return (0);
}


/**
 * path_exists - checks if a path exists in an N-ary tree, as confirmed by
 *   checking node content
 *
 * @root: pointer to the root node
 * @path: path to test, represented by a NULL terminated array of strings:
 *   each string at a given index would correspond to the content of a node
 *   at that depth
 *
 * Return: 1 if contiguous sequence of nodes with content matching `path`
 *   strings in order, or 0 on failure
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (!root || !path || !path[0])
		return (0);

	return (_path_exists(root, path, 0));
}
