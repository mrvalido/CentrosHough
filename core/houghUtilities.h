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
#define SEMILLA 				20
#define ANCHO					4			//grosor en pixeles de aro entoro al 1% de radio del disco
#define PASO_RADIO				0.25		//Incremento del radio


typedef valarray<unsigned int>   ImageValInt;
typedef valarray<unsigned char>  ImageValChar;
typedef valarray<unsigned long>  ImageValLong;
typedef valarray<float>  		 ImageValFloat;

//long xGradient(valarray<int> image, int x, int y);
//long yGradient(valarray<int> image, int x, int y);
long Sobel(int val1,int val2,int val3,int val4,int val5,int val6);
ImageValLong gradient(valarray<int> im_in);

ImageValChar escalado8(ImageValLong val);
ImageValChar escalado8(ImageValInt val);
ImageValInt findones(ImageValChar val);
ImageValInt randomizer(ImageValInt val, float random);
ImageValInt histogram (ImageValChar val);
ImageValFloat probability (ImageValInt hist);
int otsu_th(ImageValChar val);
ImageValChar binarizar (ImageValChar val, int threshold);
ImageValChar dilate(ImageValChar val);
ImageValChar erode(ImageValChar val);



ImageValFloat hough(ImageValInt val, float radio, float paso, float yc, float xc, int despla_max);
ImageValInt crear_votacion(ImageValInt val, int r2, int dimensionAcumulador, float Xmin, float Xmax, float Ymin, float Ymax, float paso);
int* maximumValue(ImageValInt val, int dimensionAcumulador);
float* centroide(ImageValInt val, int dimensionAcumulador);

#endif /* CORE_HOUGHUTILITIES_H_ */
