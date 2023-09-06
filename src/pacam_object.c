/* Struct & function implementations for pacam_scene.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <string.h>

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
    free_callback(object->on_click);
  }
  free(object);
}

pacam_object *pacam_new_object(pacam_game *game, char *name, char *desc, void *data, pacam_callback *callback)
{
  pacam_object *object = (pacam_object *)malloc(sizeof(pacam_object));
  strncpy(object->name, name, 16);
  strncpy(object->desc, desc, 128);
  object->data = data;
  object->on_click = callback;
  pacam_register_object(game, object);
  return object;
}

pacam_object *pacam_new_object_base(pacam_game *game, char *name, char *desc)
{
  return pacam_new_object(game, name, desc, NULL, pc_no_op(game));
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

void pacam_object_set_data(pacam_object *object, void *data)
{
  object->data = data;
}

void pacam_object_interact(pacam_object *object)
{
  pacam_call(object->on_click);
}