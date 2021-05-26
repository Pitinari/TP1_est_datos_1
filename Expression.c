#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"

typedef struct _Exp {
    char *alias;
    char *sentence;
    ExpTree tree;
};


Expression Expression_create(char *alias, char *sentence){
    Expression exp = malloc(sizeof(struct _Exp));

    exp->alias = alias;
    exp->sentence = sentence;

    // TODO:
    // exp->tree = parse_expression(sentence)

    return exp;
}