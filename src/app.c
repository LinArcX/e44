#include "app.h"

int initialize()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
      return 0;
  }

  window = SDL_CreateWindow("Galaxy of Nodes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
      printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
      return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
      printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
      return 0;
  }

  if (TTF_Init() == -1) {
      printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
      return 0;
  }

  font = TTF_OpenFont("monaco.ttf", 13);
  if (font == NULL) {
      printf("Font loading failed. SDL_ttf Error: %s\n", TTF_GetError());
      return 0;
  }

  generateNodes();

  return 1;
}


void handleEvents()
{
  int quit = 0;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                // Check if any node is clicked
                for (int i = 0; i < NUM_NODES; i++) {
                    SDL_Rect rect;
                    rect.x = nodes[i].x - nodeWidth / 2;
                    rect.y = nodes[i].y - nodeHeight / 2;
                    rect.w = nodeWidth;
                    rect.h = nodeHeight;

                    if (pointInsideRect(e.button.x, e.button.y, rect)) {
                        selectedNode = i;  // Mark the node as selected
                        break;
                    }
                }
            }
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                selectedNode = -1;  // Deselect the node
            }
        } else if (e.type == SDL_MOUSEMOTION) {
            if (selectedNode != -1) {
                // Update the position of the selected node
                nodes[selectedNode].x = e.motion.x;
                nodes[selectedNode].y = e.motion.y;
            }
        }
    }
    renderNodes();
  }
}

void cleanup()
{
  TTF_CloseFont(font);
  TTF_Quit();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
