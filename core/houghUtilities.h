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
#include <cstdlib>   // for srand and rand
#include <ctime>     // for time

using namespace std;

#define GRAYLEVEL_8 			255
#define MAX_BRIGHTNESS_8 		255
#define dimX					2048
#define dimY					2048
#define ind( y, x ) ( y*dimX+x )
#define semilla 				20
#define ANCHO					4			//grosor en pixeles de aro entoro al 1% de radio del disco
#define PASO_RADIO				0.25		//Incremento del radio


typedef valarray<unsigned int>   ImageValInt;
typedef valarray<unsigned char>  ImageValChar;
typedef valarray<unsigned long>  ImageValLong;

//long xGradient(valarray<int> image, int x, int y);
//long yGradient(valarray<int> image, int x, int y);
long Sobel(int val1,int val2,int val3,int val4,int val5,int val6);
valarray<unsigned long> gradient(valarray<int> im_in);

ImageValChar escalado8(valarray<unsigned long> val);
ImageValInt findones(ImageValChar val);
ImageValInt randomizer(ImageValInt val, float random);
valarray<unsigned int> histogram (ImageValChar val);
valarray<float> probability (valarray<unsigned int> hist);
int otsu_th(ImageValChar val);
ImageValChar binarizar (ImageValChar val, int threshold);
ImageValChar dilate(ImageValChar val);
ImageValChar erode(ImageValChar val);

#endif /* CORE_HOUGHUTILITIES_H_ */
