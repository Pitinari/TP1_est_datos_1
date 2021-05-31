#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"
#include "stdio.h"

struct _Exp {
    char *alias;
    char *inorder;
    ExpTree tree;
};


struct _ListaExp {
	Expression exp;
	struct _ListaExp *sig;		
};


Expression Expression_create(char *alias, char *sentence, TablaOp operators){
    Expression exp = malloc(sizeof(struct _Exp));

    exp->alias = alias;
    exp->tree = ExpTree_Generate(sentence, operators);
    exp->inorder = ExpTree_inorder(exp->tree);

    free(sentence);
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