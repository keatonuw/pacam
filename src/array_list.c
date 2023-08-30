/* Array-based list implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <stdio.h>

#include "ds.h"

struct array_list
{
  void **array;
  int size;
  int capacity;
};

array_list *array_list_alloc()
{
  array_list *list = (array_list *)malloc(sizeof(array_list));
  list->capacity = INIT_LIST_SIZE;
  list->size = 0;
  list->array = malloc(sizeof(void *) * INIT_LIST_SIZE);
  return list;
}

void array_list_free(array_list *list, dtor fn)
{
  for (int i = 0; i < array_list_size(list); i++)
  {
    fn(array_list_get(list, i));
  }
  free(list->array);
  free(list);
}

void *array_list_get(array_list *list, int i)
{
  if (i >= list->size)
  {
    return NULL;
  }
  return *(list->array + i);
}

int array_list_size(array_list *list)
{
  return list->size;
}

void array_list_add(array_list *list, void *el)
{
  if (list->size == list->capacity)
  {
    // resize array
    list->capacity *= 2;
    list->array = realloc(list->array, sizeof(void *) * list->capacity * 2);
  }
  *(list->array + list->size) = el;
  list->size++;
}
