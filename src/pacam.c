/* Implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>
#include <stdio.h>

#include "pacam.h"
#include "pacam_sdl.h"
#include "ds.h"

void dtor_no_op(void *el) {}

void build_game(pacam_window *window)
{
  v_scene *menu = pacam_v_scene(window, "menu", "welcome!", "resources/menu_background.png");
  v_scene *room = pacam_v_scene(window, "room", "a dingy room...", "resources/programmer_art.png");

  v_object *start = pacam_v_object(window, "start button", "click to start", pc_switch_scene(window->game, room), "resources/button.png", 0, 0);
  v_object *exit = pacam_v_object(window, "exit", "click to exit", pc_switch_scene(window->game, NULL), "resources/button.png", 0, 30);
  v_object *back = pacam_v_object(window, "back", "return to menu", pc_switch_scene(window->game, menu), "resources/button.png", 0, 0);

  pacam_scene_add_object(menu, start);
  pacam_scene_add_object(menu, exit);
  pacam_scene_add_object(room, back);

  pacam_set_cur_scene(window->game, menu);
}

int main(int argc, char **argv)
{
  pacam_game *game = pacam_init();

  pacam_run_sdl(game, build_game);
  pacam_close(game);
  return EXIT_SUCCESS;
}