#include "stdlib.h"
#include "../ExpTree.h"
#include "../Expression.h"
#include "test_Expression.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

void test_ListaExp (){
    ListaExp lista = ListaExp_crear();
    assert(lista);

    TablaOp operadores = crear_tabla_operadores();
    ListaExp_agregar(lista, Expression_create("prueba","1 2 +",operadores));

    assert(!strcmp(lista->exp[0]->alias,"prueba"));

    ListaExp_agregar(lista, Expression_create("test","2 8 ^",operadores));

    assert(!strcmp(lista->exp[1]->alias,"test"));
    assert(!strcmp(lista->exp[1]->inorder,"2^8"));

    assert(buscar_alias("test",lista));
    assert(!buscar_alias("falso",lista));

    ListaExp_destruir(lista);
    destruir_tabla_operadores(operadores);
}

void test_Expression_create () {
    TablaOp operadores = crear_tabla_operadores();
    Expression exp = Expression_create("prueba","1 2 +",operadores);
    assert(exp);
    assert(!Expression_create("test","1 2 2",operadores));

    assert(Expression_evaluate(exp) == 3);

    Expression_destruir(exp);
    destruir_tabla_operadores(operadores);
}

void test_Expression () {
    test_ListaExp();
    test_Expression_create();
}