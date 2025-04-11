#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QuadTree {
    int x, y, width, height;
    int colorMean[4];
    bool isLeaf;
    struct QuadTree* children[4]; 
} QuadTree;

QuadTree* createNode(int x, int y, int width, int height, unsigned char* image, int channels, int absWidth);
void connect(QuadTree* parent, QuadTree* child, int index);
void freeQuadTree(QuadTree* root);
int getTreeDepth(QuadTree* root);
int getNodeCount(QuadTree* root);

#endif 