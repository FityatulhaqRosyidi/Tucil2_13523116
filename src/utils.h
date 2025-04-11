#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "quadtree.h"


int calculate_mean(unsigned char* image, int x, int y, int width, int height, int channels, int idx, int absWidth);

double calculate_variance(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth);
double calculate_MAD(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth);
double calculate_MPD(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth);
double calculate_Entropy(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth);

long getFileSize(const char* filePath);

void DAC(int minimumBlockSize, QuadTree* root, unsigned char* image, unsigned char* newImage, int channels, int threshold, int absWidth, int method);

#endif



