/*************************************************************************/
/*                                                                       */
/*   modelado.h												             */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

#ifndef MODELADO_H
#define MODELADO_H

/* Identificador para la display list de la escena */
GLuint escena;

/* Definir el suelo */
void CreaSuelo(void);

/*Definir puerta torii*/
void CreaTorii(void);

/*Definir templo*/
void CreaTemplo(void);

/*Definir camino*/
void CreaCamino(void);

/* Definir arboles */
void CreaArbol(void);

/* Definir paredes de la caja */
void CreaCaja(float ancho, float profundidad, float altura);

/* Crea la display list para la escena */
void CreaEscenaIluminacion (void);

#endif