#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void showBanner() ;
void getInputPath(char* alamat) ;
void getOutputPath(char* alamat) ;
void getMethod(int* metode) ;
void getThreshold(int* ambang) ;
void getMinimumBlockSize(int* minimumBlockSize) ;
void getCompressionTarget(double* target) ;

#endif