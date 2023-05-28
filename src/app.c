#include "app.h"
#include "label.h"
#include "button.h"
#include "util.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

App* app;
Label lblAdd;
Button btnAdd;

void createScene()
{
  createLable(lblAdd);
  createButton(btnAdd);
}

void lblAddLeftButtonHandler()
{
  SDL_Log("lblAdd leftButton Clicked");
}

void lblAddRightButtonHandler()
{
  SDL_Log("lblAdd rightButton Clicked");
}

void btnAddLeftButtonHandler()
{
  SDL_Log("btnAdd leftButton Clicked");
}

void btnAddRightButtonHandler()
{
  SDL_Log("btnAdd rightButton Clicked");
}

void btnAddHoverHandler()
{
  //SDL_Log("btnAdd Hover Event Activated!");
  //btnAdd.textColor = btnAdd.hoverTextColor;
  //btnAdd.backgroundColor = btnAdd.hoverBackgroundColor;
}

void mouseHoverEventUpHandler(int x, int y)
{
  // btnAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + btnAdd.padding && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    btnAdd.isHovered = true;
    return;
  }

  btnAdd.isHovered = false;
}

void mouseLeftClickEventDownHandler(int x, int y)
{
  // lblAdd
  if (x >= lblAdd.x && x <= lblAdd.x + lblAdd.width + lblAdd.padding && y >= lblAdd.y && y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    lblAddLeftButtonHandler();
  }

  // btnAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + btnAdd.padding && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    btnAddLeftButtonHandler();
  }
}

void mouseRightClickEventDownHandler(int x, int y)
{
  // lblAdd
  if (x >= lblAdd.x && x <= lblAdd.x + lblAdd.width + lblAdd.padding && y >= lblAdd.y && y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    lblAddRightButtonHandler();
  }

  // lblAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + btnAdd.padding && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    btnAddRightButtonHandler();
  }
}

void mouseLeftClickEventUpHandler(int buttonX, int buttonY)
{
}

void mouseRightClickEventUpHandler(int buttonX, int buttonY)
{
}

int initialize()
{
  app = malloc(sizeof(App));
  app->font = NULL;
  app->window = NULL;
  app->renderer = NULL;
  app->x = 0;
  app->y = 0;
  app->width = 800;
  app->height = 600;
  app->backgroundColor = "#757575";

  lblAdd.x = 20;
  lblAdd.y = 20;
  lblAdd.radius = 1;
  lblAdd.width = 45;
  lblAdd.height = 20;
  lblAdd.padding = 4;
  lblAdd.text = "Name: ";
  lblAdd.textColor = "#DADADA";
  lblAdd.backgroundColor = app->backgroundColor; //#1E1E1E

  btnAdd.x = lblAdd.x + lblAdd.width;
  btnAdd.y = lblAdd.y;
  btnAdd.radius = 50;
  btnAdd.width = 60;
  btnAdd.height = lblAdd.height;
  btnAdd.padding = 6;
  btnAdd.borderDefaultWidth = 2;
  btnAdd.borderDefaultHeight = 2;
  btnAdd.isHovered = false;
  btnAdd.text = "Search";
  btnAdd.textColor = "#DADADA";
  btnAdd.backgroundColor = "#262626";
  btnAdd.borderColor = "#FF7043";
  btnAdd.backgroundColor = "#262626";
  btnAdd.hoverTextColor = "#212121";
  btnAdd.hoverBackgroundColor = "#66BB6A"; //#FF7043, #FF8A65

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
      return 0;
  }

  app->window= SDL_CreateWindow("Galaxy of Nodes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->width, app->height, SDL_WINDOW_SHOWN);
  if (app->window == NULL) {
      printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->renderer= SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (app->renderer == NULL) {
      printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  if (TTF_Init() < 0) {
      printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  app->font = TTF_OpenFont("monaco.ttf", 14); //FantasqueSansMono
  if (app->font == NULL) {
      printf("Font loading failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  // Enable text anti-aliasing
  if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
  {
    printf("Warning: Failed to enable anti-aliasing\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void handleEvents()
{
  int quit = 0;
  SDL_Event e;

  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
          quit = 1;
      }
      else if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
          mouseLeftClickEventDownHandler(e.button.x, e.button.y);
        }
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
          mouseRightClickEventDownHandler(e.button.x, e.button.y);
        }
      }
      else if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_F4 && (e.key.keysym.mod & KMOD_ALT))
        {
          quit = true;
        }
      }
      else if (e.type == SDL_MOUSEBUTTONUP)
      {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
          mouseLeftClickEventUpHandler(e.button.x, e.button.y);
        }
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
          mouseRightClickEventUpHandler(e.button.x, e.button.y);
        }
      }
      else if (e.type == SDL_MOUSEMOTION)
      {
        mouseHoverEventUpHandler(e.motion.x, e.motion.y);
      }
    }

    uint8_t red, green, blue, alpha;
    hexToRGBA(app->backgroundColor, &red, &green, &blue, &alpha);

    SDL_SetRenderDrawColor(app->renderer, red, green, blue, alpha);
    SDL_RenderClear(app->renderer);

    createScene();

    SDL_RenderPresent(app->renderer);

    // we need this delay, unless we'll face a high cpu usage. a number between 60 and 100 is ok.
    SDL_Delay(60);
  }
}

void cleanup()
{
  TTF_CloseFont(app->font);
  TTF_Quit();

  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_Quit();

  free(app);
  app = NULL;
}
