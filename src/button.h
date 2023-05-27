#ifndef _BUTTON_H
#define _BUTTON_H

#include <SDL2/SDL.h>

typedef struct SDLButton
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
  const char* hoverTextColor;
  const char* hoverBackgroundColor;

  // handlers
  //void (*onHoverHandler)(void);
  //void (*onXChangeHandler)(int16_t);
  //void (*onYChangeHandler)(int16_t);
  //void (*onWidthChangeHandler)(uint16_t);
  //void (*onHeightChangeHandler)(uint16_t);
} Button;

int createButton(Button button);

//Node nodes[2];
//int selectedNode = -1;  // -1 indicates no node is currently selected
//void generateNodes();

#endif
