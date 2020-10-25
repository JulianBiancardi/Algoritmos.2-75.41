#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "juego_tronos.h"

#define OK 0
#define ERROR -1

#define INICIAR_SIMULACION 'S'
#define AGREGAR_CASA 'A'
#define LISTAR_CASAS 'L'
#define MOSTRAR_CASAS_EXTINTAS 'E'
#define FINALIZAR_SIMULACION 'Q'


int main(){

	juego_t* westeros = juego_crear();

	char letra_ingresada;
	int cantidad_anios;
	char nombre_archivo[100];

	do{
		juego_mostrar_menu ();
		printf("Ingrese una letra: \n");
		scanf(" %c",&letra_ingresada);
		switch(letra_ingresada){
			case INICIAR_SIMULACION:
				printf("->Ingrese la cantidad de años que desea simular: \n");
				scanf("%i",&cantidad_anios);
				juego_simulacion(westeros,cantidad_anios);
				break;
			case AGREGAR_CASA:
			
				printf("->Ingrese el nombre del archivo : \n");
				scanf("%s",nombre_archivo);
								
				if(juego_agregar_casa(westeros,nombre_archivo) == OK)
					printf("\033[1;32mSe han cargado correctamente las casas.\033[0;0m\n");
				else
					printf("\033[1;31mTuvimos problemas al cargar las casas.\033[0;0m\n");
				break;
			case LISTAR_CASAS:
				juego_casas_descendente(westeros);
				break;
			case MOSTRAR_CASAS_EXTINTAS:
				juego_casas_extintas(westeros);
				break;
			case FINALIZAR_SIMULACION:
				juego_destruir(westeros);
				break;
			default:
				printf("\033[1;31mLa letra que ha ingresado es erronea,por favor intente nuevamente: \033[0;0m\n");
				break;
		}
	}while(letra_ingresada != FINALIZAR_SIMULACION);

	return 0;
}
