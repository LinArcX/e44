#include "app.h"
#include "lblAdd.h"
#include "btnAdd.h"
#include "../lib/util.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

App* app;

//------------- Initialization -------------//
void initApp()
{
  app = malloc(sizeof(App));

  app->window = NULL;
  app->renderer = NULL;

  app->font = NULL;
  app->fontName = "monaco.ttf"; //FantasqueSansMono
  app->fontSize = 14;

  app->x = 0;
  app->y = 0;
  app->mouse_x = 0;
  app->mouse_y = 0;
  app->width = 800;
  app->height = 600;
  app->backgroundColor = "#757575";

  app->hoverHandler = NULL;
  app->leftClickUpHandler = NULL;
  app->leftClickDownHandler = NULL;
  app->rightClickUpHandler = NULL;
  app->rightClickDownHandler = NULL;
  app->widgetCreatorHandler = NULL;
}

int initFont()
{
  if (TTF_Init() < 0) {
      printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  app->font = TTF_OpenFont(app->fontName, app->fontSize);
  if (app->font == NULL) {
      printf("Font loading failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  // Enable text anti-aliasing
  if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
  {
    printf("Warning: Failed to enable anti-aliasing\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int initialize()
{
  initApp();
  initLblAdd();
  initBtnAdd();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->window= SDL_CreateWindow("Galaxy of Nodes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->width, app->height, SDL_WINDOW_SHOWN);
  if (app->window == NULL) {
      printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->renderer= SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (app->renderer == NULL) {
      printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  if(EXIT_FAILURE == initFont())
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

//------------- Rendering -------------//
void render()
{
  int quit = 0;
  SDL_Event e;

  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
          quit = 1;
      }
      else if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        app->mouse_x = e.button.x;
        app->mouse_y = e.button.y;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
          callFunctions(app->leftClickDownHandler);
        }
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
          callFunctions(app->rightClickDownHandler);
        }
      }
      else if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_F4 && (e.key.keysym.mod & KMOD_ALT))
        {
          quit = 1;
        }
        if (e.key.keysym.sym == SDLK_q)
        {
          quit = 1;
        }
      }
      else if (e.type == SDL_MOUSEBUTTONUP)
      {
        app->mouse_x = e.button.x;
        app->mouse_y = e.button.y;

        if (e.button.button == SDL_BUTTON_LEFT)
        {
          callFunctions(app->leftClickUpHandler);
        }
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
          callFunctions(app->rightClickUpHandler);
        }
      }
      else if (e.type == SDL_MOUSEMOTION)
      {
        app->mouse_x = e.motion.x;
        app->mouse_y = e.motion.y;
        callFunctions(app->hoverHandler);
      }
    }

    uint8_t red, green, blue, alpha;
    hexToRGBA(app->backgroundColor, &red, &green, &blue, &alpha);

    SDL_SetRenderDrawColor(app->renderer, red, green, blue, alpha);
    SDL_RenderClear(app->renderer);

    callFunctions(app->widgetCreatorHandler);

    SDL_RenderPresent(app->renderer);
    // we need this delay, unless we'll face a high cpu usage. a number between 60 and 100 is ok.
    SDL_Delay(60);
  }
}

//------------- CleanUp -------------//
void cleanup()
{
  TTF_CloseFont(app->font);
  TTF_Quit();

  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_Quit();

  freeCallBackFunctionList(app->hoverHandler);
  freeCallBackFunctionList(app->leftClickDownHandler);
  freeCallBackFunctionList(app->leftClickUpHandler);
  freeCallBackFunctionList(app->rightClickDownHandler);
  freeCallBackFunctionList(app->rightClickUpHandler);
  freeCallBackFunctionList(app->widgetCreatorHandler);

  free(app);
  app = NULL;
}
