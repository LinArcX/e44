#ifndef _EXAMPLE_LBLADD_H
#define _EXAMPLE_LBLADD_H

#include "../lib/label.h"

extern Label lblAdd;

void initLblAdd();

void lblAddLeftClickHandler(int x, int y);
void lblAddRightButtonHandler(int x, int y);
#endif
