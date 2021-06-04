#include "stdlib.h"
#include "operadores.h"
#include "string.h"
#include "math.h"

//suma : *int -> int
int suma(int *args){
  return args[0]+args[1];
}

//resta : *int -> int
int resta(int *args){
  return args[0]-args[1];
}

//resta : *int -> int
int opuesto(int *args){
  return -(*args);
}

//resta : *int -> int
int producto(int *args){
  return args[0]*args[1];
}

//resta : *int -> int
int division(int *args){
  // decision completamente arbitraria para que no crashee el programa
  if(args[1] == 0){
    return 0;
  }
  return args[0]/args[1];
}

//resta : *int -> int
int modulo(int *args){
  return args[0] % args[1];
}

//resta : *int -> int
int potencia(int *args){
  return pow(args[0], args[1]);
}

//destruir_tabla_operadores : *(struct _TablaOp) -> Nada
void destruir_tabla_operadores(TablaOp tabla){
  if(tabla == NULL){
    return;
  }
  destruir_tabla_operadores(tabla->sig);
  free(tabla->op);
  free(tabla);
}

//buscar_operador : *char -> *(struct _TablaOp) -> *(_Op)
//Compara el simbolo pasado como *char con cada uno de los simbolos 
//dentro de los operadores de la tabla y devuelve el 
//operador que sea igual, en caso de no encontrar devuelve null
Operador buscar_operador(char *simbolo, TablaOp tabla){
  while(tabla != NULL){
    if(strcmp(tabla->op->simbolo, simbolo) == 0) {
      return tabla->op;
    }
    tabla = tabla->sig;
  }
  return NULL;
}

//cargar_operador : *(struct _TablaOp) -> *char -> int -> FuncionEvaluacion -> *(struct _TablaOp)
//Crea un operador con los datos datos y luego de crear un nuevo nodo de 
// la tabla, hace que apunte al operador y coloca el nodo al principio de la lista
TablaOp cargar_operador(TablaOp indice,char sim[],int ari,FuncionEvaluacion func) {
  Operador opAux;
  opAux = malloc(sizeof(struct _Op));
  opAux->simbolo = sim;
  opAux->aridad = ari;
  opAux->evaluador = func;
  
  TablaOp new = malloc(sizeof(struct _TablaOp));
  new->op = opAux;
  new->sig = indice;

  return new;
}

//crear_tabla_operadores : Nada -> *(_TablaOp)
//Inicializa un puntero NULL para nuestra futura tabla y la crea agregando
//los operadores con cargar_operador
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