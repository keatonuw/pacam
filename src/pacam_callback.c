/* Struct & function implementations for pacam_scene.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdlib.h>

#include "pacam.h"
#include "ds.h"

// psuedo-closure struct. a callback has a function to invoke, and
// some data that the invoked function can use.
struct pacam_callback
{
  pacam_game *game;
  pacam_callback_handler fn;
  void *data;
  dtor data_dtor;
};

pacam_callback *create_callback(pacam_game *game,
                                pacam_callback_handler handler,
                                void *data, dtor data_dtor)
{
  pacam_callback *callback = (pacam_callback *)
      malloc(sizeof(pacam_callback));
  callback->game = game;
  callback->fn = handler;
  callback->data = data;
  return callback;
}

void pacam_call(pacam_callback *callback)
{
  callback->fn(callback->game, callback->data);
}

//===========================================================================//

void pc_handle_scene(pacam_game *game, void *data)
{
  pacam_scene *scene = (pacam_scene *)data;
  pacam_set_cur_scene(game, scene);
}

pacam_callback *pc_switch_scene(pacam_game *game, pacam_scene *scene)
{
  return create_callback(game, pc_handle_scene, (void *)scene, dtor_no_op);
}
