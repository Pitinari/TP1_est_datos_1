#ifndef OPERADORES_H
#define OPERADORES_H

#include "stdlib.h"

typedef int (*FuncionEvaluacion) (int *args);

struct _Op{
    char *simbolo;
    int aridad;
    FuncionEvaluacion evaluador;
};

typedef struct _Op *Operador;

struct _TablaOp{
    struct _Op *op;
    struct _TablaOp *sig;
};

typedef struct _TablaOp *TablaOp;

int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int producto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);

TablaOp cargar_operador(TablaOp indice,char sim[],int ari,FuncionEvaluacion func);

TablaOp crear_tabla_operadores();

Operador buscar_operador(char *simbolo, TablaOp tabla);

// Destruye la tabla y libera la memoria de cada operador individual
void destruir_tabla_operadores(TablaOp tabla);

#endif