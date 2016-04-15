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


#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;

#include "core/houghUtilities.h"


#define N 9 //numbers of image

void pinta2(ImageValChar& val,int Dy,int Dx, char imageName[]);
// The library is enclosed in a namespace.

int main(){

	string nombreImagen;
	//char imageName[] = "./im/im0X.fits";
	//char imageName[] = "./imF03/im0X.fits";//11
	//char imageName[] = "./imF1/im0X.fits";//10
	char imageName[] = "./imF2/im0X.fits";//10
	vector <ImageValInt> datacube;

   /* float Kernel[3][3] = {
                          {1/9.0, 1/9.0, 1/9.0},
                          {1/9.0, 1/9.0, 1/9.0},
                          {1/9.0, 1/9.0, 1/9.0}
                         };*/

    float Kernel[3][3] = {
                              {1/16.0, 2/16.0, 1/16.0},
                              {2/16.0, 4/16.0, 2/16.0},
                              {1/16.0, 2/16.0, 1/16.0}
                             };

	ImageValChar tmp (dimX*dimY);
	float rand_parameter=1;
	// read images from fits files into vector data cube 3D objects
	for(unsigned int i = 0; i < N; i++) {

		//imageName[8] = 48 + i;//for "./im/im0X.fits" set
		imageName[10] = 48 + i;
		nombreImagen = imageName;


		datacube.push_back(readImageFit(nombreImagen));


		cout<< "image name"<< nombreImagen<<endl;
		//Calculate image gradient
	ImageValInt ima=datacube[i];

	valarray<double> ImFil=median_filter(ima,Kernel);

	cout << "max y Min"<< ImFil.max()<<"  "<<ImFil.min()<<endl;

	ImageValChar valor = escalado8(ImFil);

	 pinta2(valor,dimX,dimY,imageName);
	// waitKey(0);
	//ImageValDouble valorG = gradient(ImFil);
	ImageValLong valorG = gradient(ima);
	ImageValChar valorG8 = escalado8(valorG);
//	pinta2(valorG8,dimX,dimY,nombreImagen);

		int umbral = otsu_th(valorG8);

		cout << "Umbral: " << umbral << endl;

		binarizar(valorG8,umbral);
		pinta2(valorG8,dimX,dimY,imageName);
		ImageValInt ones = findones(valorG8);
//waitKey(0);
cout << "Size Ones: " << ones.size()/2 << endl;

		ImageValInt random_ones = randomizer(ones, rand_parameter);

		cout << "Size Random_Ones: " << random_ones.size()/2 << endl;

		ImageValFloat matrix = hough(random_ones, 963.8, 1, 1020.68, 1021.75, 800);
		cout<< "image name"<< nombreImagen<<endl;
		cout<< "randon _parameter"<< rand_parameter<<endl;
		for(int i=0; i < matrix.size(); i+=4){
			if(i%4==0){
				cout << endl;
			}
			cout << matrix[i] << "    " << matrix[i+1] << "    "  << matrix[i+2] << "    "  << matrix[i+3] << endl;
		}


	}
	cout<< "finnn"<<endl;
	waitKey(0);


	return 0;
}

void pinta2(ImageValChar& val,int Dy,int Dx, char imageName[]){

	Mat im(Dy, Dx, CV_8U, Scalar(0));  //Es un tipo de dato de 4 bytes 32S


	//Se pone primero el eje Y y despues el eje XCV_64F
	for (int y=0; y<Dy; y++){

		for (int x=0; x<Dx; x++){
			//cout << " y   x  : "  << y*Dx + x << "  " << x << endl;
			im.at<uchar>(y,x) = val[y*Dx + x];
		}
	}
	//char imageName[] = "imX.jpg";
	//imageName[2] = 48 + indice;
	//imwrite(imageName, im);

	namedWindow(imageName, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
	imshow(imageName, im);
}



