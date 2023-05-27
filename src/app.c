#include "app.h"
#include "label.h"

App* app;
Label label;

void createScene()
{
  // label
  label.x = 20;
  label.y = 20;
  label.radius = 50;
  label.width = 45;
  label.height = 20;
  label.text = "Label";
  label.textColor = "#DADADA";
  label.backgroundColor = "#262626";
  createLable(label);
}

void labelLeftButtonHandler()
{
  SDL_Log("label leftButton Clicked");
}

void labelRightButtonHandler()
{
  SDL_Log("label rightButton Clicked");
}

void labelHoverHandler()
{
  SDL_Log("label Hover Event Activated!");
}

void mouseHoverEventUpHandler(int mouseX, int mouseY)
{
}

void mouseLeftClickEventDownHandler(int buttonX, int buttonY)
{
  // label
  if (buttonX >= label.x && buttonX <= label.x + label.width && buttonY >= label.y && buttonY <= label.y + label.height)
  {
    labelLeftButtonHandler();
  }
}

void mouseRightClickEventDownHandler(int buttonX, int buttonY)
{
  // label
  if (buttonX >= label.x && buttonX <= label.x + label.width && buttonY >= label.y && buttonY <= label.y + label.height)
  {
    labelRightButtonHandler();
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
