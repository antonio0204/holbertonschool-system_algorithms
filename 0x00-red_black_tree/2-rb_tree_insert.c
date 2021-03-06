#include "rb_trees.h"


/**
 * rb_tree_get_uncle - retrieves sibling of node parent in RBT
 *
 * @n: starting node
 * Return: pointer to uncle node, or NULL if parent or grandparent missing
 */
rb_tree_t *rb_tree_get_uncle(rb_tree_t *n)
{
	rb_tree_t *p = n ? n->parent : NULL;

	/* No parent or grandparent means no uncle */
	if (!p || !p->parent)
		return (NULL);

	if (p == p->parent->left)
		return (p->parent->right);

	return (p->parent->left);
}


/**
 * rb_tree_rotate_left - left child of root becomes new root, tree rotated
 * so it retains BST ordering of values (in-order traversal of leaves is same)
 *
 * @tree: tree to left rotate
 * Return: pointer to new root node, or NULL if `root` is NULL
 */
rb_tree_t *rb_tree_rotate_left(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	/* pivot will become new root */
	pivot = tree->right;

	/* migrate children to keep BST order */
	tree->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = tree;

	/* handle upstream connections if `tree` is a subtree */
	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->left)
			tree->parent->left = pivot;
		else
			tree->parent->right = pivot;
	}

	/* finally rotate pivot into root postion */
	pivot->left = tree;
	tree->parent = pivot;

	return (pivot);
}


/**
 * rb_tree_rotate_right - R child of root becomes new root, tree rotated
 * so it retains BST ordering of values (in-order traversal of leaves is same)
 *
 * @tree: tree to right rotate
 * Return: pointer to new root node, or NULL if `root` is NULL
 */
rb_tree_t *rb_tree_rotate_right(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	/* pivot will become new root */
	pivot = tree->left;

	/* migrate children to keep BST order */
	tree->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = tree;

	/* handle upstream connections if `tree` is a subtree */
	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->right)
			tree->parent->right = pivot;
		else
			tree->parent->left = pivot;
	}

	/* finally rotate pivot into root postion */
	pivot->right = tree;
	tree->parent = pivot;

	return (pivot);
}


/**
 * rb_tree_insert_case4 - foruth repair case for insertion into an RBT:
 * parent is red but uncle is black or missing
 *
 * @node: freshly inserted node
 * Return: pointer to new root node, or NULL on failure
 */
rb_tree_t *rb_tree_insert_case4(rb_tree_t *node)
{
	rb_tree_t *p = node ? node->parent : NULL;
	rb_tree_t *g = p ? p->parent : NULL;
	rb_tree_t *new_root = NULL;

	if (!p || !g)
		return (NULL);

	/* step 1: may need to rotate into p to prep for rotation into g */
	/* - ensuring the inserted node is on the outside of its subtree */
	/* 1A: node is "center left" of g's four potential grandchildren */
	if (node == p->right && p == g->left)
	{
		new_root = rb_tree_rotate_left(p);
		node = node->left;
	}
	/* 1B: node is "center right" of g's four potential grandchildren */
	else if (node == p->left && p == g->right)
	{
		new_root = rb_tree_rotate_right(p);
		node = node->right;
	}

	p = node ? node->parent : NULL;
	g = p ? p->parent : NULL;

	/* step 2: rotate into g */
	if (node == p->left)
		new_root = rb_tree_rotate_right(g);
	else
		new_root = rb_tree_rotate_left(g);

	while (new_root && new_root->parent)
		new_root = new_root->parent;

	p->color = BLACK;
	g->color = RED;

	return (new_root);
}


/**
 * rb_tree_insert_repair - traverses a RBT after insertion of a new node to
 * retore Red-Black Tree properties
 *
 * @root: tree to repair
 * @node: newly inserted node
 * Return: pointer to new root node, or NULL on failure
 */
rb_tree_t *rb_tree_insert_repair(rb_tree_t *root, rb_tree_t *node)
{
	/* new nodes are inserted in BST order and red by default */
	if (!node)
		return (root);

	if (node->parent == NULL)
	{
		/* case 1: node is root, recolor black */
		node->color = BLACK;
		return (node);
	}
	else if (node->parent->color == BLACK)
	{
		/* case 2: node parent exists and is black - still valid RBT */
		return (root);
	}
	else if (rb_tree_get_uncle(node) != NULL &&
		 rb_tree_get_uncle(node)->color == RED)
	{
		/* case 3: parent is red, uncle exists and is red */
		node->parent->color = BLACK;
		rb_tree_get_uncle(node)->color = BLACK;
		node->parent->parent->color = RED;
		return (rb_tree_insert_repair(root, node->parent->parent));
	}

	/* case 4: parent is red, and uncle is black or missing */
	return (rb_tree_insert_case4(node));

}


/**
 * rb_tree_insert_recurse - recursively traverses RBT to insert value;
 * new node added in BST order, and colored red by default
 *
 * @tree: tree to insert value into, or start new if NULL
 * @value: integer to insert into tree
 * Return: pointer to new node, or NULL on failure or ignored value
 */
rb_tree_t *rb_tree_insert_recurse(rb_tree_t *tree, int value)
{
	rb_tree_t *new = NULL;

	if (tree)
	{
		if (tree->n > value)
		{
			if (tree->left == NULL)
			{
				new = rb_tree_node(tree, value, RED);
				tree->left = new;
				return (new);
			}

			return (rb_tree_insert_recurse(tree->left, value));
		}

		if (tree->n < value)
		{
			if (tree->right == NULL)
			{
				new = rb_tree_node(tree, value, RED);
				tree->right = new;
				return (new);
			}

			return (rb_tree_insert_recurse(tree->right, value));
		}

		/* tree->n == value, duplicates ignored */
		return (NULL);
	}

	/* new root, will be colored black by repair */
	return (rb_tree_node(NULL, value, RED));
}


/**
 * rb_tree_insert - inserts a value in a Red-Black Tree (redundant values
 * ignored)
 *
 * @tree: tree to insert value into, or start new if NULL
 * @value: integer to insert into tree
 * Return: pointer to new node, or NULL on failure or ignored value
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new = NULL, *new_root = NULL;

	if (!tree)
		/* start new tree */
		new = rb_tree_insert_recurse(NULL, value);
	else
		/* insert into the current tree */
		new = rb_tree_insert_recurse(*tree, value);
	if (!new)
		return (NULL);

	/* repair the red-black properties of the tree after insertion */
	new_root = rb_tree_insert_repair(*tree, new);
	if (!new_root)
		return (NULL);

	*tree = new_root;

	return (new);
}
