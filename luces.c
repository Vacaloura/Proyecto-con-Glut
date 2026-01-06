/*************************************************************************/
/*                                                                       */
/*   luces.c		                                                     */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include "glut.h"

/*********************** DEFINICION DE LUCES ****************************/
/******************************************************************************************/
/* Define y activa la luz 0                                                               */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Luz0 (void)
{
	GLfloat luz0_posicion[] = { 5.0f, 6.0f, 8.0f, 1.0f };

	/* Ambiente reducido, difusa fuerte, especular intensa */
	GLfloat luz0_ambiente[] = { 0.05f, 0.04f, 0.00f, 1.0f };
	GLfloat luz0_difusa[] = { 0.60f, 0.56f, 0.12f, 1.0f };
	GLfloat luz0_especular[] = { 1.00f, 1.00f, 0.60f, 1.0f };

	/* Aplicar parámetros a la luz */
	glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz0_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz0_especular);

	/* Atenuación para que se difumine según nos alejemos */
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005f);

	glEnable(GL_LIGHT0);
}

/******************************************************************************************/
/* Define y activa la luz 1                                                               */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Luz1(void)
{
}

/******************************************************************************************/
/* Define y activa la luz 2                                                               */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Luz2 (void)
{
}

/******************************************************************************************/
/* Define y activa la niebla                                                              */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Niebla (void)
{
}

/********************** RUTINA DE INICIO *************************/
/******************************************************************************************/
/* Inicia los parametros de iluminacion de OpenGL                                         */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaLuces(void)
{
	GLfloat lmodel_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	/* Parámetros del modelo de iluminación */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	/* Activa la iluminación de la escena */
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	Luz0();
}
