#ifndef _APP_H
#define _APP_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct SDLApp
{
  TTF_Font* font;
  SDL_Window* window;
  SDL_Renderer* renderer;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
}App;

extern App* app;

int initialize();
void handleEvents();
void cleanup();

#endif
