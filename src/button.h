#ifndef _BUTTON_H
#define _BUTTON_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct SDLButton
{
  // properties
  int16_t x;
  int16_t y;
  int64_t radius;
  uint16_t width;
  uint16_t height;
  uint8_t padding;
  uint8_t borderDefaultWidth;
  uint8_t borderDefaultHeight;
  bool isHovered;
  const char* text;
  const char* textColor;
  const char* backgroundColor;
  const char* borderColor;
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
