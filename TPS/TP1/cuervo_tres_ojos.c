#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cuervo_tres_ojos.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define PASADO 'P'
#define FUTURO 'F'
/*---------------------------------------*/

/*
	Precondicion: Recibe un nombre del cuervo a invocar(la cantidad de caracteres no puede exeder MAX_NOMBRE_ARCHIVO).
	Postcondion: La funcion creara la estructura "cuervo_tres_ojos" reservando el espacio de memoria necesaria en el Heap.
				Devolvera un puntero a esa estructura(con sus datos inicializados correctamente),devolvera NULL en caso contrario
				mostrando por pantalla un error informandole al usuario lo sucedido.
*/
cuervo_tres_ojos_t* invocar_cuervo(char* nombre){
	cuervo_tres_ojos_t* cuervo;
	cuervo = (cuervo_tres_ojos_t*) malloc(sizeof(cuervo_tres_ojos_t));
	if(cuervo == NULL){
		printf("\033[1;31m");//color rojo
		printf("-Tuvimos problemas al crea el cuervo.Puede que su memoria este agotada.\n");
		return NULL;
	}
	strcpy((*cuervo).nombre,nombre);
	(*cuervo).visiones_del_pasado = NULL;
	(*cuervo).visiones_del_futuro = NULL;
	(*cuervo).cantidad_visiones_pasado = 0;
	(*cuervo).cantidad_visiones_futuro = 0;
	return cuervo;
}
/*
	Precondicion: Recibe un nombre del cuervo a invocar(la cantidad de caracteres no puede exeder MAX_NOMBRE_ARCHIVO).
	Postcondion: La funcion creara la estructura "cuervo_aprendiz" reservando el espacio de memoria necesaria en el Heap.
				Devolvera un puntero a esa estructura(con sus datos inicializados correctamente),devolvera NULL en caso contrario
				mostrando por pantalla un error informandole al usuario lo sucedido.
*/
cuervo_aprendiz_t* invocar_aprendiz(char* nombre){
	cuervo_aprendiz_t* aprendiz;
	aprendiz = (cuervo_aprendiz_t*) malloc(sizeof(cuervo_aprendiz_t));
	if(aprendiz == NULL){
		printf("\033[1;31m");//color rojo
		printf("-Tuvimos problemas al crear el cuervo aprendiz.Puede que su memoria este agotada.\n");
		return NULL;
	}
	strcpy((*aprendiz).nombre,nombre);
	(*aprendiz).visiones_adquiridas = NULL;
	(*aprendiz).cantidad_visiones = 0;

	return aprendiz;
}
/*
	Precondicion: Recibe un puntero a la estructura "cuervo_tres_ojos"(este puntero debe de estar verificado a partir de la funcion "invocar_cuervo")
				y una vision (esta vision ya ha sido verificada por la funcion "leer visiones").
	Postcondion: La funcion añadira la vision al vector de visiones correspondientes de la estructura del cuervo_viejo reservando la memoria
				necesaria en el Heap.Devolvera OK(0) si pudo agregar la vision correctamente,devolvera ERROR(-1) en caso contrario.
*/
int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){
	vision_t* auxiliar_ptr;
	int cantidad_visiones = 0;

	if(vision.epoca == PASADO){
		auxiliar_ptr = (*cuervo).visiones_del_pasado;
		cantidad_visiones = (*cuervo).cantidad_visiones_pasado;
	}
	else if(vision.epoca == FUTURO){
		auxiliar_ptr = (*cuervo).visiones_del_futuro;
		cantidad_visiones = (*cuervo).cantidad_visiones_futuro;
	}
	else
		return ERROR;

	auxiliar_ptr = (vision_t*) realloc(auxiliar_ptr,sizeof(vision_t) * (long unsigned int)(cantidad_visiones + 1));
	if(auxiliar_ptr == NULL)
		return ERROR;

	if(vision.epoca == PASADO){
		(*cuervo).visiones_del_pasado = auxiliar_ptr;
		(*cuervo).cantidad_visiones_pasado++;
	}
	else{
		(*cuervo).visiones_del_futuro = auxiliar_ptr;
		(*cuervo).cantidad_visiones_futuro++;
	}

	auxiliar_ptr[cantidad_visiones] = vision;	
	
	return OK;
}

/*
	Precondicion: Recibe un puntero a la estructura "cuervo_aprendiz"(este puntero ya debio de estar verificado) y una vision
	Postcondion: Devolvera verdadero en caso de que la vision se encuentre en el vector de "visiones_adquiridas" de la estructura apuntada por
				el puntero,devolvera falso en caso contrario.
*/
bool esta_adquirida(cuervo_aprendiz_t* aprendiz,vision_t vision){
	bool esta = false;
	int i = 0;
	while(i < (*aprendiz).cantidad_visiones && !esta){
		if((*aprendiz).visiones_adquiridas[i].epoca == vision.epoca){
			if(strcmp((*aprendiz).visiones_adquiridas[i].protagonista,vision.protagonista) == 0){
				if(strcmp((*aprendiz).visiones_adquiridas[i].casa_protagonista,vision.casa_protagonista) == 0){
					if(strcmp((*aprendiz).visiones_adquiridas[i].descripcion,vision.descripcion) == 0)
						esta = true;
				}
			}
		}
		i++;
	}
	return esta;
}
/*
	Precondicion: Recibe una fecha de liberacion y una conducta las cuales ya debieron estar verificadas anteriormente.
	Postcondion: La funcion transmitira al aprendiz las visiones del pasado y del futuro del cuervo que sean transmisibles 
				de acuerdo a la función recibida como parámetro.En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida),
				no se agrega a las visiones del mismo.El puntero "es_transmisible" puede ser tanto: 
				"es_pasada" "es_futura" o cualquier funcion que tenga la firma --bool nombre_funcion(vision_t vision)--
				Devolvera OK(0) si pudo transmitir las visiones con la funcion pasada por parametro,devolvera ERROR(-1) en caso contrario.
*/
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
	int i = 0;
	bool estado_operacion = OK;
	vision_t vision_actual;
	vision_t* auxiliar_ptr;

	int cantidad_visiones = (*cuervo).cantidad_visiones_pasado;

	cantidad_visiones = (*cuervo).cantidad_visiones_pasado;
	while((i < cantidad_visiones) && (estado_operacion == OK)){
		vision_actual = (*cuervo).visiones_del_pasado[i];
 		if(es_transmisible(vision_actual) && !esta_adquirida(aprendiz,vision_actual)){
 			auxiliar_ptr = (*aprendiz).visiones_adquiridas;
 			auxiliar_ptr = (vision_t*) realloc(auxiliar_ptr,sizeof(vision_t) * (long unsigned int)((*aprendiz).cantidad_visiones + 1));
			if(auxiliar_ptr == NULL){
				printf("\033[1;31m");//color rojo
				printf("-Tuvimos problemas al pasar la vision al cuervo aprendiz.Puede que su memoria este agotada.\n");
				estado_operacion = ERROR;
			}
			else{
				(*aprendiz).visiones_adquiridas = auxiliar_ptr;
				auxiliar_ptr[(*aprendiz).cantidad_visiones] = vision_actual;
				((*aprendiz).cantidad_visiones)++;
			}
		}
		i++;
	}
	i = 0;
	cantidad_visiones = (*cuervo).cantidad_visiones_futuro;
	while((i < cantidad_visiones) && (estado_operacion == OK)){
		vision_actual = (*cuervo).visiones_del_futuro[i];
 		if(es_transmisible(vision_actual) && !esta_adquirida(aprendiz,vision_actual)){
 			auxiliar_ptr = (*aprendiz).visiones_adquiridas;
 			auxiliar_ptr = (vision_t*) realloc(auxiliar_ptr,sizeof(vision_t) * (long unsigned int)((*aprendiz).cantidad_visiones + 1));
			if(auxiliar_ptr == NULL){
				printf("\033[1;31m");//color rojo
				printf("-Tuvimos problemas al pasar la vision al cuervo aprendiz.Puede que su memoria este agotada.\n");
				estado_operacion = ERROR;
			}
			else{
				(*aprendiz).visiones_adquiridas = auxiliar_ptr;
				auxiliar_ptr[(*aprendiz).cantidad_visiones] = vision_actual;
				((*aprendiz).cantidad_visiones)++;	
			}
		}
		i++;
	}

	return estado_operacion;
}
/*
	Precondicion: Recibe una fecha de liberacion y una conducta las cuales ya debieron estar verificadas anteriormente.
	Postcondion: La funcion mostrara por pantalla las visiones adquiridas por el cuervo aprendiz. Una visión se listará 
				sólo si la función recibida como parámetro (es_listable) lo permite.El puntero "es_listable" puede ser
				tanto: "es_pasada" "es_futura" o cualquier funcion que tenga la firma --bool nombre_funcion(vision_t vision)--
*/
void listar_visiones_transmitidas(cuervo_aprendiz_t* aprendiz, bool (*es_listable)(vision_t)){
	printf("\033[0;0m");//color neutro
	vision_t vision_actual;

	for(int i = 0;i < (*aprendiz).cantidad_visiones;i++){
		vision_actual = (*aprendiz).visiones_adquiridas[i];
		if(es_listable(vision_actual))

			printf("Vision sobre %s (casa %s): %s.  Epoca:%s.\n",
				vision_actual.protagonista,
				vision_actual.casa_protagonista,
				vision_actual.descripcion,
				vision_actual.epoca == PASADO?"Pasado":"Futuro");
			
	}
}

/*
	Precondicion: Recibe un puntero a la estructura "cuervo_tres_ojos"
	Postcondion: La funcion destruira la estructura del cuervo viejo apuntada por el puntero,liberando la memoria reservado por este y sus visiones.
				Devolvera OK(0) si pudo liberar la memoria exitosamente(puntero distinto de NULL) o devolvera ERROR(-1) en caso contrario (puntero NULL).
*/
int destruir_cuervo(cuervo_tres_ojos_t* cuervo){
	int estado_operacion = OK;

	if(cuervo != NULL){
		if((*cuervo).visiones_del_pasado != NULL)
			free((*cuervo).visiones_del_pasado);

		if((*cuervo).visiones_del_futuro != NULL)
			free((*cuervo).visiones_del_futuro);

		free(cuervo);
		cuervo = NULL;
	}
	else
		estado_operacion = ERROR;

	return estado_operacion;

}
/*
	Precondicion: Recibe un puntero a la estructura "cuervo_aprendiz"
	Postcondion: La funcion destruira la estructura del cuervo aprendiz apuntada por el puntero,liberando la memoria reservado por este y sus visiones.
				Devolvera OK(0) si pudo liberar la memoria exitosamente(puntero distinto de NULL) o devolvera ERROR(-1) en caso contrario (puntero NULL).
*/
int destruir_aprendiz(cuervo_aprendiz_t* aprendiz){
	int estado_operacion = OK;

	if(aprendiz != NULL){
		if((*aprendiz).visiones_adquiridas != NULL)
			free((*aprendiz).visiones_adquiridas);

		free(aprendiz);
		aprendiz = NULL;
	}
	else
		estado_operacion = ERROR;

	return estado_operacion;
}

