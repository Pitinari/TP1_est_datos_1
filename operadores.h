#include "stdlib.h"

typedef struct _Op *Operador;

// FIXME: tengo entendido que la def de la estructura no va en los .h, pero es necesario para el compilador no se queje en otros archivos porque no esta def la estructura
typedef struct _Op{
    char *simbolo;
    int aridad;
    FuncionEvaluacion evaluador;
};

typedef int (* FuncionEvaluacion) (int *args);

typedef struct _TablaOp *TablaOp;

int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int producto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);

void cargar_operador(TablaOp indice,char sim,int ari,FuncionEvaluacion func);

TablaOp crear_tabla_operadores ();

Operador buscar_operador(char *simbolo, TablaOp tabla);

// Destruye la tabla y libera la memoria de cada operador individual
void destruir_tabla_operadores(TablaOp tabla);