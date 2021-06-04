#include "stdio.h"
#include "stdlib.h"
#include "test_ExpTree.h"
#include "../ExpTree.h"
#include "../operadores.h"
#include "string.h"
#include "assert.h"

char *string_aux (char* string){
    char *string_din = malloc(sizeof(char)*(strlen(string)+1));
    strcpy(string_din,string);
    return string_din;
}

void test_stack (){
    TablaOp operadores = crear_tabla_operadores();
    ExpNodeStack stack = NULL;
    char *aux = string_aux("1 7 - 8 ^");
    ExpTree tree1 = ExpTree_Generate(aux,operadores);
    free(aux);
    aux = string_aux("1 2 +");
    ExpTree tree2 = ExpTree_Generate(aux,operadores);
    free(aux);

    stack = push(tree1 , stack);
    assert(top(stack) == tree1);

    stack = push(tree2 , stack);
    assert(top(stack) == tree2);

    stack = pop(stack);
    assert(top(stack) == tree1);

    stack = pop(stack);
    assert(!stack);
    destruir_tabla_operadores(operadores);
    printf("%s passed\n", __func__);
}

void test_ExpTree_Generate (){
    TablaOp tabla = crear_tabla_operadores();

    char *aux = string_aux("1 2 2 +");
    assert(!ExpTree_Generate(aux,tabla));
    free(aux);
    ExpTree tree1;
    aux = string_aux("1 + +");
    assert(!(tree1 = ExpTree_Generate(aux,tabla)));
    free(aux);
    ExpTree tree2;
    aux = string_aux("1 2 + 2 *");
    assert(tree2 = ExpTree_Generate(aux,tabla));
    free(aux);

    assert(!strcmp(ExpTree_inorder(tree1),""));
    assert(!strcmp(ExpTree_inorder(tree2),"((1+2)*2)"));

    aux = string_aux("8 3 %");
    assert(tree1 = ExpTree_Generate(aux,tabla));
    free(aux);

    assert(ExpTree_evaluate(tree1) == 2);
    assert(ExpTree_evaluate(tree2) == 6);

    ExpTree_destruir(tree1);
    ExpTree_destruir(tree2);
    printf("%s passed\n", __func__);
}

void test_cant_digitos (){
    assert(cant_digitos(0) == 1);
    assert(cant_digitos(45) == 2);
    assert(cant_digitos(-100) == 3);
    printf("%s passed\n", __func__);
}

void test_Exptree (){
    test_stack();
    test_ExpTree_Generate();
    test_cant_digitos();
}

