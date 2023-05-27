#ifndef _LABEL_H
#define _LABEL_H

#include <SDL2/SDL.h>

typedef struct SDLLabel
{
  // properties
  int16_t x;
  int16_t y;
  int64_t radius;
  uint16_t width;
  uint16_t height;
  const char* text;
  const char* textColor;
  const char* backgroundColor;

  // handlers
  //void (*onHoverHandler)(void);
  //void (*onXChangeHandler)(int16_t);
  //void (*onYChangeHandler)(int16_t);
  //void (*onWidthChangeHandler)(uint16_t);
  //void (*onHeightChangeHandler)(uint16_t);
} Label;

int createLable(Label label);

#endif
