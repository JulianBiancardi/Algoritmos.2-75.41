#include <stdlib.h>
#include "cola.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

/*---------------------------------------*/

nodo_t* nodo_cola_crear(void* elemento){
	nodo_t* nodo = (nodo_t*) malloc(sizeof(nodo_t));
	if(nodo == NULL)
		return NULL;

	(*nodo).elemento = elemento;
	(*nodo).siguiente = NULL;

	return nodo;
}
int nodo_cola_destruir(nodo_t* nodo){

	if(nodo == NULL)
		return ERROR;

	free(nodo);

	return OK;
}
cola_t* cola_crear(){

	cola_t* cola = (cola_t*) malloc(sizeof(cola_t));
	if(cola == NULL)
		return NULL;

	(*cola).nodo_inicio = NULL;
	(*cola).nodo_fin = NULL;
	(*cola).cantidad = 0;

	return cola;
}

int cola_encolar(cola_t* cola, void* elemento){
	if(cola == NULL)
		return ERROR;

	nodo_t* nodo = nodo_cola_crear(elemento);
	if(nodo == NULL)
		return ERROR;

	if(cola_vacia(cola))
		(*cola).nodo_inicio = nodo;
	else
		(*(*cola).nodo_fin).siguiente = nodo;
	
	(*cola).nodo_fin = nodo;
	(*cola).cantidad++;

	return OK;
}

int cola_desencolar(cola_t* cola){
	if(cola == NULL)
		return ERROR;
	if(cola_vacia(cola))
		return ERROR;

	
	nodo_t nodo_aux;

	nodo_aux.siguiente = (*cola).nodo_inicio;
	(*cola).nodo_inicio = (*(*cola).nodo_inicio).siguiente;
	if(nodo_cola_destruir(nodo_aux.siguiente) == ERROR)
		return ERROR;

	(*cola).cantidad--;
	if((*cola).cantidad == 0)
		(*cola).nodo_fin = NULL;

	return OK;
}

bool cola_vacia(cola_t* cola){
	if(cola == NULL)
		return true;

	return ((*cola).nodo_inicio == NULL && (*cola).nodo_fin == NULL); 
}

int cola_cantidad(cola_t* cola){
	if(cola == NULL)
		return 0;

	return ((*cola).cantidad);																																																																													
}

void* cola_primero(cola_t* cola){
	if(cola == NULL)
		return NULL;

	if(cola_vacia(cola))
		return NULL;

	return((*(*cola).nodo_inicio).elemento);
}

void cola_destruir(cola_t* cola){
	if(cola == NULL)
		return;

	int estado_operacion = OK;  
	nodo_t nodo_aux;

	while((*cola).nodo_inicio != NULL  && estado_operacion == OK){
		
		nodo_aux.siguiente = (*cola).nodo_inicio;
		(*cola).nodo_inicio = (*(*cola).nodo_inicio).siguiente;
		estado_operacion = nodo_cola_destruir(nodo_aux.siguiente);
		(*cola).cantidad--;
		if((*cola).cantidad == 0)
			(*cola).nodo_fin = NULL;
	}
	
	free(cola);

	return;
}