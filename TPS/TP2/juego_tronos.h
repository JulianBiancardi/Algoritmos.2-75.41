#ifndef __JUEGO_DE_TRONOS_H__
#define __JUEGO_DE_TRONOS_H__

#include <stdio.h>
#include "abb.h"
#include "lista.h"


typedef struct juego juego_t;


/*
 * Crea el juego reservando la memoria necesaria.
 * Devuelve un puntero al juego creado o NULL en caso de error.
 */
juego_t* juego_crear();

/*
 * Agrega casas al juego,nombre_archivo sera el archivo donde se leera
 * las casas a cargar.
 * Si la casa no existe se agrega y se suman las personas a la casa,en caso de que la casa ya exista,
 * solo se sumaran las nuevas personas a la casas.
 * El formato del archivo debe ser el siguiente: 
 * C;nombre_casa;factor_envejecimiento;factor_nacimiento; para la casa    (si el formato no comple la linea no se cuenta y sigue leyendo)
 * I;nombre_persona;edad                                  para la persona (si el formato no cumple la linea no se cuenta y sigue leyendo)
 * Devuelve 0 si tuvo exito o -1 en caso de error.
 */
int juego_agregar_casa(juego_t* juego,const char* nombre_archivo);

/*
 * Simula cantidad_anios el juego y una vez finalizado informa la casa dominante.
 * La cantidad de años no puede ser menor que 0, por ende devolvera -1(error)
 * Devuelve 0 si tuvo exito o -1 en caso de error.
 */
int juego_simulacion(juego_t* juego,int cantidad_anios);

/*
 * Lista la casas por cantidad de personas en orden descendente.
 * Devuelve 0 si tuvo exito o -1 en caso de error.
 */
int juego_casas_descendente(juego_t* juego);

/*
 * Lista la casas en el mismo orden en el que fueron desapareciendo del juego.
 * Devuelve 0 si tuvo exito o -1 en caso de error.
 */
int juego_casas_extintas(juego_t* juego);

/*
 * Muestra el menu del juego.
 */
void juego_mostrar_menu();

/*
 * Destruye el juego liberando la memoria reservada por el mismo.
 */
void juego_destruir(juego_t* juego);


#endif /* __ARBOL_BINARIO_DE_BUSQUEDA_H__ */