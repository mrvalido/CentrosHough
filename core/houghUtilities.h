/*
 * houghUtilities.h
 *
 *  Created on: Mar 8, 2016
 *      Author: mrv
 */

#ifndef CORE_HOUGHUTILITIES_H_
#define CORE_HOUGHUTILITIES_H_

//#include "../ImageVal.h"
#include <math.h>
#include <valarray>
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;

#define GRAYLEVEL_8 			255
#define MAX_BRIGHTNESS_8 		255
#define dimX					2048
#define dimY					2048
#define ind( y, x ) ( y*dimX+x )


typedef valarray<unsigned int>   ImageValInt;
typedef valarray<unsigned char>  ImageValChar;
typedef valarray<unsigned long>  ImageValLong;

long xGradient(ImageValInt image, int x, int y);
long yGradient(ImageValInt image, int x, int y);
ImageValLong gradient(ImageValInt im_in);
ImageValChar escalado8(ImageValLong val);
valarray<unsigned int> histogram (ImageValChar val);
valarray<float> probability (valarray<unsigned int> hist);
int otsu_th(ImageValChar val);
ImageValChar binarizar (ImageValChar val, int threshold);
ImageValChar dilate(ImageValChar val);
ImageValChar erode(ImageValChar val);

#endif /* CORE_HOUGHUTILITIES_H_ */
