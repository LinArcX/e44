#ifndef _APP_H
#define _APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

int initialize();
void handleEvents();
void cleanup();

#endif
