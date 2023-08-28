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

// void dtor_no_op(void *el) {}

array_list *array_list_alloc();

void array_list_free(array_list *list, dtor fn);

void *array_list_get(array_list *list, int i);

int array_list_size(array_list *list);

void array_list_add(array_list *list, void *el);

#endif /* DS_H */