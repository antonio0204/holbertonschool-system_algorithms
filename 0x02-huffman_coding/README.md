# (286) 0x02. C - Huffman coding
Specializations > System programming & Algorithm > Data structures and Algorithms

---

### Project author
Alexandre Gautier

### Assignment dates
04-26-2021 to 05-07-2021

### Description
A review of Min/Max Binary Heaps, plus an introduction to priority queues, Huffman Trees, and Huffman Coding, in service of building a file compression application.

### Provided file(s)
* [`binary_tree_print.c`](./binary_tree_print.c)
* definition of `binary_tree_node_t` and `heap_t` for [`heap.h`](./heap.h)
* definition of `symbol_t` for [`huffman.h`](./heap.h)
* default test mains: [`0-main.c`](./tests/0-main.c) [`1-main.c`](./tests/1-main.c) [`2-main.c`](./tests/2-main.c) [`3-main.c`](./tests/3-main.c) [`4-main.c`](./tests/4-main.c) [`5-main.c`](./tests/5-main.c) [`6-main.c`](./tests/6-main.c) [`7-main.c`](./tests/7-main.c) [`8-main.c`](./tests/8-main.c) [`9-main.c`](./tests/9-main.c)

---

## Mandatory Tasks

### :white_check_mark: 0. Min Binary Heap - Create heap
Write a function that creates a Heap data structure

* Prototype: `heap_t *heap_create(int (*data_cmp)(void *, void *));`
* Where `data_cmp` is a pointer to a comparison function
    * This function takes two `void *` parameters, each one being the data stored in a node.
    * This function will return the difference between the two data stored at those pointers.
    * It will be used to determine if a node’s value is greater or lower than another, so we can build our heap
* Your function must return a pointer to the created `heap_t` structure, or `NULL` if it fails
* `root` must be set to `NULL`
* `size` must be set to 0

File(s): [`heap/heap_create.c`](./heap/heap_create.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/heap_create.c 0-main.c -o heap_create`

### :white_check_mark: 1. Min Binary Heap - Create node
Write a function that creates a generic Binary Tree node

* Prototype: `binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);`
* Where `parent` is a pointer to the parent node of the node to be created
* And `data` is the data to be stored in the node
* Your function must return a pointer to the created node or `NULL` if it fails

File(s): [`heap/binary_tree_node.c`](./heap/binary_tree_node.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/binary_tree_node.c 1-main.c -o binary_tree_node`

### :white_check_mark: 2. Min Binary Heap - Insert node
Write a function that inserts a value in a Min Binary Heap

* Prototype: `binary_tree_node_t *heap_insert(heap_t *heap, void *data);`
* Where `heap` is a pointer to the heap in which the node has to be inserted
* And `data` is a pointer containing the data to store in the new node
* Your function must return a pointer to the created node containing `data`, or `NULL` if it fails
* The `size` of `heap` must be incremented if the function succeeds
* If `heap` is `NULL`, your function should fail
* If `data` is `NULL`, your function should fail
* If `heap->root` is `NULL`, then the new node must take its place
* You are allowed to have at most 7 functions in your file

File(s): [`heap/heap_insert.c`](./heap/heap_insert.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/heap_insert.c heap/binary_tree_node.c heap/heap_create.c 2-main.c _binary_tree_print.c -o heap_insert`

### :white_check_mark: 3. Min Binary Heap - Extract
Write a function that extracts the root value of a Min Binary Heap

* Prototype: `void *heap_extract(heap_t *heap);`
* Where `heap` is a pointer to the heap from which to extract the value
* Your function must return a pointer to the data that was stored in the root node of the heap
* Once the data is extracted, the root node must be freed, and replaced by the last node of the heap. Then the heap must be rebuilt if necessary
* If your function fails, or `heap` is `NULL`, it must return `NULL`
* You are allowed to have at most 7 functions in your file

File(s): [`heap/heap_extract.c`](./heap/heap_extract.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/heap_insert.c heap/binary_tree_node.c heap/heap_create.c heap/heap_extract.c 3-main.c _binary_tree_print.c -o heap_extract`

### :white_check_mark: 4. Min Binary Heap - Delete heap
Write a function that deallocates a heap

* Prototype: `void heap_delete(heap_t *heap, void (*free_data)(void *));`
* Where `heap` is a pointer to the heap to delete
* And `free_data` is a pointer to a function that will be used to free the content of a node
* Your function must free the entire tree starting at `heap->root` and the heap structure itself
* If `free_data` is `NULL`, the data stored in the nodes must not be freed

File(s): [`heap/heap_delete.c`](./heap/heap_delete.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/heap_insert.c heap/binary_tree_node.c heap/heap_create.c heap/heap_delete.c 4-main.c _binary_tree_print.c -o heap_delete`

### :white_check_mark: 5. Symbols: Create symbol
Write a function that creates a symbol_t data structure

* Prototype: `symbol_t *symbol_create(char data, size_t freq);`
* Where `data` is the data to be stored in the structure
* And `freq` is its associated frequency
* Your function must return a pointer to the created structure, or `NULL` if it fails

File(s): [`symbol.c`](./symbol.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/*.c 5-main.c symbol.c -o symbol_create`

### :white_check_mark: 6. Huffman coding - Step 1: Priority queue
The first step to get the Huffman codes of our letters is to build a priority queue. The value of frequency field will be used to compare two nodes in this min heap. Once built, the least frequent character will be stored in the root node of our priority queue.

Write a function that creates a priority queue for the Huffman coding algorithm

* Prototype: `heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);`
* Where `data` is an array of characters of size size
* And `freq` is an array containing the associated frequencies (of size `size` too)
* Your function must return a pointer to the created min heap (also called priority queue)
* Each node of this priority queue stores a heap leaf node containing a `symbol_t *`
    * `node->data` is a `binary_tree_node_t *` (let’s call it `nested`)
    * `nested->data` is our `symbol_t *`

File(s): [`huffman_priority_queue.c`](./huffman_priority_queue.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/*.c 6-main.c symbol.c huffman_priority_queue.c _binary_tree_print.c -o prio`

### :white_check_mark: 7. Huffman coding - Step 2: Extract
Once we have our priority queue initialized, the next step is to build the Huffman tree. First we need to understand the process of building such a tree. We need to extract the two least frequent symbols from our priority queue, add their frequencies, and store this new frequency back in our priority queue.

Remember that in our priority queue, each node stores a leaf node that stores our symbol_t *. The goal here, is to make the two extracted nodes (containing the symbol_t *) the children of the new node we will create (the one that will store the sum of the two frequencies). The first extracted node will be the left child, and the second one will be the right child. Then this node will be stored (inside a node) in our priority queue.

So, at the end of this process, our priority queue will see its size decreased by one (we extract two, we insert back one). Note that we will use the value -1 as the char data for the new symbol we will create. (In the example below, we print it as a dollar sign)

Write a function that extracts the two nodes of the priority queue and inserts a new one

* Prototype: `int huffman_extract_and_insert(heap_t *priority_queue);`
* Where `priority_queue` is a pointer to the priority queue to extract from
* Your function must return 1 on success or 0 on failure

File(s): [`huffman_extract_and_insert.c`](./huffman_extract_and_insert.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/*.c 7-main.c symbol.c huffman_priority_queue.c huffman_extract_and_insert.c _binary_tree_print.c -o extract`

### :white_check_mark: 8. Huffman coding - Step 3: Build Huffman tree
Following the previous step, we now have to iterate the same operation until there is only one node remaining in our priority queue. This final node will store the root node of our Huffman tree.

Write a function that builds the Huffman tree

* Prototype: `binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);`
* Where `data` is an array of characters of size `size`
* And `freq` is an array containing the associated frequencies (of size size too)
* Your function must return a pointer to the root node of the Huffman tree, or `NULL` if it fails
* Remember that you have to return the root node of the Huffman tree, not the root node of the priority queue. Each node of the priority queue stores a node.

File(s): [`huffman_tree.c`](./huffman_tree.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/*.c 8-main.c symbol.c huffman_priority_queue.c huffman_extract_and_insert.c huffman_tree.c _binary_tree_print.c -o huffman_tree`

### :white_check_mark: 9. Huffman coding - Step 4: Huffman codes
Now that we have our Huffman tree, we are able to get the Huffman codes for each letter. This process is pretty straight forward: go through the Huffman tree starting at the root node. Each time you go to the left node, append a 0 to the code. Each time you go to the right, append a 1 to the code. When you hit a leaf node, get the letter and print its corresponding Huffman code.

Write a function that build the Huffman tree and print the resulting Huffman codes for each symbol

* Prototype: `int huffman_codes(char *data, size_t *freq, size_t size);`
* Where `data` is an array of characters of size `size`
* And `freq` is an array containing the associated frequencies (of size `size` too)
* Your function must return 1 if it succeed, 0 if it fails

File(s): [`huffman_codes.c`](./huffman_codes.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic -Iheap/ -I./ heap/*.c 9-main.c symbol.c huffman_priority_queue.c huffman_extract_and_insert.c huffman_tree.c huffman_codes.c _binary_tree_print.c -o huffman_codes`

---

## Advanced Tasks

### :white_check_mark: 10. Huffman - Compression & Decompression
Write a program that compress or decompress a file using Huffman codes

Name of the executable: `huffman`

Usage: `./huffman <mode> <filename> <out_filename>`, where:

* `<mode>` is either
    * `c`: Compression mode
        * `<filename>` will be compressed into `<out_filename>`
    * `d`: Decompression mode
        * `<filename>` will be decompressed into `<out_filename>`
* If `<filename>` does not exist:
    * Your program must print `No such file: <filename>`, where `<filename>` must be replaced by the actual filename
    * Your program must return `EXIT_FAILURE`
* `<out_filename>` must be created. If it already exists:
    * Your program must print `File already exists: <filename>`, where `<filename>` must be replaced by the actual filename
    * Your program must return `EXIT_FAILURE`
* If the number of arguments is not correct, your program must print `Usage: huffman <mode> <filename> <out_filename>` and return `EXIT_FAILURE`
* Your program will be compiled this way: `make all`

File(s): [`huffman/*`](./huffman/)\
Compiled: `cd huffman/ && make all`

---

## Student
* **Samuel Pomeroy** - [allelomorph](github.com/allelomorph)
