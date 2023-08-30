/* Header file for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#ifndef PACAM_H
#define PACAM_H

#define NAME_MAX_LEN 16
#define DESC_MAX_LEN 128

/* Type representing a PACAM game */
typedef struct pacam_game pacam_game;

/* Type representing a scene in a PACAM game. */
typedef struct pacam_scene pacam_scene;

/* Type representing an interactive object in a PACAM game. */
typedef struct pacam_object pacam_object;

/* Function type for callbacks used in interactable objects. */
typedef struct pacam_callback pacam_callback;

typedef void (*pacam_callback_handler)(pacam_game *game, pacam_callback *data);

typedef void (*pacam_scene_callback)(pacam_scene *scene);

typedef void (*pacam_object_callback)(pacam_object *scene);

void dtor_no_op(void *el);

//===========================================================================//
// pacam_game functions
//===========================================================================//

/*
  PACAM initialization function. This returns a pacam_game* which is used
  to manage the allocations needed while running the game, and should be
  called before building a game.
*/
pacam_game *pacam_init();

/*
  Closes a pacam_game and frees up all associated memory. Call at the end
  of your game to clean up!
*/
void pacam_close(pacam_game *game);

/*
  Runs a PACAM game. Call to start your adventure!
*/
void pacam_run(pacam_game *game, pacam_scene *init_scene);

/*
  Sets the current scene displayed in a PACAM game.
*/
void pacam_set_cur_scene(pacam_game *game, pacam_scene *scene);

/*
  Register a scene in a game.
*/
void pacam_register_scene(pacam_game *game, pacam_scene *scene);

/*
  Register an object in a game.
*/
void pacam_register_object(pacam_game *game, pacam_object *object);

/*
  Call fn for each scene in game.
*/
void pacam_for_all_scenes(pacam_game *game, pacam_scene_callback fn);

/*
  Call fn for each object in game.
*/
void pacam_for_all_objects(pacam_game *game, pacam_object_callback fn);

//===========================================================================//

void pacam_scene_free(void *scene);

void pacam_object_free(void *object);

// -----------------------

pacam_scene *pacam_new_scene(pacam_game *game);

void pacam_add_object(pacam_game *game, pacam_scene *target, pacam_object *object, pacam_callback *callback);

#endif /* PACAM_H */