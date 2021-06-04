#include "stdio.h"
#include "stdlib.h"
#include "../ExpTree.h"
#include "../operadores.h"
#include "string.h"
#include "assert.h"

void test_stack (){

    ExpNodeStack stack = NULL;

    ExpTree tree1 = ExpTree_crear();
    ExpTree tree2 = ExpTree_Generate("1 2 +");

    stack = push(tree1 , stack);
    assert(top(stack) == tree1);

    stack = push(tree2 , stack);
    assert(top(stack) == tree2);

    stack = pop(stack);
    assert(top(stack) == tree1);

    stack = pop(stack);
    assert(!stack);
}

void test_ExpTree (){
    
}