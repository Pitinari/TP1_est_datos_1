#include "test_operadores.h"
#include "../operadores.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void test_suma(){
  int args[] = {1,2};
  assert(suma(args)==3);
  args[0] = 2;
  args[1] = -5;
  assert(suma(args)==-3);
}

void test_resta(){
  int args[] = {1,2};
  assert(resta(args)==-1);
  args[0] = 2;
  args[1] = -5;
  assert(resta(args)==8);
}

void test_opuesto(){
  int args[] = {1};
  assert(opuesto(args)==-1);
  args[0] = -2;
  assert(opuesto(args)==2);
}

void test_producto(){
  int args[] = {1,2};
  assert(producto(args)==2);
  args[0] = 2;
  args[1] = -5;
  assert(producto(args)==-10);
}

void test_division(){
  int args[] = {1,2};
  assert(division(args)==0);
  args[0] = 2;
  args[1] = 0;
  assert(division(args)==0);
  args[0] = 4;
  args[1] = 2;
  assert(division(args)==2);
}

void test_modulo(){
  int args[] = {3,2};
  assert(suma(args)==1);
  args[0] = 4;
  args[1] = 2;
  assert(suma(args)==0);
}

void test_potencia(){
  int args[] = {1,2};
  assert(suma(args)==1);
  args[0] = 2;
  args[1] = 5;
  assert(suma(args)==32);
}

void test_buscar_operador (){
  TablaOp tabla = crear_tabla_operadores();
  assert(!strcmp(buscar_operador("-",tabla)->simbolo,"-"));
  assert(buscar_operador("*",tabla)->aridad == 2);
  assert(!buscar_operador("8",tabla));
  tabla = NULL;
  assert(!buscar_operador("+",tabla));
  destruir_tabla_operadores(tabla);
}

void test_cargar_operador (){
  TablaOp tabla = NULL;
  cargar_operador(tabla,"/",2,suma);
  cargar_operador(tabla,"-",2,resta);
  assert(!strcmp(tabla->sig->op->simbolo,"/"));
  assert(tabla->sig->op->aridad == 2);
  assert(!strcmp(tabla->op->simbolo,"-"));
  destruir_tabla_operadores(tabla);
}

void test_operadores (){
  test_suma();
  test_resta();
  test_opuesto();
  test_producto();
  test_division();
  test_modulo();
  test_potencia();
  test_buscar_operador ();
  test_cargar_operador ();
}

