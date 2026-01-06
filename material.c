/*************************************************************************/
/*                                                                       */
/*   material.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include <stdio.h>
#include "glut.h"
#include "material.h"


/********************** RUTINA DE INICIO **************************************************/
/******************************************************************************************/
/* Inicia OpenGL para poder definir las propiedades de los materiales                     */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaMaterial(void)
{
	glColorMaterial(GL_FRONT,GL_DIFFUSE);

}


/*********************** ESPECIFICACIÓN DE TEXTURAS****************************************/
/******************************************************************************************/
/* Lee una imagen de textura en formato tga                                               */
/* Parametros --> char *fichero : Cadena de caracteres con el nombre del fichero          */
/*				  int num: Numero que identifica la textura                               */
/* Salido --> Ninguna                                                                     */
/******************************************************************************************/
void leerTextura(char* fichero, int num)
{
	FILE* tga;
	errno_t error = fopen_s(&tga, fichero, "rb");
	if (error != 0) {
		printf("Error abriendo el fichero: %s\n", fichero);
		return;
	}

	unsigned char cabecera[18];
	if (fread(cabecera, 1, 18, tga) != 18) {
		printf("Error leyendo cabecera TGA: %s\n", fichero);
		fclose(tga);
		return;
	}

	int id_longitud = cabecera[0];
	int mapa_color = cabecera[1];
	int tipo_imagen = cabecera[2]; 
	int ancho = cabecera[12] | (cabecera[13] << 8);
	int alto = cabecera[14] | (cabecera[15] << 8);
	int bits_por_pix = cabecera[16];
	int bytesPorPixel = bits_por_pix / 8;

	if (id_longitud > 0) fseek(tga, id_longitud, SEEK_CUR);

	/* Sólo manejamos truecolor 24/32 bpp */
	if ((tipo_imagen != 2 && tipo_imagen != 10) || (bytesPorPixel != 3 && bytesPorPixel != 4)) {
		printf("Formato TGA no soportado: tipo=%d, bpp=%d (%s)\n", tipo_imagen, bits_por_pix, fichero);
		fclose(tga);
		return;
	}

	const int contPixel = ancho * alto;
	int pixelActual = 0;

	if (tipo_imagen == 2) {
		/* leer píxeles uno a uno */
		for (int j = alto - 1; j >= 0; --j) {
			for (int i = ancho - 1; i >= 0; --i) {
				unsigned char b = 0, g = 0, r = 0, a = 255;
				if (fread(&b, 1, 1, tga) != 1 || fread(&g, 1, 1, tga) != 1 || fread(&r, 1, 1, tga) != 1) {
					printf("Lectura inesperada del TGA (sin compresion): %s\n", fichero);
					fclose(tga);
					return;
				}
				if (bytesPorPixel == 4) fread(&a, 1, 1, tga); 
				textura[num][j][i][0] = (GLubyte)r;
				textura[num][j][i][1] = (GLubyte)g;
				textura[num][j][i][2] = (GLubyte)b;
				++pixelActual;
			}
		}
	}
	else {
		/* RLE compressed (tipo 10) */
		pixelActual = 0;
		while (pixelActual < contPixel) {
			unsigned char packetCabecera;
			if (fread(&packetCabecera, 1, 1, tga) != 1) break;
			int cont = (packetCabecera & 0x7F) + 1;
			if (packetCabecera & 0x80) {
				/* siguiente píxel repetido 'cont' veces */
				unsigned char b = 0, g = 0, r = 0, a = 255;
				if (fread(&b, 1, 1, tga) != 1 || fread(&g, 1, 1, tga) != 1 || fread(&r, 1, 1, tga) != 1) {
					printf("Error RLE: %s\n", fichero);
					break;
				}
				if (bytesPorPixel == 4) fread(&a, 1, 1, tga);
				for (int k = 0; k < cont && pixelActual < contPixel; ++k, ++pixelActual) {
					int py = alto - 1 - (pixelActual / ancho);
					int px = ancho - 1 - (pixelActual % ancho);
					textura[num][py][px][0] = (GLubyte)r;
					textura[num][py][px][1] = (GLubyte)g;
					textura[num][py][px][2] = (GLubyte)b;
				}
			}
			else {
				/* leer 'cont' píxeles directamente */
				for (int k = 0; k < cont && pixelActual < contPixel; ++k, ++pixelActual) {
					unsigned char b = 0, g = 0, r = 0, a = 255;
					if (fread(&b, 1, 1, tga) != 1 || fread(&g, 1, 1, tga) != 1 || fread(&r, 1, 1, tga) != 1) {
						printf("Error RLE raw: %s\n", fichero);
						break;
					}
					if (bytesPorPixel == 4) fread(&a, 1, 1, tga);
					int py = alto - 1 - (pixelActual / ancho);
					int px = ancho - 1 - (pixelActual % ancho);
					textura[num][py][px][0] = (GLubyte)r;
					textura[num][py][px][1] = (GLubyte)g;
					textura[num][py][px][2] = (GLubyte)b;
				}
			}
		}
	}

	fclose(tga);
}

/*********************** RUTINA DE CARGA Y ACTIVACION DE TEXTURAS *************************/
/******************************************************************************************/
/******************************************************************************************/
void initTextura0(char *fichero)
{
	leerTextura (fichero,0);
}

void textura0(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}


/******************************************************************************************/
/******************************************************************************************/
void initTextura1(char *fichero)
{ 
	leerTextura (fichero,1);
}

void textura1(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}


/******************************************************************************************/
/******************************************************************************************/
void initTextura2(char *fichero)
{
	leerTextura (fichero,2);
}

void textura2(void)
{ 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[2]); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glEnable (GL_TEXTURE_2D);
}

/******************************************************************************************/
/******************************************************************************************/
void initTextura3(char* fichero)
{
	leerTextura(fichero, 3);
}

void textura3(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/******************************************************************************************/
void initTextura4(char* fichero)
{
	leerTextura(fichero, 4);
}
void textura4(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/******************************************************************************************/
void initTextura5(char* fichero)
{
	leerTextura(fichero, 5);
}
void textura5(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/******************************************************************************************/
void initTextura6(char* fichero)
{
	leerTextura(fichero, 6);
}
void textura6(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/******************************************************************************************/
void initTextura7(char* fichero)
{
	leerTextura(fichero, 7);
}
void textura7(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[7]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}