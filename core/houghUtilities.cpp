/*
 * houghUtilities.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: mrv
 */

#define ind( y, x ) ( y*dimX+x )
#include <opencv2/opencv.hpp>
#include "houghUtilities.h"
using namespace cv;


ImageValInt readImageFit(string nombreImagen){

	std::auto_ptr<FITS> pInfile(new FITS(nombreImagen,Read,true));
	//std::auto_ptr<FITS> pInfile(new FITS("atestfil.fit",Read,true));

	PHDU& image = pInfile->pHDU();

	valarray<int>  contents;

	// read all user-specifed, coordinate, and checksum keys in the image
	image.readAllKeys();
	image.read(contents);

	int size_val = contents.size();
	ImageValInt im(size_val);

	for(int i = 0; i < size_val; i++){
		im[i] = contents[i];
	}
	return im;
}


//// Computes the x component of the gradient vector
//// at a given point in a image.
//// returns gradient in the x direction
double xGradient(const valarray<double>& image, int x, int y){
   return (image[ind(y-1, x-1)] +2*image[ind(y, x-1)] +image[ind(y+1, x-1)] -image[ind(y-1, x+1) ]- 2*image[ind(y, x+1)] -image[ind(y+1, x+1)]);
}
//

//// Computes the y component of the gradient vector
//// at a given point in a image
//// returns gradient in the y direction
//
double yGradient(const valarray<double>& image, int x, int y)
{

	return (image[ind(y-1, x-1)] +
                2*image[ind(y-1, x)] +
                image[ind(y-1, x+1) ]-
                  image[ind(y+1, x-1)] -
                   2*image[ind(y+1, x)] -
                    image[ind(y+1, x+1)]);
}



valarray<double> gradient(const valarray<double>& src ){
	//
	double sum;
	double gx,gy;
	valarray<double> tmp(0.0,src.size());

	for(int y = 1; y < dimY - 1; y++){
		for(int x = 1; x < dimX - 1; x++){
			gy = yGradient(src, x, y);
			gx = xGradient(src, x, y);
			sum= (gx*gx+gy*gy);
			tmp[ind(y,x)] = sum;
		}
	}
	return tmp;
}


valarray<double> median_filter(const ImageValInt& val, float Kernel[3][3]){

	ImageValDouble tmp(0.0,val.size());
	cout << "max y Min"<< val.max()<<"  "<<val.min()<<endl;
	 double sum;
	 //convolution operation
	 for(int y = 1; y < dimY - 1; y++) {
		 for(int x = 1; x < dimX - 1; x++) {
			 sum = 0.0;
			 //
			 for(int k = -1; k <= 1;k++) {
				 for(int j = -1; j <=1; j++) {
					 sum = sum + Kernel[j+1][k+1]*(float)val[ind(int(y - j), int(x - k))];
				 }
			 }
			 tmp[ind(y,x)] = sum;
		 }
	 }
	 return tmp;
}
/**
 * Sobel Kernel
 */
long Sobel(int val1,int val2,int val3,int val4,int val5,int val6){
	return (long)(val1 + 2*val2 + val3 -val4 - 2*val5 - val6);
}


/**
 * Calculate gradient of image using sobel kernel
 *
 * @param im_im 	32 bits grayscale Input image
 *
 * @return image	32 bits grayscale Gradient image
 */

ImageValLong gradient(const ImageValInt& im_in){

	int size_im = im_in.size();
	long gx, gy;

	ImageValLong temp(size_im);

	unsigned int x_y_1;			//(y-1)(x-1)
	unsigned int x_1;			//(y)(x-1)
	unsigned int x_y_t_1;		//(y+1)(x-1)
	unsigned int x_y_t_2;		//(y-1)(x+1)
	unsigned int x_2;			//(y)(x+1)
	unsigned int x_y_2;			//(y+1)(x+1)
	unsigned int y_1;			//(y-1)(x)
	unsigned int y_2;			//(y+1)(x)

	for(int y = 1; y < dimY - 1; y++){
		for(int x = 1; x < dimX - 1; x++){
			x_y_1 = im_in[(y-1)*dimX + (x-1) ];			//(y-1)(x-1)
			y_1 = im_in[(y-1)*dimX+ (x) ];				//(y-1)(x)
			x_y_t_2 = im_in[(y-1)*dimX+ (x+1) ];		//(y-1)(x+1)
			x_1 = im_in[(y)*dimX+ (x-1) ];				//(y)(x-1)
			x_2 = im_in[(y)*dimX+ (x+1) ];				//(y)(x+1)
			x_y_t_1 = im_in[(y+1)*dimX+ (x-1) ];		//(y+1)(x-1)
			y_2 = im_in[(y+1)*dimX+(x) ];				//(y+1)(x)
			x_y_2 = im_in[(y+1)*dimX+(x+1) ];			//(y+1)(x+1)

			gx = Sobel(x_y_1, x_1, x_y_t_1, x_y_t_2, x_2, x_y_2);
			gy = Sobel(x_y_1, y_1, x_y_t_2, x_y_t_1, y_2, x_y_2);
			temp[ind( y, x )] = (unsigned long)(gx*gx + gy*gy);//gradient approximate

		}
	}

	return temp;
}
/**
 * this function scales a double input image to 255 levels image
 *
 * @param image		double Image
 * @return image 	255 grey level Image
 */
ImageValChar escalado8(const ImageValDouble& val){
	int size_val = val.size();
	ImageValChar temp(size_val);
    ImageValDouble tmp=val;
	double mx ;
	double min=tmp.min();
	tmp=tmp-min;
	mx=tmp.max();
	tmp=tmp/mx;
	for(int i = 0; i < size_val; i++){
		temp[i] = (unsigned char) ( tmp[i] * 255.0);
	}

	return temp;
}
/**
 * this function scales a long input image to 255 levels image
 *
 * @param image		long  Image
 * @return image 	255 grey level Image
 */
ImageValChar escalado8(const ImageValLong& val){
	int size_val = val.size();
	ImageValChar temp(size_val);

	unsigned long mx = val.max();

	for(int i = 0; i < size_val; i++){
		temp[i] = (unsigned char) (( (float)(val[i])/(float)mx ) * 255.0);
	}

	return temp;
}
/**
 * this function scales a unsigned int input image to 255 levels image
 *
 * @param image		unsigned int Image
 * @return image 	255 grey level Image
 */
ImageValChar escalado8(const ImageValInt& val){
	int size_val = val.size();
	ImageValChar temp(size_val);

	unsigned int mx = val.max();

	for(int i = 0; i < size_val; i++){
		temp[i] = (unsigned char) (( (float)(val[i])/(float)mx ) * 255.0);
	}

	return temp;
}
/**
 * Calculate eight bit image histogram
 *
 * @param val		input image
 * @return hist 	histogram of input image
 */

ImageValInt histogram (ImageValChar val){
	valarray<unsigned int> hist(GRAYLEVEL_8);

	int size_val = val.size();

	for(int i = 0; i < size_val; i++){
		hist[ val[i] ]++;
	}

	return hist;
}
/**
 * Calculate probability vector from image histogram
 *
 * @param val		input histogram vector
 * @return hist 	probability vector
 */
ImageValFloat probability (valarray<unsigned int> hist){
	valarray<float> prob(GRAYLEVEL_8);
	int numeroPixels = dimX*dimY;
	for (int x = 0; x < GRAYLEVEL_8; x++) {
		prob[x] = (float)hist[x]/(float)numeroPixels;
	}
	return prob;
}
//--------------------------------------------------------------------------------------------------------------------

/**
 *  This function calculates automatically the optimum threshold.
 *  This threshold will be used to binarized the gradient
 *
 *  @param val		8 bit input Image
 *  @return int 	Otsu threshold
 */
int otsu_th(const ImageValChar& val){
	valarray<unsigned int> hist(GRAYLEVEL_8);
	valarray<float> prob(GRAYLEVEL_8);
	valarray<float> omega(GRAYLEVEL_8); /* prob of graylevels */
	valarray<float> myu(GRAYLEVEL_8);   /* mean value for separation */
	valarray<float> sigma(GRAYLEVEL_8); /* inter-class variance */

	double max_sigma;
	int threshold; /* threshold for binarization */

	hist = histogram (val);

	prob = probability(hist);

	/* omega & myu generation */
	omega[0] = prob[0];
	myu[0] = 0.0;       /* 0.0 times prob[0] equals zero */
	for (int i = 1; i < GRAYLEVEL_8; i++) {
		omega[i] = omega[i-1] + prob[i];
		myu[i] = myu[i-1] + i*prob[i];
	}

	/* sigma maximization
	 sigma stands for inter-class variance
	 and determines optimal threshold value */
	threshold = 0;
	max_sigma = 0.0;
	for (int i = 0; i < GRAYLEVEL_8-1; i++) {
		if (omega[i] != 0.0 && omega[i] != 1.0)
			sigma[i] = pow(myu[GRAYLEVEL_8-1]*omega[i] - myu[i], 2) /
			(omega[i]*(1.0 - omega[i]));
		else
			sigma[i] = 0.0;
		if (sigma[i] > max_sigma) {
			max_sigma = sigma[i];
			threshold = i;
		}
	}

	return threshold;
}

/**
 *  this function create a two level image
 *
 *  @param val 			8 bit gray level input /output
 *  @param threshold  	input threshold
 *
 *  @return val 		valarray<unsigned char> binary image
 */
void binarizar (ImageValChar& val, int threshold){
	int size_val = val.size();

	for(int i = 0; i < size_val; i++){
		if (val[i] > threshold){
			val[i] = MAX_BRIGHTNESS_8;
		}
		else{
			val[i] = 0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------

/**
 * this function find in binarized image the coordinates of solar limb
 *
 * @param val		binary input Image
 * @return coordinadas 	y and x Coordinates of solar limb
 */

ImageValInt findones(const ImageValChar& val){
	int size_val = val.size();
	ImageValChar temp;
	ImageValInt Y(size_val);
	ImageValInt X(size_val);
	int i=0;

	for(int y = 0; y < dimY; y++){
		for(int x = 0; x < dimX; x++){
			if ( val[ind(y,x)]==MAX_BRIGHTNESS_8){
				Y[i]=y;
				X[i]=x;
				i++;
			}
		}
	}
	ImageValInt coordenadas(2*i);

	for(int j=0;j<i;j++){
		coordenadas[2*j] 	= Y[j];
		coordenadas[2*j+1]  = X[j];
	}

	return coordenadas;
}

/**
 * this function get a random sub set from solar limb (SL)coordinates
 *
 * @param val		total solar limb coordinates
 * @param random	% of total points
 * @return image 	random subset SL coordinates
 */

ImageValInt randomizer(ImageValInt& val, float random){

	int size_val = val.size();
	int n = size_val*random;           // number of elements to deal
	srand(SEMILLA);//srand(time(0));   // initialize with SEMILLA parameter

	int tempX, tempY;
	//--- Shuffle elements by randomly exchanging each with one other.
	for (int i=0; i<(size_val/2-1); i++) {
		int r = i + (rand() % (size_val/2-i)); // Random remaining position.

		tempY = val[i*2];
		val[i*2] = val[r*2];
		val[r*2] = tempY;

		tempX = val[i*2+1];
		val[i*2+1] = val[r*2+1];
		val[r*2+1] = tempX;
	}

	return val[slice(0,n,1)];
}



// Not used functions

ImageValInt rot90(ImageValInt& i_image,int rows, int cols){

     /*******************************************
     *
     *   Rotate the image array as desired.
     *
     *******************************************/

     /*******************************************
     *
     *   1 90 degree rotation
     *
     *******************************************/
	int size_im = i_image.size();
	ImageValInt tmp(size_im);

      for(int i=0; i<rows; i++){
         for(int j=0; j<cols; j++){
            //out_image[j][cols-1-i] = the_image[i][j];
         tmp[ind(j,cols-1-i)] = i_image[ind(i,j)];
      }  /* ends loop over i */
   }
      return tmp;
}

//-----------------------------------------------------------
ImageValInt flip(ImageValInt& im_in, int rows, int cols){
	/*******************************************
	 *
	 *   Flip the image array vertically
	 *   about the center horizontal axis.
	 *
	 *******************************************/
	int size_val=im_in.size();
	ImageValInt tmp(size_val);
	int rd2 = rows/2;
	for(int i=0; i<rd2; i++){
		for(int j=0; j<cols; j++){
			tmp[ind(rows-1-i,j)]= im_in[ind(i,j)];
			//out_image[rows-1-i][j] = the_image[i][j];
		}  /* ends loop over j */
	}  /* ends loop over i */

	for(int i=rd2; i<rows; i++){
		for(int j=0; j<cols; j++){
			tmp[ind(rows-1-i,j)]= im_in[ind(i,j)];
			//out_image[rows-1-i][j] = the_image[i][j];
		}  /* ends loop over j */
	}  /* ends loop over i */


	return tmp;
}  /* ends flip_image */

//--------------------------------------------------------------------------------------------------------------------
