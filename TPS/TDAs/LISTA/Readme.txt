/*---------------------------------------TDA LISTA---------------------------------------*/

	El objetivo del siguiente trabajo consiste en la implementación del TDA LISTA con nodos simplemente enlazados. Para esto se tienen ciertas funciones primitivas propias del TDA, las cuales se les brindaran al usuario garantizando el correcto funcionamiento de cada una de ellas. Por otra parte, se crearan TESTS sobre el TDA para  determinar la calidad especialmente antes que sea llevado al uso por el usuario.
	Se entregaran 3 archivos y el enunciado: 	
		•“lista.h” y “lista.c”  (librerías del tda lista)
		•“lista_pruebas.c”     (tests sobre el tda lista creado)
		•"tda_lista.pdf"       (enunciado)

	Las funciones primitivas del TDA que serán provistas son las siguientes:
		•lista_t* lista_crear();
			creara la lista 
		•int lista_insertar(lista_t* lista, void* elemento);
			insertara el elemento en la ultima posicion de la lista
		•int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);
			insertara el elemento en la posicion ingresada,si esa posicion no existe insertara al final de la lista
		•int lista_borrar(lista_t* lista);
			borra el ultimo elemento de la lista
		•int lista_borrar_de_posicion(lista_t* lista, size_t posicion);
			borra el elemento en la posicion ingresada,si esa posicion no existe borrara al final de la lista
		•void* lista_ultimo(lista_t* lista);
			devuelve el ultimo elemento de la lista o NULL si la lista esta vacia
		•void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);
			devuelve el elemento en la posicion ingresada,si esa posicion no existe devuelve NULL
		•bool lista_vacia(lista_t* lista);
			determina si la lista esta vacia o no
		•size_t lista_elementos(lista_t* lista);
			devuelve la cantidad de elementos de la lista
		•void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*));
			iterador interno, que realizara la "funcion" mandada por el usuario por cada elemento de la lista
		•void lista_destruir(lista_t* lista);
			destruye la lista
	a su vez tenemos el TDA iterador externo que sus primitivas son:
		•lista_iterador_t* lista_iterador_crear(lista_t* lista);
			creara el iterador vinculado a la lista ingresada
		•bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador);
			determina si hay mas elementos sobre los cuales iterar
		•void* lista_iterador_siguiente(lista_iterador_t* iterador);
			movera el iterador al siguiente elemento de la lista y devolvera el actual
		•void lista_iterador_destruir(lista_iterador_t* iterador);
			destruye el iterador


	Como vemos, podemos insertar elementos al final de la lista como en la posicion que queramos.Lo mismo sucede si queremos destruir elementos.Es por esto que la 	implementacion se realizo de la siguiente manera:
		typedef struct nodo {
			void* elemento;
			struct nodo* siguiente;
		} nodo_t;

		struct lista{
			nodo_t* nodo_inicio;
			nodo_t* nodo_fin;
			int cantidad;
		};

	Sin duda el "nodo_inicio" es indispensable para la implementacion del TDA ya que sin este no se podria recorrer la lista (los nodos solo tiene la referencia al sucesor y no al predecesor como pasa en la doblemente enlazada).
	Con solo este nodo tanto 
	lista_insertar,lista_insertar_en_posicion,lista_borrar,lista_borrar_de_posicion,lista_ultimo,lista_elemento_en_posicion tienen tiempo de ejecucion --- O(n)
	Se utiliza un nuevo nodo, un "nodo_fin" que apunta al final de la lista por que solo
	lista_insertar,lista_ultimo varia su tiempo de ejecucion a ----- O(1) 
	
	Por otra parte lista_elementos tambien tendria tiempo de ejecucion O(n) si solo tuviera los dos nodos que mencionamos anteriormente ya que tenemos que recorrer toda la lista para ir contando cuantos elementos tenemos. Es por esto que se agrega una nueva variable mas a la estructura llamada "cantidad" para que
	lista_elementos varie su tiempo de ejecucion a O(1)  (cabe mencionar que esta variable tambien no sirve para buscar en posiciones estrategicas)
	Entonces resumiendo:
		lista_crear                   O(1)
		lista_insertar		      O(1)			
		lista_insertar_en_posicion    O(n)
		lista_borrar                  O(n)
		lista_borrar_de_posicion      O(n)
		lista_ultimo                  O(1)
		lista_elemento_en_posicion    O(n)
		lista_vacia                   O(1)
		lista_elementos               O(1)
		lista_con_cada_elemento	      O(n)
		lista_destruir                O(n)


/*---------------------------------------COMPILACIÓN Y EJECUCIÓN---------------------------------------*/

	Para poder compilar y ejecutar el programa deberá acceder a la consola. Una vez en la consola,mediante los comandos “ls” y “cd” deberá acceder a la carpeta contenedora de los archivos provistos mencionados anteriormente. Una vez en accedido a ella , ya podrá ingresar los siguientes comandos:

	•Compilación:
gcc *. c -o lista_se -g - std = c99 - Wall - Wconversion - Wtype - limits - pedantic - Werror – O0
	Nota: es necesario que tenga tanto “lista.c” “lista.h” y “lista_pruebas.c” en la misma carpeta 

	•Ejecución:
./ lista_se
	Nota: esta linea de comando no mostrara errores o fallas como la que se muestra a continuacion
valgrind -- leak - check = full -- track - origins = yes -- show - reachable = yes ./ lista_se
	Nota: es necesario tener previamente instalado valgrind

	(este trabajo no cuenta con makefile)



/*---------------------------------------TEST---------------------------------------*/

#=Anatomía de una Test (C)=#
	La anatomía de una test en el código(Lenguaje C) es del estilo:

					int Dado._Cuando.._Entonces..(void){
						//Inicialización de las variables o Input    
						…
						//Llamado al código a probar
						…
						//Verificación de salida esperada o Output esperado
						…
						return(resultado);
					}

		•El tipo de retorno queda a gusto del que realiza la test.
		•El nombre de la función viene dado con las buenas practicas de programación:
			-Dado..:Dado algo, en este caso damos los valores iniciales de las entradas
			-Cuando..:Cuando sucede algo,en este caso ejecutamos la función a poner a prueba
			-Entonces..:Entonces esperamos algo,en este caso esperamos el Output esperado

#=Agregar una Test al Proyecto=#
	Habiendo informado sobre la estructura de una test y cual es la buena practica para realizarla, 
	en el caso de que usted desee agregar una test al código deberá hacerlo en el archivo “lista_pruebas.c” 
	que se le provee en el proyecto.
	El siguiente archivo tiene extension “.c” (codigo) y esta estructurado de la siguiente forma:
	
						Includes
				  //// todo lo referido a librerías////
						Constantes
			  //// todo lo referido a definiciones de constantes////
					 	 Tests
			   //// todo lo referido a las funciones test////

					int main(){
						Llamado a las funciones test
					}

	1)Deberá realizar su Test en la sección Test. La Test que agregara deberá cumplir con lo siguiente:

					int nombre_de_su_test(){
						//Inicialización de las variables o Input    
						…
						//Llamado al código a probar
						…
						//Verificación de salida esperada o Output esperado
						…
						return(resultado);
					}

		•tipo de retorno: int (entero),devolverá OK(0) si paso la prueba o ERROR(-1) en caso contrario
		•tipo de entrada: void,no debe tener parámetros de entrada
		•nombre_de_su_test: siguiendo con las buenas practicas de programación como se menciono en el apartado Anatomía de una Test 

	2)Una vez hecha su Test deberá agregarla al vector de Test llamado “(*funciones_testing[])()”que se encuentra en el main:

	Supongamos que iniciamos con dos test en el vector y queremos añadir una nueva test que usted creo llamada “mi-test”
	en el main inicialmente se vera:
					int main(){
						int (*funcion_testing[])()={test1,test2}
						…						
					}
	luego:
					int main(){
						int (*funcion_testing[])()={test1,test2,mi_test}
						…
					}
	realizo otra llamada “mi_test2” y quiero añadirla:
					int main(){
						int (*funcion_testing[])()={test1,test2,mi_test,mi_test2}
						…
					}

	3)Ya realizada la Test y agregada al código lo único restante es modificar el valor de la constante “CANTIDAD_PRUEBAS” 
	que se encontrara en la sección Constantes. 
