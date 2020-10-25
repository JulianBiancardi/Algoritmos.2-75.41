#include "cola.h"
#include <stdio.h>
/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CANTIDAD_PRUEBAS 14

/*---------------------------------------*/


/*---------------------------------------*/
//TEST
int (*funcion_testing) (void);

int DadaUnaColaVacia_EntoncesEmpiezaVacia(){
  printf("#========== Pruebas cola vacia: ==========#\n");
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_vacia(cola)?OK :ERROR;

  //Control de salida
  printf(" •La cola esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaVacia_EntoncesNoTieneElementos(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_primero(cola) == NULL?OK : ERROR;

  //Control de salida
  printf(" •No hay elementos en la cola: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaVacia_EntoncesNoSePuedeDesencolar(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_desencolar(cola);

  //Control de salida
  printf(" •Se intenta desencolar en una cola vacia,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return !estado_operacion;
}

int DadaUnaColaConElementos_EntoncesSePuedeEncolar(){
  printf("#========== Pruebas cola LLena: ==========#\n");
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = cola_encolar(cola,&elementos[tope_elementos]);

  //Control de salida
  printf(" •Se intenta encolar en una cola con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaConElementos_EntoncesSePuedeDesencolar(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = cola_desencolar(cola);

  //Control de salida
  printf(" •Se intenta desencolar en una cola con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaConElementos_EntoncesNoEstaVacia(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = cola_vacia(cola)?OK :ERROR;

  //Control de salida
  printf(" •La cola no esta vacia: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return !estado_operacion;
}

int DadaUnaColaNull_EntoncesNoSePuedeEncolar(){
  printf("#========== Pruebas cola NULL,elemento NULL: ==========#\n");
  //Inicializacion de entrada
  cola_t* cola = NULL;
  char elemento = 'A';
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_encolar(cola,&elemento);

  //Control de salida
  printf(" •Se intenta encolar en una cola NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return !estado_operacion;
}
int DadaUnaColaNull_EntoncesNoSePuedeDesencolar(){
  //Inicializacion de entrada
  cola_t* cola = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_desencolar(cola);

  //Control de salida
  printf(" •Se intenta desencolar en una cola NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return !estado_operacion;
}
int DadaUnaColaNull_EntoncesEstaVacia(){
  //Inicializacion de entrada
  cola_t* cola = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_vacia(cola)?OK :ERROR;

  //Control de salida
  printf(" •La cola NULL esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");
  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaCola_CuandoSeEncolaUnElementoNULL_EntoncesDevuelveOK(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = cola_encolar(cola,NULL);

  //Control de salida
  printf(" •Se intenta encolar un elemento NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}

int DadaUnaColaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElPrimerElemento(){
  printf("#========== Pruebas cola variada: ==========#\n");
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  for(int i = 0;i < 5;i++)
    cola_desencolar(cola);

  //Llamado a codigo prueba
  estado_operacion = cola_primero(cola) == &elementos[5]?OK : ERROR;

  //Control de salida
  printf(" •Se desencolan elementos,el primer elemento es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaVariada_CuandoSeEncolanElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = cola_cantidad(cola) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Hay %i elementos almacenados en la cola: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaVariada_CuandoDesencolanTodosLosElementos_EntoncesEstaVacia(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    cola_encolar(cola,&elementos[i]); 

  for(int i = 0;i < tope_elementos;i++)
    cola_desencolar(cola);

  //Llamado a codigo prueba
  printf("%i\n", cola_cantidad(cola));
  estado_operacion = cola_vacia(cola)?OK :ERROR;

  //Control de salida
  printf(" •Se desencolaron todos los elementos,la cola esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
int DadaUnaColaVariada_CuandoSeEncolanMuchosElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  cola_t* cola = cola_crear();
  int estado_operacion;

  char elementos [100000] = {'A'};
  int tope_elementos = 100000;

  for (int i = 0; i < tope_elementos; ++i)
    cola_encolar(cola,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = cola_cantidad(cola) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Se encolan  %i elementos, la cantidad de elementos en la cola es correcta: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  cola_destruir(cola);
  return estado_operacion;
}
/*---------------------------------------*/

int main(){
  int pruebas_pasadas = 0;
  int (*funcion_testing[])()={DadaUnaColaVacia_EntoncesEmpiezaVacia,
                              DadaUnaColaVacia_EntoncesNoTieneElementos,                              
                              DadaUnaColaVacia_EntoncesNoSePuedeDesencolar,
                              DadaUnaColaConElementos_EntoncesSePuedeEncolar,
                              DadaUnaColaConElementos_EntoncesSePuedeDesencolar,
                              DadaUnaColaConElementos_EntoncesNoEstaVacia,
                              DadaUnaColaNull_EntoncesNoSePuedeEncolar,
                              DadaUnaColaNull_EntoncesNoSePuedeDesencolar,
                              DadaUnaColaNull_EntoncesEstaVacia,
                              DadaUnaCola_CuandoSeEncolaUnElementoNULL_EntoncesDevuelveOK,
                              DadaUnaColaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElPrimerElemento,
                              DadaUnaColaVariada_CuandoSeEncolanElementos_EntoncesLaCantidadEsCorrecta,
                              DadaUnaColaVariada_CuandoDesencolanTodosLosElementos_EntoncesEstaVacia,
                              DadaUnaColaVariada_CuandoSeEncolanMuchosElementos_EntoncesLaCantidadEsCorrecta};

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