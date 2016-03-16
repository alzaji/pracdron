/*
 * gestion_memoria.c
 *
 *  Created on: 11 de mar. de 2016
 *      Author: Alberto Zamora Jiménez 2º GINF "A"
 */

const int MAX = 1000;

#include <stdio.h>
#include <stdlib.h>
#include "gestion_memoria.h"

/* Crea la estructura utilizada para gestionar la memoria disponible. Inicialmente, sólo un nodo desde 0 a MAX */
void crear(T_Manejador* manejador) {

	*manejador = malloc(sizeof(struct T_Nodo));
	(*manejador)->inicio = 0;
	(*manejador)->fin = MAX - 1;
	(*manejador)->sig = NULL;

}

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El parámetro manejador debe terminar apuntando a NULL */
void destruir(T_Manejador* manejador) {

	T_Manejador ptr,aux;
	ptr = *manejador;
	aux = NULL;

	while(ptr !=NULL){

		aux = ptr -> sig;
		free(ptr);
		ptr = aux;
	}
	*manejador = NULL;


}

/* Devuelve en “dir” la dirección de memoria “simulada” (unsigned) donde comienza el trozo de memoria continua de tamaño “tam” solicitada.
 Si la operación se pudo llevar a cabo, es decir, existe un trozo con capacidad suficiente, devolvera TRUE (1) en “ok”; FALSE (0) en otro caso.
 */
void obtener(T_Manejador *manejador, unsigned tam, unsigned* dir, unsigned* ok) {

	T_Manejador ptr, ant;

	ptr = *manejador;
	ant = NULL;
	*ok = 0;
	while (ptr != NULL && !*ok) {

		if (ptr->fin - ptr->inicio + 1 > tam) {

			*ok = 1;
			*dir = ptr->inicio;
			ptr->inicio += tam;

		} else {

			if (ptr->fin - ptr->inicio + 1 == tam) {

				*ok = 1;
				*dir = ptr->inicio;

				if (ant == NULL) {

					*manejador = ptr->sig;

				} else {

					ant->sig = ptr->sig;

				}
			} else {

				ant = ptr;
				ptr = ptr->sig;

			}

		}
	}
}


/* Muestra el estado actual de la memoria, bloques de memoria libre */
void mostrar(T_Manejador manejador) {

T_Manejador ptr = manejador;

printf("Zonas de memoria libre\n");
while (ptr != NULL) {

	printf("  Inicio: %d Fin: %d \n", ptr->inicio, ptr->fin);
	ptr = ptr->sig;
}
printf("Fin de la memoria\n");
fflush(stdout);

}

/* Devuelve el trozo de memoria continua de tamaño “tam” y que
 * comienza en “dir”.
 * Se puede suponer que se trata de un trozo obtenido previamente.
 */
void devolver(T_Manejador *manejador, unsigned tam, unsigned dir) {

	T_Manejador aux = (T_Manejador)malloc(sizeof(struct T_Nodo));
	aux -> inicio = dir;
	aux -> fin = dir + tam - 1;
	aux -> sig = NULL;

	T_Manejador ant, act;
	ant = NULL;
	act = *manejador;

	while (act !=NULL){

		ant = act;
		act = act -> sig;

	}
	if (act == NULL){

		if(aux -> fin - aux -> inicio + 1 > ant -> fin - ant -> inicio + 1){

			aux -> sig = act;
			ant -> sig = aux;

		}

		aux -> sig = *manejador;
		*manejador = aux;
	}
	else{

		aux -> sig = act;
		ant -> sig = aux;
	}

}

