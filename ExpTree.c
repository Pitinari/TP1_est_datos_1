#include "stdlib.h"
#include "ExpTree.h"
#include "operadores.h"

typedef struct _ExpTreeNode {
    Operador op;
    int value;
    struct  _ExpTreeNode *right;
    struct  _ExpTreeNode *left;
};

ExpTree ExpTree_crear() { return NULL; }

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

typedef struct _ExpNodeStack {
    struct _ExpTreeNode *node;
    struct _ExpNodeStack *sig;
    struct _ExpNodeStack *prev;
};

ExpNodeStack push(ExpTree node, ExpNodeStack stack){
    ExpNodeStack new = malloc(sizeof(struct _ExpNodeStack));

    new->node = node;
    new->sig = NULL;
    new->prev = stack;

    return new;
}

ExpTree pop(ExpNodeStack stack){

    ExpTree n = stack->node;

    stack = stack->prev;

    free(stack->sig);

    return n;

}

ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack, TablaOp tabla){
    char *token;
    while(token = strtock(sentence, " ")){
        Operador op = buscar_operador(token,tabla);
        
        if(op != NULL){
            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = op;
            node->value = NULL;

            if(op->aridad >= 1){
                node->left = pop(stack);
                node->right = NULL;
            }
            if(op->aridad == 2){
                node->right = pop(stack);
            }
        } else {
            // if we want to be able to use aliases in the expression it must be done here
            int value = atoi(token);

            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = NULL;
            node->value = value;
            node->right = ExpTree_crear();
            node->left = ExpTree_crear();

            push(node, stack);
        }
    }

    return pop(stack);
}

char *ExpTree_inorder(ExpTree tree){
    if(tree == NULL){
        return "";
    }

    if(tree->op == NULL){
        return to_string(tree->value);
    }
    char base[] = "";

    strcat(base, ExpTree_inorder(tree->left));
    strcat(base,tree->op->simbolo);
    strcat(base,ExpTree_inorder(tree->right));

    return base;
}

// int ExpTree_evaluate(ExpTree tree){
//     return val
// }