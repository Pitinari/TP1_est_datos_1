#include "stdio.h"
#include "stdlib.h"
#include "ExpTree.h"
#include "operadores.h"
#include "string.h"
#include "assert.h"

ExpTree ExpTree_crear() { return NULL; }

void ExpTree_destruir(ExpTree nodo) {
    if (nodo != NULL) {
        ExpTree_destruir(nodo->left);
        ExpTree_destruir(nodo->right);
        free(nodo);
    }
}

//esto creo que esta al pedo
/*ExpTree ExpTree_unir(Operador op,int dato, ExpTree left, ExpTree right) {
  ExpTree nuevoNodo = malloc(sizeof(struct _ExpTreeNode));
  assert(nuevoNodo != NULL);
  nuevoNodo->op = op;
  nuevoNodo->value = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}*/

ExpNodeStack push(ExpTree node, ExpNodeStack stack){
    ExpNodeStack new = malloc(sizeof(struct _ExpNodeStack));

    new->node = node;
    new->prev = stack;

    return new;
}

ExpTree top(ExpNodeStack stack){
    return stack->node;
}
ExpNodeStack pop(ExpNodeStack stack){

    ExpTree n = stack->node;

    ExpNodeStack prev = stack->prev;

    free(stack);
    return prev;

}

// TODO: add wrapper function that doesn't need the stack and operators 
ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack, TablaOp tabla){

    char *token;
    while(token = strsep(&sentence, " ")){

        Operador op = buscar_operador(token,tabla);

        if(op != NULL){
            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = op;
            node->value = NULL; //cambie los valores por punteros para que exista un valor null

            if(op->aridad >= 1){
                node->left = top(stack);
                stack = pop(stack);
                node->right = NULL;
            }

            if(op->aridad == 2){
                node->right = top(stack);
                stack = pop(stack);
            }

            stack = push(node, stack);

        } else {
            // if we want to be able to use aliases in the expression it must be done here
            int value = atoi(token);

            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = NULL;
            node->value = value;
            node->right = ExpTree_crear();
            node->left = ExpTree_crear();

            stack = push(node, stack);
        }
    }
    ExpTree tree = top(stack);
    pop(stack);
    return tree;
}

int cant_digitos(int numero){
  int digitos = 1;
  while(numero != 0){
    digitos++;
    numero /= 10;
  };
  return digitos;
}

char *ExpTree_inorder(ExpTree tree){
    if(tree == NULL){
        return "";
    }

    if(tree->op == NULL){
        int length = cant_digitos(tree->value);
        char *tmp = malloc(sizeof(char) * length);
        
        sprintf(tmp, "%d", tree->value);;

        return tmp;
    }

    char *leftExp = ExpTree_inorder(tree->left);
    char *rightExp = ExpTree_inorder(tree->right);
    char *simbol = tree->op->simbolo;

    int totalLength = strlen(leftExp) + strlen(simbol) + strlen(rightExp);

    char *base = malloc(sizeof(char) * totalLength);

    strcat(base, rightExp);
    strcat(base, simbol);
    strcat(base, leftExp);

    return base;
}

// int ExpTree_evaluate(ExpTree tree){
//     return val
// }