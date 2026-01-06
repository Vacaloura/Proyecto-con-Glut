/*************************************************************************/
/*                                                                       */
/*   examinar.h                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

#ifndef EXAMINAR_H
#define EXAMINAR_H

/* Funcion de conversion de grados a radianes */
#define  grad2rad(x)  ((float) (3.14159 * x) / 180.0)
#define PASO 0.5 /* Definicion del paso para el movimiento del observador */

#define WALK 1
#define EXAMINAR 2
#define FLY 3

/* Variables Globales del modulo */
int VentanaAncho = 500, VentanaAlto = 500; /* Tamanyo de la ventana */
int VentanaX = 100, VentanaY = 100; /* Posicion de la ventana */
GLdouble  alfa = 0.0, beta = 0.0, gamma=0.0, z=0.0;
GLuint cuadrica;
double ox=0.0, oy=0.0, oz=5.0; /* Posicion del observador */
double ix=0.0, iy=0.0, iz=5.0-PASO; /* Posicion del punto de interes */
int w=1, a=1;
int modo = WALK;

/* Abre una ventana OpenGL */
void AbreVentana (int numeroArgumentos, char ** listaArgumentos);

/* Inicia parametros de la OpenGL */
void IniciaOpenGL (void);

/* Funcion de dibujado */
void Dibuja(void);

/* Establece el area visible */
void TamanyoVentana (int alto, int ancho);

/* Inicia las funciones de Callback */
void IniciaFuncionesCallback (void);

/* Define las acciones tras una pulsacion del teclado */
void Teclado (unsigned char tecla, int x, int y);

#endif