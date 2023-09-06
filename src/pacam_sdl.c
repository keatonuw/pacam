/* Toy implementation for PACAM library.

Copyright (C) 2023 Keaton Kowal

PACAM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>

#include "pacam.h"
#include "pacam_sdl.h"
#include "ds.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 480

/*
  Holds the SDL window & renderer.
*/

void free_texture(void *texture)
{
  SDL_DestroyTexture(texture);
}

v_scene *pacam_new_v_scene(pacam_game *game, char *name, char *desc,
                           SDL_Texture *texture)
{
  return (v_scene *)pacam_new_scene(game, name, desc, (void *)texture, free_texture);
}

v_scene *pacam_v_scene(pacam_window *window, char *name, char *desc, char *texture_filename)
{
  SDL_Texture *text = IMG_LoadTexture(window->renderer, texture_filename);

  return pacam_new_v_scene(window->game, name, desc, text);
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
  struct v_obj_data *data = (struct v_obj_data *)malloc(sizeof(struct v_obj_data));
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
                             pacam_callback *callback, SDL_Texture *texture, point *p)
{
  return pacam_new_object(game, name, desc, (void *)v_obj_data_alloc(texture, p), v_obj_data_free, callback);
}

v_object *pacam_v_object(pacam_window *window, char *name, char *desc,
                         pacam_callback *callback, char *texture_filename, int x, int y)
{
  SDL_Texture *text = IMG_LoadTexture(window->renderer, texture_filename);
  point p = {x, y};
  return pacam_new_v_object(window->game, name, desc, callback, text, &p);
}

SDL_Texture *pacam_v_object_set_texture(v_object *obj, SDL_Texture *texture)
{
  SDL_Texture *old = (SDL_Texture *)pacam_object_get_data((pacam_object *)obj);
  pacam_object_set_data((pacam_object *)obj, (void *)texture);
  return old;
}

void pacam_v_obj_click(v_object *obj, point *click)
{
  // get bounding points
  int x_left, y_top, x_right, y_bottom;
  struct v_obj_data *data = (struct v_obj_data *)pacam_object_get_data((pacam_object *)obj);
  x_left = point_x(&data->p);
  y_top = point_y(&data->p);
  SDL_QueryTexture(data->texture, NULL, NULL, &x_right, &y_bottom);
  x_right += x_left;
  y_bottom += y_top;

  // if click is inside of rectangle defined by
  // a top left object point corner and bottom right
  // point + (w,h), invoke obj's callback.
  if (point_x(click) >= x_left && point_x(click) <= x_right)
  {
    if (point_y(click) >= y_top && point_y(click) <= y_bottom)
    {
      pacam_object_interact((pacam_object *)obj);
    }
  }
  // otherwise, noop.
}

int handle_mouse_click(pacam_game *game, int x, int y)
{
  point p = {x, y};

  pacam_scene *scene = pacam_get_cur_scene(game);
  for (int i = 0; i < pacam_scene_num_objects(scene); i++)
  {
    pacam_v_obj_click((v_object *)pacam_scene_get_ith_object(scene, i), &p);
  }

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
      handle_mouse_click(game, mouse_event.x, mouse_event.y);
      break;
    default:
      break;
    }
  }
}

void draw_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void prepare_scene(pacam_window *app)
{
  SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
  SDL_RenderClear(app->renderer);

  pacam_game *game = app->game;
  pacam_scene *cur_scene = pacam_get_cur_scene(game);
  if (cur_scene == NULL)
  {
    return;
  }

  draw_texture(app->renderer, (SDL_Texture *)pacam_scene_get_data(cur_scene), 0, 0);
  for (int i = 0; i < pacam_scene_num_objects(cur_scene); i++)
  {
    struct v_obj_data *data = (struct v_obj_data *)pacam_object_get_data(pacam_scene_get_ith_object(cur_scene, i));
    draw_texture(app->renderer, data->texture, data->p.x, data->p.y);
  }
}

void present_scene(pacam_window *app)
{
  SDL_RenderPresent(app->renderer);
}

void pacam_run_sdl(pacam_game *game, setup_callback game_fn)
{
  pacam_window app;
  memset(&app, 0, sizeof(pacam_window));

  init_SDL(&app);

  app.game = game;

  /* Create scenes & objects at this point - callback? */
  game_fn(&app);

  while (1)
  {
    prepare_scene(&app);

    do_input(game);

    present_scene(&app);

    SDL_Delay(16);
  }

  return;
}