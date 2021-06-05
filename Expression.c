#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"
#include "stdio.h"
#include "ctype.h"


// ListaExp_crear : Nada -> *(struct _ListaExp)
// Inicializa un puntero a una estructura que tiene una lista de expresiones,
// la cantidad de espacios de expresiones y la cantidad de expresiones declaradas
ListaExp ListaExp_crear(){
    ListaExp lista = malloc(sizeof(struct _ListaExp));

    lista->size = 1;
    lista->filled = 0;

    lista->exp = malloc(sizeof(struct _Exp) * lista->size);

    return lista;
}

// ListaExp_agregar : *(struct _ListaExp) -> *(struct _Exp) -> Nada
// Dados una lista, agregamos una expresion a la misma y le agregamos 
// memoria si hace falta
void ListaExp_agregar(ListaExp lista, Expression exp){
    // si no hay espacio, agregamos memoria de a 5, para que 
    // no se hagan realloc por cada expresion
    if(lista->size <= lista->filled){
        lista->size = lista->size + 5;
        lista->exp = realloc(lista->exp, sizeof(struct _Exp) * lista->size);
    }
    // si el alias ya existe se reemplaza
    for (int i = 0; i < lista->filled; i++){
        if (!strcmp(exp->alias, lista->exp[i]->alias)){
            lista->exp[i] = exp;
            return;
        }
    }
    // si el alias no existe se agrega en la siguiente posicion
    lista->exp[lista->filled] = exp;
    lista->filled += 1;
}

// ListaExp_destruir : *(struct _ListaExp) -> Nada
// Primero libera todas las expresiones, luego el puntero a la antigua lista
// y finalmente la estructura de la que apunta lista
void ListaExp_destruir(ListaExp lista){
    for (int i = 0; i < lista->filled; i++){
        Expression_destruir(lista->exp[i]);
    }
    free(lista->exp);
    free(lista);
}

// Expression_create : *char -> *char -> *(struct _TablaOp) -> *(struct _Exp)
// En base al nombre(alias) que tendra la expresion y el string de numeros y 
// operadores, devuelve un puntero a una estrucrura de expresion
Expression Expression_create(char *alias, char *sentence, TablaOp operators){
    ExpTree tree =  ExpTree_Generate(sentence, operators);  //genera el arbol
                                    //para el string de numeros y operadores
    if(tree == NULL){
        return NULL;
    }

    Expression exp = malloc(sizeof(struct _Exp)); 
    exp->alias = malloc(sizeof(char)*(strlen(alias)+1));  ////se guarda en 
    strcpy(exp->alias , alias); //memoria nueva para liberarel buffer mas tarde
    exp->tree = tree;
    exp->inorder = ExpTree_inorder(exp->tree); //guarda un string equivalente 
                                              //a la lectura inorder del arbol

    return exp;
}

// Expression_evaluate : *(struct _Exp) -> int
// Retorna el resultado de llamar a el evaluador de ExpTree's
int Expression_evaluate(Expression exp){
    return ExpTree_evaluate(exp->tree);
}

// Expression_destruir : *(struct _Exp) -> Nada
// Libera toda la memoria que contiene la estructura de _Exp y luego libera la
// memoria de la estructura
void Expression_destruir(Expression exp){
    free(exp->alias);
    free(exp->inorder);
    ExpTree_destruir(exp->tree);
    free(exp);
}

// validar_alias : *char -> int
// verfifica que un alias cumpla todas las condiciones para poder serlo
int validar_alias(char *alias){
    // es no numerico 
    if(isdigit(alias[0])){
        return 0;
    }

    // son todos alfanumericos
    for (int i = 0; i < (int) strlen(alias); i++){
        if(!isalnum(alias[i])){
            return 0;
        }
    }

    // no es igual a alguna de las otras palabras reservadas del interprete
    if(!strcmp(alias,"cargar")){
        return 0;
    }
    if(!strcmp(alias,"imprimir")){
        return 0;
    }
    if(!strcmp(alias,"evaluar")){
        return 0;
    }
    if(!strcmp(alias,"salir")){
        return 0;
    }

    return 1;
    
}

// buscar_alias : *char -> *(struct _ListaExp)
// Recorre toda la lista de expresiones guardadas en busca de alguna que tenga
// el alias igual al string alias del parametro
Expression buscar_alias (char *alias , ListaExp lista){
    for (int i = 0; i < lista->filled; i++){
        if (!strcmp( alias , lista->exp[i]->alias))
            return lista->exp[i];
    }
    return NULL;
}