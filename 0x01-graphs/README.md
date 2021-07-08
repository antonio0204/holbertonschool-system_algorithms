# (392) 0x01. C - Graphs
Specializations > System programming & Algorithm > Data structures and Algorithms

---

### Project author
Alexandre Gautier

### Assignment dates
04-05-2021 to 04-15-2021

### Description
Introduction to Graph Theory: what are vertices and edges, different types of graphs (directed, weighted, etc.), the most common ways of representing graphs in C, and DFS versus BFS traversal.

### Provided file(s)
* [`graph_display.c`](./graph_display.c)
* definitions of `edge_type_t`, `edge_t`, `struct vertex_s`, and `graph_t` for [`graphs.h`](./graphs.h)
* default test mains: [`0-main.c`](./tests/0-main.c) [`1-main.c`](./tests/1-main.c) [`2-main.c`](./tests/2-main.c) [`3-main.c`](./tests/3-main.c) [`4-main.c`](./tests/4-main.c) [`5-main.c`](./tests/5-main.c)

---

## Mandatory Tasks

### :white_check_mark: 0. Create graph
Write a function that allocates memory to store a graph_t structure, and initializes its content.

* Prototype: `graph_t *graph_create(void);`
* Your function must return a pointer to the allocated structure, or `NULL` on failure

File(s): [`0-graph_create.c`](./0-graph_create.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-graph_create.c -o 0-graph_create`


### :white_check_mark: 1. Add a vertex
Write a function that adds a vertex to an existing graph

* Prototype: `vertex_t *graph_add_vertex(graph_t *graph, const char *str);`
* Where `graph` is a pointer to the graph to add the vertex to, and str is the string to store in the new vertex
* Your function must return a pointer to the created vertex, or `NULL` on failure
* The vertex must store a copy of the string `str`
* If a vertex in `graph` already stores the string `str`, your function must fail, and there must be no leak

File(s): [`1-graph_add_vertex.c`](./1-graph_add_vertex.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 1-main.c 0-graph_create.c 1-graph_add_vertex.c graph_display.c -o 1-graph_add_vertex`


### :white_check_mark: 2. Add an edge
Write a function that adds an edge between two vertices to an existing graph

* Prototype: `int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type);`
* Where:
    * `graph` is a pointer to the graph to add the edge to
    * `src` is the string identifying the vertex to make the connection from
    * `dest` is the string identifying the vertex to connect to
    * `type` is the type of edge
        * `UNIDIRECTIONAL`: Only one edge is created connecting `src` to `dest`
        * `BIDIRECTIONAL`: Two edges are created, connecting `src` to `dest` AND `dest` to `src`.
* Your function must return 1 on success, or 0 on failure. On failure, no edge must have be created, and there must be no memory leak.
* If either `src` or `dest` are not found in any vertex of `graph`, your function must fail, and there must be no leak

File(s): [`2-graph_add_edge.c`](./2-graph_add_edge.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 2-main.c 0-graph_create.c 1-graph_add_vertex.c 2-graph_add_edge.c graph_display.c -o 2-graph_add_edge`


### :white_check_mark: 3. Delete graph
Write a function that completely deletes a graph

* Prototype: `void graph_delete(graph_t *graph);`
* Your function must delete all the vertices and edges of the graph, and the graph itself

File(s): [`3-graph_delete.c`](./3-graph_delete.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 3-main.c 0-graph_create.c 1-graph_add_vertex.c 2-graph_add_edge.c 3-graph_delete.c graph_display.c -o 3-graph_delete`


### :white_check_mark: 4. Depth-first traversal
Write a function that goes through a graph using the depth-first algorithm.

* Prototype: `size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));`
* Where:
    * `graph` is a pointer to the graph to traverse. The traversal must start from the first vertex in the vertices list.
    * `action` is a pointer to a function to be called for each visited vertex, its parameters are:
        * `v` -> A `const` pointer to the visited vertex
        * `depth` -> The depth of `v`, from the starting vertex
* Your function must return the biggest vertex depth (See example), or 0 on failure

File(s): [`4-depth_first_traverse.c`](./4-depth_first_traverse.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 4-main.c 0-graph_create.c 1-graph_add_vertex.c 2-graph_add_edge.c 3-graph_delete.c 4-depth_first_traverse.c graph_display.c -o 4-depth_first_traverse`


### :white_check_mark: 5. Breadth-first traversal
Write a function that goes through a graph using the breadth-first algorithm.

* Prototype: `size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));`
* Where:
    * `graph` is a pointer to the graph to traverse. The traversal must start from the first vertex in the vertices list.
    * `action` is a pointer to a function to be called for each visited vertex, its parameters are:
        * `v` -> A `const` pointer to the visited vertex
        * `depth` -> The depth of `v`, fron the starting vertex
* Your function must return the biggest vertex depth (See example), or 0 on failure

File(s): [`5-breadth_first_traverse.c`](./5-breadth_first_traverse.c)\
Compiled: `gcc -Wall -Wextra -Werror -pedantic 5-main.c 0-graph_create.c 1-graph_add_vertex.c 2-graph_add_edge.c 3-graph_delete.c 5-breadth_first_traverse.c graph_display.c -o 5-breadth_first_traverse`

---

## Student
* **Samuel Pomeroy** - [allelomorph](github.com/allelomorph)
