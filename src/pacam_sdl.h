/* Header file for PACAM library's interactions with SDL.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#ifndef PACAM_SDL_H
#define PACAM_SDL_H

#include "SDL.h"

#include "ds.h"
#include "pacam.h"

//===========================================================================//
// scene wrapper functions
//===========================================================================//

/*
  SDL-backed "visual" pacam_scene. Just an alias for stricter access to the data
  ptr, as its used to store the SDL texture.
*/
typedef pacam_scene v_scene;

/*
  Create a new scene with the given SDL texture as a background image.
*/
v_scene *pacam_new_v_scene(pacam_game *game, char *name, char *desc,
                           SDL_Texture *texture);

/*
  Set the texture. The old texture is returned.
*/
SDL_Texture *pacam_v_scene_set_texture(v_scene *scene, SDL_Texture *texture);

//===========================================================================//
// object wrapper functions
//===========================================================================//

typedef pacam_object v_object;

/*
  Create a new SDL-backed "visual" object.
*/
v_object *pacam_new_v_object(pacam_game *game, char *name, char *desc,
                             SDL_Texture *data, point *p);

/*
  Set the texture, and return the old texture.
*/
SDL_Texture *pacam_v_object_set_texture(v_object *obj, SDL_Texture *texture);

/*
  Handle a mouse click event at point click. If this click collided with the v_object,
  invoke its callback.
*/
void pacam_v_obj_click(v_object obj, point *click);

#endif /* PACAM_SDL_H */