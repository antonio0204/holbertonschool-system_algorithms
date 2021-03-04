#include "rb_trees.h"

/* INT_MIN */
#include <limits.h>


/**
 * max_size_t - finds larger of two size_t values
 *
 * @a: first value to compare
 * @b: second value to compare
 * Return: larger size_t value, or value of both if equal
 */
size_t max_size_t(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}


/**
 * RBT_check_black_height - recursively tests if binary tree has Red-Black Tree
 * property of equal number of black nodes between any leaf and root
 * note: black height of a NULL leaf is defined to be 1
 *
 * @tree: root node from which to measure, starting at 0
 * Return: levels from root, or 0 if `tree` is NULL
 */
size_t RBT_check_black_height(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color == BLACK)
		return (1 + max_size_t(RBT_check_black_height(tree->left),
				       RBT_check_black_height(tree->right)));
	else
		return (max_size_t(RBT_check_black_height(tree->left),
				   RBT_check_black_height(tree->right)));
}


/**
 * RBT_check_colors - recursively validates coloring of Red-Black Tree:
 * - root of tree is always black
 * - red nodes cannot have red parents or red children
 * - every path from root to given leaf has same number of black nodes
 *
 * @tree: tree to check for BST
 * Return: 1 valid if `tree` is valid RBT, or 0 if not or `tree` is NULL
 */
int RBT_check_colors(const rb_tree_t *tree)
{
	if (tree)
	{
		/* color out of rb_color_t range */
		if (tree->color != RED && tree->color != BLACK)
			return (0);

		/* root must be black */
		if (!(tree->parent))
		{
			if (tree->color != BLACK)
				return (0);
		}
		/* no adjacent red nodes */
		else if (tree->color == RED)
		{
			if (tree->parent->color == RED ||
			    (tree->left && tree->left->color == RED) ||
			    (tree->right && tree->right->color == RED))
				return (0);
		}

		if (RBT_check_black_height(tree->left) !=
		    RBT_check_black_height(tree->right))
			return (0);

		return (RBT_check_colors(tree->left) &&
			RBT_check_colors(tree->right));
	}

	/* recursion has reached an edge of the tree */
	return (1);
}


/**
 * BST_check - recursively tests if binary tree is binary search tree:
 * - left subtree of each node only has values less than node
 * - right subtree of each node only has values greater than node
 * - no values appear twice
 * - tree is a BST at each node
 *
 * @tree: tree to check for BST
 * @prev: int passed by reference from outside recursion, should step through
 * node values in order if tree is BST
 * Return: 1 valid if `tree` is valid BST, or 0 if not or `tree` is NULL
 */
int BST_check(const rb_tree_t *tree, int *prev)
{
	if (tree)
	{
		if (!BST_check(tree->left, prev))
			return (0);

		/*
		 * checks both for repeat values and for left_child < parent
		 * and right_child > parent
		 */
		if (tree->n <= *prev)
			return (0);

		/* prev updates to current */
		*prev = tree->n;

		return (BST_check(tree->right, prev));
	}

	/* recursion has reached an edge of the tree */
	return (1);
}


/**
 * rb_tree_is_valid - validates that a binary tree is a Red-Black Tree:
 * - tree is a Binary Search Tree
 * - every node has a polarity, or "color," either red or black
 * - root of tree is always black
 * - red nodes cannot have red parents or red children
 * - every path from root to given leaf has same number of black nodes
 *
 * @tree: pointer to root node or subtree
 * Return: 1 if tree is a valid Red-Black Tree; 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int prev = INT_MIN;

	if (!tree)
		return (0);

	if (!BST_check(tree, &prev))
		return (0);

	return (RBT_check_colors(tree));
}
