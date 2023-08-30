/* Struct & function implementations for pacam_scene.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>

#include "pacam.h"
#include "ds.h"

// an object has a name, desc, and callback to invoke when clicked.
struct pacam_object
{
  char name[16];
  char desc[128];
  pacam_callback *on_click;
  void *data;
};

void pacam_object_free(void *ptr)
{
  pacam_object *object = (pacam_object *)ptr;
  // if there's a callback, free that.
  if (object->on_click != NULL)
  {
    free(object->on_click);
  }
  free(object);
}

pacam_object *pacam_new_object(pacam_game *game, char *name, char *desc, pacam_callback *callback)
{
  pacam_object *object = (pacam_object *)malloc(sizeof(pacam_object));
  strncpy(object->name, name, 16);
  strncpy(object->desc, desc, 128);
  object->on_click = callback;
  array_list_add(game->object_list, (void *)object);
  return object;
}

char *pacam_object_get_name(pacam_object *object)
{
  return object->name;
}

char *pacam_object_get_desc(pacam_object *object)
{
  return object->desc;
}

void *pacam_object_get_data(pacam_object *object)
{
  return object->data;
}

void pacam_object_interact(pacam_object *object)
{
}