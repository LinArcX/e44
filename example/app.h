#ifndef _APP_H
#define _APP_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct SDLApp
{
  SDL_Window* window;
  SDL_Renderer* renderer;

  TTF_Font* font;
  const char* fontName;
  uint8_t fontSize;

  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  const char* backgroundColor;
}App;

extern App* app;

int initialize();
void handleEvents();
void cleanup();

#endif
