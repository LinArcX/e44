#ifndef _BUTTON_H
#define _BUTTON_H

#define NODE_RADIUS 10
#define NUM_NODES 2
int selectedNode = -1;  // -1 indicates no node is currently selected

typedef struct {
    int x;
    int y;
    int width;
    int height;
    char text[20];  // Store text for each node
} Node;

int nodeWidth = 10;
int nodeHeight = 10;

Node nodes[NUM_NODES];

void generateNodes();

#endif
