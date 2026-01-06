/*************************************************************************/
/*                                                                       */
/*                 glig.c LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "glig.h"

#define PI 3.1415926535897932
#define ALFA (0.5-v)*PI
#define BETA 2*PI*u
#define E 0.001
#define F 0.002

/************************* FUNCIONES BASICAS **********************************************/
/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada x de un punto en R3                                              */
/******************************************************************************************/
float xSuperQuadric (float u, float v, float R, float s1, float s2)
{
	float cosalfa, cosbeta, powcosalfa, powcosbeta;

	cosalfa = (float)cos(ALFA);
	cosbeta = (float)cos(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa =(float) - pow(- cosalfa,s1);

	if(cosbeta > 0.0)
		powcosbeta = (float)pow(cosbeta,s2);
	else
		powcosbeta = (float) - pow(- cosbeta,s2);

	return (R*powcosalfa*powcosbeta);

}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada y de un punto en R3                                              */
/******************************************************************************************/
float ySuperQuadric (float u, float v, float R, float s1, float s2)
{
	float sinalfa, powsinalfa;

	sinalfa = (float)sin(ALFA);

	if(sinalfa > 0.0)
		powsinalfa = (float)pow(sinalfa,s1);
	else
		powsinalfa = (float)- pow(- sinalfa,s1);

	return (R*powsinalfa);
}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada z de un punto en R3                                              */
/******************************************************************************************/
float zSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, sinbeta, powcosalfa, powsinbeta;

	cosalfa = (float)cos(ALFA);
	sinbeta=(float)sin(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa=(float) - pow(- cosalfa,s1);

	if(sinbeta > 0.0)
		powsinbeta = (float)pow(sinbeta,s2);
	else
		powsinbeta = (float) - pow(- sinbeta,s2);

	return(R*powcosalfa*powsinbeta);
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con u                                                        */
/******************************************************************************************/
float dxuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u+E,v,R,s1,s2)-xSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u+E,v,R,s1,s2)-ySuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u+E,v,R,s1,s2)-zSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con v                                                        */
/******************************************************************************************/
float dxvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u,v+E,R,s1,s2)-xSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u,v+E,R,s1,s2)-ySuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u,v+E,R,s1,s2)-zSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la componente x del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente x del vector normal                                                 */
/******************************************************************************************/
float nxSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dyuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2)-
		dyvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente y del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente y del vector normal                                                 */
/******************************************************************************************/
float nySuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2)-
		dxuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente z del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente z del vector normal                                                 */
/******************************************************************************************/
float nzSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxuSuperQuadric(u,v,R,s1,s2)*dyvSuperQuadric(u,v,R,s1,s2)-
		dxvSuperQuadric(u,v,R,s1,s2)*dyuSuperQuadric(u,v,R,s1,s2));
}


/********************** RUTINA DE DIBUJO *********************************/
/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    int i;
	int j;

    v = 0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j <= pv; j++)
	{
		glBegin (GL_LINE_LOOP); 
			for (i= 0; i< pu; i++)
			{ 
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}

	v = 0.0f;
	u = 0.0f;
	for (i = 0; i < pu; i++)
	{
		glBegin (GL_LINE_STRIP);
			for (j = 0; j <= pv; j++)
			{
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				v = v + inc_v;
			}
		glEnd ();
		u = u + inc_u;
		v = 0.0f;
	}
}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireRulo (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}



/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireDado (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f);
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSemiSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCone (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}

/******************************************************************************************/
/* Crea un cilindro a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCilindro(int pu, int pv)
{
	igCreateQuadricObject(pu, pv, 1.0f, 1.0f, 0.5f, 0.01f, 1.0f);
}

/******************************************************************************************/
/* Dibuja un cono de arista unidad y centrado en el origen                                */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCube (void)
{
	float vertices[8][3] = {{0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},
							{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}};

	glBegin (GL_LINE_LOOP);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[1]);
		glVertex3fv (vertices[2]);
		glVertex3fv (vertices[3]);
	glEnd ();

	glBegin (GL_LINE_LOOP);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[6]);
		glVertex3fv (vertices[7]);
	glEnd ();

	glBegin (GL_LINES);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[1]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[2]);
		glVertex3fv (vertices[6]);
		glVertex3fv (vertices[3]);
		glVertex3fv (vertices[7]);
	glEnd ();
}


/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateSolidQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    float nx, ny, nz; 
    int i;
	int j;

    v = 0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j < pv; j++)
	{
		glBegin (GL_TRIANGLE_STRIP); 
			for (i= 0; i<= pu; i++)
			{ 
				glTexCoord2f (u, v);
				nx = nxSuperQuadric (u, v, R, s1, s2);
				ny = nySuperQuadric (u, v, R, s1, s2);
				nz = nzSuperQuadric (u, v, R, s1, s2);
				glNormal3f (nx, ny, nz);
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z);
				
				glTexCoord2f (u, v+inc_v);
				nx = nxSuperQuadric (u, v+inc_v, R, s1, s2);
				ny = nySuperQuadric (u, v+inc_v, R, s1, s2);
				nz = nzSuperQuadric (u, v+inc_v, R, s1, s2);
				glNormal3f (nx, ny, nz);
				x= xSuperQuadric (u, v+inc_v, R, s1, s2); 
				y= ySuperQuadric (u, v+inc_v, R, s1, s2); 
				z= zSuperQuadric (u, v+inc_v, R, s1, s2); 
				glVertex3f (x, y, z); 
				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}
}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSphere (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidRulo (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}


/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidDado (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f);
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSemiSphere (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCone (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cilindro a partir de las ecuaciones de la supercuadrica                        */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCilindro(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 1.0f, 0.5f, 0.01f, 1.0f);
}

/******************************************************************************************/
/* Dibuja un cono de arista unidad y centrado en el origen                                */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCube (void)
{
	float vertices[8][3] = {{0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},
							{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}};

	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f (1.0f, 0.0f, 0.0f);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[1]);
		glNormal3f (0.0f, 0.0f, -1.0f);
		glVertex3fv (vertices[6]);
		glVertex3fv (vertices[2]);
		glNormal3f (-1.0f, 0.0f, 0.0f);
		glVertex3fv (vertices[7]);
		glVertex3fv (vertices[3]);
		glNormal3f (0.0f, 0.0f, 1.0f);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[0]);
	glEnd ();

	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f (0.0f, 1.0f, 0.0f);
		glVertex3fv (vertices[1]);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[2]);
		glVertex3fv (vertices[3]);
	glEnd ();

	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f (0.0f, -1.0f, 0.0f);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[7]);
		glVertex3fv (vertices[6]);
	glEnd ();
}

/******************************************************************************************/
/* Dibuja un triangulo rectangulo estirado centrado en el origen                          */
/* Parametros: Longitud                                                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidTejado(float longitud)
{
	const float alturaTejado = 1.0f;
	const float baseTejado = 0.75f;
	float mitad = longitud * 0.5f;

	/* Tamaño en unidades mundo */
	const float tamPieza = 0.5f;

	GLboolean cullEnabled = glIsEnabled(GL_CULL_FACE);
	if (cullEnabled) glDisable(GL_CULL_FACE);

	/* Triángulo extremo - mitad */
	glBegin(GL_TRIANGLES);
	{
		float x, y, z, u, v;

		x = -mitad; y = 0.0f; z = 0.0f;
		glNormal3f(-1.0f, 0.0f, 0.0f);
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = -mitad; y = -alturaTejado; z = baseTejado;
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = -mitad; y = -alturaTejado; z = 0.0f;
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);
	}
	glEnd();

	/* Triángulo extremo + mitad  */
	glBegin(GL_TRIANGLES);
	{
		float x, y, z, u, v;

		x = mitad; y = 0.0f; z = 0.0f;
		glNormal3f(1.0f, 0.0f, 0.0f);
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = mitad; y = -alturaTejado; z = 0.0f;
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = mitad; y = -alturaTejado; z = baseTejado;
		u = x / tamPieza; v = z / tamPieza;
		glTexCoord2f(u, v); glVertex3f(x, y, z);
	}
	glEnd();

	/* Cara interior (pegada al muro) */
	glBegin(GL_QUADS);
	{
		float x, y, z, u, v;
		glNormal3f(0.0f, 0.0f, -1.0f);

		x = -mitad; y = 0.0f; z = 0.0f; u = x / tamPieza; v = 0.0f;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = -mitad; y = -alturaTejado; z = 0.0f; u = x / tamPieza; v = 0.0f;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = mitad; y = -alturaTejado; z = 0.0f; u = x / tamPieza; v = 0.0f;
		glTexCoord2f(u, v); glVertex3f(x, y, z);

		x = mitad; y = 0.0f; z = 0.0f; u = x / tamPieza; v = 0.0f;
		glTexCoord2f(u, v); glVertex3f(x, y, z);
	}
	glEnd();

	/* Cara inferior (parte hacia abajo y exterior) */
	glBegin(GL_QUADS);
	{
		float v0x = -mitad, v0y = -alturaTejado, v0z = 0.0f;
		float v1x = mitad,  v1y = -alturaTejado, v1z = 0.0f;
		float v2x = mitad,  v2y = -alturaTejado, v2z = baseTejado;
		float v3x = -mitad, v3y = -alturaTejado, v3z = baseTejado;
		glNormal3f(0.0f, -1.0f, 0.0f);

		glTexCoord2f(v0x / tamPieza, v0z / tamPieza); glVertex3f(v0x, v0y, v0z);
		glTexCoord2f(v1x / tamPieza, v1z / tamPieza); glVertex3f(v1x, v1y, v1z);
		glTexCoord2f(v2x / tamPieza, v2z / tamPieza); glVertex3f(v2x, v2y, v2z);
		glTexCoord2f(v3x / tamPieza, v3z / tamPieza); glVertex3f(v3x, v3y, v3z);
	}
	glEnd();

	/* Cara inclinada exterior (hipotenusa) */
	{
		float v0x = -mitad, v0y = 0.0f, v0z = 0.0f;
		float v1x = -mitad, v1y = -alturaTejado, v1z = baseTejado;
		float v2x = mitad,  v2y = -alturaTejado, v2z = baseTejado;
		float v3x = mitad,  v3y = 0.0f, v3z = 0.0f;

		float ax = v1x - v0x, ay = v1y - v0y, az = v1z - v0z;
		float bx = v3x - v0x, by = v3y - v0y, bz = v3z - v0z;
		float nx = ay * bz - az * by;
		float ny = az * bx - ax * bz;
		float nz = ax * by - ay * bx;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong == 0.0f) nlong = 1.0f;
		nx /= nlong; ny /= nlong; nz /= nlong;

		glBegin(GL_QUADS);
		glNormal3f(nx, ny, nz);

		glTexCoord2f(v0x / tamPieza, v0z / tamPieza); glVertex3f(v0x, v0y, v0z);
		glTexCoord2f(v1x / tamPieza, v1z / tamPieza); glVertex3f(v1x, v1y, v1z);
		glTexCoord2f(v2x / tamPieza, v2z / tamPieza); glVertex3f(v2x, v2y, v2z);
		glTexCoord2f(v3x / tamPieza, v3z / tamPieza); glVertex3f(v3x, v3y, v3z);

		glEnd();
	}

	if (cullEnabled) glEnable(GL_CULL_FACE);
}


/******************************************************************************************/
/* Dibuja un triangulo base triangular centrado en el origen                              */
/* Parametros: alturaTejado y baseTejado                                                  */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidEsquinaTejado(float alturaTejado, float baseTejado)
{
	GLboolean cullEnabled = glIsEnabled(GL_CULL_FACE);
	if (cullEnabled) glDisable(GL_CULL_FACE);

	const float tamPieza = 0.5f;

	float apice[3] = { 0.0f, 0.0f, 0.0f };
	float parte_atras[3] = { 0.0f, -alturaTejado, 0.0f };
	float borde_z[3] = { 0.0f, -alturaTejado, baseTejado };
	float borde_x[3] = { baseTejado, -alturaTejado, 0.0f };
	float esquina_externa[3] = { baseTejado, -alturaTejado, baseTejado };

	/* Cara 1 */
	{
		float ax = borde_z[0] - apice[0], ay = borde_z[1] - apice[1], az = borde_z[2] - apice[2];
		float bx = esquina_externa[0] - apice[0], by = esquina_externa[1] - apice[1], bz = esquina_externa[2] - apice[2];
		float nx = ay * bz - az * by, ny = az * bx - ax * bz, nz = ax * by - ay * bx;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = 1.0f; nz = 0.0f; }

		glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glTexCoord2f(apice[0] / tamPieza, apice[2] / tamPieza); glVertex3fv(apice);
		glTexCoord2f(borde_z[0] / tamPieza, borde_z[2] / tamPieza); glVertex3fv(borde_z);
		glTexCoord2f(esquina_externa[0] / tamPieza, esquina_externa[2] / tamPieza); glVertex3fv(esquina_externa);
		glEnd();
	}

	/* Cara 2 */
	{
		float ax = esquina_externa[0] - apice[0], ay = esquina_externa[1] - apice[1], az = esquina_externa[2] - apice[2];
		float bx = borde_x[0] - apice[0], by = borde_x[1] - apice[1], bz = borde_x[2] - apice[2];
		float nx = ay * bz - az * by, ny = az * bx - ax * bz, nz = ax * by - ay * bx;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = 1.0f; nz = 0.0f; }

		glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glTexCoord2f(apice[0] / tamPieza, apice[2] / tamPieza); glVertex3fv(apice);
		glTexCoord2f(esquina_externa[0] / tamPieza, esquina_externa[2] / tamPieza); glVertex3fv(esquina_externa);
		glTexCoord2f(borde_x[0] / tamPieza, borde_x[2] / tamPieza); glVertex3fv(borde_x);
		glEnd();
	}

	/* Cara 3 */
	{
		float ax = borde_x[0] - apice[0], ay = borde_x[1] - apice[1], az = borde_x[2] - apice[2];
		float bx = parte_atras[0] - apice[0], by = parte_atras[1] - apice[1], bz = parte_atras[2] - apice[2];
		float nx = ay * bz - az * by, ny = az * bx - ax * bz, nz = ax * by - ay * bx;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = 1.0f; nz = 0.0f; }

		glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glTexCoord2f(apice[0] / tamPieza, apice[2] / tamPieza); glVertex3fv(apice);
		glTexCoord2f(borde_x[0] / tamPieza, borde_x[2] / tamPieza); glVertex3fv(borde_x);
		glTexCoord2f(parte_atras[0] / tamPieza, parte_atras[2] / tamPieza); glVertex3fv(parte_atras);
		glEnd();
	}

	/* Cara 4 */
	{
		float ax = parte_atras[0] - apice[0], ay = parte_atras[1] - apice[1], az = parte_atras[2] - apice[2];
		float bx = borde_z[0] - apice[0], by = borde_z[1] - apice[1], bz = borde_z[2] - apice[2];
		float nx = ay * bz - az * by, ny = az * bx - ax * bz, nz = ax * by - ay * bx;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = 1.0f; nz = 0.0f; }

		glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glTexCoord2f(apice[0] / tamPieza, apice[2] / tamPieza); glVertex3fv(apice);
		glTexCoord2f(parte_atras[0] / tamPieza, parte_atras[2] / tamPieza); glVertex3fv(parte_atras);
		glTexCoord2f(borde_z[0] / tamPieza, borde_z[2] / tamPieza); glVertex3fv(borde_z);
		glEnd();
	}

	/* Cara 5 */
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(parte_atras[0] / tamPieza, parte_atras[2] / tamPieza); glVertex3fv(parte_atras);
	glTexCoord2f(borde_z[0] / tamPieza, borde_z[2] / tamPieza); glVertex3fv(borde_z);
	glTexCoord2f(esquina_externa[0] / tamPieza, esquina_externa[2] / tamPieza); glVertex3fv(esquina_externa);
	glTexCoord2f(borde_x[0] / tamPieza, borde_x[2] / tamPieza); glVertex3fv(borde_x);
	glEnd();

	if (cullEnabled) glEnable(GL_CULL_FACE);
}

/******************************************************************************************/
/* Dibuja el vértice del tejado japonés con curvatura parabólica                          */
/* Parametros: uu, vv, punta, c0, c1, caraNormal, potenciaCurvatura                       */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
static void tejadoJaponesVertex(float uu, float vv, float* punta, float* c0, float* c1, float* caraNormal, float potenciaCurvatura)
{
	float w, px, py, pz;
	float nx, ny, nz, nlong;
	float distanciaCentro, factorCurva;

	w = 1.0f - uu - vv;
	if (w < 0.0f) w = 0.0f;

	/* Calcular punto intermedio dentro de la cara usando una mezcla proporcional entre sus vértices */
	px = w * punta[0] + uu * c0[0] + vv * c1[0];
	py = w * punta[1] + uu * c0[1] + vv * c1[1];
	pz = w * punta[2] + uu * c0[2] + vv * c1[2];

	/* Distancia al borde más cercano, usada para curvatura y mezcla de normales */
	distanciaCentro = w;
	if (uu < distanciaCentro) distanciaCentro = uu;
	if (vv < distanciaCentro) distanciaCentro = vv;

	distanciaCentro = distanciaCentro * 3.0f;
	if (distanciaCentro > 1.0f) distanciaCentro = 1.0f;
	if (distanciaCentro < 0.0f) distanciaCentro = 0.0f;

	/* Curvatura parabólica */
	factorCurva = distanciaCentro * distanciaCentro * potenciaCurvatura;

	/* Normal suavizada: mezcla entre normal de cara y vertical */
	{
		const float upx = 0.0f, upy = 1.0f, upz = 0.0f;
		float t = distanciaCentro; /* 0..1 */
		nx = caraNormal[0] * t + upx * (1.0f - t);
		ny = caraNormal[1] * t + upy * (1.0f - t);
		nz = caraNormal[2] * t + upz * (1.0f - t);

		/* normalizar */
		nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = 1.0f; nz = 0.0f; }

		/* Desplazamiento a lo largo de la normal suavizada */
		float offX = nx * factorCurva;
		float offY = ny * factorCurva;
		float offZ = nz * factorCurva;

		/* Evitar penetración en la arista interna */
		const float eps = 0.0005f;
		float maxBajo = py - eps;

		if (offY > 0.0f && offY > maxBajo) {
			float escala = (offY > 0.0f) ? (maxBajo / offY) : 0.0f;
			if (escala < 0.0f) escala = 0.0f;
			offX *= escala; offY *= escala; offZ *= escala;
		}

		px -= offX;
		py -= offY;
		pz -= offZ;

		/* Pequeño ajuste de normal para iluminación debido a curvatura */
		ny += factorCurva * 0.35f;
		nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
	}

	/* Coordenadas de textura para repetición */
	const float tamPieza = 0.5f;
	float u = px / tamPieza;
	float v = pz / tamPieza;

	glTexCoord2f(u, v);
	glNormal3f(nx, ny, nz);
	glVertex3f(px, py, pz);
}

/******************************************************************************************/
/* Dibuja una piramide base cuadrada con curvatura en las aristas                         */
/* Parametros: subdivisiones, tamInterno, altura, exceso, potenciaCurvatura               */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidTejadoJapones(int subdivisiones, float tamInterno, float altura, float exceso, float potenciaCurvatura)
{
	int i, j, cara;
	float mitadInterna = tamInterno * 0.5f;
	float mitadExterna = mitadInterna + exceso;
	GLboolean cullEnabled;

	/* Forzar sombreado suave localmente */
	GLint sombreado = 0;
	glGetIntegerv(GL_SHADE_MODEL, &sombreado);
	glShadeModel(GL_SMOOTH);

	/* Ápice en la parte superior, centrado */
	float punta[3] = { 0.0f, altura, 0.0f };

	/* Esquinas internas (apoyadas en y = 0) y externas (y = -exceso) */
	float esquinasInteriores[4][3] = {
		{  mitadInterna, 0.0f,  mitadInterna },
		{ -mitadInterna, 0.0f,  mitadInterna },
		{ -mitadInterna, 0.0f, -mitadInterna },
		{  mitadInterna, 0.0f, -mitadInterna }
	};

	float esquinasExteriores[4][3] = {
		{  mitadExterna, -exceso,  mitadExterna },
		{ -mitadExterna, -exceso,  mitadExterna },
		{ -mitadExterna, -exceso, -mitadExterna },
		{  mitadExterna, -exceso, -mitadExterna }
	};

	/* Normales por cara calculadas usando la arista interna para unión */
	float normales[4][3];
	for (cara = 0; cara < 4; cara++) {
		int c0idx = cara;
		int c1idx = (cara + 1) % 4;
		float* c0 = esquinasInteriores[c0idx];
		float* c1 = esquinasInteriores[c1idx];
		float v1x = c0[0] - punta[0], v1y = c0[1] - punta[1], v1z = c0[2] - punta[2];
		float v2x = c1[0] - punta[0], v2y = c1[1] - punta[1], v2z = c1[2] - punta[2];
		float nlong;
		normales[cara][0] = v1y * v2z - v1z * v2y;
		normales[cara][1] = v1z * v2x - v1x * v2z;
		normales[cara][2] = v1x * v2y - v1y * v2x;
		nlong = sqrtf(normales[cara][0] * normales[cara][0] +
			normales[cara][1] * normales[cara][1] +
			normales[cara][2] * normales[cara][2]);
		if (nlong > 1e-6f) {
			normales[cara][0] /= nlong;
			normales[cara][1] /= nlong;
			normales[cara][2] /= nlong;
		}
		else {
			normales[cara][0] = 0.0f;
			normales[cara][1] = 1.0f;
			normales[cara][2] = 0.0f;
		}
	}

	cullEnabled = glIsEnabled(GL_CULL_FACE);
	if (cullEnabled) glDisable(GL_CULL_FACE);

	/* Caras principales: desde el ápice hasta la arista interna (y = 0) */
	for (cara = 0; cara < 4; cara++) {
		int c0idx = cara;
		int c1idx = (cara + 1) % 4;
		float* c0 = esquinasInteriores[c0idx];
		float* c1 = esquinasInteriores[c1idx];
		float* fn = normales[cara];

		glBegin(GL_TRIANGLES);
		for (i = 0; i < subdivisiones; i++) {
			for (j = 0; j < subdivisiones - i; j++) {
				float u0 = (float)i / subdivisiones;
				float v0 = (float)j / subdivisiones;
				float u1 = (float)(i + 1) / subdivisiones;
				float v1 = (float)j / subdivisiones;
				float u2 = (float)i / subdivisiones;
				float v2 = (float)(j + 1) / subdivisiones;

				tejadoJaponesVertex(u0, v0, punta, c0, c1, fn, potenciaCurvatura);
				tejadoJaponesVertex(u1, v1, punta, c0, c1, fn, potenciaCurvatura);
				tejadoJaponesVertex(u2, v2, punta, c0, c1, fn, potenciaCurvatura);

				if (i + 1 + j + 1 <= subdivisiones) {
					float u3 = (float)(i + 1) / subdivisiones;
					float v3 = (float)(j + 1) / subdivisiones;
					tejadoJaponesVertex(u1, v1, punta, c0, c1, fn, potenciaCurvatura);
					tejadoJaponesVertex(u3, v3, punta, c0, c1, fn, potenciaCurvatura);
					tejadoJaponesVertex(u2, v2, punta, c0, c1, fn, potenciaCurvatura);
				}
			}
		}
		glEnd();
	}

	/* Faldón: conectar arista interna (y=0) con arista externa (y=-exceso) por cada cara */
	for (cara = 0; cara < 4; cara++) {
		int next = (cara + 1) % 4;
		float* interior0 = esquinasInteriores[cara];
		float* interior1 = esquinasInteriores[next];
		float* exterior0 = esquinasExteriores[cara];
		float* exterior1 = esquinasExteriores[next];

		/* normal del faldón (aprox) */
		float v1x = exterior0[0] - interior0[0], v1y = exterior0[1] - interior0[1], v1z = exterior0[2] - interior0[2];
		float v2x = interior1[0] - interior0[0], v2y = interior1[1] - interior0[1], v2z = interior1[2] - interior0[2];
		float nx = v1y * v2z - v1z * v2y;
		float ny = v1z * v2x - v1x * v2z;
		float nz = v1x * v2y - v1y * v2x;
		float nlong = sqrtf(nx * nx + ny * ny + nz * nz);
		if (nlong > 1e-6f) { nx /= nlong; ny /= nlong; nz /= nlong; }
		else { nx = 0.0f; ny = -1.0f; nz = 0.0f; }

		glBegin(GL_QUADS);
		glNormal3f(nx, ny, nz);
		const float tamPieza = 0.5f;
		glTexCoord2f(interior0[0] / tamPieza, interior0[2] / tamPieza); glVertex3fv(interior0);
		glTexCoord2f(exterior0[0] / tamPieza, exterior0[2] / tamPieza); glVertex3fv(exterior0);
		glTexCoord2f(exterior1[0] / tamPieza, exterior1[2] / tamPieza); glVertex3fv(exterior1);
		glTexCoord2f(interior1[0] / tamPieza, interior1[2] / tamPieza); glVertex3fv(interior1);
		glEnd();
	}

	/* Base inferior (cara de abajo de la parte que sobresale) */
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);

		const float tamPieza = 0.5f;
		glTexCoord2f(esquinasExteriores[0][0] / tamPieza, esquinasExteriores[0][2] / tamPieza); glVertex3fv(esquinasExteriores[0]);
		glTexCoord2f(esquinasExteriores[3][0] / tamPieza, esquinasExteriores[3][2] / tamPieza); glVertex3fv(esquinasExteriores[3]);
		glTexCoord2f(esquinasExteriores[2][0] / tamPieza, esquinasExteriores[2][2] / tamPieza); glVertex3fv(esquinasExteriores[2]);
		glTexCoord2f(esquinasExteriores[1][0] / tamPieza, esquinasExteriores[1][2] / tamPieza); glVertex3fv(esquinasExteriores[1]);
	
	glEnd();
	
	if (cullEnabled) glEnable(GL_CULL_FACE);
	glShadeModel(sombreado);
}