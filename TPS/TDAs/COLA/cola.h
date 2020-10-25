#ifndef __COLA_H__
#define __COLA_H__

#include <stdbool.h>

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

typedef struct cola {
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	int cantidad;
} cola_t;

/* 
 * Crea una cola reservando la memoria necesaria
 * para almacenar la estructura.
 * Devuelve un puntero a la estructura cola_t creada.
 */
cola_t* cola_crear();

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento);

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola);

/* 
 * Determina si la cola está vacia.
 * Devuelve true si está vacía y false si no.
 * Si la cola no existe devolverá true.
 */
bool cola_vacia(cola_t* cola);

/* 
 * Devuelve la cantidad de elementos almacenados en la cola.
 * Si la cola no existe devolverá 0.
 */
int cola_cantidad(cola_t* cola);

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 * Si la cola no existe devolverá NULL.
 */
void* cola_primero(cola_t* cola);

/* 
 * Destruye la cola liberando toda la memoria reservada
 * por la cola.
 */
void cola_destruir(cola_t* cola);

#endif /* __COLA_H__ */
