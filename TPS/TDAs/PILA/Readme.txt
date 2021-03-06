/*---------------------------------------TDA PILA---------------------------------------*/

	El objetivo del siguiente trabajo consiste en la implementación del TDA PILA como vector dinámico. Para esto se tienen ciertas funciones primitivas propias del TDA, las cuales se les brindaran al usuario garantizando el correcto funcionamiento de cada una de ellas. Por otra parte, se crearan TESTS sobre el TDA para  determinar la calidad especialmente antes que sea llevado al uso por el usuario.
	Se entregaran 3 archivos y el enunciado: 	
		•“pila.h” y “pila.c”  (librerías del tda pila)
		•“pila_pruebas.c”     (tests sobre el tda pila creado)
		•"tda_pila.pdf"       (enunciado)



/*---------------------------------------COMPILACIÓN Y EJECUCIÓN---------------------------------------*/

	Para poder compilar y ejecutar el programa deberá acceder a la consola. Una vez en la consola,mediante los comandos “ls” y “cd” deberá acceder a la carpeta contenedora de los archivos provistos mencionados anteriormente. Una vez en accedido a ella , ya podrá ingresar los siguientes comandos:

	•Compilación:
gcc *. c -o pila_vd -g - std = c99 - Wall - Wconversion - Wtype - limits - pedantic - Werror – O0
	Nota: es necesario que tenga tanto “pila.c” “pila.h” y “pila_pruebas.c” en la misma carpeta 

	•Ejecución:
valgrind -- leak - check = full -- track - origins = yes -- show - reachable = yes ./ pila_vd
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
	en el caso de que usted desee agregar una test al código deberá hacerlo en el archivo “pila_prueba.c” 
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
