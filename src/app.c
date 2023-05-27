#include "app.h"
#include "label.h"
#include "button.h"

App* app;
Label lblAdd;
Button btnAdd;

void createScene()
{
  // lblAdd
  lblAdd.x = 20;
  lblAdd.y = 20;
  lblAdd.radius = 50;
  lblAdd.width = 45;
  lblAdd.height = 20;
  lblAdd.text = "Add: ";
  lblAdd.textColor = "#DADADA";
  lblAdd.backgroundColor = "#262626";
  createLable(lblAdd);

  // btnAdd
  btnAdd.x = lblAdd.x + lblAdd.width + 10;
  btnAdd.y = lblAdd.y;
  btnAdd.radius = 50;
  btnAdd.width = 60;
  btnAdd.height = lblAdd.height;
  btnAdd.text = "Click!";
  btnAdd.textColor = "#DADADA";
  btnAdd.backgroundColor = "#262626";
  btnAdd.hoverTextColor = "#212121";
  btnAdd.hoverBackgroundColor = "#FF7043";
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
  SDL_Log("btnAdd Hover Event Activated!");
  btnAdd.textColor = btnAdd.hoverTextColor;
  btnAdd.backgroundColor = btnAdd.hoverBackgroundColor;
}

void mouseHoverEventUpHandler(int x, int y)
{
  // btnAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + 4 && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + 4)
  {
    btnAddHoverHandler();
  }
}

void mouseLeftClickEventDownHandler(int x, int y)
{
  // lblAdd
  if (x >= lblAdd.x && x <= lblAdd.x + lblAdd.width + 4 && y >= lblAdd.y && y <= lblAdd.y + lblAdd.height + 4)
  {
    lblAddLeftButtonHandler();
  }

  // btnAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + 4 && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + 4)
  {
    btnAddLeftButtonHandler();
  }
}

void mouseRightClickEventDownHandler(int x, int y)
{
  // lblAdd
  if (x >= lblAdd.x && x <= lblAdd.x + lblAdd.width + 4 && y >= lblAdd.y && y <= lblAdd.y + lblAdd.height + 4)
  {
    lblAddRightButtonHandler();
  }

  // lblAdd
  if (x >= btnAdd.x && x <= btnAdd.x + btnAdd.width + 4 && y >= btnAdd.y && y <= btnAdd.y + btnAdd.height + 4)
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

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
      return 0;
  }

  app->window = SDL_CreateWindow("Galaxy of Nodes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->width, app->height, SDL_WINDOW_SHOWN);
  if (app->window == NULL) {
      printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
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
    while (SDL_PollEvent(&e) != 0)
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
    SDL_SetRenderDrawColor(app->renderer, 30, 30, 30, 1);
    SDL_RenderClear(app->renderer);

    createScene();

    SDL_RenderPresent(app->renderer);
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
