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
    while(token = strtok(sentence, " ")){
        Operador op = buscar_operador(token,tabla);
        
        if(op != NULL){
            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = op;
            node->value = NULL; //cambie los valores por punteros para que exista un valor null

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
            node->value = &value;
            node->right = ExpTree_crear();
            node->left = ExpTree_crear();

            push(node, stack);
        }
    }

    return pop(stack);
}

int cant_digitos(int numero){
  int digitos = 0;
  do{
    digitos++;
    numero /= 10;
  }while(numero != 0);

  return digitos;
}

char *ExpTree_inorder(ExpTree tree){
    if(tree == NULL){
        return "";
    }

    if(tree->op == NULL){
        int dig = cant_digitos(*(tree->value));
        char *aux;
        if(*(tree->value) >= 0)
          aux = malloc(sizeof(char)*(dig+1));
        else
          aux = malloc(sizeof(char)*(dig+2)); //reservo 1 mas de memoria por el -
        sprintf(aux, "%d", *(tree->value)); //guarda en aux el valor del int, use esto porque itoa no funcionaba
        return aux;
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