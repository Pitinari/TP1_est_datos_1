#include "stdlib.h"
#include "../ExpTree.h"
#include "../Expression.h"
#include "test_Expression.h"
#include "test_ExpTree.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

void test_ListaExp (){
    ListaExp lista = ListaExp_crear();
    assert(lista);

    TablaOp operadores = crear_tabla_operadores();
    
    char *aux = string_aux("1 2 +");
    ListaExp_agregar(lista, Expression_create("prueba",aux,operadores));
    free(aux);
    
    assert(!strcmp(lista->exp[0]->alias,"prueba"));

    aux = string_aux("2 8 ^");
    ListaExp_agregar(lista, Expression_create("test",aux,operadores));
    free(aux);

    assert(!strcmp(lista->exp[1]->alias,"test"));
    assert(!strcmp(lista->exp[1]->inorder,"(2^8)"));

    assert(buscar_alias("test",lista));
    assert(!buscar_alias("falso",lista));

    ListaExp_destruir(lista);
    destruir_tabla_operadores(operadores);

    printf("%s passed\n", __func__);
}

void test_Expression_create () {
    TablaOp operadores = crear_tabla_operadores();

    char *aux = string_aux("1 2 +");
    Expression exp = Expression_create("prueba",aux,operadores);
    free(aux);
    assert(exp);
    
    aux = string_aux("1 2 2");
    assert(!Expression_create("test",aux,operadores));
    free(aux);

    assert(Expression_evaluate(exp) == 3);

    aux = string_aux("test");
    assert(validar_alias(aux) == 1);
    free(aux);
    aux = string_aux("1prueba");
    assert(validar_alias(aux) == 0);
    free(aux);


    Expression_destruir(exp);
    destruir_tabla_operadores(operadores);

    printf("%s passed\n", __func__);
}

void test_Expression () {
    test_ListaExp();
    test_Expression_create();
}