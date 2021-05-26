#include "stdlib.h"




typedef int (* FuncionEvaluacion) (int *args);


int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int producto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);


void cargar_operador();