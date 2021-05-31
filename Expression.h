#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "stdlib.h"

struct _Exp {
    char *alias;
    char *sentence;
    ExpTree tree;
};

typedef struct _Exp *Expression;

// Crea y retorna una expresion, con su alias y su "sentence" (la expresion en si)
// Ademas cada expresion guarda su ExpTree
// TODO: ademas necesita la tabla de operadores para parsear la oracion
// En el caso que no tenga alias se setea en '\0'
Expression Expression_create(char *alias, char *sentence);

// recibe una expresion y la evalua, retorna el valor (no necesita la tabla de operadores ya que el arbol tiene un puntero a cada operador)
int Expression_evaluate(Expression exp);


// retorna la representacion inorder del arbol, osea la expresion matematica en notacion normal 
void Expression_print(Expression exp);

// Destruye la expresion liberando memoria
void Expression_destruir(Expression exp);

#endif