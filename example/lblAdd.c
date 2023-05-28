#include "app.h"
#include "lblAdd.h"

Label lblAdd;

void initLblAdd()
{
  lblAdd.x = 20;
  lblAdd.y = 20;
  lblAdd.radius = 1;
  lblAdd.width = 50;
  lblAdd.height = 20;
  lblAdd.padding = 4;
  lblAdd.text = "Name: ";
  lblAdd.textColor = "#FAFAFA";
  lblAdd.backgroundColor = app->backgroundColor;
}

void lblAddLeftClickHandler(int x, int y)
{
  if (x >= lblAdd.x
      && x <= lblAdd.x + lblAdd.width + lblAdd.padding
      && y >= lblAdd.y
      && y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    SDL_Log("[lblAdd] leftButton Clicked!");
  }
}

void lblAddRightButtonHandler(int x, int y)
{
  if (x >= lblAdd.x
      && x <= lblAdd.x + lblAdd.width + lblAdd.padding
      && y >= lblAdd.y
      && y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    SDL_Log("[lblAdd] rightButton Clicked!");
  }
}
