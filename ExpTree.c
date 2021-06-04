#include "stdio.h"
#include "stdlib.h"
#include "ExpTree.h"
#include "operadores.h"
#include "string.h"
#include "assert.h"

ExpTree ExpTree_crear() { return NULL; }

//ExpTree_destruir : *(struct _ExpTreeNode) -> Nada
//destruye los nodos del arbol recursivamente
void ExpTree_destruir(ExpTree nodo) {
    if (nodo != NULL) {
        ExpTree_destruir(nodo->left);
        ExpTree_destruir(nodo->right);
        free(nodo);
    }
}

//push : *(struct _ExpTreeNode) -> *(struct _ExpNodeStack) -> *(struct _ExpNodeStack)
//Crea un nodo de pila, que apunta al nodo de arbol, y lo coloca arriba en la pila
ExpNodeStack push(ExpTree node, ExpNodeStack stack){
    ExpNodeStack new = malloc(sizeof(struct _ExpNodeStack));

    new->node = node;
    new->prev = stack;

    return new;
}

//top : *(struct _ExpNodeStack) -> *(struct _ExpTreeNode)
//Tomando una pila, devuelve el nodo de arbol al que apunta el primer valor de la pila
ExpTree top(ExpNodeStack stack){
    return stack ? stack->node : NULL;
}

//pop : *(struct _ExpNodeStack) -> *(struct _ExpNodeStack)
//Tomando una pila, libera el primer nodo de la pila y devuelve la pila apuntando al segundo nodo
ExpNodeStack pop(ExpNodeStack stack){

    if(stack == NULL){
        return NULL;
    }

    ExpNodeStack prev = stack->prev;
    free(stack);
    return prev;

}

//ExpTree_Parse : *char -> *(struct _ExpNodeStack) -> *(struct _TablaOp) -> *(struct _ExpTreeNode)
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
        ExpTree_destruir(tree);
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
        int length = cant_digitos(tree->value);
        char *tmp = malloc(sizeof(char) * length);
        
        sprintf(tmp, "%d", tree->value);

        return tmp;
    }

    char *leftExp = ExpTree_inorder(tree->left);
    char *rightExp = ExpTree_inorder(tree->right);
    char *simbol = tree->op->simbolo;

    int totalLength = strlen(leftExp) + strlen(simbol) + strlen(rightExp);

    // +3 de los parentesis y terminador
    char *base = malloc(sizeof(char) * (totalLength+3));
    // Agregamos esto para que valgrind no tome como erroneo que se concatenan strings sin inicializar
    *base = '\0';

    // Aguegamos parentesis para que se note las prioridades ((1+2)*2)
    base = strcat(base, "(");
    base = strcat(base, leftExp);
    base = strcat(base, simbol);
    base = strcat(base, rightExp);
    base = strcat(base, ")");

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