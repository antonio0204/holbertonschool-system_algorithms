# (410) 0x03. C - Pathfinding
Specializations > System programming & Algorithm > Data structures and Algorithms

---

### Project author
Alexandre Gautier

### Assignment dates
05-18-2021 to 05-28-2021

### Description
Introduction to Pathfinding: its most common applications, backtracking as a class of solutions and how it can be less desireable in graph traversal, Dijkstra’s algorithm and its main weakness, finally the A* algorithm, and its improvements over Dijkstra’s.

### Provided file(s) and data structures
* [`graphs.h`](./graphs.h)
* [`queues.h`](./queues.h)
* [`libgraphs.a`](./libgraphs.a)
* [`libqueues.a`](./libqueues.a)
* definition of `point_t` for [`pathfinding.h`](./pathfinding.h)
* default test mains: [`0-main.c`](./tests/0-main.c) [`1-main.c`](./tests/1-main.c) [`2-main.c`](./tests/2-main.c) [`2-main_1.c`](./tests/2-main_1.c) [`100-main.c`](./tests/100-main.c) [`100-main_1.c`](./tests/100-main_1.c)

---

## Mandatory Tasks

### :white_check_mark: 0. Backtracking - Array
Write a function that searches for the first path from a starting point to a target point within a two-dimensional array.

* Prototype: `queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target);`
* Where:
    * `map` is the pointer to a read-only two-dimensional array
        * 0 represents a walkable cell
        * 1 represents a blocked cell
    * `rows` and `cols` are respectively the number of rows and columns of map
    * `start` stores the coordinates of the starting point
    * `target` stores the coordinates of the target point
* Your function must return a queue, in which each node is a point in the path from `start` to `target`
* You’ll have to use recursive backtracking to find the first working path from `start` to `target`
* For each visited cell, you’ll have to explore neighbour cells in the following order:
    * `RIGHT`
    * `BOTTOM`
    * `LEFT`
    * `TOP`
* You’ll have to print each visited cell's coordinates

File(s): [`0-backtracking_array.c`](./0-backtracking_array.c)\
Compiled: `gcc -o 0-backtracking_array -Wall -Wextra -Werror -pedantic 0-main.c 0-backtracking_array.c -lqueues`

### :white_check_mark: 1. Backtracking - Graph
Write a function that searches for the first path from a starting point to a target point in a graph.

* Prototype: `queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);`
* Where:
    * `graph` is a pointer to the graph to go through
    * `start` is a pointer to the starting vertex
    * `target` is a pointer to the target vertex
* Your function must return a queue, in which each node is a `char *` corresponding to a vertex, forming a path from `start` to `target`
* You’ll have to use recursive backtracking to find the first working path from `start` to `target`
* You’ll have to print each visited vertex's `content`

File(s): [`1-backtracking_graph.c`](./1-backtracking_graph.c)\
Compiled: `gcc -o 1-backtracking_graph -Wall -Wextra -Werror -pedantic 1-main.c 1-backtracking_graph.c -lqueues -lgraphs`

### :white_check_mark: 2. Dijkstra's - Graph
Write a function that searches for the shortest path from a starting point to a target point in a graph.

* Prototype: `queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);`
* Where:
    * `graph` is a pointer to the graph to go through
    * `start` is a pointer to the starting vertex
    * `target` is a pointer to the target vertex
* Your function must return a queue, in which each node is a `char *` corresponding to a vertex, forming a path from start to target
* You’ll have to use Dijkstra’s algorithm to find the shortest path
* You’ll have to print each visited vertex's `content`

File(s): [`2-dijkstra_graph.c`](./2-dijkstra_graph.c)\
Compiled: `gcc -o 2-dijkstra_graph -Wall -Wextra -Werror -pedantic 2-main.c 2-dijkstra_graph.c -lqueues -lgraphs`\
`gcc -o 2-dijkstra_graph_1 -Wall -Wextra -Werror -pedantic 2-main_1.c 2-dijkstra_graph.c -lqueues -lgraphs`

## Advanced Tasks

### :white_check_mark: 3. A* - Graph
Write a function that searches for the shortest and fastest path from a starting point to a target point in a graph.

* Prototype: `queue_t *a_star_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);`
* Where:
    * `graph` is a pointer to the graph to go through
    * `start` is a pointer to the starting vertex
    * `target` is a pointer to the target vertex
* Your function must return a queue, in which each node is a `char *` corresponding to a vertex, forming a path from start to target
* You’ll have to use A* algorithm to find the shortest and fastest path, using the Euclidean distance to the target vertex as the heuristic
* You’ll have to print each visited vertex as in the example below
* You are allowed to use the math library `math.h`. Your code will be linked with the math library using `-lm`

File(s): [`100-a_star_graph.c`](./100-a_star_graph.c) [`euclideanDist.c`](./euclideanDist.c)\
Compiled: `gcc -o 100-a_star_graph -Wall -Wextra -Werror -pedantic 100-main.c 100-a_star_graph.c -lqueues -lgraphs -lm`\
`gcc -o 100-a_star_graph_1 -Wall -Wextra -Werror -pedantic 100-main_1.c 100-a_star_graph.c -lqueues -lgraphs -lm`

---

## Student
* **Samuel Pomeroy** - [allelomorph](github.com/allelomorph)
