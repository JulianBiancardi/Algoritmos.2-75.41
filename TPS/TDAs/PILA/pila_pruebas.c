#include <stdio.h>
#include "pila.h"
/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CANTIDAD_PRUEBAS 14
/*---------------------------------------*/


/*---------------------------------------*/
//TEST
int (*funcion_testing) (void);


int DadaUnaPilaVacia_EntoncesEmpiezaVacia(){
  printf("#========== Pruebas pila vacia: ==========#\n");
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_vacia(pila)?OK :ERROR;

  //Control de salida
  printf(" •La pila esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaVacia_EntoncesNoTieneElementos(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_tope(pila) == NULL?OK : ERROR;

  //Control de salida
  printf(" •No hay elementos en la pila: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaVacia_EntoncesNoSePuedeDesapilar(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_desapilar(pila);

  //Control de salida
  printf(" •Se intenta desapilar en una pila vacia,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return !estado_operacion;
}

int DadaUnaPilaLLena_EntoncesSePuedeApilar(){
  printf("#========== Pruebas pila LLena: ==========#\n");
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < (*pila).tamanio; ++i)
    pila_apilar(pila,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = pila_apilar(pila,&elementos[tope_elementos]);

  //Control de salida
  printf(" •Se intenta apilar en una pila llena,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaLLena_EntoncesSePuedeDesapilar(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
 
  for (int i = 0; i < (*pila).tamanio; ++i)
    pila_apilar(pila,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = pila_desapilar(pila);

  //Control de salida
  printf(" •Se intenta desapilar en una pila llena,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaLLena_EntoncesNoEstaVacia(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
 
  for (int i = 0; i < (*pila).tamanio; ++i)
    pila_apilar(pila,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = pila_vacia(pila)?OK :ERROR;

  //Control de salida
  printf(" •La pila no esta vacia: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return !estado_operacion;
}

int DadaUnaPilaNull_EntoncesNoSePuedeApilar(){
  printf("#========== Pruebas pila NULL: ==========#\n");
  //Inicializacion de entrada
  pila_t* pila = NULL;
  char elemento = 'A';
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_apilar(pila,&elemento);

  //Control de salida
  printf(" •Se intenta apilar en una pila NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return !estado_operacion;
}
int DadaUnaPilaNull_EntoncesNoSePuedeDesapilar(){
  //Inicializacion de entrada
  pila_t* pila = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_desapilar(pila);

  //Control de salida
  printf(" •Se intenta desapilar en una pila NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return !estado_operacion;
}
int DadaUnaPilaNull_EntoncesEstaVacia(){
  //Inicializacion de entrada
  pila_t* pila = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_vacia(pila)?OK :ERROR;

  //Control de salida
  printf(" •La pila NULL esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");
  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPila_CuandoSeApilaUnElementoNULL_EntoncesDevuelveOK(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = pila_apilar(pila,NULL);

  //Control de salida
  printf(" •Se intenta apilar un elemento NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}

int DadaUnaPilaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElElementoTope(){
  printf("#========== Pruebas pila variada: ==========#\n");
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    pila_apilar(pila,&elementos[i]); 

  for(int i = 0;i < 5;i++)
    pila_desapilar(pila);

  //Llamado a codigo prueba
  estado_operacion = pila_tope(pila) == &elementos[4]?OK : ERROR;

  //Control de salida
  printf(" •Se desapilan elementos,el elemento tope es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaVariada_CuandoApilanElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    pila_apilar(pila,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = pila_cantidad(pila) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Hay %i elementos almacenados en la pila: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaVariada_CuandoDesapilanTodosLosElementos_EntoncesEstaVacia(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    pila_apilar(pila,&elementos[i]); 

  for(int i = 0;i < tope_elementos;i++)
    pila_desapilar(pila);

  //Llamado a codigo prueba
  estado_operacion = pila_vacia(pila)?OK :ERROR;

  //Control de salida
  printf(" •Se desapilaron todos los elementos,la pila esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
int DadaUnaPilaVariada_CuandoApilanMuchosElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  pila_t* pila = pila_crear();
  int estado_operacion;

  char elementos [100000] = {'A'};
  int tope_elementos = 100000;

  for (int i = 0; i < tope_elementos; ++i)
    pila_apilar(pila,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = pila_cantidad(pila) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Se apilan  %i elementos, la cantidad de elementos en la pila es correcta: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  pila_destruir(pila);
  return estado_operacion;
}
/*---------------------------------------*/


int main(){

  int pruebas_pasadas = 0;
  int (*funciones_testing[])()={DadaUnaPilaVacia_EntoncesEmpiezaVacia,
                                DadaUnaPilaVacia_EntoncesNoTieneElementos,                              
                                DadaUnaPilaVacia_EntoncesNoSePuedeDesapilar,
                                DadaUnaPilaLLena_EntoncesSePuedeApilar,
                                DadaUnaPilaLLena_EntoncesSePuedeDesapilar,
                                DadaUnaPilaLLena_EntoncesNoEstaVacia,
                                DadaUnaPilaNull_EntoncesNoSePuedeApilar,
                                DadaUnaPilaNull_EntoncesNoSePuedeDesapilar,
                                DadaUnaPilaNull_EntoncesEstaVacia,
                                DadaUnaPila_CuandoSeApilaUnElementoNULL_EntoncesDevuelveOK,
                                DadaUnaPilaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElElementoTope,
                                DadaUnaPilaVariada_CuandoApilanElementos_EntoncesLaCantidadEsCorrecta,
                                DadaUnaPilaVariada_CuandoDesapilanTodosLosElementos_EntoncesEstaVacia,
                                DadaUnaPilaVariada_CuandoApilanMuchosElementos_EntoncesLaCantidadEsCorrecta};


  printf("Realizando pruebas internas...\n\n");

  for(int i = 0;i < CANTIDAD_PRUEBAS;i++){
    if(funciones_testing[i]() == OK)
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
