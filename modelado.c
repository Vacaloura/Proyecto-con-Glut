/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "glig.h"
#include "material.h"
#include "modelado.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

/* Identificadores de las display lists de la escena */
GLuint torii = 0;
GLuint templo = 0;
GLuint camino = 0;
GLuint arbol = 0;
GLuint suelo = 0;
GLuint cielo = 0;

/******************************************************************************************/
/* Crea la display list para suelo                                                        */
/******************************************************************************************/
void CreaSuelo(void)
{
	suelo = glGenLists(1);

	glNewList(suelo, GL_COMPILE);
	glPushMatrix();

	/* Preparar y activar la textura de cesped */
	static int texturaCespedCargada = 0;
	if (!texturaCespedCargada) {
		initTextura2("cesped.tga"); 
		texturaCespedCargada = 1;
	}

	/* Factores de repetición */
	const float repetirU = 20.0f;
	const float repetirV = 40.0f;

	/* Activar textura y forzar repetir */
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
	textura2();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/* Aplicar escala a la matriz de textura para repetir sin cambiar las coordenadas */
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glScalef(repetirU, repetirV, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	/* Dibujar el suelo */
	glTranslatef(0.0f, -0.5f, 0.0f);
	glScalef(20.0f, 1.0f, 40.0f);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
	glEnd();

	/* Restaurar matriz de textura y estado */
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();

	glPopMatrix();
	glEndList();
}

/******************************************************************************************/
/* Crea la display list para Torii											          */
/******************************************************************************************/
void CreaTorii(void)
{
	torii = glGenLists(1);

	if (torii != 0)
	{
		glNewList(torii, GL_COMPILE);
		glPushMatrix();

		/* Cargar la textura de madera roja */
		static int texturaMaderaCargada = 0;
		if (!texturaMaderaCargada) {
			initTextura4("madera_roja_vertical.tga");
			texturaMaderaCargada = 1;
		}

		/* Parámetros del torii */
		const float separacion = 2.0f;
		const float alturaPata = 2.5f;
		const float grosorPata = 0.3f;
		const float grosorBalda = 0.2f;
		const float anchuraBalda = 0.4f;
		const float largoBalda = 3.0f;

		/* Repeticiones por unidad de mundo */
		const float repetirPorUnidad = 1.0f; 

		/* Preparar texturizado para torii */
		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
		textura4(); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		/* PATA IZQUIERDA */
		glPushMatrix();
		glTranslatef(-separacion / 2.0f, alturaPata / 2.0f, 0.0f);
		glScalef(grosorPata, alturaPata, grosorPata);
		igSolidCilindro(16, 8);
		glPopMatrix();

		/* PATA DERECHA */
		glPushMatrix();
		glTranslatef(separacion / 2.0f, alturaPata / 2.0f, 0.0f);
		glScalef(grosorPata, alturaPata, grosorPata);
		igSolidCilindro(16, 8);
		glPopMatrix();

		/* BALDA SUPERIOR */
		{
			float sx = largoBalda;
			float sy = grosorBalda;
			float sz = anchuraBalda;
			float hx = sx * 0.5f;
			float hy = sy * 0.5f;
			float hz = sz * 0.5f;

			const float repetir_U_delante = sx * repetirPorUnidad;
			const float repetir_V_delante = sy * repetirPorUnidad;
			const float repetir_lado_u = sz * repetirPorUnidad;
			const float repetir_lado_v = sy * repetirPorUnidad;
			const float repetir_arriba_u = sx * repetirPorUnidad;
			const float repetir_arriba_v = sz * repetirPorUnidad;

			glPushMatrix();
			glTranslatef(0.0f, 2.5f, 0.0f);

			/* Frente  */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(repetir_U_delante, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(repetir_U_delante, repetir_V_delante); glVertex3f(hx, hy, hz);
			glTexCoord2f(0.0f, repetir_V_delante); glVertex3f(-hx, hy, hz);
			glEnd();

			/* Detras */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(repetir_U_delante, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(0.0f, repetir_V_delante); glVertex3f(hx, hy, -hz);
			glTexCoord2f(repetir_U_delante, repetir_V_delante); glVertex3f(-hx, hy, -hz);
			glEnd();

			/* Laterales */
			glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(repetir_lado_u, 0.0f); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(repetir_lado_u, repetir_lado_v); glVertex3f(hx, hy, -hz);
			glTexCoord2f(0.0f, repetir_lado_v); glVertex3f(hx, hy, hz);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(repetir_lado_u, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, repetir_lado_v); glVertex3f(-hx, hy, -hz);
			glTexCoord2f(repetir_lado_u, repetir_lado_v); glVertex3f(-hx, hy, hz);
			glEnd();

			/* Superior / Inferior */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, hy, -hz);
			glTexCoord2f(repetir_arriba_u, 0.0f);   glVertex3f(hx, hy, -hz);
			glTexCoord2f(repetir_arriba_u, repetir_arriba_v);     glVertex3f(hx, hy, hz);
			glTexCoord2f(0.0f, repetir_arriba_v);   glVertex3f(-hx, hy, hz);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, repetir_arriba_v); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(repetir_arriba_u, repetir_arriba_v);   glVertex3f(hx, -hy, -hz);
			glTexCoord2f(repetir_arriba_u, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-hx, -hy, hz);
			glEnd();

			glPopMatrix();
		}

		/* TRAVESAÑO INFERIOR */
		{
			float sx = largoBalda;
			float sy = grosorBalda;
			float sz = anchuraBalda;
			float hx = sx * 0.5f;
			float hy = sy * 0.5f;
			float hz = sz * 0.5f;

			const float repetir_U_delante = sx * repetirPorUnidad;
			const float repetir_V_delante = sy * repetirPorUnidad;
			const float repetir_lado_u = sz * repetirPorUnidad;
			const float repetir_lado_v = sy * repetirPorUnidad;
			const float repetir_arriba_u = sx * repetirPorUnidad;
			const float repetir_arriba_v = sz * repetirPorUnidad;

			glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.0f);

			/* Frente */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(repetir_U_delante, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(repetir_U_delante, repetir_V_delante); glVertex3f(hx, hy, hz);
			glTexCoord2f(0.0f, repetir_V_delante); glVertex3f(-hx, hy, hz);
			glEnd();

			/* Detras */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(repetir_U_delante, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(0.0f, repetir_V_delante); glVertex3f(hx, hy, -hz);
			glTexCoord2f(repetir_U_delante, repetir_V_delante); glVertex3f(-hx, hy, -hz);
			glEnd();

			/* Laterales */
			glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(repetir_lado_u, 0.0f);   glVertex3f(hx, -hy, -hz);
			glTexCoord2f(repetir_lado_u, repetir_lado_v);     glVertex3f(hx, hy, -hz);
			glTexCoord2f(0.0f, repetir_lado_v);   glVertex3f(hx, hy, hz);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(repetir_lado_u, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, repetir_lado_v); glVertex3f(-hx, hy, -hz);
			glTexCoord2f(repetir_lado_u, repetir_lado_v);   glVertex3f(-hx, hy, hz);
			glEnd();

			/* Superior / Inferior */
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, hy, -hz);
			glTexCoord2f(repetir_arriba_u, 0.0f);   glVertex3f(hx, hy, -hz);
			glTexCoord2f(repetir_arriba_u, repetir_arriba_v);     glVertex3f(hx, hy, hz);
			glTexCoord2f(0.0f, repetir_arriba_v);   glVertex3f(-hx, hy, hz);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, repetir_arriba_v); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(repetir_arriba_u, repetir_arriba_v);   glVertex3f(hx, -hy, -hz);
			glTexCoord2f(repetir_arriba_u, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-hx, -hy, hz);
			glEnd();

			glPopMatrix();
		}

		/* Restaurar matriz de textura y estado */
		glDisable(GL_TEXTURE_2D);
		glPopAttrib();

		glPopMatrix();
		glEndList();
	}
}

/******************************************************************************************/
/* Crea la display list para el templo: base y segundo piso                              */
/******************************************************************************************/
void CreaTemplo(void)
{
	templo = glGenLists(1);

	if (templo != 0)
	{
		glNewList(templo, GL_COMPILE);
		glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_CULL_FACE);

		/* Cargar textura de pared  */
		static int texturaParedCargada = 0;
		if (!texturaParedCargada) {
			initTextura5("pared.tga");
			texturaParedCargada = 1;
		}

		/* Parámetros y colores */
		glColor3f(1.0f, 1.0f, 1.0f);
		const float ladoBase = 8.0f;
		const float alturaBase = 2.5f;
		const float ladoSuperior = 5.0f;
		const float alturaSuperior = 2.0f;

		/* PLANTA BAJA */
		{
			/* Activar textura pared */
			glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
			textura5();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor3f(1.0f, 1.0f, 1.0f);

			/* Repetición por unidad */
			const float repetirPorUnidad = 1.0f;

			glPushMatrix();
			glTranslatef(0.0f, alturaBase / 2.0f, 0.0f);
			const float sx = ladoBase, sy = alturaBase, sz = ladoBase;
			const float hx = sx * 0.5f, hy = sy * 0.5f, hz = sz * 0.5f;

			/* Repeticiones por cara */
			const float ru_delante = sx * repetirPorUnidad;
			const float rv_delante = sy * repetirPorUnidad;
			const float ru_lateral = sz * repetirPorUnidad;
			const float rv_lateral = sy * repetirPorUnidad;
			const float ru_superior = sx * repetirPorUnidad;
			const float rv_superior = sz * repetirPorUnidad;

			/* Frente */
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(ru_delante, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(ru_delante, rv_delante); glVertex3f(hx, hy, hz);
			glTexCoord2f(0.0f, rv_delante); glVertex3f(-hx, hy, hz);
			glEnd();

			/* Atrás */
			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glTexCoord2f(ru_delante, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(0.0f, rv_delante); glVertex3f(hx, hy, -hz);
			glTexCoord2f(ru_delante, rv_delante); glVertex3f(-hx, hy, -hz);
			glEnd();

			/* Lado */
			glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(ru_lateral, 0.0f); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(ru_lateral, rv_lateral); glVertex3f(hx, hy, -hz);
			glTexCoord2f(0.0f, rv_lateral); glVertex3f(hx, hy, hz);
			glEnd();

			/* Lado */
			glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glTexCoord2f(ru_lateral, 0.0f); glVertex3f(-hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(0.0f, rv_lateral); glVertex3f(-hx, hy, -hz);
			glTexCoord2f(ru_lateral, rv_lateral); glVertex3f(-hx, hy, hz);
			glEnd();

			/* Superior (techo de planta baja) */
			{
				/* Cargar textura techo para la parte superior del piso 1 */
				static int texturaTechoCargadaLocal = 0;
				if (!texturaTechoCargadaLocal) {
					initTextura6("techo.tga");
					texturaTechoCargadaLocal = 1;
				}

				/* Activar textura de techo con repetir */
				glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
				textura6();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_QUADS);
				glNormal3f(0, 1, 0);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, hy, -hz);
				glTexCoord2f(ru_superior, 0.0f); glVertex3f(hx, hy, -hz);
				glTexCoord2f(ru_superior, rv_superior); glVertex3f(hx, hy, hz);
				glTexCoord2f(0.0f, rv_superior); glVertex3f(-hx, hy, hz);
				glEnd();

				glDisable(GL_TEXTURE_2D);
				glPopAttrib();
			}

			/* Inferior */
			glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glTexCoord2f(0.0f, rv_superior); glVertex3f(-hx, -hy, -hz);
			glTexCoord2f(ru_superior, rv_superior); glVertex3f(hx, -hy, -hz);
			glTexCoord2f(ru_superior, 0.0f); glVertex3f(hx, -hy, hz);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, hz);
			glEnd();

			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			glPopAttrib();
		}

		/* ELEMENTOS DECORATIVOS Y BANDAS */
		{
			glColor3f(1.0f, 0.25f, 0.12f);

			const float mitadLado = ladoBase * 0.5f;
			const float yBanda = alturaBase * 0.42f;
			const float alturaBanda = 0.12f;
			const float profundidadBanda = 0.14f;
			const float eps = 0.01f;

			/* Frente */
			glPushMatrix();
			glTranslatef(0.0f, yBanda, mitadLado + eps);
			glScalef(ladoBase + 0.02f, alturaBanda, profundidadBanda);
			igSolidCube();
			glPopMatrix();

			/* Detras */
			glPushMatrix();
			glTranslatef(0.0f, yBanda, -mitadLado - eps);
			glScalef(ladoBase + 0.02f, alturaBanda, profundidadBanda);
			igSolidCube();
			glPopMatrix();

			/* Derecha */
			glPushMatrix();
			glTranslatef(mitadLado + eps, yBanda, 0.0f);
			glScalef(profundidadBanda, alturaBanda, ladoBase + 0.02f);
			igSolidCube();
			glPopMatrix();

			/* Izquierda */
			glPushMatrix();
			glTranslatef(-mitadLado - eps, yBanda, 0.0f);
			glScalef(profundidadBanda, alturaBanda, ladoBase + 0.02f);
			igSolidCube();
			glPopMatrix();

			/* Barras verticales y puerta */
			const float anchoBarra = 0.12f;
			const float alturaBarra = alturaBase * 0.95f;
			const float posXOff = mitadLado * 0.40f;
			const float posZOff = mitadLado * 0.40f;
			const float panelY = alturaBarra / 2.0f;

			/* Parte frontal */
			{
				glPushMatrix();
				glTranslatef(-posXOff, panelY, mitadLado + eps);
				glScalef(anchoBarra, alturaBarra, profundidadBanda);
				igSolidCube();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(posXOff, panelY, mitadLado + eps);
				glScalef(anchoBarra, alturaBarra, profundidadBanda);
				igSolidCube();
				glPopMatrix();
			}

			/* Puerta doble */
			{
				const float anchoPuerta = ladoBase * 0.25f;
				const float altoPuerta = alturaBase - 1.05f;
				const float profundidadPuerta = 0.06f;
				const float cierre = 0.02f;
				const float anchoPanel = (anchoPuerta - cierre) * 0.5f;
				const float altoPanel = altoPuerta;
				const float centroIzqX = -(cierre * 0.5f + anchoPanel * 0.5f);
				const float centroDerX = (cierre * 0.5f + anchoPanel * 0.5f);
				const float panelCentroY = altoPanel * 0.5f;
				const float panelCentroZ = mitadLado + eps + profundidadPuerta * 0.5f;

				glColor3f(0.40f, 0.20f, 0.08f);
				glPushMatrix();
				glTranslatef(centroIzqX, panelCentroY, panelCentroZ);
				glScalef(anchoPanel, altoPanel, profundidadPuerta);
				igSolidCube();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(centroDerX, panelCentroY, panelCentroZ);
				glScalef(anchoPanel, altoPanel, profundidadPuerta);
				igSolidCube();
				glPopMatrix();

				glColor3f(0.72f, 0.25f, 0.12f);
			}

			/* Resto de caras/listones */
			for (int cara = 0; cara < 3; ++cara)
			{
				if (cara == 0)
				{
					glPushMatrix();
					glTranslatef(-posXOff, panelY, -mitadLado - eps);
					glScalef(anchoBarra, alturaBarra, profundidadBanda);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(0.0f, panelY, -mitadLado - eps);
					glScalef(anchoBarra, alturaBarra, profundidadBanda);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(posXOff, panelY, -mitadLado - eps);
					glScalef(anchoBarra, alturaBarra, profundidadBanda);
					igSolidCube();
					glPopMatrix();
				}
				else if (cara == 1)
				{
					glPushMatrix();
					glTranslatef(-mitadLado - eps, panelY, -posZOff);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-mitadLado - eps, panelY, 0.0f);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-mitadLado - eps, panelY, posZOff);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();
				}
				else
				{
					glPushMatrix();
					glTranslatef(mitadLado + eps, panelY, -posZOff);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(mitadLado + eps, panelY, 0.0f);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();

					glPushMatrix();
					glTranslatef(mitadLado + eps, panelY, posZOff);
					glScalef(profundidadBanda, alturaBarra, anchoBarra);
					igSolidCube();
					glPopMatrix();
				}
			}
		}

		/* SEGUNDA PLANTA */
		{
			/* Activar textura pared */
			glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
			textura5(); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor3f(1.0f, 1.0f, 1.0f);

			glPushMatrix();
			float secondY = alturaBase + alturaSuperior / 2.0f;
			glTranslatef(0.0f, secondY, 0.0f);

			/* Dimensiones segundo piso */
			const float sx2 = ladoSuperior, sy2 = alturaSuperior, sz2 = ladoSuperior;
			const float hx2 = sx2 * 0.5f, hy2 = sy2 * 0.5f, hz2 = sz2 * 0.5f;
			const float ru_f = sx2, rv_f = sy2;
			const float ru_s = sz2, rv_s = sy2;
			const float ru_t = sx2, rv_t = sz2;

			/* Frente */
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx2, -hy2, hz2);
			glTexCoord2f(ru_f, 0.0f); glVertex3f(hx2, -hy2, hz2);
			glTexCoord2f(ru_f, rv_f); glVertex3f(hx2, hy2, hz2);
			glTexCoord2f(0.0f, rv_f); glVertex3f(-hx2, hy2, hz2);
			glEnd();

			/* Atrás */
			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glTexCoord2f(ru_f, 0.0f); glVertex3f(-hx2, -hy2, -hz2);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx2, -hy2, -hz2);
			glTexCoord2f(0.0f, rv_f); glVertex3f(hx2, hy2, -hz2);
			glTexCoord2f(ru_f, rv_f); glVertex3f(-hx2, hy2, -hz2);
			glEnd();

			/* Laterales */
			glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(hx2, -hy2, hz2);
			glTexCoord2f(ru_s, 0.0f); glVertex3f(hx2, -hy2, -hz2);
			glTexCoord2f(ru_s, rv_s); glVertex3f(hx2, hy2, -hz2);
			glTexCoord2f(0.0f, rv_s); glVertex3f(hx2, hy2, hz2);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glTexCoord2f(ru_s, 0.0f); glVertex3f(-hx2, -hy2, hz2);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx2, -hy2, -hz2);
			glTexCoord2f(0.0f, rv_s); glVertex3f(-hx2, hy2, -hz2);
			glTexCoord2f(ru_s, rv_s); glVertex3f(-hx2, hy2, hz2);
			glEnd();

			/* Techo y suelo de la segunda planta */
			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx2, hy2, -hz2);
			glTexCoord2f(ru_t, 0.0f); glVertex3f(hx2, hy2, -hz2);
			glTexCoord2f(ru_t, rv_t); glVertex3f(hx2, hy2, hz2);
			glTexCoord2f(0.0f, rv_t); glVertex3f(-hx2, hy2, hz2);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glTexCoord2f(0.0f, rv_t); glVertex3f(-hx2, -hy2, -hz2);
			glTexCoord2f(ru_t, rv_t); glVertex3f(hx2, -hy2, -hz2);
			glTexCoord2f(ru_t, 0.0f); glVertex3f(hx2, -hy2, hz2);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx2, -hy2, hz2);
			glEnd();

			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			glPopAttrib();
		}

		/* Tejado del primer piso (laterales y esquinas) */
		{
			const float mitadLado = ladoBase * 0.5f;
			const float yBase = alturaBase;

			/* Cargar y activar textura del techo */
			static int texturaTechoCargada = 0;
			if (!texturaTechoCargada) {
				initTextura6("techo.tga");
				texturaTechoCargada = 1;
			}

			glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
			textura6();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor3f(1.0f, 1.0f, 1.0f);

			/* Lado Delantero */
			glPushMatrix();
			glTranslatef(0.0f, yBase, mitadLado);
			igSolidTejado(ladoBase);
			glPopMatrix();

			/* Lado Trasero */
			glPushMatrix();
			glTranslatef(0.0f, yBase, -mitadLado);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			igSolidTejado(ladoBase);
			glPopMatrix();

			/* Lado Derecho */
			glPushMatrix();
			glTranslatef(mitadLado, yBase, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			igSolidTejado(ladoBase);
			glPopMatrix();

			/* Lado Izquierdo */
			glPushMatrix();
			glTranslatef(-mitadLado, yBase, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			igSolidTejado(ladoBase);
			glPopMatrix();

			/* Esquinas */
			const float tejadoH = 1.0f;
			const float tejadoB = 0.75f;

			glPushMatrix();
			glTranslatef(mitadLado, yBase, mitadLado);
			igSolidEsquinaTejado(tejadoH, tejadoB);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-mitadLado, yBase, mitadLado);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			igSolidEsquinaTejado(tejadoH, tejadoB);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-mitadLado, yBase, -mitadLado);
			glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
			igSolidEsquinaTejado(tejadoH, tejadoB);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(mitadLado, yBase, -mitadLado);
			glRotatef(-270.0f, 0.0f, 1.0f, 0.0f);
			igSolidEsquinaTejado(tejadoH, tejadoB);
			glPopMatrix();
		}

		/* Tejado segunda planta */
		glColor3f(0.72f, 0.25f, 0.12f);
		glPushMatrix();
		glTranslatef(0.0f, alturaBase + alturaSuperior + 0.02f, 0.0f);
		igSolidTejadoJapones(36, ladoSuperior, 1.5f, 1.0f, 0.65f);
		glPopMatrix();

		glPopAttrib();

		glPopMatrix();
		glEndList();
	}
}
/******************************************************************************************/
/* Crea la display list para el camino                                                    */
/******************************************************************************************/
void CreaCamino(void)
{
	camino = glGenLists(1);
	glNewList(camino, GL_COMPILE);

	/* Caracteristicas */
	#define NUM_PIEDRAS 8
	const float mediaSuelo = 10.0f;
	const int numSegmentos = 28;
	const float alturaSobreSuelo = -0.49f;

	/* Lista de partes del camino */
	const float piedras[NUM_PIEDRAS][3] = { {-3.0f,  1.0f, 0.75f},{-1.8f,  1.6f, 0.60f},
	{-0.6f,  2.4f, 0.55f},{ 0.8f,  3.8f, 0.75f},{ 2.6f,  5.2f, 0.70f},{ 4.0f,  6.4f, 0.55f},
	{ 5.2f,  7.4f, 0.80f},{ 5.0f,  9.0f, 0.65f} };

	/* Preparar textura de camino para las piedras */
	static int texturaCaminoCargadaCamino = 0;
	if (!texturaCaminoCargadaCamino) {
		initTextura3("camino.tga");
		texturaCaminoCargadaCamino = 1;
	}

	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glColor3f(0.45f, 0.45f, 0.45f);

	const float tileSize = 0.5f;
	glEnable(GL_TEXTURE_2D);
	textura3();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);


	for (int i = 0; i < NUM_PIEDRAS; ++i)
	{
		/* Coordenadas y radio de la parte actual */
		float centroX = piedras[i][0];
		float centroZ = piedras[i][1];
		float radio = piedras[i][2];

		/* Calculo para que ninguna piedra se salga del suelo */
		float minC = -mediaSuelo + radio;
		float maxC = mediaSuelo - radio;
		if (centroX < minC) centroX = minC;
		if (centroX > maxC) centroX = maxC;
		if (centroZ < minC) centroZ = minC;
		if (centroZ > maxC) centroZ = maxC;

		/* Repeticiones necesarias sobre la piedra */
		float repetir = (2.0f * radio) / tileSize;
		if (repetir < 1.0f) repetir = 1.0f; 

		glPushMatrix();
		glTranslatef(centroX, alturaSobreSuelo, centroZ);
		glNormal3f(0.0f, 1.0f, 0.0f);

		/* Centro */
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5f * repetir, 0.5f * repetir);
		glVertex3f(0.0f, 0.0f, 0.0f);

		for (int s = 0; s <= numSegmentos; ++s)
		{
			double ang = (2.0 * 3.141592653589793 * s) / (double)numSegmentos;
			float vx = (float)cos(ang) * radio;
			float vz = (float)sin(ang) * radio;

			/* Coordenadas base */
			float u_base = (vx / (2.0f * radio)) + 0.5f;
			float v_base = (vz / (2.0f * radio)) + 0.5f;

			/* Aplicar repetición (multiplica el rango 0..1) */
			float u = u_base * repetir;
			float v = v_base * repetir;

			glTexCoord2f(u, v);
			glVertex3f(vx, 0.0f, vz);
		}
		glEnd();
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glEndList();
}

/******************************************************************************************/
/* Crea la display list para los arboles                                                  */
/******************************************************************************************/
void CreaArbol(void)
{
	arbol = glGenLists(1);
	if (arbol != 0)
	{
		glNewList(arbol, GL_COMPILE);

		/* Tronco */
		static int texturaTroncoCargada = 0;
		if (!texturaTroncoCargada) {
			initTextura1("tronco.tga"); 
			texturaTroncoCargada = 1;
		}

		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
		textura1(); 
		glColor3f(1.0f, 1.0f, 1.0f); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		/* Factores de repetición para el tronco */
		const float repetirU_tronco = 1.0f;  
		const float repetirV_tronco = 4.0f; 

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		glScalef(repetirU_tronco, repetirV_tronco, 1.0f);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glTranslatef(0.0f, 0.9f, 0.0f);
		glScalef(0.60f, 1.8f, 0.60f);
		igSolidCilindro(16, 8);
		glPopMatrix();

		/* Restaurar matriz de textura */
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		glDisable(GL_TEXTURE_2D);
		glPopAttrib();

		/* Copa del árbol */
		static int texturaCargada = 0;
		if (!texturaCargada) {
			initTextura0("cerezo.tga"); 
			texturaCargada = 1;
		}

		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
		textura0(); 
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		/* Factores de repetición para las hojas */
		const float repetirU_leaves = 1.0f;  
		const float repetirV_leaves = 1.0f;  

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		glScalef(repetirU_leaves, repetirV_leaves, 1.0f);
		glMatrixMode(GL_MODELVIEW);

		{
			const int pU = 12, pV = 12;
			const float hojas[][4] = {
				{ 0.0f,  2.10f,  0.0f, 1.0f },
				{-0.8f,  1.95f,  0.2f, 0.9f },
				{ 0.8f,  1.95f,  0.2f, 0.9f },
				{ 0.0f,  1.95f, -0.9f, 0.95f },
				{-0.35f, 2.35f,  0.6f, 0.7f },
				{ 0.35f, 2.35f,  0.6f, 0.7f }
			};
			const int nHojas = sizeof(hojas) / sizeof(hojas[0]);

			for (int i = 0; i < nHojas; ++i)
			{
				glPushMatrix();
				glTranslatef(hojas[i][0], hojas[i][1], hojas[i][2]);
				glScalef(hojas[i][3], hojas[i][3], hojas[i][3]);
				igSolidSphere(pU, pV);
				glPopMatrix();
			}
		}

		/* Restaurar matriz de textura */
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		/* Restaurar estado */
		glDisable(GL_TEXTURE_2D);
		glPopAttrib();

		glEndList();
	}
}

/******************************************************************************************/
/* Crea la display list para la caja del cielo                                            */
/******************************************************************************************/
void CreaCaja(float ancho, float profundidad, float altura)
{
	const float hx = ancho * 0.5f;
	const float hz = profundidad * 0.5f;
	const float y0 = -0.5f;
	const float y1 = altura;

	cielo = glGenLists(1);
	if (cielo == 0) return;

	glNewList(cielo, GL_COMPILE);
	glPushMatrix();

	static int texturaCieloCargada = 0;
	if (!texturaCieloCargada) {
		initTextura7("cielo.tga");
		texturaCieloCargada = 1;
	}

	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
	textura7();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glScalef(1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	/* Pared trasera */
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, y0, -hz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, y0, -hz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, y1, -hz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, y1, -hz);
	glEnd();

	/* Pared izquierda */
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, y0, hz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-hx, y0, -hz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-hx, y1, -hz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, y1, hz);
	glEnd();

	/* Pared derecha */
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, y0, -hz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, y0, hz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, y1, hz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(hx, y1, -hz);
	glEnd();

	/* Tapa superior */
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, y1, -hz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, y1, -hz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, y1, hz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, y1, hz);
	glEnd();

	/* Restaurar matriz de textura */
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	/* Restaurar estado */
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();

	glPopMatrix();
	glEndList();
}



/******************************************************************************************/
/* Crea la display list para la escena                                                    */
/******************************************************************************************/
void CreaEscenaIluminacion(void)
{
	CreaTorii();
	CreaTemplo();
	CreaArbol();	
	CreaSuelo();
	CreaCamino();
	CreaCaja(20.0f, 40.0f, 30.0f);

	escena = glGenLists(1);

	//ToDo: Añadir las texturas a los elementos :D

	if (escena != 0)
	{
		glNewList(escena, GL_COMPILE);
		glPushMatrix();

			/* Dibujar el suelo */
			glColor3f(0.0f, 0.87f, 0.0f);
			glPushMatrix();
				glCallList(suelo);
			glPopMatrix();

			glColor3f(0.0f, 0.87f, 0.0f);
			glPushMatrix();
				glCallList(cielo);
			glPopMatrix();

			/* Dibujar el camino */
			glPushMatrix();
				glCallList(camino);
			glPopMatrix();

			/* Posicionar el torii */
			glPushMatrix();
				glTranslatef(5.0f, -0.5f, 8.0f);
				glCallList(torii);
			glPopMatrix();

			/* Posicionar el templo */
			glPushMatrix();
				glTranslatef(-3.0f, -0.5f, -3.0f);
				glCallList(templo);
			glPopMatrix();

			/* Posicionar el arbol 1 */
			glPushMatrix(); 
				glTranslatef(5.0f, -0.5f, -6.0f); 
				glCallList(arbol);
			glPopMatrix();

			/* Posicionar el arbol 2 */
			glPushMatrix();
				glTranslatef(8.0f, -0.5f, 5.5f);
				glCallList(arbol);
			glPopMatrix();

			/* Posicionar el arbol 3 */
			glPushMatrix();
				glTranslatef(-5.0f, -0.5f, 7.0f);
				glCallList(arbol);
			glPopMatrix();

		glPopMatrix();
		glEndList();
	}
}