#include <stdlib.h>
#include "pila.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CANTIDAD_INICIAL 10
#define CANTIDAD_AUMENTAR 2
#define CANTIDAD_DISMINUIR 2
/*---------------------------------------*/


pila_t* pila_crear(){

	pila_t* pila = (pila_t*) malloc(sizeof(pila_t));
	if(pila == NULL)
		return NULL;

	(*pila).elementos = malloc(sizeof(void*) * CANTIDAD_INICIAL);
	if((*pila).elementos == NULL)
		return NULL;

	(*pila).tope = 0;
	(*pila).tamanio = CANTIDAD_INICIAL;
	
	return pila;
}

int redimensionar_pila(pila_t* pila,int nuevo_tamanio){
	void** auxiliar_ptr = realloc((*pila).elementos,sizeof(void*) * (unsigned int)nuevo_tamanio);
	if(auxiliar_ptr == NULL)
		return ERROR;

	(*pila).elementos = auxiliar_ptr;
	(*pila).tamanio = nuevo_tamanio;

	return OK;
}
int pila_apilar(pila_t* pila, void* elemento){
	if(pila == NULL)
		return ERROR;

	if((*pila).tope == (*pila).tamanio){
		int nuevo_tamanio = (*pila).tamanio * CANTIDAD_AUMENTAR;
		if(redimensionar_pila(pila,nuevo_tamanio) == ERROR)
			return ERROR;
	}
	(*pila).elementos[(*pila).tope] = elemento;
	((*pila).tope)++;

	return OK;
}

int pila_desapilar(pila_t* pila){
	if(pila == NULL)
		return ERROR;
	if(pila_vacia(pila))
		return ERROR;

	(*pila).elementos[(*pila).tope - 1] = NULL;
	((*pila).tope)--;
	if((*pila).tope <= ((*pila).tamanio / 2) && !pila_vacia(pila)){
		int nuevo_tamanio = (*pila).tamanio / CANTIDAD_DISMINUIR;
		if(redimensionar_pila(pila,nuevo_tamanio) == ERROR)
			return ERROR;
	}

	return OK;
}

bool pila_vacia(pila_t* pila){
	if(pila == NULL)
		return true;

	return((*pila).tope == 0);
}

int pila_cantidad(pila_t* pila){
	if(pila == NULL)
		return 0;

	return((*pila).tope);
}

void* pila_tope(pila_t* pila){
	if(pila_vacia(pila))
		return NULL;

	return((*pila).elementos[(*pila).tope - 1]);
}

void pila_destruir(pila_t* pila){
	if(pila == NULL)
		return;
	
	if((*pila).elementos != NULL)
		free((*pila).elementos);
	free(pila);
}