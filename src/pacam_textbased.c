/* Toy implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"
#include "pacam.h"

/*
  Toy implementation of pacam.h which demonstrates using the interface
  for a text-based adventure type of game.
*/
void print_object(pacam_object *object)
{
  printf("  %s: %s\n", pacam_object_get_name(object), pacam_object_get_desc(object));
}

void print_scene(pacam_scene *scene)
{
  printf("\nScene: %s: %s\n", pacam_scene_get_name(scene), pacam_scene_get_desc(scene));
  pacam_scene_for_each_object(scene, print_object);
}
/*
void pacam_run(pacam_game *game, pacam_scene *init_scene)
{
  pacam_set_cur_scene(game, init_scene);
  while (pacam_get_cur_scene(game) != NULL)
  {
    print_scene(pacam_get_cur_scene(game));

    pacam_object *object = NULL;
    int i = 0;
    while (object == NULL)
    {
      printf("Enter number of object to interact with: ");
      scanf("%d", &i);
      object = (pacam_object *)pacam_scene_get_object(pacam_get_cur_scene(game), i);
    }
    pacam_object_interact(object);
  }
}
*/