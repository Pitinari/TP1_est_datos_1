#include "stdio.h"
#include "stdlib.h"
#include "ExpTree.h"
#include "operadores.h"
#include "string.h"
#include "assert.h"
#include "ctype.h"

// la redifino aca porque no es estandar strsep
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

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
//Dada una cadena de caracteres transforma la misma en un arbol de operadores y valores
ExpTree ExpTree_Parse(char *sentence,ExpNodeStack stack, TablaOp tabla){
    char *token;

    //hasta que no haya mas valores o caracteres
    while((token = strsep(&sentence, " "))){
        Operador op = buscar_operador(token,tabla);
        //si el caracter es un operador
        if(op != NULL){
            ExpTree node = malloc(sizeof(struct _ExpTreeNode));

            node->op = op;
            node->value = 0; //por las dudas, no deberia ser accedido nunca

            if(op->aridad >= 1){    //si la aridad es al menos 1, se carga el nodo derecho del arbol
                node->right = top(stack);
                if(node->right == NULL){
                    // error en la expresion retornamos null
                    while(top(stack) != NULL){
                        ExpTree_destruir(top(stack));
                        stack = pop(stack);
                    }
                    return NULL;
                }
                stack = pop(stack); //borramos el nodo que acabamos de sacar
                node->left = NULL;
            }

            if(op->aridad == 2){    //si es de aridad 2, completamos con el nodo izquierdo
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

            stack = push(node, stack); //colocamos el arbol recien formado en la pila

        } else {//si es un valor

            for (int i = 0; i < (int) strlen(token); i++){
                if(token[i] == '-' && i == 0)
                    continue;
                if(!isdigit(token[i])){ // si el valor con es un numero, es un error, es invalido
                    while(top(stack) != NULL){
                        ExpTree_destruir(top(stack));
                        stack = pop(stack);
                    }
                    return NULL;
                }
            }
            
            int value = atoi(token);

            ExpTree node = malloc(sizeof(struct _ExpTreeNode)); //cargamos el nodo de un valor

            node->op = NULL;
            node->value = value;
            node->right = ExpTree_crear();
            node->left = ExpTree_crear();

            stack = push(node, stack);  //colocamos el nodo en la pila
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

// ExpTree_Generate : *char -> *(struct _TablaOp) -> *(struct _ExpTreeNode)
ExpTree ExpTree_Generate(char *sentence, TablaOp operadores){
    ExpNodeStack stack = NULL;
    return ExpTree_Parse(sentence,stack,operadores);
}

// cant_digitos : int -> int
// Tomando un numero entero retorna la cantidad de digitos del mismo
int cant_digitos(int numero){
  int digitos = 0;
  do{
    digitos++;
    numero /= 10; //Seria lo mismo que truncar el entero
  }while(numero != 0);
  return digitos;
}

// ExpTree_inorder : *(struct _ExpTreeNode) -> *char
// Dado un arbol, arma un string del mismo en forma inorder (izquierda medio derecha)
char *ExpTree_inorder(ExpTree tree){
    if(tree == NULL){
        return "";
    }

    if(tree->op == NULL){ // si es un valor 
        int length = cant_digitos(tree->value);
        char *tmp;
        if (tree->value < 0)
            tmp = malloc(sizeof(char) * length+2);
        else
            tmp = malloc(sizeof(char) * length+1);
        
        sprintf(tmp, "%d", tree->value);  //transformamos el entero

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

    if (strcmp(leftExp , ""))
        free(leftExp);
    if (strcmp(rightExp , ""))
        free(rightExp);

    return base;
}

// ExpTree_evaluate : *(struct _ExpTreeNode) -> int
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