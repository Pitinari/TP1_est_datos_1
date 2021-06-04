#include "stdio.h"
#include "stdlib.h"
#include "test_ExpTree.h"
#include "../ExpTree.h"
#include "../operadores.h"
#include "string.h"
#include "assert.h"

void test_stack (){
    TablaOp operadores = crear_tabla_operadores();
    ExpNodeStack stack = NULL;

    ExpTree tree1 = ExpTree_Generate("1 7 - 8 ^",operadores);;
    ExpTree tree2 = ExpTree_Generate("1 2 +",operadores);

    stack = push(tree1 , stack);
    assert(top(stack) == tree1);

    stack = push(tree2 , stack);
    assert(top(stack) == tree2);

    stack = pop(stack);
    assert(top(stack) == tree1);

    stack = pop(stack);
    assert(!stack);
    destruir_tabla_operadores(operadores);
    printf("hecho\n");
}

void test_ExpTree_Generate (){
    TablaOp tabla = crear_tabla_operadores();

    assert(!ExpTree_Generate("1 2 2 +",tabla));
    ExpTree tree1;
    assert(!(tree1 = ExpTree_Generate("1 + +",tabla)));
    ExpTree tree2;
    assert(tree2 = ExpTree_Generate("1 2 + 2 *",tabla));

    assert(!strcmp(ExpTree_inorder(tree1),""));
    assert(!strcmp(ExpTree_inorder(tree2),"1+2*2"));

    assert(tree1 = ExpTree_Generate("8 3 %",tabla));

    assert(ExpTree_evaluate(tree1) == 2);
    assert(ExpTree_evaluate(tree2) == 6);

    ExpTree_destruir(tree1);
    ExpTree_destruir(tree2);
}

void test_cant_digitos (){
    assert(cant_digitos(0) == 1);
    assert(cant_digitos(45) == 2);
    assert(cant_digitos(-100) == 3);
}

void test_Exptree (){
    test_stack();
    test_ExpTree_Generate();
    test_cant_digitos();
}

