/*---------------------------------------TDA HASH-------------------------------------------------*/

	El objetivo del siguiente trabajo consiste en la implementación del TDA HASH,para este caso realizamos un HASH ABIERTO. Para esto se tienen ciertas funciones primitivas propias del TDA, las cuales se les brindaran al usuario garantizando el correcto funcionamiento de cada una de ellas. Por otra parte, se crearan TESTS sobre el TDA para  determinar la calidad especialmente antes que sea llevado al uso por el usuario.
	Se entregaran 3 archivos y el enunciado: 	
		•“hash.h” y “hash.c”     	           (librerías del tda hash)
		•“hash_iterador.h” y “hash_iterador.c”     (librerías del iterador del hash)
		•“hash_prebas.c”      			   (tests sobre el tda hash creado)
		•"tda_hash.pdf"       			   (enunciado)

	Las funciones primitivas del TDA que serán provistas son las siguientes:
		•hash_t* hash_crear(hash_destruir_dato_t destructor, size_t capacidad);
			creara el hash con la capacidad provista(esta sera la minima y no podra ser 0) y con su destructor(este ultimo puede ser NULL)
		•int hash_insertar(hash_t* hash, const char* clave, void* elemento);
			insertara la clave con su elemento en el hash
		•int hash_quitar(hash_t* hash, const char* clave);
			quita,si existe,la clave del hash.Si la clave es repetida quita la primera encontrada  
		•void* hash_obtener(hash_t* hash, const char* clave);
			devuelve el elemento del hash que contenga la clave dada o NULL si no existe dicha clave
		•bool hash_contiene(hash_t* hash, const char* clave);
			determina si la clave esta contenida en el hash
		•size_t hash_cantidad(hash_t* hash);
			devuelve la cantidad de elementos almacenados en el hash
		•void hash_destruir(hash_t* hash);
			destruye el hash:
	a su vez tenemos el TDA iterador externo que sus primitivas son:
		•hash_iterador_t* hash_iterador_crear(hash_t* hash);
			creara el iterador vinculado al hash ingresado
		•bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador);
			determina si hay mas claves sobre los cuales iterar
		•void* hash_iterador_siguiente(hash_iterador_t* iterador);
			movera el iterador a la siguiente clave del hash y la devolvera
		•void hash_iterador_destruir(hash_iterador_t* iterador);
			destruye el iterador

	

/*---------------------------------------COMPILACIÓN Y EJECUCIÓN---------------------------------------*/

	Para poder compilar y ejecutar el programa deberá acceder a la consola. Una vez en la consola,mediante los comandos “ls” y “cd” deberá acceder a la carpeta contenedora de los archivos provistos mencionados anteriormente. Una vez en accedido a ella , ya podrá ingresar los siguientes comandos:

	•Compilación:
gcc *. c -o hash -g - std = c99 - Wall - Wconversion - Wtype - limits - pedantic - Werror – O0
	Nota: es necesario que tenga tanto “hash.c” “hash.h” "hash_iterador.c" "hash_iterador.h" y “hash_prebas.c” en la misma carpeta 

	•Ejecución:
./ hash
	Nota: esta linea de comando no mostrara errores o fallas como la que se muestra a continuacion

valgrind -- leak - check = full -- track - origins = yes -- show - reachable = yes ./ hash
	Nota: es necesario tener previamente instalado valgrind

	(este trabajo no cuenta con makefile)



/*---------------------------------------TEST--------------------------------------------------------*/

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
	en el caso de que usted desee agregar una test al código deberá hacerlo en el archivo “arbol_preubas.c” 
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
