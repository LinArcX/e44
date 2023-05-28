#ifndef _EXAMPLE_BTNADD_H
#define _EXAMPLE_BTNADD_H

#include "../lib/button.h"

extern Button btnAdd;

void initBtnAdd();

void btnAddLeftClickHandler(int x, int y);
void btnAddRightButtonHandler(int x, int y);
void btnAddHoverHandler(int x, int y);
#endif
