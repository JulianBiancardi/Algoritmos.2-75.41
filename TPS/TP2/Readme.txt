/*======================================================================TP2============================================================================================*/

	El objetivo del siguiente trabajo consiste en la implementación de un juego con tematica de Game Of Thrones.Para esto se icorpora no solo los conocimientos previos de los TDA previos hechos(como cola.lista y abb) sino que tambien los mismos para la implementacion.Como bien se ha mencionado, para este trabajo se ha optado por
utilizar los TDA: cola lista y abb.

	Se entregaran los siguientes archivos: 	
		•“TP2.c”     	                           (codigo para manejar el juego)
		•“juego_tronos.h” y “juego_tronos.c”       (librerías del juego)
		•nombres_personas.txt			   (nombres de personas para el juego)
		•casas.txt				   (modelo de archivo de casas para el juego)
		•librerias de tda cola     			  
		•librerias de tda lista    	
		•librerias de tda abb	  
		•"TP2.pdf"       			   (enunciado)


	Las funciones de las librerias del juego que usted podra usar son las siguientes:
		•juego_t* juego_crear();
			creara el juego inicialmente vacio
		•int juego_agregar_casa(juego_t* juego,const char* nombre_archivo);
			agregara las casas,con sus personas, al juego.Estas casas estaran en el archivo pasado por el usuario
		•int juego_simulacion(juego_t* juego,int cantidad_anios);
			simula el juego una cantidad de anios pasada por el usuario, al finalizar mostrara la casa dominante 
		•int juego_casas_descendente(juego_t* juego);
			mostrara la casas activas por cantidad de personas en orden descendente
		•int juego_casas_extintas(juego_t* juego);
			mostrara las casas en el mismo orden en el que fueron desapareciendo del juego
		•void juego_mostrar_menu();
			muestra el menu del juego
		•void juego_destruir(juego_t* juego);
			destruye el juego
Aclaraciones:
	- El archivo de nombres de personas es utilizado para cuando nuevas personas son generadas.Puede ser modificado a gusto del usuario 
	pero no eliminado.
	- El archivo de casas es un modelo,es decir, muestra como debe de estar estructurado.Puede ser modificado a gusto del usuario y a su
	vez elminado(si se elmina no se podra agregar casas pero si se podra ejecutar las otras acciones).El formato del archivo debe ser el siguiente


	Casa 1 ------->			C;nombre_casa;factor_envejecimiento;factor_nacimiento;     para la casa
		persona 1(casa1)	I;nombre_persona;edad 					   para la persona
		persona 2(casa1)	I;nombre_persona;edad 
							*
							*
	Casa 2 ------->			C;nombre_casa;factor_envejecimiento;factor_nacimiento;
		persona 1(casa2)	I;nombre_persona;edad 
							*
							*                                        y asi sucesivamente
        Casos:
		-Si el archivo se encuentra vacio, el juego no agrega ninguna casa
		-Si la linea de Casa 1 falta, las personas seran invisibles para el juego y solo agregara la Casa2 con sus personas
		-Caso contrario si la linea Casa 2 falta, las personas de la casa 2 seran agregadas a la casa 1
		-Si hay espacios entre linea no causa problemas



/*---------------------------------------STRUCTS---------------------------------------*/

	En este apartado veremos un poco de la implementacion, y explicaremos porque se ha elejido cada cosa:

	El trabajo trata acerca de casas y personas, por lo que generaremos abamas estructuras (cada una con sus primivitas por separado)

				typedef struct persona{
					char nombre[MAX_NOMBRE_PERSONA];
					int edad;
				}persona_t;						Notese que las variables contenedoras en las estructuras
											no es mas que el formato que se lee del archivo.
				typedef struct casa{					
					char nombre_casa[MAX_NOMBRE_CASA];
					int factor_envejecimiento;
					int factor_nacimiento; 
					lista_t* familia;                    --------> La casa a su vez contendra un lista que en nuestro caso				
				}casa_t;                                               solo le insertaremos "personas".Luego las personas viven en una casa.

				struct juego{
					abb_t* arbol_juego;                  -------> Arbol del juego que en nuestro caso le insertaremos casas.Asi el juego tiene casas
					size_t cantidad_casas;               -------> Cantidad de casas actuales en el juego
					cola_t* casas_extintas;              -------> Cola con las casas que se fueron extinguiendo en todo el juego
					cola_t* casas_extintas_auxiliar;     -------> Cola auxiliar con las casas que se fueron extinguiendo en la simulacion actual
					FILE* archivo_nombres_personas;      -------> Archivo de nombres de personas para el nacimiento de las mismas
				};
	

/*---------------------------------------COMPILACIÓN Y EJECUCIÓN---------------------------------------*/

	Para poder compilar y ejecutar el programa deberá acceder a la consola. Una vez en la consola,mediante los comandos “ls” y “cd” deberá acceder a la carpeta contenedora de los archivos provistos mencionados anteriormente. Una vez en accedido a ella , ya podrá ingresar los siguientes comandos:

	•Compilación:
gcc *. c -o tp2 -g - std = c99 - Wall - Wconversion - Wtype - limits - pedantic - Werror – O0
	Nota: es necesario que tenga todos los archivos .c y .h mencionados al inicio en la misma carpeta 

	•Ejecución:
./ tp2
	Nota: esta linea de comando no mostrara errores o fallas como la que se muestra a continuacion

valgrind -- leak - check = full -- track - origins = yes -- show - reachable = yes ./ tp2
	Nota: es necesario tener previamente instalado valgrind

	(este trabajo no cuenta con makefile)


