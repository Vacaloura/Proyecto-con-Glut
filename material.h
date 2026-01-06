/*************************************************************************/
/*                                                                       */
/*   material.h												             */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H

/*********************** DECLARACION DE CONSTANTES ***********************/
#define anchoTextura 256
#define altoTextura  256
#define numTextura      10       

/***************** DECLARACION DE LA VARIABLES GLOBALES  *****************/
GLubyte textura[numTextura][anchoTextura][altoTextura][3];

/* Inicia OpenGL para poder definir las propiedades de los materiales */
void IniciaMaterial(void);

/* Lee una imagen de textura en formato tga */
void leerTextura (char *fichero, int num);
void initTextura0(char *fichero);
void textura0(void);
void initTextura1(char *fichero);
void textura1(void);
void initTextura2(char *fichero);
void textura2(void);
void initTextura3(char *fichero);
void textura3(void);
void initTextura4(char *fichero);
void textura4(void);
void initTextura5(char* fichero);
void textura5(void);
void initTextura6(char* fichero);
void textura6(void);
void initTextura7(char* fichero);
void textura7(void);
#endif