#include "houghUtilities.h"
#include <opencv2/opencv.hpp>
using namespace cv;

/**
 * Funcion hough
 *
 */

ImageValFloat hough(ImageValInt val, float radio, float paso, float yc, float xc, int despla_max){
	 float Rmin=radio-ANCHO/2;
	 float Rmax=radio+ANCHO/2;

	 float Xmin=xc-despla_max; 	// Xmin and Xmax are boundaries of coordinates of initial center
	 float Xmax=xc+despla_max;
	 float Ymin=yc-despla_max;	// Ymin and Ymax are boundaries of coordinates of initial center
	 float Ymax=yc+despla_max;

	 float lmax=(Rmax-Rmin)/PASO_RADIO+1;
	 int dimensionAcumulador=floor((Xmax-Xmin)/paso)+1;

	 ImageValFloat matrix(lmax*4);

	 cout << "Lmax: " << lmax << "\t" << Xmax << "\t" << Ymax << "\t" << dimensionAcumulador <<  endl;
	 int count = 0;
	 for (float r=Rmin; r < Rmax; r+=PASO_RADIO){					// Para un rango de radios realiza

		 ImageValInt votacion = crear_votacion(val, r*r, dimensionAcumulador, Xmin, Xmax, Ymin, Ymax, paso);


		 cout << "Maximo Metodo: " << votacion.max() << endl << endl;
		 float *max = maximumValue(votacion, dimensionAcumulador);
		 cout << "Maximo: " << max[0] << "\t" << max[1] << "\t" << max[2] <<  endl;

		 matrix[count] = max[2];							//Valor
		 matrix[count+1] = (float)(max[0])*paso + Ymin;		//Y
		 matrix[count+2] = (float)(max[1])*paso + Xmin;		//X
		 matrix[count+3] = r;								//Radio
		 count+=4;
	 }
	 return matrix;
 }

ImageValInt crear_votacion(ImageValInt& val, int r2, int dimensionAcumulador, float Xmin, float Xmax, float Ymin, float Ymax, float paso){
	 int size_val = val.size();
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
	 return acu_ini;
}

float* maximumValue(ImageValInt& val, int dimensionAcumulador)
{
     static float array [3]= {0,0,0};
     float *max = array;
     float* ker;
     max[2] = 0;

     static int array_ant [3]= {0,0,0};
     int *max_ant = array_ant;
     max_ant[2] = val[0];

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
			cout << "Y: " << j << "\tX:" << i <<  endl;
			if ( ker[2] > max[2]){
				max[0] = ker[0];						// Coordenada Y
				max[1] = ker[1];						// Coordenada X
				max[2] = ker[2];						// Valor maximo de acu_ini
			}
		}
	 }

     return max;                // return max
}


float* kernel(ImageValInt& val, int y, int x, int dimensionAcumulador){
	static float array [3]= {0,0,0};
	float *max = array;
	//max[2] = ((float)(val[(y-1)*dimensionAcumulador+(x-1)]) + (float)(val[(y-1)*dimensionAcumulador+(x)]) + (float)(val[(y-1)*dimensionAcumulador+(x+1)])
	//		+ (float)(val[(y)*dimensionAcumulador+(x-1)])+ (float)(val[(y)*dimensionAcumulador+(x)]) + (float)(val[(y)*dimensionAcumulador+(x+1)])
	//		+ (float)(val[(y+1)*dimensionAcumulador+(x-1)]) + (float)(val[(y+1)*dimensionAcumulador+(x)]) + (float)(val[(y+1)*dimensionAcumulador+(x+1)]))/9.0;

	int pos;
	float sumatorio = 0;
	float sum_x = 0.0;
	float sum_y = 0.0;
	for(int j = -1; j < 2; j++){
		for(int i = -1; i < 2; i++){
			pos = val[(y+j)*dimensionAcumulador + (x+i)];
			sumatorio += pos;
			sum_x += (x+i)*pos;
			sum_y += (y+j)*pos;
		}
	}

	max[0] = sum_y/sumatorio;
	max[1] = sum_x/sumatorio;
	max[2] = sumatorio/9;

	return max;
}




/*
 *
 * int* maximumValue(ImageValInt val, int dimensionAcumulador)
{
     static int array [3]= {0,0,0};
     int *max = array;
     max[2] = val[0];

     for(int y = 1; y < dimensionAcumulador; y++){
		for(int x = 1; x < dimensionAcumulador; x++){
			if ( val[y*dimensionAcumulador + x]>max[2]){
				max[0]=y;						// Coordenada Y
				max[1]=x;						// Coordenada X
				max[2] = val[y*dimensionAcumulador + x];			// Valor maximo de acu_ini
			}
		}
	 }

     return max;                // return max
}

float* centroide(ImageValInt val, int dimensionAcumulador){
	static float array [2]= {0,0};
	float *centros = array;

	float sum_x =0;
	float sum_y =0;
	int num_pixeles=0;


	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(val[y*3 + x] != 0){
				num_pixeles++;
				sum_x = sum_x + x;
	            sum_y = sum_y + y;
			}
		}
	}

	centros[0] = sum_y/num_pixeles;
	centros[1] = sum_x/num_pixeles;

	return centros;
}
 *
 */





/*
 *
 *
 * [filas,columnas] = size(B);

sum_i =0;
sum_j =0;
num_pixeles=0;


for(int y = 0; y < dimensionAcumulador; y++){
	for(int x = 0; x < dimensionAcumulador; x++){
		if(val[y*dimensionAcumulador + x] != 0){
			num_pixeles++;
			sum_x = sum_x + x;
            sum_y = sum_y + y;
		}
	}
}

cx = sum_x/num_pixeles;
cy = sum_y/num_pixeles;

for i = 1:filas
    for j = 1: columnas
        if (B(i,j)~=0)
            num_pixeles= num_pixeles + 1;
            sum_i = sum_i + i;
            sum_j = sum_j + j;
        end
    end
end

%coord.del centroide en (filas, columnas)
ci = sum_i/num_pixeles;
cj = sum_j/num_pixeles;
centro = [ci, cj];
 */









