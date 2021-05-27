#include "stdlib.h"
#include "operadores.h"

typedef int (* FuncionEvaluacion) (int *args);

typedef struct _Op{
    char *simbolo;
    int aridad;
    FuncionEvaluacion evaluador;
};

typedef struct _TablaOp{
    Operador op;
    struct _TablaOp *sig;
};

int suma(int *args){
  return args[0]+args[1];
}

int resta(int *args){
  return arg[0]-args[1];
}

int opuesto(int *args){
  return -(*args);
}

int producto(int *args){
  return args[0]*args[1];
}

int division(int *args){
  return args[0]/args[1];
}

int modulo(int *args){
  return abs(*args);
}

int potencia(int *args){
  int valor = args[0];
  for(int i = 0 ; i < args[1] ; i++){
    valor *= args[0];
  }
  return valor;
}

void cargar_operador (TablaOp indice,char sim,int ari,FuncionEvaluacion func){
  Operador opAux;
  opAux = malloc(sizeof(_Op));
  opAux->simbolo = sim;
  opAux->aridad = ari;
  opAux->evaluador = func;

  indice = malloc(sizeof(_TablaOp));
  indice->op = opAux;
  indice->sig = NULL;
  indice = indice->sig;
}

TablaOp crear_tabla_operadores (){
  typedef struct _TablaOp *tabla;
  typedef struct _TablaOp *indice;
  indice = tabla;

  cargar_operador(indice , "+" , 2 , suma);
  cargar_operador(indice , "-" , 2 , resta);
  cargar_operador(indice , "--" , 1 , opuesto);
  cargar_operador(indice , "*" , 2 , producto);
  cargar_operador(indice , "/" , 2 , division);
  cargar_operador(indice , "|" , 1 , modulo);
  cargar_operador(indice , "^" , 2 , potencia);

  return tabla;
}