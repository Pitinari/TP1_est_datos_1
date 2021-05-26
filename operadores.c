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

TablaOp agregar_operador (TablaOp indice,Operador operador){
  indice->sig = malloc(sizeof(_TablaOp));
  indice->sig->op = operador;
  indice->sig->sig = NULL;
  return indice->sig;
}

TablaOp iniciar_tabla_operadores (){
  typedef struct _TablaOp *tabla;
  typedef struct _TablaOp *indice;
  indice = tabla;

  typedef struct _Op *opSuma;
  opSuma = malloc(sizeof(typedef struct _Op));
  opSuma->simbolo = malloc(sizeof(char));
  *(opSuma->simbolo) = '+';
  opSuma->aridad = 2;
  opSuma->evaluador = suma;

  indice->op = opSuma;

  typedef struct _Op *opResta;
  opResta = malloc(sizeof(typedef struct _Op));
  opResta->simbolo = malloc(sizeof(char));
  *(opResta->simbolo) = '-';
  opResta->aridad = 2;
  opResta->evaluador = resta;

  indice = agregar_operador(indice,opResta);

  typedef struct _Op *opOpuesto;
  opOpuesto = malloc(sizeof(typedef struct _Op));
  opOpuesto->simbolo = malloc(sizeof(char));
  *(opOpuesto->simbolo) = '--';
  opOpuesto->aridad = 1;
  opOpuesto->evaluador = opuesto;

  indice = agregar_operador(indice,opOpuesto);

  typedef struct _Op *opProducto;
  opProducto = malloc(sizeof(typedef struct _Op));
  opProducto->simbolo = malloc(sizeof(char));
  *(opProducto->simbolo) = '*';
  opProducto->aridad = 2;
  opProducto->evaluador = producto;

  indice = agregar_operador(indice,opProducto);

  typedef struct _Op *opDivision;
  opDivision = malloc(sizeof(typedef struct _Op));
  opDivision->simbolo = malloc(sizeof(char));
  *(opDivision->simbolo) = '/';
  opDivision->aridad = 2;
  opDivision->evaluador = division;

  indice = agregar_operador(indice,opDivision);

  typedef struct _Op *opModulo;
  opModulo = malloc(sizeof(typedef struct _Op));
  opModulo->simbolo = malloc(sizeof(char));
  *(opModulo->simbolo) = '|';
  opModulo->aridad = 1;
  opModulo->evaluador = modulo;

  indice = agregar_operador(indice,opModulo);

  typedef struct _Op *opPotencia;
  opPotencia = malloc(sizeof(typedef struct _Op));
  opPotencia->simbolo = malloc(sizeof(char));
  *(opPotencia->simbolo) = '^';
  opPotencia->aridad = 2;
  opPotencia->evaluador = potencia;

  indice = agregar_operador(indice,opPotencia);

  return tabla;
}