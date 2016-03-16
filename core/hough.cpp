#include "houghUtilities.h"

/**
 * Funcion hough
 *
 */

 int* hough(ImageValInt val, float radio, float paso, float yc, float xc, int despla_max){
	 float Rmin=radio-ANCHO/2;
	 float Rmax=radio+ANCHO/2;

	 float Xmin=xc-despla_max; 	// Xmin and Xmax are boundaries of coordinates of initial center
	 float Xmax=xc+despla_max;
	 float Ymin=yc-despla_max;	// Ymin and Ymax are boundaries of coordinates of initial center
	 float Ymax=yc+despla_max;

	 float lmax=(Rmax-Rmin)/PASO_RADIO+1;

	 for (float r=Rmin; r < Rmax; r+=PASO_RADIO){					// Para un rango de radios realiza
		 ImageValInt votacion = crear_votacion(val, r*r, Xmin, Xmax, Ymin, Ymax, paso);

	 }

 }

ImageValInt crear_votacion(ImageValInt val, int r2, float Xmin, float Xmax, float Ymin, float Ymax, float paso){
	 int size_val = val.size();
	 int dimensionAcumulador=floor((Xmax-Xmin)/paso)+1;
	 ImageValInt acu_ini(dimensionAcumulador*dimensionAcumulador);

	 int y, x;
	 float det;
	 float b;
	 int bb, aa;
	 for(int k=0; k < size_val/2; k++){
		 //Extraemos las coordenadas del punto
		 y = val[2*k];
		 x = val[2*k+1];

		 for(float a = Xmin; a < Xmax; a+=paso){		// a es la coordenada del centro X xc
			 det=r2-(x-a)*(x-a);

			 if (det>0){
				b=(y-sqrt(det));
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
	 return acu_ini;
}

int maximumValue(ImageValInt val)
{
     int length = val.size( );  // establish size of array
     int max = val[0];       // start with max = first element
     int Ymax,Xmax;			//Coordinates of local maximum

     for(int y = 0; y < dimY; y++){
     		for(int x = 0; x < dimX; x++){
     			if ( val[ind(y,x)]>max){
     				Ymax=y;
     				Xmax=x;
     				max = val[ind(y,x)];
     			}
     		}
     	}
     return max;                // return highest value in array
}








