#include "stdlib.h"
#include "operadores.h"

typedef int (* FuncionEvaluacion) (int *args);

typedef struct _Op{
    char *simbolo;
    int aridad;
    FuncionEvaluacion evaluador;
};

