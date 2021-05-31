#include "stdlib.h"
#include "operadores.h"
#include "string.h"
#include "math.h"

int suma(int *args){
  return args[0]+args[1];
}

int resta(int *args){
  return args[0]-args[1];
}

int opuesto(int *args){
  return -(*args);
}

int producto(int *args){
  return args[0]*args[1];
}

int division(int *args){
  // decision completamente arbitraria para que no crashee el programa
  if(args[1] == 0){
    return 0;
  }
  return args[0]/args[1];
}

int modulo(int *args){
  return args[0] % args[1];
}

int potencia(int *args){
  return pow(args[0], args[1]);
}

void destruir_tabla_operadores(TablaOp tabla){
  if(tabla == NULL){
    return;
  }
  destruir_tabla_operadores(tabla->sig);
  // sera necesaria esta linea?
  free(tabla->op->simbolo);
  free(tabla->op);
  free(tabla);
}

Operador buscar_operador(char *simbolo, TablaOp tabla){
  while(tabla != NULL){
    if(strcmp(tabla->op->simbolo, simbolo) == 0) {
      return tabla->op;
    }
    tabla = tabla->sig;
  }
  return NULL;
}

TablaOp cargar_operador(TablaOp indice,char sim[],int ari,FuncionEvaluacion func) {
  Operador opAux;
  opAux = (struct _Op*)malloc(sizeof(struct _Op));
  opAux->simbolo = sim;
  opAux->aridad = ari;
  opAux->evaluador = func;
  
  TablaOp new = malloc(sizeof(struct _TablaOp));
  new->op = opAux;
  new->sig = indice;

  return new;
}

TablaOp crear_tabla_operadores (){
  TablaOp tabla = NULL;

  tabla = cargar_operador(tabla , "+" , 2 , suma);
  tabla = cargar_operador(tabla , "-" , 2 , resta);
  tabla = cargar_operador(tabla , "--" , 1 , opuesto);
  tabla = cargar_operador(tabla , "*" , 2 , producto);
  tabla = cargar_operador(tabla , "/" , 2 , division);
  tabla = cargar_operador(tabla , "%" , 2 , modulo);
  tabla = cargar_operador(tabla , "^" , 2 , potencia);

  return tabla;
}