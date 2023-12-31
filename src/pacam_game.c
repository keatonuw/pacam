/* Implementation game struct and functions for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <stdio.h>

#include "pacam.h"
#include "ds.h"

// game is current scene, with a list of scenes & objects tracked for memory mgmt
struct pacam_game
{
  pacam_scene *cur_scene;
  array_list *scene_list;
  array_list *object_list;
};

pacam_game *pacam_init()
{
  pacam_game *game = (pacam_game *)malloc(sizeof(pacam_game));
  game->object_list = array_list_alloc();
  game->scene_list = array_list_alloc();
  return game;
}

void pacam_close(pacam_game *game)
{
  array_list_free(game->scene_list, pacam_scene_free);
  array_list_free(game->object_list, pacam_object_free);
  free(game);
}

pacam_scene *pacam_get_cur_scene(pacam_game *game)
{
  return game->cur_scene;
}

void pacam_set_cur_scene(pacam_game *game, pacam_scene *scene)
{
  game->cur_scene = scene;
}

void pacam_register_scene(pacam_game *game, pacam_scene *scene)
{
  array_list_add(game->scene_list, (void *)scene);
}

void pacam_register_object(pacam_game *game, pacam_object *object)
{
  array_list_add(game->object_list, (void *)object);
}

void pacam_for_all_scenes(pacam_game *game, pacam_scene_callback fn)
{
  for (int i = 0; i < array_list_size(game->scene_list); i++)
  {
    fn((pacam_scene *)array_list_get(game->scene_list, i));
  }
}

void pacam_for_all_objects(pacam_game *game, pacam_object_callback fn)
{
  for (int i = 0; i < array_list_size(game->object_list); i++)
  {
    fn((pacam_object *)array_list_get(game->object_list, i));
  }
}