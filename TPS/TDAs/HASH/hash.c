#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_iterador.h"
#include "lista.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define FACTOR_CARGA_MAXIMO 3
/*---------------------------------------*/

// Necesario porque strdup es POSIX pero no C99
extern char* strdup(const char*);

typedef struct dato{
	const char* clave;
	void* elemento;	
}dato_t;

struct hash{
	lista_t** tabla_hash;
	size_t cantidad_elementos;
	size_t capacidad;
	hash_destruir_dato_t destructor;
};
struct hash_iter{
	lista_iterador_t* iterador_lista;
	size_t lista_actual;
	hash_t* hash;
};

dato_t* dato_crear(const char* clave,void* elemento){
	dato_t* dato = (dato_t*) malloc(sizeof(dato_t));
	if(dato == NULL || clave == NULL)
		return NULL;

	(*dato).clave = clave;
	(*dato).elemento = elemento;

	return dato;
}
dato_t* dato_buscar(lista_t* lista,const char* clave){

	dato_t* dato_actual = NULL;
	bool esta = false;
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	while(lista_iterador_tiene_siguiente(iterador) && !esta){
		dato_actual = (dato_t*)lista_iterador_siguiente(iterador);
		if(strcmp((*dato_actual).clave,clave) == 0)
			esta = true;
	}
	lista_iterador_destruir(iterador);
	if(!esta)
		dato_actual = NULL;

	return dato_actual;
}
void dato_destruir(dato_t* dato){
	if(dato != NULL){
		free((void*)(*dato).clave);
		free(dato);
	}
}

size_t funcion_hash(hash_t* hash,const char* clave){

	size_t contador = 0;
	while(*clave != '\0'){
		contador +=  (size_t)*clave;
		clave = clave + 1;
	}
	return (contador % (*hash).capacidad);
}


hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
	if(capacidad < 1)
		return NULL;

	hash_t* hash = (hash_t*) malloc(sizeof(hash_t));
	if(hash == NULL)
		return NULL;

	(*hash).tabla_hash = (lista_t**) malloc(sizeof(lista_t*) * capacidad);
	if((*hash).tabla_hash == NULL){
		free(hash);
		return NULL;
	}

	for (int i = 0; i < capacidad;i++)
		(*hash).tabla_hash[i] = lista_crear();

	(*hash).cantidad_elementos = 0;
	(*hash).destructor = destruir_elemento;
	(*hash).capacidad = capacidad;

	return hash;
}

bool numero_primo(size_t numero){
	if(numero < 1)
		return false;

	bool es_primo = true;
    size_t divisores = 2;
    while(divisores < numero  && es_primo){
        if(numero % divisores == 0) 
        	es_primo = false;
        divisores++;
    }
    return es_primo;
}
size_t buscar_proximo_numero_primo(size_t numero_actual){
	if(numero_actual < 1)
		return numero_actual;

	if(numero_primo(numero_actual + 1))
		return numero_actual + 1;

	return buscar_proximo_numero_primo(numero_actual + 1);
}
int rehash(hash_t* hash){

	//Busco el proximo numero primo al doble de la capacida.Al doble de la capacidad y no la capacidad misma 
	//para no volver a tener que hacer rehash tan pronto(es un proceso costoso)
	size_t nueva_capacidad = buscar_proximo_numero_primo((*hash).capacidad * 2);
	hash_t* hash_auxiliar = hash_crear(NULL,nueva_capacidad);
	
	if(hash_auxiliar == NULL)
		return ERROR;	

 	hash_iterador_t* iterador = hash_iterador_crear(hash);
  	while(hash_iterador_tiene_siguiente(iterador)){
    	const char* clave_actual = (char*)hash_iterador_siguiente(iterador);
    	void* elemento_actual = hash_obtener(hash,clave_actual);
    	hash_insertar(hash_auxiliar,clave_actual,elemento_actual);
  	}
  	hash_iterador_destruir(iterador);

  	lista_t** vieja_tabla_hash = (*hash).tabla_hash;
  	(*hash).tabla_hash = (*hash_auxiliar).tabla_hash;
  	(*hash_auxiliar).tabla_hash = vieja_tabla_hash;

  	(*hash_auxiliar).capacidad = (*hash).capacidad;
  	(*hash).capacidad = nueva_capacidad;

	hash_destruir(hash_auxiliar);
  	return OK;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	if(hash == NULL || clave == NULL)
		return ERROR;

	size_t ubicacion = funcion_hash(hash,clave);
		
	dato_t* dato = dato_buscar((*hash).tabla_hash[ubicacion],clave);
	if(dato != NULL){
		if((*hash).destructor != NULL)
			(*hash).destructor((*dato).elemento);
		(*dato).elemento = elemento;
	}
	else{
		
		dato = dato_crear((const char*)strdup(clave),elemento);
		if(dato == NULL)
			return ERROR;
		lista_insertar((*hash).tabla_hash[ubicacion],dato);

		((*hash).cantidad_elementos)++;

		float factor_carga = ((float)(*hash).cantidad_elementos / (float)(*hash).capacidad);
		if(factor_carga > FACTOR_CARGA_MAXIMO)		
			rehash(hash);
	}
	
	return OK;
}

int hash_quitar(hash_t* hash, const char* clave){
	if(hash == NULL)
		return ERROR;

	size_t ubicacion = funcion_hash(hash,clave);
	if(ubicacion == ERROR)
		return ERROR;

	bool esta = false;
	size_t contador = 0;
	lista_iterador_t* iterador = lista_iterador_crear((*hash).tabla_hash[ubicacion]);

	while(lista_iterador_tiene_siguiente(iterador) && !esta){
		dato_t* dato_actual = (dato_t*)lista_iterador_siguiente(iterador);
		if(strcmp((*dato_actual).clave,clave) == 0){
			if((*hash).destructor != NULL)
				(*hash).destructor((*dato_actual).elemento);
			dato_destruir(dato_actual);
			lista_borrar_de_posicion((*hash).tabla_hash[ubicacion],contador);
			((*hash).cantidad_elementos)--;
			esta = true;
		}
		contador++;
	}
	lista_iterador_destruir(iterador);

	return (esta == true)?OK : ERROR;
}

void* hash_obtener(hash_t* hash, const char* clave){
	if(hash == NULL || clave == NULL)
		return NULL;

	size_t ubicacion = funcion_hash(hash,clave);

	dato_t* dato = dato_buscar((*hash).tabla_hash[ubicacion],clave);
	if(dato == NULL)
		return NULL;

	return (*dato).elemento;;
}

bool hash_contiene(hash_t* hash, const char* clave){

	return (hash_obtener(hash,clave) != NULL)?true : false;
}

size_t hash_cantidad(hash_t* hash){
	if(hash == NULL)
		return 0;

	return (*hash).cantidad_elementos;
}

void hash_destruir(hash_t* hash){
	if(hash != NULL){
		for(int i = 0;i < (*hash).capacidad;i++){
			lista_t* lista_actual = (*hash).tabla_hash[i];
			lista_iterador_t* iterador = lista_iterador_crear(lista_actual);

			while(lista_iterador_tiene_siguiente(iterador)){
				dato_t* dato_actual = (dato_t*)lista_iterador_siguiente(iterador);
				if((*hash).destructor != NULL)
					(*hash).destructor((*dato_actual).elemento);
				dato_destruir(dato_actual);
			}
			lista_iterador_destruir(iterador);
			lista_destruir(lista_actual);
		}
		free((*hash).tabla_hash);
		free(hash);
	}
}

size_t buscar_proxima_lista_recursiva(hash_t* hash,size_t posicion_actual){

	if(posicion_actual > (*hash).capacidad - 1)
		return ((*hash).capacidad); 

	lista_t* lista_actual = (*hash).tabla_hash[posicion_actual];
	if(posicion_actual < (*hash).capacidad && lista_vacia(lista_actual)){
		return buscar_proxima_lista_recursiva(hash,posicion_actual + 1);
	}
	return posicion_actual;
}
size_t buscar_proxima_lista(hash_t* hash,size_t posicion_actual){

	size_t proxima_lista = buscar_proxima_lista_recursiva(hash,posicion_actual + 1);
	return (proxima_lista >= (*hash).capacidad)?posicion_actual : proxima_lista;
}

hash_iterador_t* hash_iterador_crear(hash_t* hash){
	
	if(hash == NULL)
		return NULL;

	hash_iterador_t* iterador = (hash_iterador_t*) malloc(sizeof(hash_iterador_t));
	if(iterador == NULL)
		return NULL;

	(*iterador).hash = hash;
	(*iterador).lista_actual = 0;
	(*iterador).iterador_lista = lista_iterador_crear((*hash).tabla_hash[0]);
	
	return iterador;
}

void* hash_iterador_siguiente(hash_iterador_t* iterador){
	if(iterador == NULL)
		return NULL;

	void* dato_siguiente = lista_iterador_siguiente((*iterador).iterador_lista);
	
	return (void*)(*(dato_t*)dato_siguiente).clave;
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){

	if(iterador == NULL)
		return false;

	bool hay_claves = lista_iterador_tiene_siguiente((*iterador).iterador_lista);
	
	if(!hay_claves){
		lista_iterador_destruir((*iterador).iterador_lista);
		size_t nueva_posicion = buscar_proxima_lista((*iterador).hash,(*iterador).lista_actual);
		if(nueva_posicion == (*iterador).lista_actual){
			(*iterador).iterador_lista = NULL;
			return false;
		}
		(*iterador).lista_actual = nueva_posicion;
		(*iterador).iterador_lista = lista_iterador_crear((*(*iterador).hash).tabla_hash[nueva_posicion]);
		hay_claves = lista_iterador_tiene_siguiente((*iterador).iterador_lista);
	}

	return hay_claves;
}

void hash_iterador_destruir(hash_iterador_t* iterador){
	if(iterador == NULL)
		return;

	if((*iterador).iterador_lista != NULL)
		lista_iterador_destruir((*iterador).iterador_lista);

	free(iterador);
}
