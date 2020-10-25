#include "abb.h"
#include <stdio.h>
/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CANTIDAD_PRUEBAS 25

/*---------------------------------------*/


/*---------------------------------------*/
//TEST
int (*funcion_testing) (void);

bool mostrar_elemento(void* elemento, void* extra){
  extra = extra; 
  if(elemento == NULL)
    return true;

  printf("%i ", (*(int*)elemento));
  /*
  if((*(int*)elemento) == 5)
    return true;
*/
  return false;

}

int comparador(void* elemento1, void* elemento2){
  if(!elemento1 || !elemento2)
    return 0;

  if((*(int*)elemento1) > (*(int*)elemento2))  
    return 1;
  if((*(int*)elemento1) < (*(int*)elemento2))      
    return -1;

  return 0;
}

int DadoUnArbolVacio_EntoncesEmpiezaVacio(){
  printf("#========== Pruebas \033[1;36marbol vacio\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_vacio(arbol)?OK :ERROR;

  //Control de salida
  printf(" •El arbol esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVacio_EntoncesLaRaizEsNull(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_raiz(arbol) == NULL?OK :ERROR;

  //Control de salida
  printf(" •La raiz de un arbol vacio es NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnaArbolVacio_EntoncesSePuedeInsertar(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_insertar(arbol,&elemento) == OK?OK :ERROR;

  //Control de salida
  printf(" •Se intenta insertar en un arbol vacio,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnaArbolVacio_EntoncesNoSePuedeBorrar(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_borrar(arbol,&elemento) == ERROR?OK :ERROR;

  //Control de salida
  printf(" •Se intenta borrar en un arbol vacio,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnaArbolVacio_EntoncesBuscarDevuelveNull(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_buscar(arbol,&elemento) == NULL?OK :ERROR;

  //Control de salida
  printf(" •Se intenta buscar en un arbol vacio,devuelve NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}


int DadoUnArbolConElementos_EntoncesNoEstaVacio(){
  printf("#========== Pruebas \033[1;36marbol con elementos\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion; 
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = arbol_vacio(arbol)?OK :ERROR;

  //Control de salida
  printf(" •La arbol no esta vacio: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return !estado_operacion;
}
int DadoUnArbolConElementos_EntoncesSePuedeInsertar(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]); 

  //Llamado a codigo prueba
  int elemento_insertar = 9;
  estado_operacion = arbol_insertar(arbol,&elemento_insertar);

  //Control de salida
  printf(" •Se intenta insertar en un arbol con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolConElementos_EntoncesSePuedeInsertarRepetido(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = arbol_insertar(arbol,&elementos[5]);
  estado_operacion = arbol_insertar(arbol,&elementos[5]);
  estado_operacion = arbol_insertar(arbol,&elementos[0]);
  estado_operacion = arbol_insertar(arbol,&elementos[2]);

  //Control de salida
  printf(" •Se intenta insertar insertar  elementos repetidos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolConElementos_EntoncesSePuedeBorrar(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = arbol_borrar(arbol,&elementos[tope_elementos]);

  //Control de salida
  printf(" •Se intenta borrar en un arbol con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}


int DadoUnArbolNull_EntoncesEstaVacio(){
  printf("#========== Pruebas \033[1;36marbol NULL,elemento NULL\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  abb_t* arbol = NULL; 
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_vacio(arbol)?OK :ERROR;

  //Control de salida
  printf(" •El arbol NULL esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");
  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolNull_EntoncesNoSePuedeInsertar(){
  //Inicializacion de entrada
  abb_t* arbol = NULL;
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_insertar(arbol,&elemento); 

  //Control de salida
  printf(" •Se intenta insertar en un arbol NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return !estado_operacion;
}
int DadoUnArbolNull_EntoncesNoSePuedeBorrar(){
  //Inicializacion de entrada
  abb_t* arbol = NULL;
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_borrar(arbol,&elemento);

  //Control de salida
  printf(" •Se intenta borrar en un arbol NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return !estado_operacion;
}
int DadoUnArbolNull_EntoncesBuscarDevuelveNull(){
  //Inicializacion de entrada
  abb_t* arbol = NULL;
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = arbol_buscar(arbol,&elemento) == NULL?OK :ERROR;

  //Control de salida
  printf(" •Se intenta buscar en un arbol NULL,devuelve NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbol_CuandoSeInsertaUnElemenetoNull_EntoncesDevuelveERROR(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_insertar(arbol,NULL); 

  //Control de salida
  printf(" •Se intenta insertar un elemento NULL: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return !estado_operacion;
}
int DadoUnArbol_CuandoSeBorraUnElemenetoNull_EntoncesDevuelveERROR(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_borrar(arbol,NULL); 

  //Control de salida
  printf(" •Se intenta borrar un elemento NULL: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return !estado_operacion;
}
int DadoUnArbol_CuandoSeBuscaUnElementoNull_EntoncesDevuelveNull(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL); 
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = arbol_buscar(arbol,NULL) == NULL?OK :ERROR;

  //Control de salida
  printf(" •Se intenta buscar un elemento NULL,devuelve NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}

bool sumar_elementos_hasta_5(void* elemento,void* extra){
  if(elemento == NULL || extra == NULL)
    return true;

  (*(int*)extra) += (*(int*)elemento);
  if((*(int*)elemento) == 5)
    return true;

  return false;
 }
int DadoUnArbolVariado_CuandoSeBuscaElElemento_EntoncesSeDevuelveElElemento(){
  printf("#========== Pruebas \033[1;36marbol variado\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]); 
  
  for(int i = 0;i < 5;i++)
    arbol_borrar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  estado_operacion = arbol_buscar(arbol,&elementos[tope_elementos - 1]) == &elementos[tope_elementos -1]?OK : ERROR;

  //Control de salida
  printf(" •Se realizan operaciones con el arbol,el elemento buscado es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeBorranTodosLosElementos_EntoncesEstaVacio(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[4] = {2,4,1,2};  
  int tope_elementos = 4;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  for (int i = 0; i < tope_elementos;i++)
    arbol_borrar(arbol,&elementos[i]);  

  //Llamado a codigo prueba
  estado_operacion = arbol_vacio(arbol)?OK :ERROR;

  //Control de salida
  printf(" •Se borraron todos los elementos,el arbol esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeBorraLaRaiz_EntoncesLaRaizEsCorrecta(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;


  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  arbol_borrar(arbol,&elementos[4]);

  //Llamado a codigo prueba
  estado_operacion =  arbol_raiz(arbol) == &elementos[0]?OK :ERROR;

  //Control de salida
  printf(" •Se borra la raiz de un arbol,la nueva raiz es correcta:");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeRecorreInorden_EntoncesElArrayEsCorrecto(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;
  int* array[5];
  int tamanio_array = 5;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int cantidad = arbol_recorrido_inorden(arbol,(void**)array,tamanio_array);
  estado_operacion = (cantidad == tamanio_array)?OK : ERROR; 
  estado_operacion = (*array[0] == elementos[8])?OK : ERROR;
  estado_operacion = (*array[1] == elementos[2])?OK : ERROR; 
  estado_operacion = (*array[2] == elementos[0])?OK : ERROR; 
  estado_operacion = (*array[3] == elementos[4])?OK : ERROR; 

  //Control de salida
  printf(" •Se recorre inorden ,el array generado es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeRecorrePreorden_EntoncesElArrayEsCorrecto(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;
  int* array[20];
  int tamanio_array = 20;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int cantidad = arbol_recorrido_preorden(arbol,(void**)array,tamanio_array);
  estado_operacion = (cantidad == tope_elementos)?OK : ERROR; 
  estado_operacion = (*array[0] == elementos[0])?OK : ERROR;
  estado_operacion = (*array[1] == elementos[2])?OK : ERROR; 
  estado_operacion = (*array[2] == elementos[8])?OK : ERROR; 
  estado_operacion = (*array[3] == elementos[1])?OK : ERROR; 

  //Control de salida
  printf(" •Se recorre preorden ,el array generado es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeRecorrePostorden_EntoncesElArrayEsCorrecto(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;
  int* array[5];
  int tamanio_array = 5;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int cantidad = arbol_recorrido_postorden(arbol,(void**)array,tamanio_array);
  estado_operacion = (cantidad == tamanio_array)?OK : ERROR; 
  estado_operacion = (*array[0] == elementos[8])?OK : ERROR;
  estado_operacion = (*array[1] == elementos[2])?OK : ERROR; 
  estado_operacion = (*array[2] == elementos[4])?OK : ERROR; 
  estado_operacion = (*array[3] == elementos[7])?OK : ERROR; 

  //Control de salida
  printf(" •Se recorre postorden ,el array generado es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeIteraInorden_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int contador = 0;
  abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,sumar_elementos_hasta_5,&contador);

  estado_operacion = (contador == (0+1+2+3+4+5))?OK : ERROR;

  //Control de salida
  printf(" •Se itera inorden internamente sumando los elementos,la cantidad es correcta: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeIteraPreorden_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int contador = 0;
  abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,sumar_elementos_hasta_5,&contador);
 
  estado_operacion = (contador == (2+1+0+4+3+5))?OK : ERROR;

  //Control de salida
  printf(" •Se itera preorden internamente sumando los elementos,la cantidad es correcta: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}
int DadoUnArbolVariado_CuandoSeIteraPostorden_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  abb_t* arbol = arbol_crear(comparador, NULL);
  int estado_operacion;
  int elementos[10] = {2,4,1,5,3,8,6,7,0,20};  
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    arbol_insertar(arbol,&elementos[i]);

  //Llamado a codigo prueba
  int contador = 0;
  abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,sumar_elementos_hasta_5,&contador);

  estado_operacion = (contador == (0+1+3+7+6+20+8+5))?OK : ERROR;

  //Control de salida
  printf(" •Se itera postorden internamente sumando los elementos,la cantidad es correcta: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  arbol_destruir(arbol);
  return estado_operacion;
}

/*---------------------------------------*/

int main(){
  int pruebas_pasadas = 0;
  int (*funcion_testing[])()={DadoUnArbolVacio_EntoncesEmpiezaVacio,
                              DadoUnaArbolVacio_EntoncesSePuedeInsertar,                             
                              DadoUnArbolVacio_EntoncesLaRaizEsNull,
                              DadoUnaArbolVacio_EntoncesNoSePuedeBorrar, 
                              DadoUnaArbolVacio_EntoncesBuscarDevuelveNull,

                              DadoUnArbolConElementos_EntoncesNoEstaVacio,
                              DadoUnArbolConElementos_EntoncesSePuedeInsertar,
                              DadoUnArbolConElementos_EntoncesSePuedeInsertarRepetido,
                              DadoUnArbolConElementos_EntoncesSePuedeBorrar,

                              DadoUnArbolNull_EntoncesEstaVacio,
                              DadoUnArbolNull_EntoncesNoSePuedeInsertar,
                              DadoUnArbolNull_EntoncesNoSePuedeBorrar,
                              DadoUnArbolNull_EntoncesBuscarDevuelveNull,
                              DadoUnArbol_CuandoSeInsertaUnElemenetoNull_EntoncesDevuelveERROR,
                              DadoUnArbol_CuandoSeBorraUnElemenetoNull_EntoncesDevuelveERROR,
                              DadoUnArbol_CuandoSeBuscaUnElementoNull_EntoncesDevuelveNull,

                              DadoUnArbolVariado_CuandoSeBuscaElElemento_EntoncesSeDevuelveElElemento,
                              DadoUnArbolVariado_CuandoSeBorranTodosLosElementos_EntoncesEstaVacio,
                              DadoUnArbolVariado_CuandoSeBorraLaRaiz_EntoncesLaRaizEsCorrecta,
                              DadoUnArbolVariado_CuandoSeRecorreInorden_EntoncesElArrayEsCorrecto,
                              DadoUnArbolVariado_CuandoSeRecorrePreorden_EntoncesElArrayEsCorrecto,
                              DadoUnArbolVariado_CuandoSeRecorrePostorden_EntoncesElArrayEsCorrecto,
                              DadoUnArbolVariado_CuandoSeIteraInorden_EntoncesLaCantidadEsCorrecta,
                              DadoUnArbolVariado_CuandoSeIteraPreorden_EntoncesLaCantidadEsCorrecta,
                              DadoUnArbolVariado_CuandoSeIteraPostorden_EntoncesLaCantidadEsCorrecta
                              };

  printf("Realizando pruebas internas...\n\n");

  for(int i = 0;i < CANTIDAD_PRUEBAS;i++){
    if(funcion_testing[i]() == OK)
      pruebas_pasadas++;
  }
  
  printf("\033[0;0m");//color neutro
  printf("\n#=======================================#\n");
  printf("#                                       #\n");
  printf("#         Pruebas pasadas: %i/%i        #\n",pruebas_pasadas,CANTIDAD_PRUEBAS);
  printf("#                                       #\n");
  printf("#=======================================#\n");
  
  return 0;
}