/* Header file for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PACAM.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef PACAM_H
#define PACAM_H

/* Type representing a complete PACAM game. */
typedef struct pacam_game pacam_game;

/* Type representing a room in a PACAM game. */
typedef struct pacam_room pacam_room;

/* Type representing an interactive object in a PACAM game. */
typedef struct pacam_interactable pacam_interactable;

/* Type representing a text box in PACAM. */
typedef struct pacam_dialogue pacam_dialogue;

/* Function type for callbacks used in interactable objects. */
typedef void (*pacam_callback)();

/* Function type for conditional check. Receives data pointer from pacam_game,
    return 0 if the condition should fail and non-zero if condition should pass */
typedef int (*pacam_cond)(void *data);

/* Add a connection between two rooms. */
void pacam_add_hall(pacam_room *src, pacam_room *dest);

/* Add a conditional connection between two rooms. */
void pacam_add_cond_hall(pacam_room *src, pacam_room *dest, pacam_interactable *trigger, pacam_cond fn);

#endif /* PACAM_H */