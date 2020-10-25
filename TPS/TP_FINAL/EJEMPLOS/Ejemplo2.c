#include <stdlib.h>
#include <stdio.h>

#include "abb.h"          // <---------------------------------------------- Debe agregar la libreria para poder usar el iterador

//CONSTANTES
#define OK 0
#define ERROR -1

#define RECORRIDO_INVALIDO -1


int comparador(void* elemento1, void* elemento2){
  if(!elemento1 || !elemento2)
    return 0;

  if((*(int*)elemento1) > (*(int*)elemento2))  
    return 1;
  if((*(int*)elemento1) < (*(int*)elemento2))      
    return -1;

  return 0;
}

void mostrar_arbol(){
	printf("Tenemos el siguiente arbol binario creado con los siguientes diez elementos: \033[01;33m0 1 2 3 4 5 9 20 29 30 40 60\033[0;0m insertados de la siguiente manera:\n\n");

	printf("                  3   \n");
	printf("                 / \\  \n");
	printf("                2   4   \n");
	printf("               /     \\  \n");
	printf("              0      20   \n");
	printf("               \\   /  \\  \n");
	printf("                1  9   60   \n");
	printf("                  /    /      \n");
	printf("                 5    30       \n");
	printf("                     / \\       \n");
	printf("                    29 40       \n\n");
}

int main(){

	printf("\n\033[01;33mEJEMPLO 2: RECORRIDOS\033[0;0m\n");

	//•PASO 1: Crear el arbol
 	//-------Primero debemos tener un arbol creado sobre el cual iterar-----//
	abb_t* arbol = arbol_crear(comparador, NULL);                                        
	if(arbol == NULL)                          										   
		return ERROR;	
															  

	int elementos[12] = {3,2,4,0,1,20,60,30,29,40,9,5};												      
  	int tope_elementos = 12;


  	for (int i = 0; i < tope_elementos;i++)
    	arbol_insertar(arbol,&elementos[i]);
	

	//•PASO 2: Crear el iterador
 	//-------Luego creamos el iterador,debe pasarle el arbol en cuestion y el tipo de recorrido que quiere utilizarr-----//


    printf("Creamos el iterador de un arbol con recorrido invalido: ");
	abb_iterador_t* iterador_inorden = abb_iterador_crear(arbol,RECORRIDO_INVALIDO);  //Si el recorrido es invalido, el iterado no se creara     
																						                     

	if(iterador_inorden == NULL)													         
		printf("\033[1;31mNo se puede crear.\033[0;0m\n");                            // En caso no poder crear el iterador, este sera NULL
                                                              
	printf("Creamos el iterador de un arbol con recorrido inorden: ");
	iterador_inorden = abb_iterador_crear(arbol,ABB_RECORRER_INORDEN);

	if(iterador_inorden == NULL){													  //
		printf("\033[1;31mTuvimos problemas al crear el iterador.\033[0;0m\n");      // En caso no poder crear el iterador, este sera NULL
		return ERROR;                                                               //
	}
	else printf("\033[1;32mOK\033[0;0m\n");

   	printf("Creamos el iterador de un arbol con recorrido preorden: ");
	abb_iterador_t* iterador_preorden = abb_iterador_crear(arbol,ABB_RECORRER_PREORDEN);        
																						                     
	if(iterador_preorden == NULL){													  //
		printf("\033[1;31mTuvimos problemas al crear el iterador.\033[0;0m\n");      // En caso no poder crear el iterador, este sera NULL
		return ERROR;                                                               //
	}
	else printf("\033[1;32mOK\033[0;0m\n");

	printf("Creamos el iterador de un arbol con recorrido postorden: ");
	abb_iterador_t* iterador_postorden = abb_iterador_crear(arbol,ABB_RECORRER_POSTORDEN);

	if(iterador_postorden == NULL){													 //
		printf("\033[1;31mTuvimos problemas al crear el iterador.\033[0;0m\n");      // En caso no poder crear el iterador, este sera NULL
		return ERROR;                                                               //
	}
	else printf("\033[1;32mOK\033[0;0m\n\n");

	//(Nota:Si desea cambiar de reorrido simplemente puede destruir el iterador y crear uno nuevo con el nuevo recorrido.Esto le ahorrara memoria)//


	//•PASO 3: Utilizar el iterador
 	//-------Una vez creado el iterador podremos usar las funciones del mismo, veamos:-----//

	mostrar_arbol();


	//Completando el recorrido hasta que no queden mas elementos en forma inorden
	printf("Los elementos del arbol en recorrido inorden:");
	while(abb_iterador_tiene_siguiente(iterador_inorden)){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_inorden);
		printf("%i ",elemento_actual);
		abb_iterador_siguiente(iterador_inorden); 
	}
	printf("\n");

	//Completando el recorrido hasta que no queden mas elementos en forma preorden
	printf("Los elementos del arbol en recorrido preorden:");
	while(abb_iterador_tiene_siguiente(iterador_preorden)){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_preorden);
		printf("%i ",elemento_actual);
		abb_iterador_siguiente(iterador_preorden); 
	}
	printf("\n");

	//Completando el recorrido hasta que no queden mas elementos en forma postorden
	printf("Los elementos del arbol en recorrido postorden:");
	while(abb_iterador_tiene_siguiente(iterador_postorden)){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_postorden);
		printf("%i ",elemento_actual);
		abb_iterador_siguiente(iterador_postorden); 
	}
	printf("\n\n");

	//•PASO 5: Reiniciar el iterador
	//-------Si usted lo desea puede reiniciar el iterador a la posicion inicial del recorrido que fue creado:-----//

	printf("~Reiniciamos los iteradores a las posiciones iniciales...\n\n");
	abb_iterador_inicio(iterador_inorden);
	abb_iterador_inicio(iterador_preorden);
	abb_iterador_inicio(iterador_postorden);

	bool termino = false;
	//Completando el recorrido hasta encontrar un elemento en especifico en forma inorden
	printf("Los elementos del arbol hasta la raiz en recorrido inorden:");
	while(abb_iterador_tiene_siguiente(iterador_inorden) && !termino){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_inorden);
		printf("%i ",elemento_actual);
		if(elemento_actual == 3){
			termino = true;
		}
		else
			abb_iterador_siguiente(iterador_inorden);	 
	}

	termino = false;
	//Completando el recorrido hasta encontrar un elemento en especifico en forma preorden
	printf("\nLos elementos del arbol hasta la raiz recorrido preorden:");
	while(abb_iterador_tiene_siguiente(iterador_preorden) && !termino){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_preorden);
		printf("%i ",elemento_actual);
		if(elemento_actual == 3){
			termino = true;
		}
		else
			abb_iterador_siguiente(iterador_preorden); 
	}

	termino = false;
	//Completando el recorrido hasta encontrar un elemento en especifico en forma postorden
	printf("\nLos elementos del arbol hasta la raiz recorrido postorden:");
	while(abb_iterador_tiene_siguiente(iterador_postorden) && !termino){
		int elemento_actual = *(int*)abb_iterador_actual(iterador_postorden);
		printf("%i ",elemento_actual);
		if(elemento_actual == 3){
			termino = true;
		}
		else
			abb_iterador_siguiente(iterador_postorden);
	}

	//•PASO 6: Destruit el iterador
 	//-------Cuando termine de usar el iterador recuerde destruirlo:-----//

	printf("\n\nDestruimos los iterador\n\n");
	abb_iterador_destruir(iterador_inorden); 
	abb_iterador_destruir(iterador_preorden);  
	abb_iterador_destruir(iterador_postorden);  

	arbol_destruir(arbol);

	return OK;
}

