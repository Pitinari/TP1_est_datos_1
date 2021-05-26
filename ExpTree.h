#include "stdlib.h"

typedef struct _ExpTreeNode *ExpTree;


ExpTree ExpTree_crear();

void ExpTree_destruir(ExpTree nodo);

ExpTree ExpTree_unir(char op,int dato, ExpTree left, ExpTree right);

ExpTree ExpTree_Parse(char *sentence);

int ExpTree_evaluate(ExpTree tree)

