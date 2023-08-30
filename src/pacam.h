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
// pacam_scene_functions
//===========================================================================//

void pacam_scene_free(void *scene);

/*
  Create a new scene with the given name and desc, then add it to the game.
*/
pacam_scene *pacam_new_scene(pacam_game *game, char *name, char *desc, void *data);

/*
  Create a simple scene with no data contained in it, only objects, a name, and desc.
*/
pacam_scene *pacam_new_scene_base(pacam_game *game, char *name, char *desc);

/*
  Set the data field for a scene. Note that the scene's data_dtor is not
  changed. Therefore, the same dtor will be invoked when cleaning the new
  data, so this dtor should be prepared to handle whatever data really is,
  in memory.
*/
void pacam_scene_set_data(pacam_scene *scene, void *data);

/*
  Add an object to the scene.
*/
void pacam_scene_add_object(pacam_scene *scene, pacam_object *object);

/*
  Get the name of a scene.
*/
char *pacam_scene_get_name(pacam_scene *scene);

/*
  Get the desc of a scene.
*/
char *pacam_scene_get_desc(pacam_scene *scene);

/*
  Get the data of a scene.
*/
void *pacam_scene_get_data(pacam_scene *scene);

/*
  Call fn for each object in the scene.
*/
void *pacam_scene_for_each_object(pacam_scene *scene, pacam_object_callback fn);

//===========================================================================//
// pacam_object_functions
//===========================================================================//

void pacam_object_free(void *object);

// -----------------------

pacam_scene *pacam_new_scene(pacam_game *game);

void pacam_add_object(pacam_game *game, pacam_scene *target, pacam_object *object, pacam_callback *callback);

#endif /* PACAM_H */