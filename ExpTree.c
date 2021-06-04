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

ExpNodeStack push(ExpTree node, ExpNodeStack stack){
    ExpNodeStack new = malloc(sizeof(struct _ExpNodeStack));

    new->node = node;
    new->prev = stack;

    return new;
}

ExpTree top(ExpNodeStack stack){
    return stack ? stack->node : NULL;
}
ExpNodeStack pop(ExpNodeStack stack){

    if(stack == NULL){
        return NULL;
    }

    ExpTree n = stack->node;

    ExpNodeStack prev = stack->prev;
    free(stack);
    return prev;

}

ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack, TablaOp tabla){
    char *token;

    while(token = strsep(&sentence, " ")){
        Operador op = buscar_operador(token,tabla);

        if(op != NULL){
            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = op;
            node->value = 0; //por las dudas, no deberia ser accedido nunca

            if(op->aridad >= 1){
                node->right = top(stack);
                if(node->right == NULL){
                    // error en la expresion retornamos null
                    while(top(stack) != NULL){
                        ExpTree_destruir(top(stack));
                        stack = pop(stack);
                    }
                    return NULL;
                }
                stack = pop(stack);
                node->left = NULL;
            }

            if(op->aridad == 2){
                node->left = top(stack);
                if(node->left == NULL){
                    // error en la expresion retornamos null
                    while(top(stack) != NULL){
                        ExpTree_destruir(top(stack));
                        stack = pop(stack);
                    }
                    return NULL;
                }
                stack = pop(stack);
            }

            stack = push(node, stack);

        } else {
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
    stack = pop(stack);

    if(stack != NULL){
        // quedaron nodos pendientes en el stack, por lo tanto la expresion esta mal
        // liberamos todos los pendientes
        while(stack != NULL){
            ExpTree_destruir(top(stack));
            stack = pop(stack);
        }
        return NULL;
    }

    return tree;
}

ExpTree ExpTree_Generate(char *sentence, TablaOp operadores){
    ExpNodeStack stack = NULL;
    return ExpTree_Parse(sentence,stack,operadores);
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
        
        sprintf(tmp, "%d", tree->value);

        return tmp;
    }

    char *leftExp = ExpTree_inorder(tree->left);
    char *rightExp = ExpTree_inorder(tree->right);
    char *simbol = tree->op->simbolo;

    int totalLength = strlen(leftExp) + strlen(simbol) + strlen(rightExp);

    char *base = malloc(sizeof(char) * totalLength);

    strcat(base, leftExp);
    strcat(base, simbol);
    strcat(base, rightExp);

    free(leftExp);
    free(rightExp);

    return base;
}

int ExpTree_evaluate(ExpTree tree){    
    if(tree->op == NULL) {
        return tree->value;
    }

    int params[2];

    int rightValue = ExpTree_evaluate(tree->right);
    if(tree->op->aridad == 1) {
        params[0] = rightValue;
    }

    if(tree->op->aridad == 2) {
    int leftValue = ExpTree_evaluate(tree->left);
        params[0] = leftValue;
        params[1] = rightValue;
    }

    return tree->op->evaluador(params);
}