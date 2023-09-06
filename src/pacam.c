/* Implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "pacam.h"
#include "ds.h"

void dtor_no_op(void *el) {}

int main(int argc, char **argv)
{
  pacam_game *game = pacam_init();

  pacam_scene *menu = pacam_new_scene_base(game, "menu", "this is a main menu");
  pacam_scene *room = pacam_new_scene_base(game, "room", "this could be a room!");

  pacam_object *start = pacam_new_object(game, "start", "interact to start!", NULL, NULL, pc_switch_scene(game, room));
  pacam_object *exit = pacam_new_object(game, "exit", "interact to exit", NULL, NULL, pc_switch_scene(game, NULL));
  pacam_object *back = pacam_new_object(game, "back", "return to menu", NULL, NULL, pc_switch_scene(game, menu));
  pacam_object *pc = pacam_new_object(game, "computer", "look! a computer!", NULL, NULL, pc_no_op(game));

  pacam_scene_add_object(menu, start);
  pacam_scene_add_object(menu, exit);
  pacam_scene_add_object(room, back);
  pacam_scene_add_object(room, pc);

  pacam_run(game, menu);
  pacam_close(game);
  return EXIT_SUCCESS;
}