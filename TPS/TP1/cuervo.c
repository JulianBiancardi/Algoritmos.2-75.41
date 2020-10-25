#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuervo_tres_ojos.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define NOMBRE_CUERVO "Tyrion"
#define NOMBRE_APRENDIZ "Bran"
#define ARYA_STARK "Arya Stark"
#define PASADO 'P'
#define FUTURO 'F'

#define LECTURA "r"
#define MAX_LECTURA 800
#define ARCHIVO_VISIONES "visiones.txt"
#define FORMATO_LECTURA "%[^;];%[^;];%[^;];%c\n"
#define CANTIDAD_CAMPOS 4
/*---------------------------------------*/

/*
	Postcondion: Devolvera verdadero si la vision es del pasado,devolvera falso en caso contrario.
*/
bool es_pasada(vision_t vision){
	return(vision.epoca == PASADO);
}
/*
	Postcondion: Devolvera verdadero si la vision es del futuro,devolvera falso en caso contrario.
*/
bool es_futura(vision_t vision){
	return(vision.epoca == FUTURO);
}
/*
	Postcondion: Devolvera verdadero si la vision es de JON,devolvera falso en caso contrario.
*/
bool es_arya_protagonista(vision_t vision){
	return(strcmp(vision.protagonista,ARYA_STARK) == 0);
}

/*
	Precondicion: Recibe un puntero a la estructura "cuervo_tres_ojos"(este puntero debe de estar verificado a partir de la funcion "invocar_cuervo").
	Postcondion: La funcion abrira el archivo de visiones "visiones.txt" (en caso de que no exista devolvera ERROR) y 
				leera 1 vision siguiendo el FORMATO_LECTURA llamando a la funcion "agregar_vision". En caso de que alguna de las visiones dentro del
				archivo no tenga los campos suficientes definidos por CANTIDAD_DE_CAMPOS devolvera ERROR.
*/
int leer_visiones(cuervo_tres_ojos_t* cuervo_viejo){
	FILE* archivo_visiones = fopen(ARCHIVO_VISIONES,LECTURA);
	int estado_operacion = OK;

	if(archivo_visiones == NULL){
		printf("\033[1;31m");//color rojo
		printf("-EL archivo ( %s ) no se ha encontrado o tuvo problemas para abrirse.\n",ARCHIVO_VISIONES);
	}
	else{
		vision_t vision;
		char linea_leida[MAX_LECTURA];
		int leido = 0;

		while((fgets(linea_leida,MAX_LECTURA,archivo_visiones) != NULL) && (estado_operacion == OK)){
			if(linea_leida[0] != '\n'){
				leido = sscanf(linea_leida,FORMATO_LECTURA,vision.protagonista,vision.casa_protagonista,vision.descripcion,&vision.epoca);
				if(leido < CANTIDAD_CAMPOS){
					printf("El formato de la vision no es correcto, le falta/sobra infomacion.\n");
					estado_operacion = ERROR;
				}
				else{	
					if(agregar_vision(cuervo_viejo,vision) == ERROR){
						estado_operacion = ERROR;
						printf("\033[1;31m");//color rojo
						printf("-No se ha podido agregar la vision al cuervo.Puede que no tenga memoria suficiente o la infomacion de la vision sea erronea.\n");
					}
				}
				
			}	
		}
		fclose(archivo_visiones);
	}
	return estado_operacion;
}

void destruir_cuervos(cuervo_tres_ojos_t* cuervo_viejo_ptr,cuervo_aprendiz_t* cuervo_aprendiz_ptr){
	bool estado_operacion = OK;

	printf("\033[1;31m");//color rojo
	if(destruir_cuervo(cuervo_viejo_ptr) == ERROR){
		estado_operacion = ERROR;
		printf("-La memoria del cuervo viejo (o una parte de esta) no ha sido liberada.\n");
	}
	if(destruir_aprendiz(cuervo_aprendiz_ptr) == ERROR){
		estado_operacion = ERROR;
		printf("-La memoria del cuervo aprendiz (o una parte de esta) no ha sido liberada.\n");
	}

	if(estado_operacion == OK){
		printf("\033[1;32m");//color verde
		printf("-Toda la memoria ha sido liberada exitosamente.\n");
	}
	else
		printf("-No pudimos liberar la memoria exitosamente.\n");

	printf("\033[0;0m");//color neutro
}

int main(){

	cuervo_tres_ojos_t* cuervo_viejo_ptr;
	cuervo_aprendiz_t* cuervo_aprendiz_ptr;

	printf("\033[0;0m");//color neutro

	cuervo_viejo_ptr = invocar_cuervo(NOMBRE_CUERVO);
	if(cuervo_viejo_ptr == NULL)
		return ERROR;

	cuervo_aprendiz_ptr = invocar_aprendiz(NOMBRE_APRENDIZ);
	if(cuervo_aprendiz_ptr == NULL)
		return ERROR;


	printf("\033[1;31m");//color rojo
	if(leer_visiones(cuervo_viejo_ptr) == ERROR){
		printf("-No se han podido agregar las visiones al cuervo viejo.\n");
		destruir_cuervos(cuervo_viejo_ptr,cuervo_aprendiz_ptr);
		return ERROR;
	}

	if(transmitir_visiones(cuervo_viejo_ptr,cuervo_aprendiz_ptr,es_pasada) == ERROR){
		printf("-No se ha podido transmitir las visiones al cuervo aprendiz.\n");
		destruir_cuervos(cuervo_viejo_ptr,cuervo_aprendiz_ptr);
		return ERROR;
	}
	
	if(transmitir_visiones(cuervo_viejo_ptr,cuervo_aprendiz_ptr,es_arya_protagonista) == ERROR){
		printf("-No se ha podido transmitir las visiones al cuervo aprendiz.\n");
		destruir_cuervos(cuervo_viejo_ptr,cuervo_aprendiz_ptr);
		return ERROR;
	}

	printf("\033[0;0m");//color neutro
	listar_visiones_transmitidas(cuervo_aprendiz_ptr,es_pasada);
	listar_visiones_transmitidas(cuervo_aprendiz_ptr,es_futura);

	destruir_cuervos(cuervo_viejo_ptr,cuervo_aprendiz_ptr);	

	return OK;
}