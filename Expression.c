#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"


Expression Expression_create(char *alias, char *sentence){
    Expression exp = malloc(sizeof(struct _Exp));

    exp->alias = alias;
    exp->sentence = sentence;

    exp->tree = parse_expression(sentence);

    return exp;
}

int Expression_evaluate(Expression exp){
    return ExpTree_evaluate(exp->tree);
}

void Expression_print(Expression exp){
    char* inorder = ExpTree_inorder(exp->tree);

    printf("%s \n", inorder);

    free(inorder);
}

void Expression_destruir(Expression exp){
    free(exp->alias);
    free(exp->sentence);
    ExpTree_destruir(exp->tree);
}