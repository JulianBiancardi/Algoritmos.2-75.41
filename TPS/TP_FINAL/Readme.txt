
				//==========================================¡¡¡IMPORTANTE!!!============================================//
                                //Para ver las funciones que podra usar del iterador externo, solo vaya a la ultima seccion de “abb.h”. //
			        //Si quiere ver la implementacion de las mismas solo vaya a la ultima seccion de “abb.c” (linea 364)    //
				//======================================================================================================//

/*------------------------------------------------------------------------------ITERADOR EXTERNO ABB------------------------------------------------------------------------------------------------------*/

	El objetivo del siguiente trabajo consiste en la implementación de un iterador externo para un arbol del tipo binario de busqueda. Para esto se tienen ciertas funciones primitivas propias del iterador, las cuales se les brindaran al usuario garantizando el correcto funcionamiento de cada una de ellas.

	Se entregaran 6 archivos y el enunciado: 	
		•“abb.h” y “abb.c”            (librerías del tda arbol que contendran al iterador externo)
		•“pila.h” y “pila.c”          (librerías del tda arbol que contendran al iterador externo)
		•“Ejmplo1.c” y “Ejmplo2.c”    (ejemplos del funcionamiento del iterador externo)

	Las funciones primitivas del iterador externo que serán provistas son las siguientes:
		•abb_iterador_t* abb_iterador_crear(abb_t* arbol, int recorrido);
			creara el iterador vinculado al arbol ingresado.Las secuencias posibles son ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN y ABB_RECORRER_POSTORDEN.

		•void* abb_iterador_actual(abb_iterador_t* iterador);
			devuelve el elemento actual del iterador o NULL en caso de error

		•bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador);
			determina si hay mas elementos sobre los cuales iterar

		•void abb_iterador_siguiente(abb_iterador_t* iterador);
			movera el iterador al siguiente elemento del arbol segun el recorrido

		•void abb_iterador_inicio(abb_iterador_t* iterador);
			movera el iterador al inicio del recorrido

		•void abb_iterador_destruir(abb_iterador_t* iterador);
			destruye el iterador

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------IMPLEMENTACION-------------------------------------------------------------------------------------------------------*/

	En este apartado veremos un poco de la implementacion, y explicaremos porque se ha elejido cada cosa:


	•Struct del iterador:

				struct abb_iterador{
					abb_t* arbol                  -------> Arbol del cual iterar
					pila_t* pila;                 -------> Pila  auxiliar encargada de guardar los nodos faltantes por visitar del arbol
					int recorrido;                -------> Recorrido a usar: 0(INORDEN) 1(PREORDEN) 2(POSTORDEN)
				};

	En todos los recorridos, el elemento tope de la pila es aquel elemento que sigue por ser visitado.Es decir entonces,la pila funciona como un stack de los elementos proximos a ser visitados.(No se 		apilan todos y luego se recorre, como indica el enunciado)
	En este trabajo se opto por usar una pila ya que abarca a los tres tipos de recorridos posibles.

		-INORDEN: Para este recorrido lo que haremos inicialmente es apilar hasta econtrar un nodo que no tenga rama izquierda.Este sera el nodo minimo y por ende el primer nodo del recorrido
			  Si queremos avanzar desapilamos el nodo tope y nos fijamos si tiene hijo derecho.Si no tiene no hacer nada(nodo hoja).Si tiene debemos realizar el mismo procedimiento que el 		          inicio,es decir,buscar el minimo pero ahora de la rama derecha del nodo en cuestion.Continuar hasta finalizar el recorrido.

		-PREORDEN:Apilamos el nodo, en este caso la raiz. Si queremos avanzar desapilamos el nodo y apilamos sus hijos, primero el derecho y luego el izquierdo para que este ultimo sea el proximo 				  del recorrido.Continuar repitiendo el proceso (borrar nodo y agregar sus hijos) hasta finalizar el recorrido
		
		-POSTORDEN:Para este recorrido lo que haremos inicialmente es apilar buscando el minimo nodo hoja del arbol.Este sera el primer nodo del recorrido.Si queremos avanzar desapilamos el 			           elemento tope y lo guardamos en una variable auxiliar.Se presentan 3 casos:
					--Si el nuevo elemento tope tiene hijo derecho y es distinto a la variable auxiliar,apilamos buscando un nuevo minimo nodo hoja.
					--Si el nuevo elemento tope tiene hijo derecho y es igual a la variable auxiliar,no hacer nada.
					--Si el nuevo elemento tope es NULL, el recorrido ha finalizado.	
	
	Vemos asi que la iteracion se realiza sobre el arbol,al contrario de apilar todos los elementos y luego realizar la iteracion sobre la pila.

	•Cambiar recorrido:
	
	Si se quiere cambiar de recorrido tenemos 2 opciones:
		-Eliminar el iterador y crear uno nuevo con el nuevo recorrido.Esto le ahorraria memoria pero perderia la informacion del iterador anterior si desaria utilizarla.
		-Crear un nuevo iterador con el nuevo recorrido.Esto ocupa mas espacio en memoria pero puede utilizar mas de 1 recorrido a la vez.

	•Elemento actual:
	
	Cuando cree el iterador el elemento actual sera siempre el primer elemento del recorrido en cuestion (por ejemplo: en preorden el primer elemento siempre es la raiz del arbol).
	Si el recorrido ha finalizado, no hay mas elementos por recorrer y la funcion "abb_iterador_actual" devolvera NULL. Es por esto que cuando usted desea obtener el elemento que devuelve la funcion
	se produce un error devido a que esta desreferenciando un puntero NULL.

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------EJEMPLOS-------------------------------------------------------------------------------------------------------*/

	Se le entrega dos archivos .c(codigo) a modo de ejemplo.

		•Ejemplo 1:Se muestra como debe crearse, utilizarse y destruirse el iterador.Muestra los diferentes casos en la creacion de creacion del iterador, asi tambien los errores que puede haber
			   y un uso basico de las funciones.

		•Ejemplo 2:Se muestra los recorridos posibles.Muestra como utilizar las funciones basicas para realizar los tres diferentes tipos de recorridos de un arbol.

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------COMPILACIÓN Y EJECUCIÓN-------------------------------------------------------------------------------------------------*/

	Para poder compilar y ejecutar el programa deberá acceder a la consola. Una vez en la consola,mediante los comandos “ls” y “cd” deberá acceder a la carpeta contenedora de los archivos provistos mencionados anteriormente. Una vez en accedido a ella , ya podrá ingresar los siguientes comandos (aquellos que aparezcan con "$" seran comandos,quite el caracter inicial si desea usarlo):

	•Compilación:
		Coloque el archivo ejemplo (o el codigo que haya implementado) junto con los otros archivos provistos y luego introduzca el siguiente codigo

				$ gcc *.c -o abb_iterador -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

	(Nota: es necesario que tenga tanto “abb.c” “abb.h” “pila.c” y “pila.h” en la misma carpeta)

	•Ejecución:
				$ ./abb_iterador

	(Nota: esta linea de comando no mostrara errores o fallas como la que se muestra a continuacion)

				$ valgrind --tool=memcheck --leak-check=yes ./abb_iterador

	(Nota: es necesario tener previamente instalado valgrind)

					(Este trabajo no cuenta con makefile)

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



