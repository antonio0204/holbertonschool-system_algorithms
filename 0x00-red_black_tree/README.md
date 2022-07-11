# (378) 0x00. C - Red-Black trees
Specializations > System programming & Algorithm > Data structures and Algorithms

---

### Project author
Alexandre Gautier

### Assignment dates
02-23-2021 to 03-05-2021

### Description
Introduction to Red-Black Trees: how they differ from other types of Binary Trees, and how to implement tree validation and node insertion/deletion based on their properties. 

### Provided file(s)
* [`binary_tree_print.c`](./binary_tree_print.c)
* [`rb_tree_print.c`](./rb_tree_print.c)
* [`rb_trees.h`](./rb_trees.h) (only definitions of `rb_color_t` and `rb_tree_t`)
* [`heap.h`](./heap.h) (only definition of `binary_tree_node_t`)
* default test mains: [`0-main.c`](./tests/0-main.c) [`1-main.c`](./tests/1-main.c) [`2-main.c`](./tests/2-main.c) [`3-main.c`](./tests/3-main.c)

---

## Mandatory Tasks

### :white_check_mark: 0. Red-Black - New node
Write a function that creates a Red-Black Tree node

* Prototype: `rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);`
* Where `parent` is a pointer to the parent node of the node to create
* `value` is the value to put in the new node
* And `color` is the color of the node
* When created, a node does not have any child
* Your function must return a pointer to the new node, or `NULL` on failure

File(s): [`0-rb_tree_node.c`](./0-rb_tree_node.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-rb_tree_node.c rb_tree_print.c -o rb_tree_node`


### :white_check_mark: 1. Red-Black - Is Red-Black
Write a function that checks if a binary tree is a valid Red-Black Tree

* Prototype: `int rb_tree_is_valid(const rb_tree_t *tree);`
* Where `tree` is a pointer to the root node of the tree to check
* Your function must return `1` if `tree` is a valid Red-Black Tree, and `0` otherwise
* If tree is `NULL`, return `0`

File(s): [`1-rb_tree_is_valid.c`](./1-rb_tree_is_valid.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 1-main.c 1-rb_tree_is_valid.c 0-rb_tree_node.c rb_tree_print.c -o rb_tree_valid`


### :white_check_mark: 2. Red-Black - Insert
Write a function that inserts a value in a Red-Black Tree

* Prototype: `rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);`
* Where `tree` is a double pointer to the root node of the Red-Black tree to insert the value in
* And `value` is the value to store in the node to be inserted
* Your function must return a pointer to the created node, or `NULL` on failure
* If the address stored in `tree` is `NULL`, the created node must become the root node.
* If the value is already present in the tree, it must be ignored
* The resulting tree after insertion, must be a Red-Black Tree
* You are allowed to have up to 7 functions in your file

File(s): [`2-rb_tree_insert.c`](./2-rb_tree_insert.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 2-main.c 0-rb_tree_node.c 2-rb_tree_insert.c rb_tree_print.c -o rb_tree_insert`


### :white_check_mark: 3. Red-Black - Array to R-B Tree
Write a function that builds a Binary Search Tree from an array

* Prototype: `rb_tree_t *array_to_rb_tree(int *array, size_t size);`
* Where `array` is a pointer to the first element of the array to be converted
* And `size` is the number of elements in the array
* Your function must return a pointer to the root node of the created R-B tree, or `NULL` on failure
* If a value in the array is already present in the tree, this value must be ignored

File(s): [`3-array_to_rb_tree.c`](./3-array_to_rb_tree.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 3-main.c 0-rb_tree_node.c 2-rb_tree_insert.c 3-array_to_rb_tree.c rb_tree_print.c -o rb_tree_array`


### :white_large_square: 4. Red-Black - Remove
Write a function that removes a node from a Red-Black tree

* Prototype: `rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);`
* Where `root` is a pointer to the root node of the tree
* And `n` is the value to search and remove from the tree
* Your function must return the pointer to the new root of the tree after deletion
* The resulting tree must be a valid Red-Black tree
* You’re allowed to have up to 7 functions in your file

File(s): [`4-rb_tree_remove.c`](./4-rb_tree_remove.c) [`0-rb_tree_node.c`](./0-rb_tree_node.c)


### :white_check_mark: 5. Big O Red-Black Tree
What are the average time complexities of the below operations for a Red-Black Tree (one answer per line):

1. Inserting a node in a Red-Black Tree of size n
2. Removing a node from a Red-Black Tree of size n
3. Searching for a node in a Red-Black Tree of size n

File(s): [`5-O`](./5-O)

---

## Student
* **Ronal Aguirre Villalobos** - [ronald0204](https://github.com/ronald0204)
