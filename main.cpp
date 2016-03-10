// cookbook CCfits demonstration program
//	Astrophysics Science Division,
//	NASA/ Goddard Space Flight Center
//	HEASARC
//	http://heasarc.gsfc.nasa.gov
//	e-mail: ccfits@legacy.gsfc.nasa.gov
//
//	Original author: Ben Dorman


// The CCfits headers are expected to be installed in a subdirectory of
// the include path.

// The <CCfits> header file contains all that is necessary to use both the CCfits
// library and the cfitsio library (for example, it includes fitsio.h) thus making
// all of cfitsio's symbolic names available.

#ifdef _MSC_VER
#include "MSconfig.h" // for truncation warning
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// this includes 12 of the CCfits headers and will support all CCfits operations.
// the installed location of the library headers is $(ROOT)/include/CCfits

// to use the library either add -I$(ROOT)/include/CCfits or #include <CCfits/CCfits>
// in the compilation target.

#include <CCfits/CCfits>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

//#include "ImageVal.h"
#include "core/houghUtilities.h"

// The library is enclosed in a namespace.
using namespace CCfits;
using namespace std;
using namespace cv;



int main();


int readImage();
int readImage32S(string nombreImagen);
ImageValInt readImageFit(string nombreImagen);


int main()
{
	/*
	FITS::setVerboseMode(true);
	try{
		if (!readImage()) std::cerr << " readImage() \n";
	}
	catch (FitsException&){
		std::cerr << " Fits Exception Thrown by test function \n";
	}
	*/
	string nombreImagen = "im00.fits";
	ImageValInt imageVal = readImageFit(nombreImagen);

	ImageValLong valorG = gradient(imageVal);

	ImageValChar valorG8 = escalado8(valorG);


	int umbral = otsu_th(valorG8);

	cout << "Umbral: " << umbral << endl;

	ImageValChar bin = binarizar(valorG8, umbral);

	ImageValChar open = dilate(erode(bin));


	cout << "Long Size: " << sizeof(unsigned long) << endl;
	cout << "Int Size: " << sizeof(unsigned int) << endl;
	cout << "Char Size: " << sizeof(unsigned char) << endl;
	cout << "Short Size: " << sizeof(unsigned short) << endl;


	Mat im(dimY, dimX, CV_8UC1, Scalar(0));  //Es un tipo de dato de 4 bytes 32S

	//Se pone primero el eje Y y despues el eje X
	for (long y=0; y<dimY; y++){
			for (long x=0; x<dimX; x++){
			im.at<uchar>(y,x) = (uchar)(bin[ind( y, x )]);
		}
	}

	namedWindow( "Display window", WINDOW_NORMAL );// Create a window for display.
	imshow( "Display window", im );




	Mat im2(dimY, dimX, CV_8UC1, Scalar(0));  //Es un tipo de dato de 4 bytes 32S
	//Se pone primero el eje Y y despues el eje X
	for (long y=0; y<dimY; y++){
		for (long x=0; x<dimX; x++){
			im2.at<uchar>(y,x) = (uchar)(open[ind( y, x )]);
		}
	}

	namedWindow( "Display window 2", WINDOW_NORMAL );// Create a window for display.
	imshow( "Display window 2", im2 );

	waitKey(0);
	//imageVal.showImageMat();


	return 0;
}
int readImage()
{
	//std::auto_ptr<FITS> pInfile(new FITS("im00.fits",Read,true));
	std::auto_ptr<FITS> pInfile(new FITS("atestfil.fit",Read,true));

	PHDU& image = pInfile->pHDU();

	valarray<unsigned short>  contents;


	// read all user-specifed, coordinate, and checksum keys in the image
	image.readAllKeys();
	image.read(contents);
	cout << image << std::endl;
	long ax1(image.axis(0));
	long ax2(image.axis(1));
	valarray<float>  v(contents.size());

	//valarray<unsigned short> mmx(contents.max(),contents.size());
	//v= contents/mmx;
	float mx=(float)contents.max();
	for (long j = 0; j < contents.size(); j++)
	{
		v[j]=(float) contents[j]/mx;
	}

	//     row,col  (y,x)
	//Mat im(ax2,ax1, CV_32FC1, Scalar(0));
	Mat im(ax2,ax1, CV_8UC1, Scalar(0));

	for (long y=0; y<ax2; y++){		 //200
		for (long x=0; x<ax1; x++){  //300
			//im.at<float>(y,x) = (v[y*ax1+x]);
			im.at<uchar>(y,x) = (uchar)(v[y*ax1+x]*255.0);
		}
	}

	imshow("imagen", im);
	waitKey(0);

	return 0;
}

int readImage32S(string nombreImagen){

	std::auto_ptr<FITS> pInfile(new FITS(nombreImagen,Read,true));
	//std::auto_ptr<FITS> pInfile(new FITS("atestfil.fit",Read,true));

	PHDU& image = pInfile->pHDU();

	valarray<int>  contents;

	// read all user-specifed, coordinate, and checksum keys in the image
	image.readAllKeys();
	image.read(contents);
	//cout << image << std::endl;
	long ax1(image.axis(0));
	long ax2(image.axis(1));


	//     row,col  (y,x)
	Mat im(ax2,ax1, CV_32SC1, Scalar(0));  //Es un tipo de dato de 4 bytes 32S

	//Se pone primero el eje Y y despues el eje X
	for (long y=0; y<ax2; y++){
		for (long x=0; x<ax1; x++){
			im.at<int>(y,x) = (int)(contents[y*ax1+x]);
		}
	}

	imshow("imagen", im);
	waitKey(0);

	return 0;
}

ImageValInt readImageFit(string nombreImagen){

	std::auto_ptr<FITS> pInfile(new FITS(nombreImagen,Read,true));
	//std::auto_ptr<FITS> pInfile(new FITS("atestfil.fit",Read,true));

	PHDU& image = pInfile->pHDU();

	valarray<int>  contents;

	int size_val = contents.size();
	ImageValInt imagen(size_val);

	// read all user-specifed, coordinate, and checksum keys in the image
	image.readAllKeys();
	image.read(contents);

	for(int i = 0; i < size_val; i++){
		imagen[i] = contents[i];
	}

	return imagen;
}
