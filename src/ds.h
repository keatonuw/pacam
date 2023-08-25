/* Header file for common data structures.

Copyright (C) 2023 Keaton Kowal

PACAM is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PACAM.  If not, see <https://www.gnu.org/licenses/>.  */

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