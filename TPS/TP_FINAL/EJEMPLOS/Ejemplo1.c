#include <stdlib.h>
#include <stdio.h>

#include "abb.h"          // <---------------------------------------------- Debe agregar la libreria para poder usar el iterador

//CONSTANTES
#define OK 0
#define ERROR -1


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

	printf("\n\033[01;33mEJEMPLO 1: INICIALIZACION\033[0;0m\n");

	//•PASO 1: Crear el arbol
 	//-------Primero debemos tener un arbol creado sobre el cual iterar-----//
	abb_t* arbol = arbol_crear(comparador, NULL);                                        
	if(arbol == NULL)                          										   
		return ERROR;	
															  

	int elementos[12] = {3,2,4,0,1,20,60,30,29,40,9,5};												      
  	int tope_elementos = 12;


  	for (int i = 0; i < tope_elementos;i++)
    	arbol_insertar(arbol,&elementos[i]);
	
	//==============================================IMPORTANTE=============================================//
	//Si utiliza las funciones del arbol "arbol_insertar" o "arbol_borrar" el arbol dejara de ser el mismo,//
	//por ende el iterador creado no sera valido. Necesitara crear uno nuevo para el nuevo arbol.          //
    //=====================================================================================================//

	
	//•PASO 2: Crear el iterador
 	//-------Luego creamos el iterador,debe pasarle el arbol en cuestion y el tipo de recorrido que quiere utilizarr-----//


    printf("Creamos el iterador de un arbol NULL: ");
	abb_iterador_t* iterador = abb_iterador_crear(NULL,ABB_RECORRER_INORDEN);        //Puede ser que no haya creado el arbol pero aun asi creo el iterador     
																						                     

	if(iterador == NULL)													         
		printf("\033[1;31mNo se puede crear.\033[0;0m\n");                           // En caso de no poder crear el iterador, este sera NULL
                                                              

   	printf("Creamos el iterador de un arbol: ");
	iterador = abb_iterador_crear(arbol,ABB_RECORRER_INORDEN);        
																						                     

	if(iterador == NULL){													         //
		printf("\033[1;31mTuvimos problemas al crear el iterador.\033[0;0m\n");      // En caso no poder crear el iterador, este sera NULL
		return ERROR;                                                               //
	}
	else printf("\033[1;32mOK\033[0;0m\n\n");

	                    //(Nota si el recorrido no es el correcto el iterador no se creara)//


	//•PASO 3: Utilizar el iterador
 	//-------Una vez creado el iterador podremos usar las funciones del mismo, veamos:-----//


	mostrar_arbol();

 	
	int elemento_actual = *(int*)abb_iterador_actual(iterador);  				  //Nos devuelve el elemento actual del iterador,0 en este caso
	printf("El elemento actual del iterador es: %i\n",elemento_actual);

	bool hay_siguiente = abb_iterador_tiene_siguiente(iterador);                  //Nos indica si existe un proximo elemento en el recorrido actual,1 en este caso
	printf("El iterador %s tiene siguiente.\n\n", hay_siguiente ? "si" : "no");

	printf("~Avanzamos...\n");
	abb_iterador_siguiente(iterador);                                             //Mueve el iterador al proximo elemento en el recorrido actual,1 en este caso

	elemento_actual = *(int*)abb_iterador_actual(iterador);
	printf("El elemento actual del iterador es: %i\n\n",elemento_actual);

	printf("~Avanzamos 3 elementos...\n");
	abb_iterador_siguiente(iterador);
	abb_iterador_siguiente(iterador);
	abb_iterador_siguiente(iterador);

	elemento_actual = *(int*)abb_iterador_actual(iterador);
	printf("El elemento actual del iterador es: %i\n",elemento_actual);

	hay_siguiente = abb_iterador_tiene_siguiente(iterador);                 
	printf("El iterador %s tiene siguiente.\n\n", hay_siguiente ? "si" : "no");

	printf("~Avanzamos hasta el final...\n");
	while( abb_iterador_tiene_siguiente(iterador))
		abb_iterador_siguiente(iterador);

	hay_siguiente = abb_iterador_tiene_siguiente(iterador);                 
	printf("El iterador %s tiene siguiente.\n\n", hay_siguiente ? "si" : "no");


	//•PASO 4: Destruit el iterador
 	//-------Cuando termine de usar el iterador recuerde destruirlo:-----//


	printf("Destruimos el iterador\n\n");
	abb_iterador_destruir(iterador);         
	arbol_destruir(arbol);

	return OK;
}
