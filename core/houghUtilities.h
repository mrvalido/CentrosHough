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
#include <CCfits/CCfits>
#include <vector>

#include <cmath>

using namespace CCfits;
using namespace std;

#define GRAYLEVEL_8 			255
#define MAX_BRIGHTNESS_8 		255
#define dimX					2048
#define dimY					2048
#define ind( y, x ) ( y*dimX+x ) //macro to transform image coordinates to image index position
#define SEMILLA 				25 //Rando seed to get a subset of solar limb coordinates from total
#define ANCHO					5			//grosor en pixeles de aro entoro al 1% de radio del disco
#define PASO_RADIO				0.25		//Incremento del radio
#define PASO 					1


typedef valarray<unsigned int>   ImageValInt;
typedef valarray<unsigned char>  ImageValChar;
typedef valarray<unsigned long>  ImageValLong;
typedef valarray<float>  		 ImageValFloat;
typedef valarray<double>  		 ImageValDouble;

ImageValInt readImageFit(string nombreImagen);

valarray<double> median_filter(const ImageValInt& val, float Kernel[3][3]);


double xGradient(const valarray<double>& image, int x, int y);
double yGradient(const valarray<double>& image, int x, int y);
valarray<double> gradient(const valarray<double>& src );

long Sobel(int val1,int val2,int val3,int val4,int val5,int val6);
//ImageValLong gradient(const ImageValInt& im_in);



ImageValLong gradient(const ImageValInt& im_in);

ImageValChar escalado8(const ImageValLong& val);
ImageValChar escalado8(const ImageValInt& val);
ImageValChar escalado8(const ImageValDouble& val);

ImageValInt histogram (ImageValChar val);
ImageValFloat probability (ImageValInt hist);
int otsu_th(const ImageValChar& val);
void binarizar (ImageValChar& val, int threshold);
ImageValInt findones(const ImageValChar& val);
ImageValInt randomizer(ImageValInt& val, float random);






ImageValFloat hough(ImageValInt& val, float radio, float paso, float yc, float xc, int despla_max);
ImageValInt do_hough(ImageValInt& val, int r2, int dimensionAcumulador, float Xmin, float Xmax, float Ymin, float Ymax, float paso);
float* maximumValue(ImageValInt& val, int dimensionAcumulador);
float* kernel(ImageValInt& val, int y, int x, int dimensionAcumulador);

ImageValInt rot90(ImageValInt& i_image,int rows, int cols);
//template <typename Tt>
//void write_im(Tt& val,int Dy,int Dx, int indice);
#endif /* CORE_HOUGHUTILITIES_H_ */
