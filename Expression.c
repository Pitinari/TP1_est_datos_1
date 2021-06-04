#include "stdlib.h"
#include "ExpTree.h"
#include "Expression.h"
#include "stdio.h"
#include "ctype.h"



ListaExp ListaExp_crear(){
    ListaExp lista = malloc(sizeof(struct _ListaExp));

    lista->size = 1;
    lista->filled = 0;

    lista->exp = malloc(sizeof(struct _Exp) * lista->size);

    return lista;
}

void ListaExp_agregar(ListaExp lista, Expression exp){
    // if not big enough resize
    if(lista->size <= lista->filled){
        lista->size = lista->size + 5;
        lista->exp = realloc(lista->exp, sizeof(struct _Exp) * lista->size);
    }
    // if alias already exist replace it
    for (int i = 0; i < lista->filled; i++){
        if (!strcmp(exp->alias, lista->exp[i]->alias)){
            lista->exp[i] = exp;
            return;
        }
    }
    // add it if not
    lista->exp[lista->filled] = exp;
    lista->filled += 1;
}

void ListaExp_destruir(ListaExp lista){
    for (int i = 0; i < lista->filled; i++){
        Expression_destruir(lista->exp[i]);
    }
    free(lista->exp);
    free(lista);
}



Expression Expression_create(char *alias, char *sentence, TablaOp operators){
    Expression exp = malloc(sizeof(struct _Exp));
    ExpTree tree =  ExpTree_Generate(sentence, operators);

    if(tree == NULL){
        return NULL;
    }

    exp->alias = malloc(sizeof(char)*(strlen(alias)+1));
    strcpy(exp->alias , alias);
    exp->tree = tree;
    exp->inorder = ExpTree_inorder(exp->tree);

    return exp;
}

int Expression_evaluate(Expression exp){
    return ExpTree_evaluate(exp->tree);
}

//esto realmente se usa??
void Expression_print(Expression exp){
    printf("%s \n", exp->inorder);
}

void Expression_destruir(Expression exp){
    free(exp->alias);
    free(exp->inorder);
    ExpTree_destruir(exp->tree);
    free(exp);
}

int validar_alias(char *alias){
    // es no numerico 
    if(isdigit(alias[0])){
        return 0;
    }

    // son todos alfanumericos
    for (int i = 0; i < strlen(alias); i++){
        if(!isalnum(alias[i])){
            return 0;
        }
    }

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

Expression buscar_alias (char *alias , ListaExp lista){
    for (int i = 0; i < lista->filled; i++){
        if (!strcmp( alias , lista->exp[i]->alias))
            return lista->exp[i];
    }
    return NULL;
}