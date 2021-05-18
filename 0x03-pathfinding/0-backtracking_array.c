#include "pathfinding.h"


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
	if (!map || !rows || !cols || !start || !target)
		return (NULL);
}
