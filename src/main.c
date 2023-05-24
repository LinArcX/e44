#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>  // Include the SDL_ttf header

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define NODE_RADIUS 10
#define NUM_NODES 2
int selectedNode = -1;  // -1 indicates no node is currently selected

typedef struct {
    int x;
    int y;
    char text[20];  // Store text for each node
} Node;

int nodeWidth = 10;
int nodeHeight = 10;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;  // Declare a font object

Node nodes[NUM_NODES];

int pointInsideRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h));
}


int initializeSDL() {
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

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    // Load a font file
    font = TTF_OpenFont("monaco.ttf", 13);
    if (font == NULL) {
        printf("Font loading failed. SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

void generateNodes() {
    nodes[0].x = WINDOW_WIDTH / 4;
    nodes[0].y = WINDOW_HEIGHT / 2;
    sprintf(nodes[0].text, "Node 1");  // Set text for the first node

    nodes[1].x = (3 * WINDOW_WIDTH) / 4;
    nodes[1].y = WINDOW_HEIGHT / 2;
    sprintf(nodes[1].text, "Node 2");  // Set text for the second node
    //for (int i = 0; i < NUM_NODES; i++) {
    //    nodes[i].x = rand() % WINDOW_WIDTH;
    //    nodes[i].y = rand() % WINDOW_HEIGHT;
    //    sprintf(nodes[i].text, "Node %d", i);  // Set text for each node
    //}
}


void renderNodes() {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = { 255, 255, 255, 255 };  // Color for the text

    for (int i = 0; i < NUM_NODES; i++) {
        int depth = 200 + (nodes[i].y * 55) / WINDOW_HEIGHT;  // Increase the depth range
        SDL_SetRenderDrawColor(renderer, 130, 175, depth, 255);  // Set node color to blue

        // Create a surface from the node's text
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, nodes[i].text, textColor);

        // Render the node as a filled rectangle
        SDL_Rect rect;
        rect.w = nodeWidth + textSurface->w;
        rect.h = nodeHeight + textSurface->h;
        rect.x = nodes[i].x - (rect.w / 2);
        rect.y = nodes[i].y - (rect.h / 2);

        SDL_RenderFillRect(renderer, &rect);

        if (textSurface != NULL)
        {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture != NULL) {
                // Set the position for rendering the text
                SDL_Rect textRect;
                textRect.x = nodes[i].x - textSurface->w / 2;
                textRect.y = nodes[i].y - textSurface->h / 2;
                textRect.w = textSurface->w;
                textRect.h = textSurface->h;

                // Render the text texture on the screen
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                // Free the text texture
                SDL_DestroyTexture(textTexture);
            }

            // Free the text surface
            SDL_FreeSurface(textSurface);
        }

    }
    // Render the line and arrow
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set line and arrow color to red

    // Draw the line
    SDL_RenderDrawLine(renderer, nodes[0].x + 30, nodes[0].y, nodes[1].x - 30, nodes[1].y);

    // Calculate the position of the arrow
    int arrowSize = 5;  // Size of the arrow
    double angle = atan2(nodes[1].y - nodes[0].y, nodes[1].x - nodes[0].x);
    int arrowX = nodes[1].x - arrowSize * cos(angle);
    int arrowY = nodes[1].y - arrowSize * sin(angle);

    // Draw the arrow
    SDL_RenderDrawLine(renderer, nodes[1].x - 30, nodes[1].y, arrowX, arrowY);
    SDL_RenderDrawLine(renderer, arrowX, arrowY, arrowX - arrowSize * cos(angle + M_PI_4), arrowY - arrowSize * sin(angle + M_PI_4));
    SDL_RenderDrawLine(renderer, arrowX, arrowY, arrowX - arrowSize * cos(angle - M_PI_4), arrowY - arrowSize * sin(angle - M_PI_4));

    SDL_RenderPresent(renderer);
}


//void renderNodes() {
//    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
//    SDL_RenderClear(renderer);
//
//    SDL_Color textColor = { 255, 255, 255, 255 };  // Color for the text
//
//    for (int i = 0; i < NUM_NODES; i++)
//    {
//      int depth = 200 + (nodes[i].y * 55) / WINDOW_HEIGHT;  // Increase the depth range
//      SDL_SetRenderDrawColor(renderer, 130, 175, depth, 255);  // Set node color to blue
//
//      // Create a surface from the node's text
//      SDL_Surface* textSurface = TTF_RenderText_Solid(font, nodes[i].text, textColor);
//
//      // Render the node as a filled rectangle
//      SDL_Rect rect;
//      rect.w = nodeWidth + textSurface->w;
//      rect.h = nodeHeight + textSurface->h ;
//      rect.x = nodes[i].x - (rect.w / 2);
//      rect.y = nodes[i].y - (rect.h / 2);
//
//      SDL_RenderFillRect(renderer, &rect);
//
//
//      if (textSurface != NULL) {
//          SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//          if (textTexture != NULL)
//          {
//              // Set the position for rendering the text
//              SDL_Rect textRect;
//              textRect.x = nodes[i].x - textSurface->w / 2;
//              textRect.y = nodes[i].y - textSurface->h / 2;
//              textRect.w = textSurface->w;
//              textRect.h = textSurface->h;
//
//              // Render the text texture on the screen
//              SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//
//              // Free the text texture
//              SDL_DestroyTexture(textTexture);
//          }
//
//          // Free the text surface
//          SDL_FreeSurface(textSurface);
//      }
//    }
//
//    SDL_RenderPresent(renderer);
//}


//void renderNodes() {
//    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
//    SDL_RenderClear(renderer);
//
//    SDL_Color textColor = { 0, 0, 0, 255 };  // Color for the text
//
//    for (int i = 0; i < NUM_NODES; i++) {
//        //int depth = (nodes[i].y * 255) / WINDOW_HEIGHT;
//        int depth = 200 + (nodes[i].y * 55) / WINDOW_HEIGHT;  // Increase the depth range
//        int nodeSize = NODE_RADIUS * (depth / 255.0);
//
//        SDL_SetRenderDrawColor(renderer, depth, depth, depth, 255);  // Set node color based on depth
//
//        for (int x = -nodeSize; x <= nodeSize; x++) {
//            for (int y = -nodeSize; y <= nodeSize; y++) {
//                int distanceSquared = x * x + y * y;
//                if (distanceSquared <= nodeSize * nodeSize) {
//                    SDL_RenderDrawPoint(renderer, nodes[i].x + x, nodes[i].y + y);
//                }
//            }
//        }
//
//        // Create a surface from the node's text
//        SDL_Surface* textSurface = TTF_RenderText_Solid(font, nodes[i].text, textColor);
//        if (textSurface != NULL) {
//            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//            if (textTexture != NULL) {
//                // Set the position for rendering the text
//                SDL_Rect textRect;
//                textRect.x = nodes[i].x - textSurface->w / 2;
//                textRect.y = nodes[i].y - textSurface->h / 2;
//                textRect.w = textSurface->w;
//                textRect.h = textSurface->h;
//
//                // Render the text texture on the screen
//                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//
//                // Free the text texture
//                SDL_DestroyTexture(textTexture);
//            }
//
//            // Free the text surface
//            SDL_FreeSurface(textSurface);
//        }
//    }
//
//    SDL_RenderPresent(renderer);
//}

void cleanupSDL() {
    TTF_CloseFont(font);  // Close the font
    TTF_Quit();  // Quit SDL_ttf

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    if (!initializeSDL()) {
        return 1;
    }

    generateNodes();

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


    //while (!quit) {
    //    while (SDL_PollEvent(&e) != 0) {
    //        if (e.type == SDL_QUIT) {
    //            quit = 1;
    //        }
    //    }

    //    renderNodes();
    //}

    cleanupSDL();

    return 0;
}
