#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"
#include "pacam.h"

/*
  Global State: room
  Room has its own state, represented by the state of all interactibles
*/

struct pacam_game
{
  pacam_room *start_room;
};

struct pacam_room
{
  char name[16];
  char desc[128];
  array_list *interactables;
  array_list *connected_rooms;
};

struct pacam_interactable
{
  pacam_callback on_interact;
  char name[16];
  char desc[128];
};

struct pacam_dialogue
{
};

pacam_interactable *pacam_make_interactable()
{
  pacam_interactable *interact = (pacam_interactable *)malloc(sizeof(pacam_room));
  return interact;
}

pacam_room *pacam_make_room(char *name, char *desc)
{
  pacam_room *room = (pacam_room *)malloc(sizeof(pacam_room));
  room->interactables = array_list_alloc();
  room->connected_rooms = array_list_alloc();
  strncpy(room->name, name, 16);
  strncpy(room->desc, desc, 128);
  return room;
}

void pacam_free_room(pacam_room *room)
{
  array_list_free(room->connected_rooms, pacam_free_room);
}

void pacam_add_hall(pacam_room *src, pacam_room *dest)
{
  array_list_add(src->connected_rooms, (void *)dest);
}

void pacam_add_interactable(pacam_room *room, pacam_interactable *item)
{
  array_list_add(room->interactables, (void *)item);
}

void pacam_print_room(pacam_room *room)
{
  printf("%s: %s\nInteractables:\n", room->name, room->desc);
  for (int i = 0; i < array_list_size(room->interactables); i++)
  {
    pacam_interactable *e = (pacam_interactable *)array_list_get(room->interactables, i);
    printf("%d. %s: %s\n", i, e->name, e->desc);
  }
  printf("Connected Rooms:\n");
  for (int i = 0; i < array_list_size(room->connected_rooms); i++)
  {
    pacam_room *e = (pacam_room *)array_list_get(room->connected_rooms, i);
    printf("%d. %s: %s\n", i, e->name, e->desc);
  }
}

int main(int argc, char **argv)
{
  pacam_room *room = pacam_make_room("test", "this is a desc");
  pacam_print_room(room);
  pacam_free_room(room);
  return EXIT_SUCCESS;
}