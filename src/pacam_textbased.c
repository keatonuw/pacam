#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"
#include "pacam.h"

struct pacam_game
{
  pacam_scene *cur_scene;
  array_list *scene_list;
};

struct pacam_scene
{
  char name[16];
  char desc[128];
  array_list *object_list;
};

struct pacam_object
{
  char name[16];
  char desc[128];
  pacam_callback *on_click;
};

struct pacam_callback
{
  void (*fn)(pacam_callback *callback, pacam_game *game);
  void *data;
};

void pacam_object_free(void *ptr)
{
  pacam_object *object = (pacam_object *)ptr;
  if (object->on_click != NULL)
  {
    free(object->on_click);
  }
  free(object);
}

void pacam_scene_free(void *ptr)
{
  pacam_scene *scene = (pacam_scene *)ptr;
  array_list_free(scene->object_list, pacam_object_free);
  free(scene);
}

pacam_game *pacam_init()
{
  pacam_game *game = (pacam_game *)malloc(sizeof(pacam_game));
  game->scene_list = array_list_alloc();
  return game;
}

void pacam_close(pacam_game *game)
{
  array_list_free(game->scene_list, pacam_scene_free);
  free(game);
}

pacam_scene *pacam_new_scene(pacam_game *game)
{
  pacam_scene *scene = (pacam_scene *)malloc(sizeof(pacam_scene));
  scene->object_list = array_list_alloc();
  scene->name[0] = '\0';
  scene->desc[0] = '\0';
  array_list_add(game->scene_list, scene);
  return scene;
}

pacam_scene *pacam_text_scene(pacam_game *game, char *name, char *desc)
{
  pacam_scene *scene = pacam_new_scene(game);
  strncpy(scene->name, name, 16);
  strncpy(scene->desc, desc, 128);
  return scene;
}

pacam_object *pacam_text_object(pacam_scene *scene, char *name, char *desc, pacam_callback *callback)
{
  pacam_object *object = (pacam_object *)malloc(sizeof(pacam_object));
  strncpy(object->name, name, 16);
  strncpy(object->desc, desc, 128);
  object->on_click = callback;
  array_list_add(scene->object_list, (void *)object);
  return object;
}

void pacam_print_scene(pacam_scene *scene)
{
  printf("Scene %s: %s\n  Objects:\n", scene->name, scene->desc);
  for (int i = 0; i < array_list_size(scene->object_list); i++)
  {
    pacam_object *e = (pacam_object *)array_list_get(scene->object_list, i);
    printf("%d.  %s: %s\n", i, e->name, e->desc);
  }
}

void pacam_run(pacam_game *game)
{
  while (game->cur_scene != NULL)
  {
    pacam_print_scene(game->cur_scene);

    pacam_object *object = NULL;
    int i = 0;
    while (object == NULL)
    {
      printf("Enter number of object to interact with: ");
      // parse int
      scanf("%d", &i);
      object = (pacam_object *)array_list_get(game->cur_scene->object_list, i);
    }
    // if valid, run callback for object
    object->on_click->fn(object->on_click, game);
    // loop :)
  }
}

void handle_switch_scene(pacam_callback *callback, pacam_game *game)
{
  game->cur_scene = (pacam_scene *)callback->data;
}

pacam_callback *switch_scene(pacam_scene *dest_scene)
{
  pacam_callback *fn = (pacam_callback *)malloc(sizeof(pacam_callback));
  fn->data = (void *)dest_scene;
  fn->fn = handle_switch_scene;
  return fn;
}

int main(int argc, char **argv)
{
  pacam_game *game = pacam_init();

  pacam_scene *entry_scene = pacam_text_scene(game, "test", "desc");
  pacam_scene *room_scene = pacam_text_scene(game, "room", "another desc");

  pacam_object *start_game_obj = pacam_text_object(entry_scene, "start", "interact to start!", switch_scene(room_scene));

  game->cur_scene = entry_scene;
  // pacam_print_scene(entry_scene);
  pacam_run(game);

  pacam_close(game);

  return EXIT_SUCCESS;
}
