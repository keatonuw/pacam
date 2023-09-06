/* Header file for common data structures.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.  */

#ifndef DS_H
#define DS_H

#define INIT_LIST_SIZE 10

typedef void (*dtor)(void *el);

typedef struct array_list array_list;

array_list *array_list_alloc();

void array_list_free(array_list *list, dtor fn);

void *array_list_get(array_list *list, int i);

int array_list_size(array_list *list);

void array_list_add(array_list *list, void *el);

// point

typedef struct point point;

point *point_alloc(int x, int y);

void point_free(point *p);

int point_compare(point *point_a, point *point_b);

point *point_add(point *left, point *right);

int point_x(point *p);

int point_y(point *p);

#endif /* DS_H */