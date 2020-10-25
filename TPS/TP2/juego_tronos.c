#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "abb.h"
#include "lista.h"
#include "cola.h"
#include "juego_tronos.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define ESPERANZA_VIDA 60

#define LECTURA "r"
#define EXTENSION_TEXTO ".txt"
#define CASA 'C'
#define MAX_NOMBRE_CASA 500
#define PERSONA 'I'
#define MAX_NOMBRE_PERSONA 300
#define MAX_LECTURA 800
#define FORMATO_LECTURA_CASA "C;%[^;];%i;%i\n"
#define FORMATO_LECTURA_INTEGRANTE "I;%[^;];%i\n"
#define ARCHIVO_NOMBRES_PERSONAS "nombres_personas.txt"

/*---------------------------------------*/

typedef struct persona{
	char nombre[MAX_NOMBRE_PERSONA];
	int edad;
}persona_t;
typedef struct casa{
	char nombre_casa[MAX_NOMBRE_CASA];
	int factor_envejecimiento;
	int factor_nacimiento; 
	lista_t* familia;
}casa_t;
struct juego{
	abb_t* arbol_juego;
	size_t cantidad_casas;
	cola_t* casas_extintas;
	cola_t* casas_extintas_auxiliar;
	FILE* archivo_nombres_personas;
};

/*	Postcondion: La funcion recorre la cola e invoca la funcion con cada elemento del mismo. 
				El puntero 'extra' se pasa como segundo parámetro a la función. Si la función devuelve true,
				se finaliza el recorrido aun si quedan elementos por recorrer. Si devuelve false se sigue
				recorriendo mientras queden elementos.Devuelve un puntero a la nueva cola
*/
cola_t* cola_con_cada_elemento(cola_t* cola,void (*funcion)(void* , void*),void* extra){

	cola_t* cola_aux = cola_crear();
	while(!cola_vacia(cola)){
		casa_t* casa_actual = cola_primero(cola);

		if(funcion != NULL)
			funcion((void*)casa_actual,extra);

		cola_encolar(cola_aux,casa_actual);
		cola_desencolar(cola);
	}
	cola_destruir(cola);
	return cola_aux;
}


/*
	Precondicion: Recibe un nombre de la persona a crear(la cantidad de caracteres no puede exeder MAX_NOMBRE_PERSONA)
				y una edad para la misma(esta edad no puede ser negativa es decir edad >= 0).
	Postcondion: La funcion creara la estructura "persona" reservando el espacio de memoria necesaria en el Heap.
				Devolvera un puntero a esa estructura(con sus datos inicializados correctamente),devolvera NULL en 
				caso de que algunas de las caracteristicas de la persona antes mencionada sea incorrecta.
*/
persona_t* persona_crear(char* nombre,int edad){
	if(edad < 0)
		return NULL;

	persona_t* persona = (persona_t*)malloc(sizeof(persona_t));
	if(persona == NULL)
		return NULL;

	strcpy((*persona).nombre,nombre);
	
	(*persona).edad = edad;
	return persona;
}
/*
	Precondicion: Recibe un nombre de la persona a crear(la cantidad de caracteres no puede exeder MAX_NOMBRE_PERSONA)
				y una edad para la misma(esta edad no puede ser negativa es decir edad >= 0).
	Postcondion: La funcion agregara la persona a la familia dada.Devolvera OK(0) si pudo agregarla, o ERROR(-1) en caso contrario 
*/
int persona_agregar(lista_t* familia, char* nombre,int edad){
	if(familia == NULL)
		return ERROR;

	persona_t* nueva_persona = persona_crear(nombre,edad);
	if(nueva_persona == NULL)
		return ERROR;

	return lista_insertar(familia,nueva_persona);
}
/*
	Precondicion: Recibe un puntero a la estructura "persona"
	Postcondion: La funcion destruira la estructura de la persona apuntada por el puntero,liberando la memoria reservada por esta.
*/
void persona_destruir(persona_t* persona){
	if(persona != NULL){
		free(persona);
	}
}



/*
	Precondicion: Recibe un nombre de la casa a crear(la cantidad de caracteres no puede exeder MAX_NOMBRE_CASA)
				un factor_envejecimiento y un factor_nacimiento (ambos factores deben ser mayor o igual a 0)
	Postcondion: La funcion creara la estructura "casa" reservando el espacio de memoria necesaria en el Heap.
				Devolvera un puntero a esa estructura(con sus datos inicializados correctamente),devolvera NULL en 
				caso de que algunas de las caracteristicas de la casa antes mencionada sea incorrecta.
*/
casa_t* casa_crear(char* nombre,int factor_envejecimiento,int factor_nacimiento){
	if(factor_envejecimiento < 0 || factor_nacimiento < 0)
		return NULL;

	casa_t* casa = (casa_t*)malloc(sizeof(casa_t));
	if(casa == NULL)
		return NULL;

	strcpy((*casa).nombre_casa,nombre);
	(*casa).factor_envejecimiento = factor_envejecimiento;
	(*casa).factor_nacimiento = factor_nacimiento;
	(*casa).familia = lista_crear();
	return casa;
}
/*
	Precondicion: Recibe un puntero a la estructura "casa" y un puntero a la estructura "juego"
	Postcondion: La funcion borrara la casa del arbol del juego si tuvo exito.
*/
void casa_borrar(void* casa, void* juego){
	if(casa == NULL || juego == NULL)
		return;

	if(arbol_borrar((*(juego_t*)juego).arbol_juego,(casa_t*)casa) == OK){
		printf("\033[1;31m¡La casa %s ha sido eliminada!\033[0;0m\n",(*(casa_t*)casa).nombre_casa);
		((*(juego_t*)juego).cantidad_casas)--;
	}
}
/*
	Precondicion: Recibe un puntero a la estructura "casa"
	Postcondion: La funcion actualizara la casa, para esto a cada persona que integra la casa se le sumara la edad 
				de acorde a la siguiente formula:  "nueva edad = edad actual + factor_envejecimiento". A su vez si
				una persona supera la esperanza de vida (60 años) se la eliminara de la casa.Devolvera OK(0) si tuvo 
				exito o ERRO(-1) en caso de error.
*/
int casa_actualizar(casa_t* casa){
	if(casa == NULL)
    	return ERROR;

    printf("%s;%i,%i\n",(*casa).nombre_casa,(*casa).factor_envejecimiento,(*casa).factor_nacimiento);
    lista_t* familia = (*(casa_t*)casa).familia;
    lista_t* familia_auxiliar = lista_crear();
    if(familia_auxiliar == NULL)
    	return ERROR;

    lista_iterador_t* iterador = lista_iterador_crear(familia);
    if(iterador == NULL)
    	return ERROR;

    while(lista_iterador_tiene_siguiente(iterador)){
    	persona_t* persona_actual = (persona_t*)lista_iterador_siguiente(iterador);

    	if((*(casa_t*)casa).factor_envejecimiento >= 0)
    		(*persona_actual).edad += (*(casa_t*)casa).factor_envejecimiento;
    	printf("--- %s;%i\n",(*persona_actual).nombre,(*persona_actual).edad);
    	if((*persona_actual).edad >= ESPERANZA_VIDA){
    		printf("PERSONA DESTRUIDA: %s;%i\n",(*persona_actual).nombre,(*persona_actual).edad);
    		persona_destruir(persona_actual);
    	}
    	else
    		lista_insertar(familia_auxiliar,persona_actual);

    }
   	lista_iterador_destruir(iterador);

   	lista_destruir(familia);
   	(*casa).familia = familia_auxiliar;

	return OK;
}
/*
	Precondicion: Recibe un puntero a la estructura "casa",extra sera el contenido agregado que se podra mostrar
				(si es NULL solo mostrara el nombre de la casa)
	Postcondion: La funcion mostrara el nombre de la casa si esta no es NULL concatenado a extra.		
*/
void casa_mostrar(void* casa, void* extra){
	if(casa == NULL)
		return;

	printf("%s%s",(*(casa_t*)casa).nombre_casa,(char*)extra);
}
/*
	Precondicion: Recibe un puntero a la estructura "casa"
	Postcondion: La funcion destruira la estructura de la casa apuntada por el puntero,liberando la memoria reservada por esta.		
*/
void casa_destruir(casa_t* casa){
	if(casa != NULL){
		if((*casa).familia != NULL){
			lista_iterador_t* iterador = lista_iterador_crear((*casa).familia);
			while(lista_iterador_tiene_siguiente(iterador)){
				persona_t* persona_actual = (persona_t*)lista_iterador_siguiente(iterador);
				persona_destruir(persona_actual);
			}
			lista_iterador_destruir(iterador);
			lista_destruir((*casa).familia);
		}
		free(casa);
	}
}


/*
   Comparador de elementos del juego. Recibe dos elementos del arbol del juego y devuelve
   0 en caso de ser iguales, 1 si el primer elemento es mayor al segundo o -1 si el primer 
   elemento es menor al segundo. La claves para la comparacion son los nombres de las casas.
*/
int comparador(void* elemento1, void*elemento2){
    if(!elemento1 || !elemento2)
    	return 0;
	
	char* casa1 = (*(casa_t*)elemento1).nombre_casa;
	char* casa2 = (*(casa_t*)elemento2).nombre_casa;

	if(strcmp(casa1,casa2) < 0)
    	return 1;
  	if(strcmp(casa1,casa2) > 0)      
    	return -1;

  	return 0;
}
/*
	Destructor de elementos del juego. Cada vez que una casa deja el juego
	se invoca al destructor pasandole la casa a destuir.
*/
void destructor(void* elemento){

	casa_destruir((casa_t*)elemento);
}
/*
	Postcondion: La funcion creara la estructura "juego" reservando el espacio de memoria necesaria en el Heap.
				Devolvera un puntero a esa estructura(con sus datos inicializados correctamente),devolvera NULL 
				en caso contrario.
*/
juego_t* juego_crear(){

	juego_t* juego = (juego_t*)malloc(sizeof(juego_t));
	if(juego == NULL)
		return NULL;

	(*juego).arbol_juego = arbol_crear(comparador,destructor);
	if((*juego).arbol_juego == NULL){
		free(juego);
		return NULL;
	}

	(*juego).cantidad_casas = 0;

	(*juego).casas_extintas = cola_crear();
	if((*juego).casas_extintas == NULL){
		arbol_destruir((*juego).arbol_juego);
		free(juego);
		return NULL;
	}

	(*juego).casas_extintas_auxiliar = cola_crear();
	if((*juego).casas_extintas == NULL){
		cola_destruir((*juego).casas_extintas);
		arbol_destruir((*juego).arbol_juego);
		free(juego);
		return NULL;
	}

	(*juego).archivo_nombres_personas = fopen(ARCHIVO_NOMBRES_PERSONAS,LECTURA);
	if((*juego).archivo_nombres_personas == NULL){
		cola_destruir((*juego).casas_extintas);
		cola_destruir((*juego).casas_extintas_auxiliar);
		arbol_destruir((*juego).arbol_juego);
		free(juego);
	}

	return juego;
}

/*
	Precondicion: Recibe un puntero a un archivo y un string donde almacenar la linea leida.
	Postcondion: La funcion leera una linea del archivo.Devolvera es lina leida si pudo o 
				devolvera NULL si EOF es encontrado o se produce un error con el archivo.
*/
char* leer_linea(FILE* archivo, char* linea_leida){
  
  linea_leida = fgets(linea_leida,MAX_LECTURA, archivo); 

  if(linea_leida != NULL)
  	linea_leida[strlen(linea_leida) - 1] = '\0';//Sacamos el \n

  return linea_leida;
}
/*
	Precondicion: Recibe un puntero a la estructura "juego" y un nombre de archivo
	Postcondion: La funcion agregara casas al juego.Las casas estaran contenidas en el archivo
				Si la casa no existe se agrega y se suman las personas a la casa,en caso de que la casa ya exista,
				solo se sumaran las nuevas personas a la casas.Devuelve OK(0) si tuvo exito o ERRO(-1) en caso de error.
*/
int juego_agregar_casa(juego_t* juego,const char* nombre_archivo){
	if(juego == NULL)
		return ERROR;

	strcat((char*)nombre_archivo,EXTENSION_TEXTO);
	FILE* archivo_casas = fopen(nombre_archivo,LECTURA); 
	if(archivo_casas == NULL){
		printf("\033[1;31m-EL archivo ( %s ) no se ha encontrado o tuvo problemas para abrirse.\033[0;0m\n",nombre_archivo);
		return ERROR;
	}

	int campos_leidos = 0;
	casa_t casa_actual; 
	persona_t persona_actual;
	char linea_leida[MAX_LECTURA];

	casa_actual.familia = NULL;

	while(leer_linea(archivo_casas,linea_leida) != NULL){
	
		if(linea_leida[0] == CASA){
			campos_leidos = sscanf(linea_leida,FORMATO_LECTURA_CASA,casa_actual.nombre_casa,&casa_actual.factor_envejecimiento,&casa_actual.factor_nacimiento);
			if(campos_leidos == 3){

				casa_t* casa_encontrada = (casa_t*)arbol_buscar((*juego).arbol_juego,casa_actual.nombre_casa);
				if(casa_encontrada == NULL){

					casa_t* nueva_casa = casa_crear(casa_actual.nombre_casa,casa_actual.factor_envejecimiento,casa_actual.factor_nacimiento);
					if(nueva_casa == NULL)
						return ERROR;

					arbol_insertar((*juego).arbol_juego,nueva_casa);
					((*juego).cantidad_casas)++;
					casa_actual.familia = (*nueva_casa).familia;
			}
			else
				casa_actual.familia = (*casa_encontrada).familia;
			}	
		}
		else if(linea_leida[0] == PERSONA  && casa_actual.familia != NULL){
			campos_leidos = sscanf(linea_leida,FORMATO_LECTURA_INTEGRANTE,persona_actual.nombre,&(persona_actual.edad));
			if(campos_leidos == 2)
				persona_agregar(casa_actual.familia,persona_actual.nombre,persona_actual.edad);
		}
	}

	fclose(archivo_casas);
	return OK;
}

/*
	Precondicion: Recibe un puntero a la estructura "juego" y un string donde guardar (ambos no deben ser NULL)
	Postcondion: La funcion leera del archivo de nombres de personas (incorporado del juego) y lo guardara en el
				string nombre.Si EOF es encontrado se volvera a leer del inicio.
*/
void nuevo_nombre(juego_t* juego,char* nombre){
	if(juego == NULL || nombre == NULL)
		return;

	if(leer_linea((*(juego_t*)juego).archivo_nombres_personas,nombre) == NULL){
		fclose((*(juego_t*)juego).archivo_nombres_personas);
		(*(juego_t*)juego).archivo_nombres_personas = fopen(ARCHIVO_NOMBRES_PERSONAS,LECTURA);
		leer_linea((*(juego_t*)juego).archivo_nombres_personas,nombre);
	}
}
/*
	Postcondion: Por cada elemento del arbol del juego, la funcion actualiza la casa, si esta esta vacia se elimina del juego, sino
				se agregar las nuevas personas por nacimiento a la casa mediante la formula: "cantidad a nacer = cantidad personas / factor_nacimiento"
				Devolvera OK(0) si pudo o devolvera ERROR(-1) en caso contrario.
*/
bool abb_juego_simulacion(void* casa, void* juego){
	if(casa == NULL || juego == NULL)
    	return true;

    casa_actualizar((casa_t*)casa);
	

 	if((*(casa_t*)casa).factor_nacimiento != 0){
		int cantidad_personas = (int)lista_elementos((*(casa_t*)casa).familia);
		int cantidad_a_nacer = cantidad_personas / (*(casa_t*)casa).factor_nacimiento; 
		printf("cantidad de personas a agegar: %i (%i/%i)",cantidad_a_nacer,cantidad_personas,(*(casa_t*)casa).factor_nacimiento);
		for(int i = 0;i < cantidad_a_nacer;i++){

			char nombre[MAX_NOMBRE_PERSONA];
			nuevo_nombre((juego_t*)juego,nombre);
			persona_agregar((*(casa_t*)casa).familia,nombre,0);
		}
		printf("--- nuevo tamaño :%i\n", (int)lista_elementos((*(casa_t*)casa).familia));
	}
	return false;
}


/*
	Postcondion: La funcion determinara si la casa es extinta o no.
				Una casa se considera extinta si la misma esta vacia. 
*/
bool es_casa_extinta(void* casa, void*juego){
	if(casa == NULL || juego == NULL)
    	return true;

    if(lista_vacia((*(casa_t*)casa).familia)){
		casa_t* casa_copia = casa_crear((*(casa_t*)casa).nombre_casa,(*(casa_t*)casa).factor_envejecimiento,(*(casa_t*)casa).factor_nacimiento);
		if(casa_copia == NULL)
			return true;

		cola_encolar((*(juego_t*)juego).casas_extintas_auxiliar,casa_copia);
	}
	return false;
}
/*
	Postcondion: La funcion determinara las nuevas casas extintas en la simulacion actual,
				luego borrara dichas casas del arbol del juego y por ultimo agregara las casas
				extintas a las casas extintas generales del juego.
*/
void juego_nueva_casas_extintas(juego_t* juego){
	abb_con_cada_elemento((*juego).arbol_juego,ABB_RECORRER_INORDEN,es_casa_extinta,juego);
	(*juego).casas_extintas_auxiliar = cola_con_cada_elemento((*juego).casas_extintas_auxiliar,casa_borrar,juego);

	while(!cola_vacia((*juego).casas_extintas_auxiliar)){
		casa_t* casa_actual = cola_primero((*juego).casas_extintas_auxiliar);

		cola_encolar((*juego).casas_extintas,casa_actual);
		cola_desencolar((*juego).casas_extintas_auxiliar);
	}
}
/*
	Precondicion: Recibe un puntero a la estructura "juego"
	Postcondion: La funcion lista la casas en el mismo orden en el que fueron desapareciendo del juego.
				Devolvera OK(0) si pudo o devolvera ERROR(-1) en caso contrario.
*/
int juego_casas_extintas(juego_t* juego){
	if(juego == NULL)
		return ERROR;

	printf("\033[1;36mCasas extintas:\033[0;0m ");
	(*juego).casas_extintas = cola_con_cada_elemento((*juego).casas_extintas,casa_mostrar," -> ");
	printf("\n");

	return OK;
}
/*
	Postcondion: La funcion determinara si la nueva casa pasada por referencia es dominante.
				Una casa es dominante si su cantidad de personas es mayor a las demas.
*/
bool es_casa_dominante(void* casa,void* casa_dominante){
	if(casa == NULL)
    	return true;

    size_t personas_casa_dominante = lista_elementos((**(casa_t**)casa_dominante).familia);
    size_t personas_nueva_casa = lista_elementos((*(casa_t*)casa).familia);
    
    if(personas_nueva_casa > personas_casa_dominante){
    	(*(casa_t**)casa_dominante) = (casa_t*)casa;
    }
    return false;
}
/*
	Precondicion: Recibe un puntero a la estructura "juego" 
	Postcondion: La funcion determinara la nueva casa dominante y la mostrara por pantalla.
				Si el arbol del juego esta vacio la casa dominante sera nula.
*/
void juego_nueva_casa_dominante(juego_t* juego){

	casa_t** casa_dominante = (casa_t**)malloc(sizeof(casa_t*));
	if(casa_dominante == NULL)
		return;

	(*casa_dominante) = (casa_t*)arbol_raiz((*juego).arbol_juego);
	abb_con_cada_elemento((*juego).arbol_juego,ABB_RECORRER_PREORDEN,es_casa_dominante,casa_dominante);

	if(*casa_dominante != NULL){
		printf("La nueva casa que domina el TRONO DE HIERRO es: \033[1;33m");
		casa_mostrar(*casa_dominante,"");
		printf("\033[0;0m Larga vida a su reino.\n"); 
	}

	free(casa_dominante);
}
/*
	Precondicion: Recibe un puntero a la estructura "juego" y una cantidad de años(no puede ser menor que 0)
	Postcondion: La funcion simula la cantidad de años ingresada por el usuario y una vez finalizado informa la casa dominante.
				Devolvera OK(0) si pudo o devolvera ERROR(-1) en caso contrario.
*/
int juego_simulacion(juego_t* juego,int cantidad_anios){
	if(juego == NULL)
		return ERROR;

	if(cantidad_anios < 0){
		printf("\033[1;31mLa cantidad de años ingresada es incorrecta.\033[0;0m\n");
		return ERROR;
	}

	for(int i = 0;i < cantidad_anios;i++)
		abb_con_cada_elemento((*juego).arbol_juego,ABB_RECORRER_INORDEN,abb_juego_simulacion,juego);

	if(arbol_vacio((*juego).arbol_juego)){
		printf("\033[1;31mSe han muerto todas las casas...ya no quedan mas casas en el juego.\033[0;0m\n");
		return OK;
	}

	juego_nueva_casas_extintas(juego);

	juego_nueva_casa_dominante(juego);

	return OK;
}
/*
   Comparador de elementos auxiliar para listar las casas en orden descendente. Recibe dos elementos 
   devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor al segundo o -1 si el primer 
   elemento es menor al segundo. La claves para la comparacion son la cantidad de personas en cadad elemento.
*/
int comparador_aux(const void* elemento1, const void*elemento2){
    if(!elemento1 || !elemento2)
    	return 0;

	size_t casa1_personas = lista_elementos((**(casa_t**)elemento1).familia);
	size_t casa2_personas = lista_elementos((**(casa_t**)elemento2).familia);

	//Coloco el comparador invertido asi el qsort ordena de mayor a menor (descendente)
  	return (int)(casa2_personas - casa1_personas);
}
/*
	Precondicion: Recibe un puntero a la estructura "juego"
	Postcondion: La funcion lista la casas por cantidad de personas en orden descendente.
				Devolvera OK(0) si pudo o devolvera ERROR(-1) en caso contrario.
*/
int juego_casas_descendente(juego_t* juego){
	if(juego == NULL)
		return ERROR;

	printf("\033[1;36mCasas en orden descendente: \033[0;0m");

	casa_t* vector[(*juego).cantidad_casas];

	size_t cantidad_elementos = (size_t)arbol_recorrido_preorden((*juego).arbol_juego,(void**)vector,(int)(*juego).cantidad_casas);
	if(cantidad_elementos != (*juego).cantidad_casas)
		return ERROR;

	//qsort con comparador invertido asi ordena de mayor a menor (descendente)
	qsort(vector,cantidad_elementos,sizeof(casa_t*),comparador_aux);

	for(size_t i = 0;i < cantidad_elementos;i++){
		casa_t* casa_actual = vector[i];
		casa_mostrar(casa_actual," -> ");
	}
	printf("\n");
	return OK;
}
/*
	Postcondion: La funcion muestra el menu del juego.
*/
void juego_mostrar_menu(){

	printf("\n\033[0;0m");
	printf("# ==========  MENU DE OPCIONES ========== #\n");
	printf("| •S: Iniciar la simulacion.              |\n");
	printf("| •A: Agregar casa.                       |\n");
	printf("| •L: Listar casas en orden descendente.  |\n");
	printf("| •E: Listar casas extintas.              |\n");
	printf("| •Q: Salir del programa.                 |\n");
	printf("# ======================================= #\n\n");
}
/*
	Precondicion: Recibe un puntero a la estructura "juego"
	Postcondion: La funcion destruira la estructura del juego principal apuntada por el puntero,liberando la memoria reservada por esta.
*/
void juego_destruir(juego_t* juego){
	if(juego != NULL){
		arbol_destruir((*juego).arbol_juego);
		while(!cola_vacia((*juego).casas_extintas)){
			casa_t* casa_actual = (casa_t*)cola_primero((*juego).casas_extintas);
			casa_destruir(casa_actual);
			cola_desencolar((*juego).casas_extintas);
		}
		cola_destruir((*juego).casas_extintas);
		cola_destruir((*juego).casas_extintas_auxiliar);
		fclose((*juego).archivo_nombres_personas);
		free(juego);
	}
}


