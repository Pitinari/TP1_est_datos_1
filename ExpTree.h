#include "stdlib.h"

typedef struct _ExpTreeNode *ExpTree;


ExpTree ExpTree_crear();

void ExpTree_destruir(ExpTree nodo);

ExpTree ExpTree_unir(char op,int dato, ExpTree left, ExpTree right);

