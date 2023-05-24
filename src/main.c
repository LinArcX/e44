#include "app.h"

int main()
{
  if (!initialize())
  {
    return 1;
  }

  handleEvents();

  cleanup();
  return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>  // Include the SDL_ttf header
//#include "button.h"


    //while (!quit) {
    //    while (SDL_PollEvent(&e) != 0) {
    //        if (e.type == SDL_QUIT) {
    //            quit = 1;
    //        }
    //    }

    //    renderNodes();
    //}
    //
    //

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
