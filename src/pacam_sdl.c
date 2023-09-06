/* Toy implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#include "ds.h"
#include "pacam.h"
#include "pacam_sdl.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 480

/*
  Holds the SDL window & renderer.
*/
typedef struct pacam_window pacam_window;

struct pacam_window
{
  SDL_Renderer *renderer;
  SDL_Window *window;
};

void free_texture(void *texture)
{
  SDL_DestroyTexture(texture);
}

v_scene *pacam_new_v_scene(pacam_game *game, char *name, char *desc,
                           SDL_Texture *texture)
{
  pacam_new_scene(game, name, desc, (void *)texture, free_texture);
}

SDL_Texture *pacam_v_scene_set_texture(v_scene *scene, SDL_Texture *texture)
{
  SDL_Texture *old = (SDL_Texture *)pacam_scene_get_data((pacam_scene *)scene);
  pacam_scene_set_data((pacam_scene *)scene, (void *)texture);
  return old;
}

struct v_obj_data
{
  SDL_Texture *texture;
  point p;
};

struct v_obj_data *v_obj_data_alloc(SDL_Texture *texture, point *p)
{
  struct v_obj_data *data = (v_obj_data *)malloc(sizeof(v_obj_data));
  data->texture = texture;
  data->p = *p;
  return data;
}

void v_obj_data_free(void *p)
{
  struct v_obj_data *data = (struct v_obj_data *)p;
  SDL_DestroyTexture(data->texture);
  free(data);
}

v_object *pacam_new_v_object(pacam_game *game, char *name, char *desc,
                             SDL_Texture *texture, point *p)
{
  return pacam_new_object(game, name, desc, (void *)v_obj_data_alloc(texture, p), v_obj_data_free);
}

SDL_Texture *pacam_v_object_set_texture(v_object *obj, SDL_Texture *texture)
{
  SDL_Texture *old = (SDL_Texture *)pacam_object_get_data((pacam_object *)obj);
  pacam_object_set_data((pacam_object *)obj, (void *)texture);
  return old;
}

void pacam_v_obj_click(v_object obj, point *click)
{
  // TODO
  // if click is inside of rectangle defined by
  // a top left object point corner and bottom right
  // point + (w,h), invoke obj's callback.
  // otherwise, noop.
}

// TODO: add a shortcut to create an object from a filename
// as opposed to a full SDL_Texture. Same for scenes.

int handle_mouse_click(pacam_game *game, int x, int y)
{

  return 0;
}

void init_SDL(pacam_window *app)
{
  int render_flags, window_flags;

  render_flags = SDL_RENDERER_ACCELERATED;
  window_flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL Init Error\n");
    exit(EXIT_FAILURE);
  }

  app->window = SDL_CreateWindow("PACAM", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, window_flags);
  if (!app->window)
  {
    printf("SDL Window Error\n");
    exit(EXIT_FAILURE);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app->renderer = SDL_CreateRenderer(app->window, -1, render_flags);
  if (!app->renderer)
  {
    printf("SDL Renderer Error\n");
    exit(EXIT_FAILURE);
  }
}

void do_input(pacam_game *game)
{
  SDL_Event event;
  SDL_MouseButtonEvent mouse_event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      pacam_close(game);
      exit(EXIT_SUCCESS);
      break;
    case SDL_MOUSEBUTTONUP:
      mouse_event = event.button;
      printf("click @ (%d, %d)\n", mouse_event.x, mouse_event.y);
      break;
    default:
      break;
    }
  }
}

void prepare_scene(pacam_window *app)
{
  SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
  SDL_RenderClear(app->renderer);
}

void present_scene(pacam_window *app)
{
  SDL_RenderPresent(app->renderer);
}

void pacam_run(pacam_game *game, pacam_scene *scene)
{
  pacam_window app;
  memset(&app, 0, sizeof(pacam_window));

  init_SDL(&app);

  while (1)
  {
    prepare_scene(&app);

    do_input(game);

    present_scene(&app);

    SDL_Delay(16);
  }

  return;
}