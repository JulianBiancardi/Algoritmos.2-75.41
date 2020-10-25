#include <stdlib.h>
#include "abb.h"
#include "pila.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

/*---------------------------------------*/

nodo_abb_t* nodo_crear(void* elemento){
	nodo_abb_t* nodo = (nodo_abb_t*) malloc(sizeof(nodo_abb_t));
	if(nodo == NULL)
		return NULL;

	(*nodo).elemento = elemento;
	(*nodo).izquierda = NULL;
	(*nodo).derecha = NULL;

	return nodo;
}
void nodo_destruir(nodo_abb_t* nodo){
	if(nodo != NULL)
		free(nodo);
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	abb_t* arbol = malloc(sizeof(nodo_abb_t));
	if (arbol == NULL) 
		return NULL;

	(*arbol).nodo_raiz = NULL;
	(*arbol).comparador = comparador;
	(*arbol).destructor = destructor;

	return arbol;
}

nodo_abb_t* arbol_insertar_recursivo(abb_t* arbol,nodo_abb_t* nodo,void* elemento){

	if(nodo == NULL){
		nodo = nodo_crear(elemento);
		return nodo;
	}

	if((*arbol).comparador(elemento,(*nodo).elemento) > 0)
		(*nodo).derecha = arbol_insertar_recursivo(arbol,(*nodo).derecha,elemento);
	else if((*arbol).comparador(elemento,(*nodo).elemento) < 0)
		(*nodo).izquierda = arbol_insertar_recursivo(arbol,(*nodo).izquierda,elemento);
	else if((*arbol).comparador(elemento,(*nodo).elemento) == 0){
		//Si es repetido insertamos a la izquierda
		nodo_abb_t* nodo_repetido = nodo_crear(elemento);
		(*nodo_repetido).izquierda = (*nodo).izquierda;
		(*nodo).izquierda = nodo_repetido;
	}
		
	return nodo;
}
int arbol_insertar(abb_t* arbol, void* elemento){
	if(arbol == NULL)
 		return ERROR;

 	if(elemento == NULL)
 		return ERROR;

 	if(arbol_vacio(arbol)){
 		(*arbol).nodo_raiz = nodo_crear(elemento);
 		if((*arbol).nodo_raiz == NULL)
 			return ERROR;

 		return OK;
 	}


 	return ((arbol_insertar_recursivo(arbol,(*arbol).nodo_raiz,elemento) != NULL)?OK : ERROR);
}

nodo_abb_t* buscar_padre_mas_izq(nodo_abb_t* nodo){
	if(nodo == NULL)
		return NULL;

	nodo_abb_t* proximo_padre = NULL;

	while((*nodo).izquierda != NULL){
		proximo_padre = nodo;
		nodo = (*nodo).izquierda;
	}
	return proximo_padre;
}
nodo_abb_t* arbol_borrar_recursivo(abb_t* arbol,nodo_abb_t* nodo,void* elemento){

	if(nodo == NULL)
		return NULL;

	if((*arbol).comparador(elemento,(*nodo).elemento) > 0){
		(*nodo).derecha = arbol_borrar_recursivo(arbol,(*nodo).derecha,elemento);
		return nodo;
	}
	if((*arbol).comparador(elemento,(*nodo).elemento) < 0){
		(*nodo).izquierda = arbol_borrar_recursivo(arbol,(*nodo).izquierda,elemento);
		return nodo;
	}
	
	// Si nodo es hoja
	if(!(*nodo).izquierda && !(*nodo).derecha){
		if(nodo == ((*arbol).nodo_raiz))
			((*arbol).nodo_raiz) = NULL;

		if(nodo == ((*arbol).nodo_raiz))
			((*arbol).nodo_raiz) = nodo;

		if((*arbol).destructor != NULL)
			(*arbol).destructor((*nodo).elemento);
		nodo_destruir(nodo);
		return NULL;	
	}
		
	// Si tiene un solo hijo
	else if((!(*nodo).izquierda && (*nodo).derecha)|| ((*nodo).izquierda && !(*nodo).derecha)){
		nodo_abb_t* nodo_aux = (*nodo).derecha != NULL?(*nodo).derecha : (*nodo).izquierda;

		if(nodo == ((*arbol).nodo_raiz))
			((*arbol).nodo_raiz) = nodo_aux;

		if((*arbol).destructor != NULL)
			(*arbol).destructor((*nodo).elemento);
		nodo_destruir(nodo);
		return nodo_aux;
	}
		
	// Si tiene dos hijos
	else if((*nodo).izquierda && (*nodo).derecha){

		nodo_abb_t* nodo_padre = buscar_padre_mas_izq((*nodo).derecha);
		nodo_abb_t* nodo_reemplazante;

		if(nodo_padre == NULL){
			nodo_reemplazante = (*nodo).derecha;
			(*nodo_reemplazante).izquierda = (*nodo).izquierda;
		}
		else{
			nodo_reemplazante = (*nodo_padre).izquierda;
			(*nodo_padre).izquierda =(*nodo_reemplazante).derecha;
			(*nodo_reemplazante).izquierda = (*nodo).izquierda;
			(*nodo_reemplazante).derecha = (*nodo).derecha;
		}


		if(nodo == ((*arbol).nodo_raiz))
			((*arbol).nodo_raiz) = nodo_reemplazante;

		if((*arbol).destructor != NULL)
			(*arbol).destructor((*nodo).elemento);
		nodo_destruir(nodo);

		return nodo_reemplazante;
	}
	
	return nodo;
}
int arbol_borrar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol))
		return ERROR;

	if(elemento == NULL)
		return ERROR;

	arbol_borrar_recursivo(arbol,(*arbol).nodo_raiz,elemento);

	return OK;
}

void* arbol_buscar_recursivo(abb_t* arbol,nodo_abb_t* nodo,void* elemento){

	if(nodo == NULL)
		return NULL;
	
	if((*arbol).comparador(elemento,(*nodo).elemento) > 0)
		return arbol_buscar_recursivo(arbol,(*nodo).derecha,elemento);

	if((*arbol).comparador(elemento,(*nodo).elemento) < 0)
		return arbol_buscar_recursivo(arbol,(*nodo).izquierda,elemento);

	return (*nodo).elemento;
}
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol == NULL)
		return NULL;
	
	return(arbol_buscar_recursivo(arbol,(*arbol).nodo_raiz,elemento));
}

void* arbol_raiz(abb_t* arbol){
	if(arbol_vacio(arbol))
		return NULL;

	return((*(*arbol).nodo_raiz).elemento);
}

bool arbol_vacio(abb_t* arbol){
	if(arbol == NULL)
		return true;

	return((*arbol).nodo_raiz == NULL);
}

int agregar_array(void* elemento,void** array,int* tope,int tamanio_array){
	if(tamanio_array == 0)
		return ERROR;

	if((*tope) >= tamanio_array)
		return ERROR;

	array[(*tope)] = elemento;
	(*tope)++;

	return OK;
}
int arbol_recorrido_inorden_recursivo(nodo_abb_t* nodo,void** array,int* tope,int tamanio_array){
	if(nodo == NULL)
		return 0;

	arbol_recorrido_inorden_recursivo((*nodo).izquierda,array,tope,tamanio_array);
	if(agregar_array((*nodo).elemento,array,tope,tamanio_array) == ERROR)
		return (*tope);
	arbol_recorrido_inorden_recursivo((*nodo).derecha,array,tope,tamanio_array);


	return(*tope);
}
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL)
		return 0;

	int tope = 0;

	return(arbol_recorrido_inorden_recursivo((*arbol).nodo_raiz,array,&tope,tamanio_array));
}

int arbol_recorrido_preorden_recursivo(nodo_abb_t* nodo,void** array,int* tope,int tamanio_array){
	if(nodo == NULL)
		return 0;

	if(agregar_array((*nodo).elemento,array,tope,tamanio_array) == ERROR)
		return (*tope);
	arbol_recorrido_preorden_recursivo((*nodo).izquierda,array,tope,tamanio_array);
	arbol_recorrido_preorden_recursivo((*nodo).derecha,array,tope,tamanio_array);

	return(*tope);
}
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL)
		return 0;

	int tope = 0;

	return(arbol_recorrido_preorden_recursivo((*arbol).nodo_raiz,array,&tope,tamanio_array));
}

int arbol_recorrido_postorden_recursivo(nodo_abb_t* nodo,void** array,int* tope,int tamanio_array){
	if(nodo == NULL)
		return 0;

	arbol_recorrido_postorden_recursivo((*nodo).izquierda,array,tope,tamanio_array);
	arbol_recorrido_postorden_recursivo((*nodo).derecha,array,tope,tamanio_array);
	if(agregar_array((*nodo).elemento,array,tope,tamanio_array) == ERROR)
		return (*tope);

	return(*tope);
}
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL)
		return 0;

	int tope = 0;

	return(arbol_recorrido_postorden_recursivo((*arbol).nodo_raiz,array,&tope,tamanio_array));
}

void arbol_destruir_recursivo(abb_t* arbol,nodo_abb_t* nodo){
	if(nodo == NULL)
		return;

	arbol_destruir_recursivo(arbol,(*nodo).izquierda);
	arbol_destruir_recursivo(arbol,(*nodo).derecha);

	if((*arbol).destructor != NULL)
		(*arbol).destructor((*nodo).elemento);

	nodo_destruir(nodo);

	return;
}
void arbol_destruir(abb_t* arbol){
	if(arbol == NULL)
		return;

	if(!arbol_vacio(arbol))
		arbol_destruir_recursivo(arbol,(*arbol).nodo_raiz);

	free (arbol);
}

bool iterar_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if(nodo == NULL)
		return true;

	if(iterar_inorden((*nodo).izquierda,funcion,extra) == false)
		return false;
	if(funcion((*nodo).elemento,extra) == true)
		return false;
	if(iterar_inorden((*nodo).derecha,funcion,extra) == false)
		return false;

	return true;
}
bool iterar_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if(nodo == NULL)
		return true;

	if(funcion((*nodo).elemento,extra) == true)
		return false;
	if(iterar_preorden((*nodo).izquierda,funcion,extra) == false)
		return false;
	if(iterar_preorden((*nodo).derecha,funcion,extra) == false)
		return false;

	return true;
}
bool iterar_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra){
	if(nodo == NULL)
		return true;

	if(iterar_postorden((*nodo).izquierda,funcion,extra) == false)
		return false;
	if(iterar_postorden((*nodo).derecha,funcion,extra) == false)
		return false;		
	if(funcion((*nodo).elemento,extra) == true)
		return false;

	return true;
}
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol == NULL)
		return;

	switch(recorrido){
		case ABB_RECORRER_INORDEN:
			iterar_inorden((*arbol).nodo_raiz,funcion,extra);
			break;
		case ABB_RECORRER_PREORDEN:
			iterar_preorden((*arbol).nodo_raiz,funcion,extra);
			break;
		case ABB_RECORRER_POSTORDEN:
			iterar_postorden((*arbol).nodo_raiz,funcion,extra);
			break;
		default:
			break;
	}
}

//______________________ITERADOR EXTERNO____________________________//

struct abb_iterador
{
	abb_t* arbol;
	pila_t* pila;
	int recorrido;  // 0:INORDEN  1:PREORDEN  2: POSTORDEN
};

void apilar_hijos_izquierdos(pila_t* pila,nodo_abb_t* nodo_actual){
	if(nodo_actual == NULL)
		return;

	pila_apilar(pila,nodo_actual);
	apilar_hijos_izquierdos(pila,nodo_actual->izquierda);
}
void apilar_hasta_nodo_hoja(pila_t* pila,nodo_abb_t* nodo_actual){
	if(nodo_actual == NULL)
		return;

	pila_apilar(pila,nodo_actual);
	if(nodo_actual->izquierda != NULL)
		apilar_hasta_nodo_hoja(pila,nodo_actual->izquierda);
	else if(nodo_actual->derecha != NULL)
		apilar_hasta_nodo_hoja(pila,nodo_actual->derecha);

	return;	
}

abb_iterador_t* abb_iterador_crear(abb_t* arbol, int recorrido){
	if(arbol == NULL)
		return NULL;

	if(recorrido != ABB_RECORRER_INORDEN && recorrido != ABB_RECORRER_PREORDEN && recorrido !=ABB_RECORRER_POSTORDEN)
		return NULL;

	abb_iterador_t* iterador = (abb_iterador_t*)malloc(sizeof(abb_iterador_t));
	if(iterador == NULL)
		return NULL;

	iterador->pila = pila_crear();
	if(iterador->pila == NULL){
		free(iterador);
		return NULL;
	}

	iterador->arbol = arbol;
	iterador->recorrido = recorrido;

	if(iterador->recorrido == ABB_RECORRER_INORDEN)
		apilar_hijos_izquierdos(iterador->pila,arbol->nodo_raiz);
	
	else if(iterador->recorrido == ABB_RECORRER_PREORDEN && !arbol_vacio(arbol))
		pila_apilar(iterador->pila,arbol->nodo_raiz);	
	
	else if(iterador->recorrido == ABB_RECORRER_POSTORDEN)
		apilar_hasta_nodo_hoja(iterador->pila,arbol->nodo_raiz);
	
	return iterador;
}

void* abb_iterador_actual(abb_iterador_t* iterador){
	if(iterador == NULL)
		return NULL;

	nodo_abb_t* nodo_actual = (nodo_abb_t*)pila_tope(iterador->pila);
	return nodo_actual ? nodo_actual->elemento : NULL; 
}
bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador){
	if(iterador == NULL)
		return false;

	return !pila_vacia(iterador->pila);
}

void abb_iterador_siguiente(abb_iterador_t* iterador){
	if(iterador == NULL)
		return;

	if(!abb_iterador_tiene_siguiente(iterador))
		return;

	nodo_abb_t* nodo_actual = (nodo_abb_t*)pila_tope(iterador->pila);
	pila_desapilar(iterador->pila);

	if(iterador->recorrido == ABB_RECORRER_INORDEN){
		if(nodo_actual->derecha != NULL)
			apilar_hijos_izquierdos(iterador->pila,nodo_actual->derecha);
	}
	
	else if(iterador->recorrido == ABB_RECORRER_PREORDEN){
		if(nodo_actual->derecha != NULL)
			pila_apilar(iterador->pila,nodo_actual->derecha);
		if(nodo_actual->izquierda != NULL)
			pila_apilar(iterador->pila,nodo_actual->izquierda);
	}
	
	else if(iterador->recorrido == ABB_RECORRER_POSTORDEN){
		nodo_abb_t* nodo_aux = (nodo_abb_t*)pila_tope(iterador->pila);
		if(nodo_aux != NULL){
			if(nodo_aux->derecha != NULL && nodo_aux->derecha != nodo_actual)
				apilar_hasta_nodo_hoja(iterador->pila,nodo_aux->derecha);
		}
	}		
}

void abb_iterador_inicio(abb_iterador_t* iterador){
	if(iterador == NULL)
		return;

	pila_destruir(iterador->pila);
	iterador->pila = pila_crear();

	if(iterador->pila == NULL)
		return;

	if(iterador->recorrido == ABB_RECORRER_INORDEN)
		apilar_hijos_izquierdos(iterador->pila,iterador->arbol->nodo_raiz);
	
	else if(iterador->recorrido == ABB_RECORRER_PREORDEN && !arbol_vacio(iterador->arbol))
		pila_apilar(iterador->pila,iterador->arbol->nodo_raiz);	
	
	else if(iterador->recorrido == ABB_RECORRER_POSTORDEN)
		apilar_hasta_nodo_hoja(iterador->pila,iterador->arbol->nodo_raiz);
	
}

void abb_iterador_destruir(abb_iterador_t* iterador){
	if(iterador != NULL){
		pila_destruir(iterador->pila);
		free(iterador);
	}
}