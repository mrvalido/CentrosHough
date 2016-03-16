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



#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;

#include "core/houghUtilities.h"

// The library is enclosed in a namespace.

int main(){

	string nombreImagen = "im00.fits";
	ImageValInt  imageVal = readImageFit(nombreImagen);

	ImageValLong valorG = gradient(imageVal);

	ImageValChar valorG8 = escalado8(valorG);

	int umbral = otsu_th(valorG8);

	cout << "Umbral: " << umbral << endl;

	binarizar(valorG8, umbral);

	ImageValInt ones = findones(valorG8);

	cout << "Size Ones: " << ones.size()/2 << endl;

	ImageValInt random_ones = randomizer(ones, 0.5);

	cout << "Size Random_Ones: " << random_ones.size()/2 << endl;

	ImageValFloat matrix = hough(random_ones, 963.8, 1, 1020.68, 1021.75, 450);

	for(int i=0; i < matrix.size(); i+=4){
		if(i%4==0){
			cout << endl;
		}
		cout << matrix[i] << "    " << matrix[i+1] << "    "  << matrix[i+2] << "    "  << matrix[i+3] << endl;
	}


	cout << "Long Size: " << sizeof(unsigned long) << endl;
	cout << "Int Size: " << sizeof(unsigned int) << endl;
	cout << "Char Size: " << sizeof(unsigned char) << endl;
	cout << "Short Size: " << sizeof(unsigned short) << endl;


	Mat im(dimY, dimX, CV_8UC1, Scalar(0));  //Es un tipo de dato de 4 bytes 32S

	//Se pone primero el eje Y y despues el eje X
	for (long y=0; y<dimY; y++){
			for (long x=0; x<dimX; x++){
			im.at<uchar>(y,x) = (uchar)(valorG8[ind( y, x )]);
		}
	}

	namedWindow( "Display window", WINDOW_NORMAL );// Create a window for display.
	imshow( "Display window", im );




//	Mat im2(dimY, dimX, CV_8UC1, Scalar(0));  //Es un tipo de dato de 4 bytes 32S
//	//Se pone primero el eje Y y despues el eje X
//	for (long y=0; y<dimY; y++){
//		for (long x=0; x<dimX; x++){
//			im2.at<uchar>(y,x) = (uchar)(open[ind( y, x )]);
//		}
//	}
//
//	namedWindow( "Display window 2", WINDOW_NORMAL );// Create a window for display.
//	imshow( "Display window 2", im2 );

	waitKey(0);
	//imageVal.showImageMat();


	return 0;
}

