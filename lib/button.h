#ifndef _BUTTON_H
#define _BUTTON_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct SDLButton
{
  int16_t x;
  int16_t y;
  int64_t radius;
  uint16_t width;
  uint16_t height;
  uint8_t padding;
  const char* backgroundColor;

  const char* text;
  const char* textColor;

  bool isHovered;
  const char* hoverText;
  const char* hoverTextColor;
  const char* hoverBackgroundColor;

  const char* borderColor;
  BorderStyle borderStyle;
  uint8_t borderDefaultWidth;
  uint8_t borderDefaultHeight;
} Button;

int createButton(SDL_Renderer* renderer, TTF_Font* font, Button button);

// handlers
//void (*onHoverHandler)(void);
//void (*onXChangeHandler)(int16_t);
//void (*onYChangeHandler)(int16_t);
//void (*onWidthChangeHandler)(uint16_t);
//void (*onHeightChangeHandler)(uint16_t);

//Node nodes[2];
//int selectedNode = -1;  // -1 indicates no node is currently selected
//void generateNodes();

#endif
