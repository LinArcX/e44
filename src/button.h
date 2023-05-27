#ifndef _BUTTON_H
#define _BUTTON_H

typedef struct SDLButton
{
  int x;
  int y;
  int width;  // 10
  int height; // 10
  char text[40];
  int radius; // 10
  bool hover;
  bool isRightClicked;
  bool isLeftClicked;
} Button;

//Node nodes[2];
//int selectedNode = -1;  // -1 indicates no node is currently selected
//
//void generateNodes();

#endif
