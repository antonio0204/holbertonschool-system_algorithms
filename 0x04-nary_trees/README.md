# (196) 0x04. C - N-ary trees
Specializations > System programming & Algorithm > Data structures and Algorithms

---

### Project author
Alexandre Gautier

### Assignment dates
07-01-2021 to 07-14-2021

### Description
Introduction to N-ary trees as an extension of previous Binary Tree concepts: node insertion, tree deletion and traversal, measuring the diameter of a tree, and pathfinding from the root node.

### Provided file(s) and data structures
* definition of `nary_tree_t` for [`nary_trees.h`](./nary_trees.h)
* default test mains: [`0-main.c`](./tests/0-main.c) [`1-main.c`](./tests/1-main.c) [`2-main.c`](./tests/2-main.c) [`3-main.c`](./tests/3-main.c) [`4-main.c`](./tests/4-main.c)

---

## Mandatory Tasks

### :white_check_mark: 0. Insert
Write a function that inserts a node in a N-ary tree.

* Prototype: `nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str);`
* Where `parent` is a pointer to the parent node.
* `str` is the string to be stored in the created node. It must be duplicated.
* If parent is not `NULL`, the created node must be added at the beginning of the parent’s children linked list.
* Your function must return a pointer to the created node, or `NULL` on failure.

File(s): [`0-nary_tree_insert.c`](./0-nary_tree_insert.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -o 0-nary_tree_insert 0-nary_tree_insert.c 0-main.c`

### :white_check_mark: 1. Delete
Write a function that deallocates an entire N-ary tree

* Prototype: `void nary_tree_delete(nary_tree_t *tree);`

File(s): [`1-nary_tree_delete.c`](./1-nary_tree_delete.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -o 1-nary_tree_delete 1-nary_tree_delete.c 0-nary_tree_insert.c 1-main.c`

### :white_check_mark: 2. Traversal
Write a function that goes through an N-ary tree, node by node.

* Prototype: `size_t nary_tree_traverse(nary_tree_t const *root, void (*action)(nary_tree_t const *node, size_t depth));`
* Where `root` is a pointer to the root node of the tree to traverse
* `action` is a pointer to a function to execute for each node being traversed. Its arguments are:
    * `node` is a pointer to the node being traversed
    * `depth` is the depth of the node being traversed
* Your function must return the biggest depth of the tree pointed to by `root`

File(s): [`2-nary_tree_traverse.c`](./2-nary_tree_traverse.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -o 2-nary_tree_traverse 2-nary_tree_traverse.c 1-nary_tree_delete.c 0-nary_tree_insert.c 2-main.c`

### :white_check_mark: 3. Diameter
Write a function that computes the diameter of an N-ary tree

* Prototype: `size_t nary_tree_diameter(nary_tree_t const *root);`
* Where `root` is a pointer to the root node of the tree to compute the diameter of.
* Your function must return the diameter of the tree pointed to by root.

File(s): [`3-nary_tree_diameter.c`](./3-nary_tree_diameter.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -o 3-nary_tree_diameter 3-nary_tree_diameter.c 1-nary_tree_delete.c 0-nary_tree_insert.c 3-main.c`

### :white_check_mark: 4. Path exists
Write a function that checks if a path exists in an N-ary tree.

* Prototype: `int path_exists(nary_tree_t const *root, char const * const *path);`
* Where `root` is a pointer to the root node of the tree
* and `path` is a `NULL` terminated array of strings. The string at the index `i` can be the content of one of the nodes of the tree at the depth `i`.
* Your function must return 1 if all the elements of path are present in the tree and if for an element of path at the index `i` is present in one of the nodes at the depth `i`. And of course, all the nodes must be linked to form a path.

File(s): [`4-path_exists.c`](./4-path_exists.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -o 4-path_exists 4-path_exists.c 1-nary_tree_delete.c 0-nary_tree_insert.c 4-main.c`

---

## Student
* **Samuel Pomeroy** - [allelomorph](github.com/allelomorph)
