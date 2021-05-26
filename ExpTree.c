#include "stdlib.h"
#include "ExpTree.h"

typedef struct _ExpTreeNode {
    char op;
    int value;
    struct  _ExpTreeNode *right;
    struct  _ExpTreeNode *left;
};

ExpTree btree_crear() { return NULL; }

void ExpTree_destruir(ExpTree nodo) {
    if (nodo != NULL) {
        ExpTree_destruir(nodo->left);
        ExpTree_destruir(nodo->right);
        free(nodo);
    }
}

ExpTree ExpTree_unir(char op,int dato, ExpTree left, ExpTree right) {
  ExpTree nuevoNodo = malloc(sizeof(struct _ExpTreeNode));
  assert(nuevoNodo != NULL);
  nuevoNodo->op = op;
  nuevoNodo->value = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}