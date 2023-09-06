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
  dtor data_dtor;
};

void pacam_scene_free(void *ptr)
{
  pacam_scene *scene = (pacam_scene *)ptr;
  array_list_free(scene->object_list, dtor_no_op);
  if (scene->data_dtor != NULL && scene->data != NULL)
  {
    scene->data_dtor((void *)scene->data);
  }
  free(scene);
}

// creates a new scene and adds it to game.
pacam_scene *pacam_new_scene(pacam_game *game, char *name, char *desc, void *data, dtor data_dtor)
{
  pacam_scene *scene = (pacam_scene *)malloc(sizeof(pacam_scene));
  scene->object_list = array_list_alloc();
  strncpy(scene->name, name, 16);
  strncpy(scene->desc, desc, 128);
  scene->data = data;
  scene->data_dtor = data_dtor;
  pacam_register_scene(game, scene);
  return scene;
}

pacam_scene *pacam_new_scene_base(pacam_game *game, char *name, char *desc)
{
  return pacam_new_scene(game, name, desc, NULL, NULL);
}

void pacam_scene_set_data(pacam_scene *scene, void *data)
{
  scene->data = data;
}

void pacam_scene_add_object(pacam_scene *scene, pacam_object *object)
{
  array_list_add(scene->object_list, object);
}

pacam_object *pacam_scene_get_object(pacam_scene *scene, int i)
{
  return array_list_get(scene->object_list, i);
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

void pacam_scene_for_each_object(pacam_scene *scene, pacam_object_callback fn)
{
  for (int i = 0; i < array_list_size(scene->object_list); i++)
  {
    fn((pacam_object *)array_list_get(scene->object_list, i));
  }
}

int pacam_scene_num_objects(pacam_scene *scene)
{
  return array_list_size(scene->object_list);
}

pacam_object *pacam_scene_get_ith_object(pacam_scene *scene, int i)
{
  return (pacam_object *)array_list_get(scene->object_list, i);
}