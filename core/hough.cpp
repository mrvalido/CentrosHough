#include "houghUtilities.h"
#include <opencv2/opencv.hpp>
using namespace cv;


/**
 *
 */
/**
 *  Hough Fucntion caculate initial parameter to do hough transform. This preprocessing steps reduce the complexity of computation
 *  Calculamos el valor del radio de la circunferencia presente en la imagen asi como su posicion en la misma
 *	@param val		Coordinates of Solar limb
 *  @param radio 	initial Radio
 *  @param paso 	incremental step to coordinates search Imagen binarizada con el borde calculado, a calcular su radio
 *  @param yc  	     Initial yc center coordinate
 *	@param xc  	     Initial xc center coordinate
 *  @return Matrix  a set of centers coordinates, size of matrix depending of search range of radio
 */
ImageValFloat hough(ImageValInt& val, float radio, float paso, float yc, float xc, int despla_max){
	 float Rmin=radio-ANCHO/2;
	 float Rmax=radio+ANCHO/2;

	 float Xmin=xc-despla_max; 	// Xmin and Xmax are boundaries of coordinates around of initial center
	 float Xmax=xc+despla_max;
	 float Ymin=yc-despla_max;	// Ymin and Ymax are boundaries of coordinates around of initial center
	 float Ymax=yc+despla_max;
//cout << " Xmin  "<<Xmin<<" Xmax  "<<Xmax<<"  Ymin  "<<Ymin<<"  Ymax   "<<Ymax<<endl;
	 float lmax=(Rmax-Rmin)/PASO_RADIO+1;
	 int dimensionAcumulador=floor((Xmax-Xmin)/paso)+1;

	 ImageValFloat matrix(lmax*4);
int indice=0;
	 int count = 0;
	 for (float r=Rmin; r < Rmax; r+=PASO_RADIO){					// do_hough transform for each radio value belong to range

		 ImageValInt votacion = do_hough(val, r*r, dimensionAcumulador, Xmin, Xmax, Ymin, Ymax, paso);

		// write_im(votacion,dimensionAcumulador,dimensionAcumulador, indice);

		 float *max = maximumValue(votacion, dimensionAcumulador);
		 //cout << "Maximo: " << max[0] << "\t" << max[1] << "\t" << max[2] <<  endl;

		 matrix[count] = max[2];							//Valor
		 matrix[count+1] = (float)(max[0])*paso + Ymin;		//Y
		 matrix[count+2] = (float)(max[1])*paso + Xmin;		//X
		 matrix[count+3] = r;								//Radio
		 count+=4;
		 indice+=1;
	 }
	 return matrix;
 }

/**
 *  do_Hough Function calculate hough transform.
 *
 *	@param val		Coordinates of Solar limb
 *  @param r2 	    r^2 Radio
 *  @param Xmin, Xmax X coordinate range for algorithm searching
 *  @param Ymin, Ymax Y coordinate range for algorithm searching
 *  @param paso 	incremental step to coordinates search Image
 *  @param dimensionAcumulador  	     Hough Space dimensions
 *  @return Hough space
 */
ImageValInt do_hough(ImageValInt& val, int r2, int dimensionAcumulador, float Xmin, float Xmax, float Ymin, float Ymax, float paso){
	 int size_val = val.size();
	 ImageValInt acu_ini(dimensionAcumulador*dimensionAcumulador);

	 int y, x;
	 float det;
	 float b;
	 int bb, aa;
	 for(int k=0; k < size_val/2; k++){
		 //we get y and x coordinates from input val
		 y = val[2*k];
		 x = val[2*k+1];
//do votation in Hough space
		 for(float a = Xmin; a < Xmax; a+=paso){		// a es la coordenada del centro X xc
			 det=r2-(x-a)*(x-a);

			 if (det>0){
				b=((float)y-sqrt(det));
				if (b>Ymin && b<Ymax){
					aa=(int)round((a-Xmin)/paso);
					bb=(int)round((b-Ymin)/paso);
					if (bb>0 && aa>0){
						acu_ini[bb*dimensionAcumulador + aa] = acu_ini[bb*dimensionAcumulador + aa] + 1;
					}
				}
			 }
		 }
	 }
	 //cout<< "suma del acumulador"<<acu_ini.sum()<<endl;
	 return acu_ini;
}


/**
 *  find maximun value in hough space
 *	@param val		hough space (dimentions is dimensionAcumuladorxdimensionAcumulador)
 *  @param dimensionAcumulador 	    it is side dimetion of hough space
 *
 *  @return  a pointer to vector (max) of 3 components y and x coordinates and value of maximum
 */
float* maximumValue(ImageValInt& val, int dimensionAcumulador)
{
     static float array [3]= {0,0,0};
     float *max = array;
     float* ker;
     max[2] = 0;

     static int array_ant [3]= {0,0,0};
     int *max_ant = array_ant;
     max_ant[2] = val[0];
//
     for(int y = 0; y < dimensionAcumulador; y++){
		for(int x = 0; x < dimensionAcumulador; x++){
			if ( val[y*dimensionAcumulador + x]>max_ant[2]){
				max_ant[0]=y;											// Coordenada Y
				max_ant[1]=x;											// Coordenada X
				max_ant[2] = val[y*dimensionAcumulador + x];			// Valor maximo de acu_ini
			}
		}
	 }


     for(int j = -20; j < 20; j++){
		for(int i = -20; i < 20; i++){
			ker = kernel(val, (max_ant[0]+j), (max_ant[1]+i), dimensionAcumulador);
			if ( ker[2] > max[2]){
				max[0] = ker[0];						// Coordenada Y
				max[1] = ker[1];						// Coordenada X
				max[2] = ker[2];						// Valor maximo de acu_ini
			}
		}
	 }

     return max;                // return max
}

/**
 *  Kerner function find find maximun value in hough space
 *	@param val		hough space (dimentions is dimensionAcumuladorxdimensionAcumulador)
 *  @param dimensionAcumulador 	    it is side dimetion of hough space
 *
 *  @return  a pointer to vector (max) of 3 components y and x coordinates and value of maximum
 */
float* kernel(ImageValInt& val, int y, int x, int dimensionAcumulador){
	static float array [3]= {0,0,0};
	float *max = array;
	int pos;
	float sumatorio = 0;
	float sum_x = 0.0;
	float sum_y = 0.0;
	for(int j = -1; j < 2; j++){
		for(int i = -1; i < 2; i++){
			pos = val[(y+j)*dimensionAcumulador + (x+i)];//vote value is the weigh this is used to determine y and x coordinates
			sumatorio += pos;
			sum_x += (x+i)*pos;
			sum_y += (y+j)*pos;
		}
	}

	max[0] = sum_y/sumatorio;
	max[1] = sum_x/sumatorio;
	max[2] = round(sumatorio/9);

	return max;
}


