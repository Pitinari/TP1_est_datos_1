#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"
#include "stdio.h"

Expression Expression_create(char *alias, char *sentence, TablaOp operators){
    Expression exp = malloc(sizeof(struct _Exp));
    ExpTree tree =  ExpTree_Generate(sentence, operators);

    if(tree == NULL){
        return NULL;
    }
    
    exp->alias = alias;
    exp->tree = tree;
    exp->inorder = ExpTree_inorder(exp->tree);

    return exp;
}

int Expression_evaluate(Expression exp){
    return ExpTree_evaluate(exp->tree);
}

void Expression_print(Expression exp){
    printf("%s \n", exp->inorder);
}

void Expression_destruir(Expression exp){
    free(exp->alias);
    free(exp->inorder);
    ExpTree_destruir(exp->tree);
}