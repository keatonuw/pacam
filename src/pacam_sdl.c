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

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 480

typedef struct
{
  SDL_Renderer *renderer;
  SDL_Window *window;
} App;

void initSDL(App *app)
{
  int renderFlags, windowFlags;

  renderFlags = SDL_RENDERER_ACCELERATED;
  windowFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL Init Error\n");
    exit(EXIT_FAILURE);
  }

  app->window = SDL_CreateWindow("PACAM", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, windowFlags);
  if (!app->window)
  {
    printf("SDL Window Error\n");
    exit(EXIT_FAILURE);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app->renderer = SDL_CreateRenderer(app->window, -1, renderFlags);
  if (!app->renderer)
  {
    printf("SDL Renderer Error\n");
    exit(EXIT_FAILURE);
  }
}

void doInput(pacam_game *game)
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

void prepareScene(App *app)
{
  SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
  SDL_RenderClear(app->renderer);
}

void presentScene(App *app)
{
  SDL_RenderPresent(app->renderer);
}

void pacam_run(pacam_game *game, pacam_scene *scene)
{
  App app;
  memset(&app, 0, sizeof(App));

  initSDL(&app);

  while (1)
  {
    prepareScene(&app);

    doInput(game);

    presentScene(&app);

    SDL_Delay(16);
  }

  return;
}