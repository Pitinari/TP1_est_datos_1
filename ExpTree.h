#ifndef EXPTREE_H
#define EXPTREE_H

#include "stdlib.h"
#include "operadores.h"
#include "string.h"

struct _ExpTreeNode {
    Operador op;
    int value;
    struct  _ExpTreeNode *right;
    struct  _ExpTreeNode *left;
};

struct _ExpNodeStack {
    struct _ExpTreeNode *node;
    struct _ExpNodeStack *prev;
};

typedef struct _ExpTreeNode *ExpTree;

typedef struct _ExpNodeStack *ExpNodeStack;

ExpTree ExpTree_crear();

void ExpTree_destruir(ExpTree nodo);

ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack, TablaOp tabla);

ExpTree ExpTree_Generate(char *sentence, TablaOp operators);

char *ExpTree_inorder(ExpTree tree);

int ExpTree_evaluate(ExpTree tree);

#endif