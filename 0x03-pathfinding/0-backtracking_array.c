#include "pathfinding.h"
/* malloc free */
#include <stdlib.h>
/* printf */
#include <stdio.h>


/**
  * backtrackPath - deletes record of path traveled from dead end back to last
  *   junction point
  *
  * @path: queue of visited map nodes, represents current backtracking
  *   solution candidate
  * @x: x coordinate of last junction point
  * @y: y coordinate of last junction point
  */
void backtrackPath(queue_t *path, int x, int y)
{
	queue_node_t *node = NULL;
	point_t *point = NULL, *pop = NULL;

	if (!path || !path->front || !path->back)
		return;

	node = path->front;
	if (node)
		point = (point_t *)node->ptr;

	while (node && point &&
	       !(point->x == x && point->y == y))
	{
		pop = (point_t *)dequeue(path);
		if (pop)
			free(pop);

		/*
		 * dequeue does not set path->back in the edge case of
		 * popping the head of a queue with only 1 member
		 */
		if (path->front == NULL)
			path->back = NULL;

		node = path->front;
		point = node ? (point_t *)(node->ptr) : NULL;
	}
}


/**
  * mapPointInQueue - traverses a queue with `void *` data points, assuming
  *   they are all castable to `point_t *`, to find a given map point
  *
  * @queue: queue to search
  * @point: coordinate data to search for
  * Return: first queue node containing matching data, or NULL on failure
  */
queue_node_t *mapPointInQueue(queue_t *queue, const point_t *point)
{
	queue_node_t *temp = NULL;
	point_t *node_point = NULL;

	if (!queue || !queue->front || !queue->back)
		return (NULL);

	temp = queue->front;
	while (temp)
	{
		if (temp->ptr)
		{
			node_point = (point_t *)temp->ptr;

			if (node_point->x == point->x &&
			    node_point->y == point->y)
				return (temp);
		}

		temp = temp->next;
	}

	return (NULL);
}


int isValidStep(queue_t *path, char **map, int rows, int cols,
		const point_t *step)
{
	if (!path || !map || !rows || !cols || !step)
		return (0);

	/* step out of map boundaries? */
	if (!((step->x >= 0 && step->x < cols) &&
	      (step->y >= 0 && step->x < rows)))
		return (0);

	/* step into wall? */
	if (map[step->y][step->x] == '1')
		return (0);

	/* step already in current solution trunk? (to prevent loops) */
	if (mapPointInQueue(path, step) != NULL)
		return (0);

	return (1);
}


/**
  * floodFillMaze - recursive helper to backtrack_array, searches for the
  *   first path from a starting point to a target point within a
  *   two-dimensional array using a recursive flood-fill in RDLU order
  *
  * @path: queue of nodes visited, represents current candidate solution
  * @map: pointer to a read-only two-dimensional array (0 represents a
  *   walkable cell, 1 represents a blocked cell)
  * @rows: count of rows in map
  * @cols: count of columns in map
  * @curr_x: x coordinate of current map cell
  * @curr_y: y coordinate of current map cell
  * @target: coordinates of the target point
  * Return: 1 if target found in current recursion frame, 0 if not or failure
  */
int floodFillMaze(queue_t *path, char **map, int rows, int cols,
		   int curr_x, int curr_y, const point_t *target)
{
	point_t *curr = NULL;
	point_t next_step[4] = { {+1, 0}, {0, +1}, {-1, 0}, {0, -1} };
	int i, target_found = 0;

	if (!path || !map || !rows || !cols || !target)
		return (0);

	for (i = 0; i < 4; i++)
	{
		next_step[i].x += curr_x;
		next_step[i].y += curr_y;
	}
	printf("Checking coordinates [%i, %i]\n", curr_x, curr_y);

	curr = malloc(sizeof(point_t));
	if (!curr)
		return (0);
	curr->x = curr_x;
	curr->y = curr_y;
	if (!queue_push_front(path, (void *)curr))
	{
		free(curr);
		return (0);
	}

	if (curr_x == target->x && curr_y == target->y)
		return (1);
	for (i = 0; !target_found && i < 4; i++)
	{
		if (isValidStep(path, map, rows, cols, next_step + i))
		{
			target_found |= floodFillMaze(path, map, rows, cols,
						      next_step[i].x,
						      next_step[i].y, target);
			if (!target_found)
				backtrackPath(path, curr_x, curr_y);
		}
	}

	return (target_found);
}


/**
  * backtracking_array -  searches for the first path from a starting point to
  *   a target point within a two-dimensional array using a recursive
  *   flood-fill in RDLU order
  *
  * @map: pointer to a read-only two-dimensional array (0 represents a
  *   walkable cell, 1 represents a blocked cell)
  * @rows: count of rows in map
  * @cols: count of columns in map
  * @start: coordinates of the starting point
  * @target: coordinates of the target point
  * Return: returns a queue in which each node is a point in the path from
  *   start to target, or NULL on failure
  */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path = NULL;
	queue_node_t *temp = NULL, *swap = NULL;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	if (!floodFillMaze(path, map, rows, cols, start->x, start->y, target))
	{
		/* assumes that free() can be used with node data */
		queue_delete(path);
		return (NULL);
	}

	/* reverse path */
	temp = path->front;
	swap = path->front;
	path->front = path->back;
	path->back = swap;
	while (temp)
	{
		swap = temp->next;
		temp->next = temp->prev;
		temp->prev = swap;
		temp = temp->prev;
	}

	return (path);
}
