/* Header file for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#ifndef PACAM_H
#define PACAM_H

/* Type representing a PACAM game */
typedef struct pacam_game pacam_game;

/* Type representing a scene in a PACAM game. */
typedef struct pacam_scene pacam_scene;

/* Type representing an interactive object in a PACAM game. */
typedef struct pacam_object pacam_object;

/* Function type for callbacks used in interactable objects. */
typedef struct pacam_callback pacam_callback;

pacam_game *pacam_init();

void pacam_close(pacam_game *game);

pacam_scene *pacam_new_scene(pacam_game *game);

void pacam_add_object(pacam_game *game, pacam_scene *target, pacam_object *object, pacam_callback *callback);

void pacam_run(pacam_game *game);

#endif /* PACAM_H */