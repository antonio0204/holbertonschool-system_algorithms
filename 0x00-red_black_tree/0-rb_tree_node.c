#include "rb_trees.h"

/* malloc NULL */
#include <stdlib.h>

/* fprintf */
#include <stdio.h>

/**
 * rb_tree_node - creates a red-black binary tree node of struct `rb_tree_t`
 *
 * @parent: pointer to parent of node created
 * @value: integer stored in new node
 * @color: red-black polarity of new node
 * Return: pointer to new node
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;

	if (color > DOUBLE_BLACK || color < RED)
	{
		fprintf(stderr,
			"rb_tree_node: color out of rb_color_t range\n");
		return (NULL);
	}

	new = malloc(sizeof(rb_tree_t));
	if (!new)
		return (NULL);

	new->n = value;
	new->color = color;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;

	return (new);
}
