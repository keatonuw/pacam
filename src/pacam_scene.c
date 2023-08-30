/* Struct & function implementations for pacam_scene.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <string.h>

#include "pacam.h"
#include "ds.h"

// scene has a name, desc, and list of objects it contains. It also
// has a void* for data as needed in various usecases!
struct pacam_scene
{
  char name[NAME_MAX_LEN];
  char desc[DESC_MAX_LEN];
  array_list *object_list;
  void *data;
};

void pacam_scene_free(void *ptr)
{
  pacam_scene *scene = (pacam_scene *)ptr;
  array_list_free(scene->object_list, dtor_no_op);
  free(scene);
}

// creates a new scene and adds it to game.
pacam_scene *pacam_new_scene(pacam_game *game, char *name, char *desc)
{
  pacam_scene *scene = (pacam_scene *)malloc(sizeof(pacam_scene));
  scene->object_list = array_list_alloc();
  strncpy(object->name, name, 16);
  strncpy(object->desc, desc, 128);
  scene->data = NULL;
  pacam_register_scene(game, scene);
  return scene;
}

void pacam_scene_set_data(pacam_scene *scene, void *data)
{
  scene->data = data;
}

void pacam_scene_add_object(pacam_scene *scene, pacam_object *object)
{
  array_list_add(scene->object_list, object);
}

char *pacam_scene_get_name(pacam_scene *scene)
{
  return scene->name;
}

char *pacam_scene_get_desc(pacam_scene *scene)
{
  return scene->desc;
}

void *pacam_scene_get_data(pacam_scene *scene)
{
  return scene->data;
}

void *pacam_scene_for_each_object(pacam_scene *scene, pacam_object_callback fn)
{
  for (int i = 0; i < array_list_size(scene->object_list); i++)
  {
    fn((pacam_object *)array_list_get(scene->object_list, i));
  }
}