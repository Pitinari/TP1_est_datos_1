#include "stdlib.h"
#include "operadores.h"
#include "string.h"

typedef struct _ExpTreeNode *ExpTree;

typedef struct _ExpNodeStack *ExpNodeStack;

ExpTree ExpTree_crear();

void ExpTree_destruir(ExpTree nodo);

ExpTree ExpTree_unir(char op,int dato, ExpTree left, ExpTree right);

ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack,TablaOp tabla);

char *ExpTree_inorder(ExpTree tree);

int ExpTree_evaluate(ExpTree tree);

