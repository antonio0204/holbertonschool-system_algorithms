#include "pathfinding.h"

#include <stdio.h>
/* malloc */
#include <stdlib.h>


int mapPointInQueue(queue_t *queue, point_t point)
{
	queue_node_t *temp = NULL;
	point_t *node_point = NULL;

	if (!queue || !queue->front || !queue->back)
		return (0);

	/*
	 * intersection with traversed path more likely to be later
	 * in list of visited points, so check in reverse order
	 */
	temp = queue->back;
	while (temp)
	{
		if (temp->ptr)
		{
			node_point = (point_t *)temp->ptr;
			if (node_point->x == point.x &&
			    node_point->y == point.y)
				return (1);
		}
		temp = temp->prev;
	}

	return (0);
}


void backtrackMaze(queue_t *visited, char **map, int rows, int cols, int curr_x, int curr_y,
		   const point_t *target)
{
	point_t *curr = NULL, next;
        int R = 0, D = 0, L = 0, U = 0;

	if (!visited || !map || !rows || !cols || !target)
		return;

	printf("Checking coordinates [%i, %i]\n", curr_x, curr_y);
/*
	printf("\t\tmap context: "
	       "R: map[%i][%i]:%c "
	       "D: map[%i][%i]:%c "
	       "L: map[%i][%i]:%c "
	       "U: map[%i][%i]:%c\n",
	       curr_y, curr_x + 1, curr_x + 1 < cols ? map[curr_y][curr_x + 1] + '0' : ' ',
	       curr_y + 1, curr_x, curr_y + 1 < rows ? map[curr_y + 1][curr_x] + '0' : ' ',
	       curr_y, curr_x - 1, curr_x - 1 >= 0 ? map[curr_y][curr_x - 1] + '0' : ' ',
	       curr_y - 1, curr_x, curr_y - 1 >= 0 ? map[curr_y - 1][curr_x] + '0' : ' '
		);
*/
	curr = malloc(sizeof(point_t));
	if (!curr)
		return;
	curr->x = curr_x;
	curr->y = curr_y;
	if (!queue_push_back(visited, (void *)curr))
	{
		free(curr);
		return;
	}

	if (curr_x == target->x && curr_y == target->y)
	{
		printf("Target found!\n");
		return;
	}

	/*RIGHT*/
	next.y = curr_y;
	next.x = curr_x + 1;
	if (curr_x + 1 < cols && /* not OOB? */
	    map[curr_y][curr_x + 1] == '0' && /* not wall? */
	    !mapPointInQueue(visited, next)/* not in current solution trunk? (prevent loops) */)
	{
		R = 1;
		backtrackMaze(visited, map, rows, cols, curr_x + 1, curr_y, target);
	}

	/*BOTTOM*/
	next.y = curr_y + 1;
	next.x = curr_x;
	if (curr_y + 1 < rows && /* not OOB? */
	    map[curr_y + 1][curr_x] == '0' && /* not wall? */
	    !mapPointInQueue(visited, next)/* not in current solution trunk? (prevent loops) */)

	{
		D = 1;
		backtrackMaze(visited, map, rows, cols, curr_x, curr_y + 1, target);
	}

	/*LEFT*/
	next.y = curr_y;
	next.x = curr_x - 1;
	if (curr_x - 1 >= 0 && /* not OOB? */
	    map[curr_y][curr_x - 1] == '0' && /* not wall? */
	    !mapPointInQueue(visited, next)/* not in current solution trunk? (prevent loops) */)   
	{
		L = 1;
		backtrackMaze(visited, map, rows, cols, curr_x - 1, curr_y, target);
	}

	/*TOP*/
	next.y = curr_y - 1;
	next.x = curr_x;
	if (curr_y - 1 >= 0 && /* not OOB? */
	    map[curr_y - 1][curr_x] == '0' && /* not wall? */
	    !mapPointInQueue(visited, next)/* not in current solution trunk? (prevent loops) */)
	{
		U = 1;
		backtrackMaze(visited, map, rows, cols, curr_x, curr_y - 1, target);
	}

	if (!R && !D && !L && !U)
		printf("Dead end!\n");
}

/**
  * backtracking_array -  searches for the first path from a starting point to
  *   a target point within a two-dimensional array
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
	queue_t *visited = NULL;
	queue_node_t *temp = NULL, *remove = NULL;
	point_t *tmp_pt = NULL, *prv_pt = NULL;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	visited = queue_create();
	if (!visited)
		return (NULL);

	backtrackMaze(visited, map, rows, cols, start->x, start->y, target);
	if (!visited->front || !visited->back)
		return (NULL);

	/* bactrack visited nodes to prune those not in solution */
	temp = visited->back;
	while (temp)
	{
		if (temp->prev && temp->prev->ptr)
		{
			tmp_pt = (point_t *)temp->ptr;
		        prv_pt = (point_t *)temp->prev->ptr;

			if (!((prv_pt->x == tmp_pt->x &&
			       (prv_pt->y == tmp_pt->y + 1 ||
				prv_pt->y == tmp_pt->y - 1)) ||
			      (prv_pt->y == tmp_pt->y &&
			       (prv_pt->x == tmp_pt->x + 1 ||
				prv_pt->x == tmp_pt->x - 1))))
			{
				remove = temp->prev;
				temp->prev = temp->prev->prev;
				temp->prev->next = temp;
				free(remove->ptr);
				free(remove);
			}
		}

		temp = temp->prev;
	}

	return (visited);
}
