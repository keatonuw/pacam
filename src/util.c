/* Util code for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <math.h>

#include "ds.h"

point *point_alloc(int x, int y)
{
  point *p = (point *)malloc(sizeof(point));
  p->x = x;
  p->y = y;
  return p;
}

void point_free(point *p)
{
  free(p);
}

int point_compare(point *point_a, point *point_b)
{
  // return dist between pts
  return 0;
}

point *point_add(point *left, point *right)
{
  return point_alloc(left->x + right->x, left->y + right->y);
}

int point_x(point *p)
{
  return p->x;
}

int point_y(point *p)
{
  return p->y;
}
