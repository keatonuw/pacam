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

void print_object(pacam_object *object)
{
  printf("  %s: %s\n", pacam_object_get_name(object), pacam_object_get_desc(object));
}

void print_scene(pacam_scene *scene)
{
  printf("\nScene: %s: %s\n", pacam_scene_get_name(scene), pacam_scene_get_desc(scene));
  pacam_scene_for_each_object(scene, print_object);
}

void pacam_run(pacam_game *game, pacam_scene *init_scene)
{
  game->cur_scene = init_scene;
  while (game->cur_scene != NULL)
  {
    print_scene(game->cur_scene);

    pacam_object *object = NULL;
    int i = 0;
    while (object == NULL)
    {
      printf("Enter number of object to interact with: ");
      scanf("%d", &i);
      object = (pacam_object *)pacam_scene_get_object(game->cur_scene, i);
    }
    pacam_object_interact(object);
  }
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