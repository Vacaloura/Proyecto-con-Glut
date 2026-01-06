/*************************************************************************/
/*                                                                       */
/*   examinar.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include "glut.h"
#include <stdio.h>
#include <math.h>
#include "examinar.h"
#include "glig.h"
#include "luces.h"
#include "material.h"
#include "modelado.h"


/******************************************************************************************/
/* Establece el area visible y el tipo de proyeccion                                      */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana(GLsizei ancho, GLsizei alto)
{
	if (alto <= 0) alto = 1;

	glViewport(0, 0, ancho, alto);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)ancho / (GLdouble)alto, 1.0, 400.0);
}

/******************************************************************************************/
/* Abre una ventana OpenGL                                                                */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void AbreVentana (int numeroArgumentos, char ** listaArgumentos)
{
	glutInit(&numeroArgumentos, listaArgumentos);
	/* Cambia los parametros para utilizar doble buffer */
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (VentanaAncho, VentanaAlto);
	glutInitWindowPosition (VentanaX, VentanaY);
	glutCreateWindow (listaArgumentos[0]);
	glutDisplayFunc (Dibuja);
	glutReshapeFunc (TamanyoVentana);
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado                                     */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Teclado (unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
		case 27 : /* Codigo de la tecla de Escape */
			exit (0);
			break;

		case 'w' :
			modo = WALK;
			printf ("Modo = WALK      \r");
			break;

		case 'e' :
			modo = EXAMINAR;
			printf ("Modo = EXAMINAR    \r");
			break;

		case 'f' :
			modo = FLY;
			printf ("Modo = FLY      \r");
			break;
	}
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado ampliado                            */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TecladoAmpliado (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_PAGE_UP :
			if (modo == FLY)
			{
				beta = beta + 1.50;
				if (beta > 360.0) beta = beta - 360.0;
				iy = oy + PASO * sin (grad2rad (beta));
			}
			break;
		case GLUT_KEY_UP : /* Pulsacion cursor arriba del teclado ampliado */
			if (modo == WALK || modo == FLY)
			{
				ox = ix;
				oz = iz;
				ix = ox + PASO * sin(grad2rad(alfa));
				iz = oz - PASO * cos(grad2rad(alfa));
				if (modo == FLY)
				{
					oy = iy;
					iy = iy + PASO * sin (grad2rad (beta));
				}
			}
			else if (modo == EXAMINAR)
			{
				beta = beta + 1.50;
				if (beta > 360.0) beta = beta - 360.0;
				iy = oy + PASO * sin (grad2rad (beta));
			}
			break;

		case GLUT_KEY_PAGE_DOWN :
			if (modo == FLY)
			{
				beta = beta - 1.50;
				if (beta > 360.0) beta = beta - 360.0;
				iy = oy + PASO * sin (grad2rad (beta));
			}
			break;
		case GLUT_KEY_DOWN : /* Pulsacion cursor abajo del teclado ampliado */
			if (modo == WALK || modo == FLY)
			{
				ox = ox - (ix-ox);
				oz = oz - (iz-oz);
				ix = ox + PASO * sin(grad2rad(alfa));
				iz = oz - PASO * cos(grad2rad(alfa));
				if (modo == FLY)
				{
					iy = oy;
					oy = oy - PASO * sin (grad2rad (beta));
				}
			}
			else if (modo == EXAMINAR)
			{
				beta = beta - 1.50;
				if (beta < 0.0) beta = beta + 360.0;
				iy = oy + PASO * sin (grad2rad (beta));
			}
			break;

		case GLUT_KEY_RIGHT : /* Pulsacion cursor derecha del teclado ampliado */
			alfa = alfa + 15.0;
			if (alfa > 360.0) alfa = alfa - 360.0;
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			break;

		case GLUT_KEY_LEFT : /* Pulsacion cursor izquierda del teclado ampliado */
			alfa = alfa - 15.0;
			if (alfa < 0.0) alfa = alfa + 360.0;
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			break;
	}
	glutPostRedisplay ();
}

/******************************************************************************************/
/* Inicia las funciones de callback                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaFuncionesCallback (void)
{
	glutKeyboardFunc (Teclado);
	glutSpecialFunc (TecladoAmpliado);
}

/******************************************************************************************/
/* Funcion de dibujado                                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Dibuja (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    /* Transformacion de la camara */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt (ox, oy, oz, ix, iy, iz, 0, 1, 0);

	/* Defino y activo las luces */
	Luz0 ();

	/* Llamadas a las display lists */
	glCallList (escena);

	/* Utiliza la funcion de la glut que intercambia los buffers */
	glutSwapBuffers ();
}

/******************************************************************************************/
/* Inicia caracteristicas de la visualizacion OpenGL                                      */
/* Parametros: Ninguno.                                                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaOpenGL (void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f); /* Establece el color de borrado */
	//glColor3f (1.0f, 1.0f, 1.0f); /* Establece el color de dibujo */

	/* Especifica el tipo de la comparación en el Z-buffer */
	//glDepthFunc (GL_LEQUAL);

	/* Activa el Z-buffer */
	glEnable (GL_DEPTH_TEST);

	/* Habilita eliminación de caras */
	//glCullFace (GL_BACK);
	glEnable (GL_CULL_FACE);

	/* Elige las caras a eliminar y define que se va a pintar en sentido horario*/
	glFrontFace (GL_CW);

	/* Sombreado suave */
	glShadeModel(GL_SMOOTH);

	/* Inicia las luces */
	IniciaLuces();

	/* Inicia los materiales */
	IniciaMaterial();
}

/******************************************************************************************/
/* Funcion principal                                                                      */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Un entero que se devuelve al sistema al acabar la ejecucion del programa       */
/******************************************************************************************/
int main(int numArgumentos, char ** listaArgumentos)
{	
	/* Creación de la ventana de la aplicación */
	AbreVentana (numArgumentos, listaArgumentos);

	/* Llamada a las funciones de inicializacion */
	IniciaOpenGL ();

	/* Rutinas para el control de eventos */
    IniciaFuncionesCallback ();

	initTextura0 ("cerezo.tga");
	initTextura1 ("tronco.tga");
	initTextura2 ("cesped.tga");
	initTextura3("camino.tga");
	initTextura4("madera_roja_vertical.tga");
	initTextura5("pared.tga");
	initTextura6("techo.tga");
	initTextura7("cielo.tga");

	/* Creo la display list de la escena */
	CreaEscenaIluminacion ();

	printf ("Modo = WALK\r");
	
	/* A la espera de eventos.... */
	glutMainLoop();

	return (0);
}

