#include <stdlib.h>
#include <stdio.h>

#include "nary_trees.h"


void print_node(nary_tree_t const *node, size_t depth)
{
	printf("%*s%s\n", (int)depth * 2, "", node->content);
}


/* test from original 3-main.c */
int test1(void)
{
	nary_tree_t *root, *tmp, *var, *opt, *betty, *home, *alex;
	size_t diameter;

	root = nary_tree_insert(NULL, "/");
	if (!root)
	{
		fprintf(stderr, "tes1: failed to create node\n");
		return (EXIT_FAILURE);
	}

	tmp = nary_tree_insert(root, "tmp");
	nary_tree_insert(tmp, "tmp_file");

	var = nary_tree_insert(root, "var");
	nary_tree_insert(var, "www");

	opt = nary_tree_insert(root, "opt");
	betty = nary_tree_insert(opt, "Betty");
	nary_tree_insert(betty, "betty-style.pl");
	nary_tree_insert(betty, "betty-doc.pl");

	home = nary_tree_insert(root, "home");
	alex = nary_tree_insert(home, "alex");
	nary_tree_insert(alex, "Desktop");
	nary_tree_insert(alex, "Downloads");
	nary_tree_insert(alex, "Pictures");
	nary_tree_insert(alex, "Movies");
	nary_tree_insert(alex, "Documents");
	nary_tree_insert(alex, "Applications");

	nary_tree_traverse(root, &print_node);

	diameter = nary_tree_diameter(root);
	printf("\nDiameter = %lu (expected %i, or %i not including start)\n\n", diameter, 7, 6);

	nary_tree_delete(root);

	return (EXIT_SUCCESS);
}


/* https://leetcode.ca/2020-01-30-1522-Diameter-of-N-Ary-Tree/ example 1 */
int test2(void)
{
	nary_tree_t *_1, *_3;
	size_t diameter;

	_1 = nary_tree_insert(NULL, "1");
	if (!_1)
	{
		fprintf(stderr, "test2: failed to create node\n");
		return (EXIT_FAILURE);
	}

	nary_tree_insert(_1, "2");
	_3 = nary_tree_insert(_1, "3");
	nary_tree_insert(_1, "4");

	nary_tree_insert(_3, "5");
	nary_tree_insert(_3, "6");

	nary_tree_traverse(_1, &print_node);

	diameter = nary_tree_diameter(_1);
	printf("\nDiameter = %lu (expected %i, or %i not including start)\n\n", diameter, 4, 3);

	nary_tree_delete(_1);

	return (EXIT_SUCCESS);
}


/* https://leetcode.ca/2020-01-30-1522-Diameter-of-N-Ary-Tree/ example 2 */
int test3(void)
{
	nary_tree_t *_1, *_2, *_3, *_4;
	size_t diameter;

	_1 = nary_tree_insert(NULL, "1");
	if (!_1)
	{
		fprintf(stderr, "test3: failed to create node\n");
		return (EXIT_FAILURE);
	}

	_2 = nary_tree_insert(_1, "2");
	_3 = nary_tree_insert(_2, "3");
	_4 = nary_tree_insert(_2, "4");

	nary_tree_insert(_3, "5");
	nary_tree_insert(_4, "6");

	nary_tree_traverse(_1, &print_node);

	diameter = nary_tree_diameter(_1);
	printf("\nDiameter = %lu (expected %i, or %i not including start)\n\n", diameter, 5, 4);

	nary_tree_delete(_1);

	return (EXIT_SUCCESS);
}


/* https://leetcode.ca/2020-01-30-1522-Diameter-of-N-Ary-Tree/ example 3 */
int test4(void)
{
	nary_tree_t *_1, *_3, *_4, *_5, *_7, *_8, *_9, *_11;
	size_t diameter;

	_1 = nary_tree_insert(NULL, "1");
	if (!_1)
	{
		fprintf(stderr, "test2: failed to create node\n");
		return (EXIT_FAILURE);
	}

	nary_tree_insert(_1, "2");
	_3 = nary_tree_insert(_1, "3");
	_4 = nary_tree_insert(_1, "4");
	_5 = nary_tree_insert(_1, "5");

	nary_tree_insert(_3, "6");
	_7 = nary_tree_insert(_3, "7");

	_8 = nary_tree_insert(_4, "8");

	_9 = nary_tree_insert(_5, "9");
	nary_tree_insert(_5, "10");

	_11 = nary_tree_insert(_7, "11");

	nary_tree_insert(_8, "12");

	nary_tree_insert(_9, "13");

	nary_tree_insert(_11, "14");

	nary_tree_traverse(_1, &print_node);

	diameter = nary_tree_diameter(_1);
	printf("\nDiameter = %lu (expected %i, or %i not including start)\n\n",
	       diameter, 8, 7);

	nary_tree_delete(_1);

	return (EXIT_SUCCESS);
}


int main(void)
{
	return (test1() || test2() || test3() || test4());
}
