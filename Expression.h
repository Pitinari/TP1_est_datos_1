#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "stdlib.h"

struct _Exp {
    char *alias;
    char *inorder;
    ExpTree tree;
};

typedef struct _Exp *Expression;

struct _ListaExp {
	Expression *exp;
    int size, filled;
};

typedef struct _ListaExp *ListaExp;


ListaExp ListaExp_crear();
void ListaExp_agregar(ListaExp lista, Expression exp);
void ListaExp_destruir(ListaExp lista);


// Crea y retorna una expresion, con su alias y su "sentence" (la expresion en si)
// Ademas cada expresion guarda su ExpTree
// TODO: ademas necesita la tabla de operadores para parsear la oracion
// En el caso que no tenga alias se setea en '\0'
Expression Expression_create(char *alias, char *sentence, TablaOp operators);

// recibe una expresion y la evalua, retorna el valor (no necesita la tabla de operadores ya que el arbol tiene un puntero a cada operador)
int Expression_evaluate(Expression exp);


// retorna la representacion inorder del arbol, osea la expresion matematica en notacion normal 
void Expression_print(Expression exp);

// Destruye la expresion liberando memoria
void Expression_destruir(Expression exp);

// Busca un alias dentro de la lista de expresiones desde un string y devuelve la expresion
Expression buscar_alias (char *alias , ListaExp lista);

#endif