#ifndef _BUTTON_H
#define _BUTTON_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef enum _BorderStyle
{
  LEFT = 0,
  RIGHT,
  TOP,
  BOTTOM,
  ALL
} BorderStyle;

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
  const char* hoverTextColor;
  const char* hoverBackgroundColor;

  uint8_t borderDefaultHeight;
  uint8_t borderDefaultWidth;
  const char* borderColor;
  BorderStyle borderStyle;
} Button;

int createButton(Button button);

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
