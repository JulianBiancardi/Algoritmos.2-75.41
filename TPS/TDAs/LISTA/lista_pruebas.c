#include <stdio.h>
#include "lista.h"

/*---------------------------------------*/
//CONSTANTES
#define OK 0
#define ERROR -1

#define CANTIDAD_PRUEBAS 31

/*---------------------------------------*/


/*---------------------------------------*/
//TEST
int (*funcion_testing) (void);

int DadaUnaListaVacia_EntoncesEmpiezaVacia(){
  printf("#========== Pruebas \033[1;36mlista vacia\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_vacia(lista)?OK :ERROR;

  //Control de salida
  printf(" •La lista esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVacia_EntoncesNoTieneElementos(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_elementos(lista) == 0?OK : ERROR;

  //Control de salida
  printf(" •No hay elementos en la lista: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVacia_EntoncesNoSePuedeBorrar(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_borrar(lista);

  //Control de salida
  printf(" •Se intenta borrar en una lista vacia,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaVacia_EntoncesNoSePuedeBorrarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_borrar_de_posicion(lista,10);

  //Control de salida
  printf(" •Se intenta borrar en una posicion de una lista vacia,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaVacia_EntoncesSePuedeInsertar(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elemento ='A';

  //Llamado a codigo prueba
  estado_operacion = lista_insertar(lista,&elemento);

  //Control de salida
  printf(" •Se intenta insertar en una lista vacia,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVacia_EntoncesSePuedeInsertarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elemento ='A';

  //Llamado a codigo prueba
  estado_operacion = lista_insertar_en_posicion(lista,&elemento,10);

  //Control de salida
  printf(" •Se intenta insertar en una posicion de una lista vacia,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}

int DadaUnaListaConElementos_EntoncesSePuedeInsertar(){
  printf("#========== Pruebas \033[1;36mlista con elementos\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = lista_insertar(lista,&elementos[tope_elementos]);

  //Control de salida
  printf(" •Se intenta insertar en una lista con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaConElementos_EntoncesSePuedeInsertarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = lista_insertar_en_posicion(lista,&elementos[tope_elementos],0);

  //Control de salida
  printf(" •Se intenta insertar en una posicion de una lista con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaConElementos_EntoncesSePuedeBorrar(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);  

  //Llamado a codigo prueba
  estado_operacion = lista_borrar(lista);

  //Control de salida
  printf(" •Se intenta borrar en una lista con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaConElementos_EntoncesSePuedeBorrarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);  

  //Llamado a codigo prueba
  estado_operacion = lista_borrar_de_posicion(lista,0);

  //Control de salida
  printf(" •Se intenta borrar en una posicion de una lista con elementos,se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaConElementos_EntoncesNoEstaVacia(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]); 

  //Llamado a codigo prueba
  estado_operacion = lista_vacia(lista)?OK :ERROR;

  //Control de salida
  printf(" •La lista no esta vacia: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}

int DadaUnIteradorExterno_CuandoSeEstaEnUnaListaConElementos_EntoncesHayMasElementos(){
  printf("#========== Pruebas \033[1;36miterador externo\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);

  lista_iterador_t* iterador = lista_iterador_crear(lista);
  //Llamado a codigo prueba
  estado_operacion = lista_iterador_tiene_siguiente(iterador)? OK : ERROR; 

  //Control de salida
  printf(" •Se esta en una lista con elementos,se pregunta al iterador externo si hay mas elementos: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnIteradorExterno_CuandoSeEstaEnUnaListaVacia_EntoncesNoHayMasElementos(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  lista_iterador_t* iterador = lista_iterador_crear(lista);
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_iterador_tiene_siguiente(iterador)? ERROR : OK; 

  //Control de salida
  printf(" •Se esta en una lista vacia,se pregunta al iterador externo si hay mas elementos: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnIteradorExterno_CuandoSeAvanzaEnUnaLIstaConElementos_EntoncesDevuelveElElementoActual(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  
  int estado_operacion;
  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);
  lista_iterador_t* iterador = lista_iterador_crear(lista);
  //Llamado a codigo prueba
  estado_operacion = (*(char*)lista_iterador_siguiente(iterador)) == elementos[0]? OK : ERROR; 

  //Control de salida
  printf(" •Se esta en una lista con elementos,se mueve iterador externo, el elemento es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
  return estado_operacion;
}

int DadaUnaListaNull_EntoncesNoSePuedeInsertar(){
  printf("#========== Pruebas \033[1;36mlista NULL,iterador NULL,elemento NULL\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  lista_t* lista = NULL;
  char elemento = 'A';
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_insertar(lista,&elemento); 

  //Control de salida
  printf(" •Se intenta insertar en una lista NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaNull_EntoncesNoSePuedeInsertarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = NULL;
  char elemento = 'A';
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_insertar_en_posicion(lista,&elemento,10); 

  //Control de salida
  printf(" •Se intenta insertar en una posicion de una lista NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaNull_EntoncesNoSePuedeBorrar(){
  //Inicializacion de entrada
  lista_t* lista = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_borrar(lista);

  //Control de salida
  printf(" •Se intenta borrar en una lista NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaNull_EntoncesNoSePuedeBorrarEnPosicion(){
  //Inicializacion de entrada
  lista_t* lista = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_borrar_de_posicion(lista,10);

  //Control de salida
  printf(" •Se intenta borrar en una lista NULL,no se puede: ");
  printf("%s\n",estado_operacion == ERROR?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return !estado_operacion;
}
int DadaUnaListaNull_EntoncesEstaVacia(){
  //Inicializacion de entrada
  lista_t* lista = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_vacia(lista)?OK :ERROR;

  //Control de salida
  printf(" •La lista NULL esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");
  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaLista_CuandoSeEncolaUnElementoNULL_EntoncesDevuelveOK(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_insertar(lista,NULL); 

  //Control de salida
  printf(" •Se intenta insertar un elemento NULL: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaNull_EntoncesNoSePuedeCrearElIterador(){
  //Inicializacion de entrada
  lista_t* lista = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_iterador_crear(lista) == NULL? OK : ERROR;

  //Control de salida
  printf(" •Se intenta crear el iterador en una lista NULL,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}
int DadoUnIteradorNull_EntoncesNoTieneSiguiente(){
  //Inicializacion de entrada
  lista_iterador_t* iterador = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_iterador_tiene_siguiente(iterador)? ERROR : OK;

  //Control de salida
  printf(" •Un iterador NULL no tiene un siguiente: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}
int DadoUnIteradorNull_EntoncesNoPuedeAvanzar(){
  //Inicializacion de entrada
  lista_iterador_t* iterador = NULL;
  int estado_operacion;

  //Llamado a codigo prueba
  estado_operacion = lista_iterador_siguiente(iterador) == NULL? OK : ERROR;

  //Control de salida
  printf(" •Se intenta mover un iterador NULL,no se puede: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  return estado_operacion;
}

int DadaUnaListaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElUltimoElemento(){
  printf("#========== Pruebas \033[1;36mlista variada\033[0;0m: ==========#\n");
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]); 

  for(int i = 0;i < 5;i++)
    lista_borrar(lista);

  //Llamado a codigo prueba
  estado_operacion = lista_ultimo(lista) == &elementos[4]?OK : ERROR;

  //Control de salida
  printf(" •Se borran elementos,el ultimo elemento es correcto: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeInsertanElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);

  //Llamado a codigo prueba
  estado_operacion = lista_elementos(lista) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Hay %i elementos almacenados en la lista: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeBorranTodosLosElementos_EntoncesEstaVacia(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos;i++)
    lista_insertar(lista,&elementos[i]);

  for (int i = 0; i < tope_elementos;i++)
    lista_borrar(lista);

  //Llamado a codigo prueba
  estado_operacion = lista_vacia(lista)?OK :ERROR;

  //Control de salida
  printf(" •Se borraron todos los elementos,la lista esta vacia: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeInsertanMuchosElementos_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [100000] = {'A'};
  int tope_elementos = 100000;

  for (int i = 0; i < tope_elementos; ++i)
    lista_insertar(lista,&elementos[i]);



  //Llamado a codigo prueba
  estado_operacion = lista_elementos(lista) == tope_elementos?OK :ERROR;

  //Control de salida
  printf(" •Se insertan  %i elementos, la cantidad de elementos en la lista es correcta: ",tope_elementos);
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeInsertaEnPosicionInvalida_EntoncesSeInsertaAlFinal(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    lista_insertar(lista,&elementos[i]);

  //Llamado a codigo prueba
  lista_insertar_en_posicion(lista,&elementos[2],lista_elementos(lista) + 1);
   estado_operacion = lista_ultimo(lista) == &elementos[2] ?OK :ERROR;

  //Control de salida
  printf(" •Se quiere insertar en una posicion invalida entonces se inserta al final: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeBorraEnPosicionInvalida_EntoncesSeBorraAlFinal(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  char elementos [10] = {'2','o','g','l','A',' ','&','O','P','m'};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    lista_insertar(lista,&elementos[i]);

  //Llamado a codigo prueba
  lista_borrar_de_posicion(lista,lista_elementos(lista) + 1);
   estado_operacion = lista_ultimo(lista) == &elementos[tope_elementos - 2] ?OK :ERROR;

  //Control de salida
  printf(" •Se quiere borrar en una posicion invalida entonces se borra al final: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
void aumentar_elementos(void* elemento){
  if(elemento != NULL)
    (*(int *)elemento) = (*(int *)elemento) * 2;
}
int DadaUnaListaVariada_CuandoSeIteraInternamente_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;

  int elementos [10] = {1,4,5,6,7,0,10,11,12,21};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    lista_insertar(lista,&elementos[i]); 

  //Llamado a codigo prueba
  lista_con_cada_elemento(lista,(*aumentar_elementos));

  estado_operacion = (*(int*)lista_elemento_en_posicion(lista,3)) == elementos[3] ?OK :ERROR;
  estado_operacion = (*(int*)lista_elemento_en_posicion(lista,2)) == elementos[2] ?OK :ERROR;
  estado_operacion = (*(int*)lista_elemento_en_posicion(lista,(size_t)tope_elementos - 1)) == elementos[tope_elementos - 1] ?OK :ERROR;

  //Control de salida
  printf(" •Se itera internamente aumentando los elementos,los elementos en la lista son correctos: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_destruir(lista);
  return estado_operacion;
}
int DadaUnaListaVariada_CuandoSeIteraExternamente_EntoncesLaCantidadEsCorrecta(){
  //Inicializacion de entrada
  lista_t* lista = lista_crear();
  int estado_operacion;
  int contador = 0;

  int elementos [10] = {1,4,5,6,7,0,10,11,12,21};
  int tope_elementos = 10;

  for (int i = 0; i < tope_elementos; ++i)
    lista_insertar(lista,&elementos[i]); 

  lista_iterador_t* iterador = lista_iterador_crear(lista);

  while(lista_iterador_tiene_siguiente(iterador))
    contador+= (*(int*)lista_iterador_siguiente(iterador));

  //Llamado a codigo prueba
  estado_operacion = contador == (1+4+5+6+7+0+10+11+12+21)?OK : ERROR;

  //Control de salida
  printf(" •Se itera externamente sumando los elementos,la cantidad es correcta: ");
  printf("%s\n",estado_operacion == OK?"\033[1;32mOK :)\033[0;0m" :"\033[1;31mERROR\033[0;0m");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
  return estado_operacion;
}

/*---------------------------------------*/

int main(){
  int pruebas_pasadas = 0;
  int (*funcion_testing[])()={DadaUnaListaVacia_EntoncesEmpiezaVacia,
                              DadaUnaListaVacia_EntoncesNoTieneElementos,                              
                              DadaUnaListaVacia_EntoncesNoSePuedeBorrar,
                              DadaUnaListaVacia_EntoncesNoSePuedeBorrarEnPosicion,
                              DadaUnaListaVacia_EntoncesSePuedeInsertar,
                              DadaUnaListaVacia_EntoncesSePuedeInsertarEnPosicion,

                              DadaUnaListaConElementos_EntoncesSePuedeInsertar,
                              DadaUnaListaConElementos_EntoncesSePuedeInsertarEnPosicion,
                              DadaUnaListaConElementos_EntoncesSePuedeBorrar,
                              DadaUnaListaConElementos_EntoncesSePuedeBorrarEnPosicion,
                              DadaUnaListaConElementos_EntoncesNoEstaVacia,

                              DadaUnIteradorExterno_CuandoSeEstaEnUnaListaConElementos_EntoncesHayMasElementos,
                              DadaUnIteradorExterno_CuandoSeEstaEnUnaListaVacia_EntoncesNoHayMasElementos,
                              DadaUnIteradorExterno_CuandoSeAvanzaEnUnaLIstaConElementos_EntoncesDevuelveElElementoActual,

                              DadaUnaListaNull_EntoncesNoSePuedeInsertar,
                              DadaUnaListaNull_EntoncesNoSePuedeInsertarEnPosicion,
                              DadaUnaListaNull_EntoncesNoSePuedeBorrar,
                              DadaUnaListaNull_EntoncesNoSePuedeBorrarEnPosicion,
                              DadaUnaListaNull_EntoncesEstaVacia,
                              DadaUnaLista_CuandoSeEncolaUnElementoNULL_EntoncesDevuelveOK,
                              DadaUnaListaNull_EntoncesNoSePuedeCrearElIterador,
                              DadoUnIteradorNull_EntoncesNoTieneSiguiente,
                              DadoUnIteradorNull_EntoncesNoPuedeAvanzar,

                              DadaUnaListaVariada_CuandoSePideElElemento_EntoncesSeDevuelveElUltimoElemento,
                              DadaUnaListaVariada_CuandoSeInsertanElementos_EntoncesLaCantidadEsCorrecta,
                              DadaUnaListaVariada_CuandoSeBorranTodosLosElementos_EntoncesEstaVacia,
                              DadaUnaListaVariada_CuandoSeInsertanMuchosElementos_EntoncesLaCantidadEsCorrecta,
                              DadaUnaListaVariada_CuandoSeInsertaEnPosicionInvalida_EntoncesSeInsertaAlFinal,
                              DadaUnaListaVariada_CuandoSeBorraEnPosicionInvalida_EntoncesSeBorraAlFinal,
                              DadaUnaListaVariada_CuandoSeIteraInternamente_EntoncesLaCantidadEsCorrecta,
                              DadaUnaListaVariada_CuandoSeIteraExternamente_EntoncesLaCantidadEsCorrecta};

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
