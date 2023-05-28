#include "btnAdd.h"
#include "lblAdd.h"

Button btnAdd;

void initBtnAdd()
{
  btnAdd.x = lblAdd.x + lblAdd.width;
  btnAdd.y = lblAdd.y;
  btnAdd.radius = 50;
  btnAdd.width = 60;
  btnAdd.height = lblAdd.height;
  btnAdd.padding = 6;
  btnAdd.borderDefaultWidth = 2;
  btnAdd.borderDefaultHeight = 2;
  btnAdd.isHovered = false;
  btnAdd.borderStyle = ALL;
  btnAdd.text = "Search";
  btnAdd.textColor = "#FAFAFA"; //#DADADA,
  btnAdd.backgroundColor = "#262626";
  btnAdd.borderColor = "#616161";
  btnAdd.backgroundColor = "#262626";
  btnAdd.hoverTextColor = "#212121";
  btnAdd.hoverBackgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E
}

void btnAddLeftClickHandler(int x, int y)
{
  if (x >= btnAdd.x
      && x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && y >= btnAdd.y
      && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    SDL_Log("[btnAdd] leftButton Clicked!");
  }
}

void btnAddRightButtonHandler(int x, int y)
{
  if (x >= btnAdd.x
      && x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && y >= btnAdd.y
      && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    SDL_Log("[btnAdd] rightButton Clicked!");
  }
}

void btnAddHoverHandler(int x, int y)
{
  if (x >= btnAdd.x
      && x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && y >= btnAdd.y
      && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    btnAdd.isHovered = true;
    return;
  }
  btnAdd.isHovered = false;
}
