#include "nary_trees.h"

/* fprintf */
#include <stdio.h>
/* strdup */
#include <string.h>
/* malloc free */
#include <stdlib.h>


/**
 * nary_tree_insert - inserts a node in a N-ary tree
 *
 * @parent: pointer to the parent node
 * @str: string to be duplicated and stored in the created node
 *
 * Return: pointer to the created node, or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new;
	char *str_copy;

	new = malloc(sizeof(nary_tree_t));
	if (!new)
	{
		fprintf(stderr, "nary_tree_insert: malloc failure\n");
		return (NULL);
	}

	str_copy = strdup(str);
	if (!str_copy)
	{
		free(new);
		fprintf(stderr, "nary_tree_insert: strdup failure\n");
		return (NULL);
	}

	new->content = str_copy;
	new->parent = parent;
	new->nb_children = 0;
	new->children = NULL;
	new->next = NULL;

	if (parent)
	{
		new->next = parent->children;
		parent->children = new;
		parent->nb_children++;
	}

	return (new);
}
