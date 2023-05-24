#include "button.h"

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

int pointInsideRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h));
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
