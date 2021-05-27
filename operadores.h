#include "stdlib.h"

typedef struct _Op *Operador;

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

// Operador buscar_operador(char *simbolo, TablaOperadores tabla)

// Destruye la tabla y libera la memoria de cada operador individual
// void tablaOperadores_destruir(TablaOperadores tabla)