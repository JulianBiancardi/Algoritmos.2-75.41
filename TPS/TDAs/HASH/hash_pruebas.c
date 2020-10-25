#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "hash_iterador.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CAPACIDAD_HASH_PRUEBA 11
#define CLAVE_PRUEBA "A"

#define CANTIDAD_PRUEBAS 24

/*---------------------------------------*/


/*---------------------------------------*/
//TEST
int (*funcion_testing) (void);



int DadoUnHashVacio_EntoncesEmpiezaVacio(){
  printf("#========== Pruebas \033[1;36mhash vacio\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_cantidad(hash) == 0?OK :ERROR;

  //Control de salida
  printf(" •El hash esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashVacio_EntoncesSePuedeInsertar(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  int elemento = 1;

  const char* clave = "A";
  //Llamado a codigo prueba
  estado_operacion = hash_insertar(hash,clave,&elemento);

  //Control de salida
  printf(" •Se intenta insertar en un hash vacio,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashVacio_EntoncesNoSePuedeQuitar(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_quitar(hash,CLAVE_PRUEBA);

  //Control de salida
  printf(" •Se intenta quitar en un hash vacio,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return !estado_operacion;
}
int DadoUnHashVacio_EntoncesNoSePuedeObtenerClaves(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_obtener(hash,CLAVE_PRUEBA) == NULL?OK :ERROR;

  //Control de salida
  printf(" •Se intenta obtener claves en un hash vacio,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashVacio_EntoncesNoContieneElementos(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_contiene(hash,CLAVE_PRUEBA) == false?OK :ERROR;

  //Control de salida
  printf(" •El hash no contiene el elemento con la clave dada: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}


int DadoUnHashConElementos_EntoncesNoEstaVacio(){
  printf("#========== Pruebas \033[1;36mhash con elementos\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);

  //Llamado a codigo prueba
  estado_operacion = hash_cantidad(hash) > 0?OK :ERROR;

  //Control de salida
  printf(" •El hash no esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashConElementos_EntoncesSePuedeInsertar(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);
  //Llamado a codigo prueba
  const char* clave_insertar = "BWM";
  int elemento_insertar = 9;
  estado_operacion =  hash_insertar(hash,clave_insertar,&elemento_insertar);

  //Control de salida
  printf(" •Se intenta insertar en un hash con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnArbolConElementos_EntoncesSePuedeInsertarRepetido(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion1,estado_operacion2;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);


  //Llamado a codigo prueba
  estado_operacion1 = hash_insertar(hash,claves[5],&elementos[5]); //Repetir clave y valor
  estado_operacion2 = hash_insertar(hash,claves[5],&elementos[0]); //Repetir clave 


  //Control de salida
  printf(" •Se intenta insertar insertar  elementos repetidos,se puede: ");
  printf("%s\n",(estado_operacion1 == OK && estado_operacion2 == OK)?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return (estado_operacion1 == OK && estado_operacion2 == OK)?OK : ERROR;
}
int DadoUnHashConElementos_EntoncesSePuedeQuitar(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);

  //Llamado a codigo prueba
  estado_operacion = hash_quitar(hash,claves[tope_elementos - 1]);

  //Control de salida
  printf(" •Se intenta quitar en un hash con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}


int DadoUnHashNull_EntoncesEstaVacio(){
  printf("#========== Pruebas \033[1;36mhash NULL,clave NULL,elemento NULL,iterador NULL\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;

  estado_operacion = hash_cantidad(hash) == 0?OK :ERROR;

  //Control de salida
  printf(" •El hash NULL esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashNull_EntoncesNoSePuedeInsertar(){
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = hash_insertar(hash,CLAVE_PRUEBA,&elemento); 

  //Control de salida
  printf(" •Se intenta insertar en un hash NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return !estado_operacion;
}
int DadoUnHashNull_EntoncesNoSePuedeQuitar(){
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_quitar(hash,CLAVE_PRUEBA);

  //Control de salida
  printf(" •Se intenta quitar en un hash NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return !estado_operacion;
}
int DadoUnHashNull_EntoncesNoSePuedeObtenerClaves(){
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_obtener(hash,CLAVE_PRUEBA) == NULL?OK :ERROR;

  //Control de salida
  printf(" •Se intenta obtener claves en un hash NULL,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashNull_EntoncesNoContieneElementos(){
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_contiene(hash,CLAVE_PRUEBA) == false?OK :ERROR;

  //Control de salida
  printf(" •El hash NULL no contiene el elemento con la clave dada: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHash_CuandoSeInsertaUnElemenetoNull_EntoncesDevuelveOK(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_insertar(hash,CLAVE_PRUEBA,NULL); 

  //Control de salida
  printf(" •Se intenta insertar un elemento NULL,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHash_CuandoSeInsertaUnElemenetoConClaveNull_EntoncesDevuelveERROR(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  int elemento = 1;

  //Llamado a codigo prueba
  estado_operacion = hash_insertar(hash,NULL,&elemento); 

  //Control de salida
  printf(" •Se intenta insertar un elemento con clave NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return !estado_operacion;
}
int DadaUnHashNull_EntoncesNoSePuedeCrearElIterador(){
  //Inicializacion de entrada
  hash_t* hash = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_iterador_crear(hash) == NULL? OK : ERROR;

  //Control de salida
  printf(" •Se intenta crear el iterador en un hash NULL,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}
int DadoUnIteradorNull_EntoncesNoTieneSiguiente(){
  //Inicializacion de entrada
  hash_iterador_t* iterador = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_iterador_tiene_siguiente(iterador)? ERROR : OK;

  //Control de salida
  printf(" •Un iterador NULL no tiene siguiente: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}
int DadoUnIteradorNull_EntoncesNoPuedeAvanzar(){
  //Inicializacion de entrada
  hash_iterador_t* iterador = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = hash_iterador_siguiente(iterador) == NULL? OK : ERROR;

  //Control de salida
  printf(" •Se intenta mover un iterador NULL,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}


int DadoUnHashVariado_CuandoSeObtieneLaClave_EntoncesSeDevuelveElElemento(){
  printf("#========== Pruebas \033[1;36mhash variado\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);
  
  for(int i = 0;i < 5;i++)
    hash_quitar(hash,claves[i]);

  //Llamado a codigo prueba
  estado_operacion = hash_obtener(hash,claves[tope_elementos - 1]) == &elementos[tope_elementos -1]?OK : ERROR;

  //Control de salida
  printf(" •Se realizan operaciones con el hash,la clave obtenida es correcta: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashVariado_EntoncesContieneLaClaveDada(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]);
  
  for(int i = 0;i < 5;i++)
    hash_quitar(hash,claves[i]);

  //Llamado a codigo prueba
  estado_operacion = hash_contiene(hash,claves[5]) == true?OK : ERROR;

  //Control de salida
  printf(" •Se realizan operaciones con el hash,la clave dada esta contenida: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadoUnHashVariado_CuandoSeInsertanMuchosElementos_EntoncesSeReHashea(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;
  const char* claves_prueba[30]; //el que se utiliza para comparar 

  for(int j = 0; j < 3 ;j++){
    for (int i = 0; i < tope_elementos;i++)
      hash_insertar(hash,claves[i] + j,&elementos[i]);
  }
  
  hash_iterador_t* iterador = hash_iterador_crear(hash);
  int j = 0;
  while(hash_iterador_tiene_siguiente(iterador)){
    claves_prueba [j] = (char*)hash_iterador_siguiente(iterador);
    j++;
  }

  //Llamado a codigo prueba
  bool estado_operacion1 = strcmp(claves_prueba[1],claves[6]) == 0;
  bool estado_operacion2 = strcmp(claves_prueba[19],claves[4]) == 0;
  bool estado_operacion3 = hash_contiene(hash,claves[5]);
  bool estado_operacion4 = (*(int*)hash_obtener(hash,claves[tope_elementos - 1])) == elementos[tope_elementos -1];

  //Control de salida
  printf(" •Se insertan muchos elementos en el hash,se producen rehash y el hash final es correcto: ");
  printf("%s\n",(estado_operacion1 && estado_operacion2 && estado_operacion3 && estado_operacion4)?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_iterador_destruir(iterador);
  hash_destruir(hash);
  return (estado_operacion1 && estado_operacion2 && estado_operacion3 && estado_operacion4)?OK : ERROR;
}
int DadoUnHashVariado_CuandoSeQuitanTodasLasClaves_EntoncesEstaVacio(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);
  int estado_operacion;
  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","KLT"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;

  for(int j = 0; j < 3 ;j++){
    for (int i = 0; i < tope_elementos;i++)
      hash_insertar(hash,claves[i] + j,&elementos[i]);
  }
  for(int j = 0; j < 3 ;j++){
    for (int i = 0; i < tope_elementos;i++)
      hash_quitar(hash,claves[i] + j); 
  }

  //Llamado a codigo prueba
  estado_operacion = hash_cantidad(hash) == 0?OK :ERROR;

  //Control de salida
  printf(" •Se borraron todas las claves,el hash esta vacio: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_destruir(hash);
  return estado_operacion;
}
int DadaUnHashVariada_CuandoSeIteraExternamente_EntoncesLasClavesSonCorrectas(){
  //Inicializacion de entrada
  hash_t* hash = hash_crear(NULL,CAPACIDAD_HASH_PRUEBA);

  const char* claves [10] = {"ABR","FTE","HFR","QWE","ASD","CDS","MNB","KJL","IOP","XXX"}; 
  int elementos[10] =       {  2  ,  4  ,  1  ,  5  ,  3  ,  8  ,  6  ,  7  ,  0  , 20  };
  int tope_elementos = 10;
  const char* claves_prueba[10]; //el que se utiliza para comparar 

  for (int i = 0; i < tope_elementos;i++)
    hash_insertar(hash,claves[i],&elementos[i]); 

  hash_iterador_t* iterador = hash_iterador_crear(hash);

  int j = 0;
  while(hash_iterador_tiene_siguiente(iterador)){
    claves_prueba [j] = (char*)hash_iterador_siguiente(iterador);
    j++;
  }

  //Llamado a codigo prueba
  bool estado_operacion1 = strcmp(claves_prueba[5],claves[2]) == 0;
  bool estado_operacion2 = strcmp(claves_prueba[9],claves[5]) == 0;

  //Control de salida
  printf(" •Se itera externamente,las claves son correctas: ");
  printf("%s\n",(estado_operacion1 && estado_operacion2)?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  hash_iterador_destruir(iterador);
  hash_destruir(hash);
  return (estado_operacion1 && estado_operacion2)?OK : ERROR;
}

/*---------------------------------------*/

int main(){
  int pruebas_pasadas = 0;
  int (*funcion_testing[])()={DadoUnHashVacio_EntoncesEmpiezaVacio,
  
                              DadoUnHashVacio_EntoncesSePuedeInsertar,                             
                              DadoUnHashVacio_EntoncesNoSePuedeQuitar,
                              DadoUnHashVacio_EntoncesNoSePuedeObtenerClaves, 
                              DadoUnHashVacio_EntoncesNoContieneElementos,

                              DadoUnHashConElementos_EntoncesNoEstaVacio,
                              DadoUnHashConElementos_EntoncesSePuedeInsertar,
                              DadoUnArbolConElementos_EntoncesSePuedeInsertarRepetido,
                              DadoUnHashConElementos_EntoncesSePuedeQuitar,

                              DadoUnHashNull_EntoncesEstaVacio,
                              DadoUnHashNull_EntoncesNoSePuedeInsertar,
                              DadoUnHashNull_EntoncesNoSePuedeQuitar,
                              DadoUnHashNull_EntoncesNoSePuedeObtenerClaves,
                              DadoUnHashNull_EntoncesNoContieneElementos,
                              DadoUnHash_CuandoSeInsertaUnElemenetoNull_EntoncesDevuelveOK,
                              DadoUnHash_CuandoSeInsertaUnElemenetoConClaveNull_EntoncesDevuelveERROR,
                              DadaUnHashNull_EntoncesNoSePuedeCrearElIterador,
                              DadoUnIteradorNull_EntoncesNoTieneSiguiente,
                              DadoUnIteradorNull_EntoncesNoPuedeAvanzar,

                              DadoUnHashVariado_CuandoSeObtieneLaClave_EntoncesSeDevuelveElElemento,
                              DadoUnHashVariado_EntoncesContieneLaClaveDada,
                              DadoUnHashVariado_CuandoSeInsertanMuchosElementos_EntoncesSeReHashea,
                              DadoUnHashVariado_CuandoSeQuitanTodasLasClaves_EntoncesEstaVacio,
                              DadaUnHashVariada_CuandoSeIteraExternamente_EntoncesLasClavesSonCorrectas};

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