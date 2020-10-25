#include <stdlib.h>
#include "lista.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

/*---------------------------------------*/

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

struct lista{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	int cantidad;
};

struct lista_iterador{
	nodo_t* nodo_actual;
	lista_t* lista;
};


nodo_t* nodo_crear(void* elemento){
	nodo_t* nodo = (nodo_t*) malloc(sizeof(nodo_t));
	if(nodo == NULL)
		return NULL;

	(*nodo).elemento = elemento;
	(*nodo).siguiente = NULL;

	return nodo;
}
int nodo_destruir(nodo_t* nodo){

	if(nodo == NULL)
		return ERROR;

	free(nodo);

	return OK;
}
nodo_t* buscar_nodo_posicion(lista_t* lista,size_t posicion){

	nodo_t* nodo = (*lista).nodo_inicio;
	for(int i = 0;i < posicion;i++)
		nodo = (*nodo).siguiente;

	return nodo;
}


lista_t* lista_crear(){

	lista_t* lista = (lista_t*) malloc(sizeof(lista_t));
	if(lista == NULL)
		return NULL;

	(*lista).nodo_inicio = NULL;
	(*lista).nodo_fin = NULL;
	(*lista).cantidad = 0;

	return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
	if(lista == NULL)
		return ERROR;

	nodo_t* nodo = nodo_crear(elemento);
	if(nodo == NULL)
		return ERROR;

	if(lista_vacia(lista))
		(*lista).nodo_inicio = nodo;
	else
		(*(*lista).nodo_fin).siguiente = nodo;
	
	(*lista).nodo_fin = nodo;
	(*lista).cantidad++;

	return OK;
}

bool posicion_invalida(lista_t* lista,size_t posicion){

	return (posicion >= (*lista).cantidad);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(lista == NULL)
		return ERROR;
	if(posicion_invalida(lista,posicion)){
		if(lista_insertar(lista,elemento) == ERROR)
			return ERROR;
		else
			return OK;
	}

	nodo_t* nodo_insertar = nodo_crear(elemento);
	if(nodo_insertar == NULL)
		return ERROR;

	
	if(posicion == 0){
		(*nodo_insertar).siguiente = (*lista).nodo_inicio;
		(*lista).nodo_inicio = nodo_insertar;
	}
	else{
		nodo_t* nodo_aterior = buscar_nodo_posicion(lista,posicion - 1);
		(*nodo_insertar).siguiente = (*nodo_aterior).siguiente;
		(*nodo_aterior).siguiente = nodo_insertar;
	}

	((*lista).cantidad)++;

	return OK;
}

int lista_borrar(lista_t* lista){
	if(lista == NULL)
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;

	nodo_t* nodo_tope;
	nodo_t* nodo_anterior_tope;

	if(lista_elementos(lista) == 1){
		nodo_tope = (*lista).nodo_inicio;
		nodo_anterior_tope = nodo_tope;
	}
	else{
		nodo_anterior_tope = buscar_nodo_posicion(lista,(size_t)(*lista).cantidad - 2);
		nodo_tope = (*nodo_anterior_tope).siguiente;
		(*nodo_anterior_tope).siguiente = NULL;
		(*lista).nodo_fin = nodo_anterior_tope;

	}
	if(nodo_destruir(nodo_tope) == ERROR)
		return ERROR;


	((*lista).cantidad)--;
	if((*lista).cantidad == 0){
		(*lista).nodo_inicio = NULL;
		(*lista).nodo_fin = NULL;
	}

	return OK;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista == NULL)
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;
	if(posicion_invalida(lista,posicion)){
		if(lista_borrar(lista) == ERROR)
			return ERROR;
		else
			return OK;
	}

	nodo_t* nodo_eleminar;

	if(posicion == 0){
		nodo_eleminar = (*lista).nodo_inicio;
		(*lista).nodo_inicio = (*nodo_eleminar).siguiente;
	}
	else{
		nodo_t* nodo_aterior = buscar_nodo_posicion(lista,posicion - 1);
		nodo_eleminar = (*nodo_aterior).siguiente;
		(*nodo_aterior).siguiente = (*nodo_eleminar).siguiente;
	}
	
	if(nodo_destruir(nodo_eleminar) == ERROR)
		return ERROR;

	((*lista).cantidad)--;
	if((*lista).cantidad == 0){
		(*lista).nodo_inicio = NULL;
		(*lista).nodo_fin = NULL;
	}

	return OK;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(lista == NULL)
		return NULL;

	if(posicion_invalida(lista,posicion))
	    return NULL;

	nodo_t* nodo_dato = buscar_nodo_posicion(lista,posicion);

	return ((*nodo_dato).elemento);
}

void* lista_ultimo(lista_t* lista){
	if(lista == NULL)
		return NULL;

	if(lista_vacia(lista))
		return NULL;

	return((*(*lista).nodo_fin).elemento);
}

bool lista_vacia(lista_t* lista){
	if(lista == NULL)
		return true;

	return ((*lista).nodo_inicio == NULL && (*lista).nodo_fin == NULL); 
}

size_t lista_elementos(lista_t* lista){
	if(lista == NULL)
		return 0;

	return ((size_t)(*lista).cantidad);
}

void lista_destruir(lista_t* lista){
	if(lista == NULL)
		return;

	int estado_operacion = OK;  
	nodo_t* nodo_aux;

	while(!lista_vacia(lista) && estado_operacion == OK){
		
		nodo_aux = (*lista).nodo_inicio;
		(*lista).nodo_inicio = (*(*lista).nodo_inicio).siguiente;
		estado_operacion = nodo_destruir(nodo_aux);
		(*lista).cantidad--;
		if((*lista).cantidad == 0)
			(*lista).nodo_fin = NULL;
	}
	
	free(lista);

	return;
}



lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(lista == NULL)
		return NULL;

	lista_iterador_t* iterador = (lista_iterador_t*) malloc(sizeof(lista_iterador_t));
	if(iterador == NULL)
		return NULL;

	(*iterador).lista = lista;
	(*iterador).nodo_actual = (*lista).nodo_inicio;

	return iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

	if(iterador == NULL)
		return false;

	return((*iterador).nodo_actual != NULL);
}


void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(iterador == NULL)
		return NULL;
	if(lista_vacia((*iterador).lista))
		return NULL;

	void* elemento = (*(*iterador).nodo_actual).elemento;
	(*iterador).nodo_actual = (*(*iterador).nodo_actual).siguiente;

	return elemento;
}


void lista_iterador_destruir(lista_iterador_t* iterador){
	if(iterador != NULL)
		free(iterador);
}


void iterador_interno_recursivo(nodo_t* nodo,void (*funcion)(void*)){
 	if(nodo == NULL)
		return;	

	(*funcion)((*nodo).elemento);
	iterador_interno_recursivo((*nodo).siguiente,(*funcion));
 }

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if(lista == NULL)
		return;

	iterador_interno_recursivo((*lista).nodo_inicio,(*funcion));
}
