#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"
#include "string.h"

char *ingresar_buffer(){
  int c,i; 
  char* string = malloc(sizeof(char));
  for(i=0;(c=getchar())!='\n'; i++)
    {
        string = realloc(string, (i+2)*sizeof(char));
        string[i] = (char) c;
    }
    string[i]='\0';
    return string;
}

void imprimir_alias (char *alias , ListaExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%s\n", exp->inorder);
    else
        printf("No hay alias guardado con ese nombre\n");
}

void evaluar_alias (char *alias , ListaExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%d\n", Expression_evaluate(exp));
    else
        printf("No hay alias guardado con ese nombre\n");
}

int analizar_comando (char *buffer , ListaExp lista_alias , TablaOp operadores){
    char *primer_palabra = strsep(&buffer , " ");
    if (!strcmp("salir",primer_palabra))
        return 0;
    
    if (!buffer){
        printf("Comando invalido\n");
        return 1;
    }
    if (!strcmp("imprimir",primer_palabra)){
        imprimir_alias(buffer,lista_alias);
        return 1;
    }
    if (!strcmp("evaluar",primer_palabra)){
        evaluar_alias(buffer,lista_alias);
        return 1;
    }
    if (strstr(buffer, "= cargar ")){
        Expression exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        if(exp != NULL){
            ListaExp_agregar(lista_alias, exp);
        } else {
            printf("Ecuacion invalida \n");
        }
        return 1;
    }
    else {
        printf("Comando invalido\n");
    }
    return 1;
}

int main() {

    TablaOp operadores = crear_tabla_operadores();
    ListaExp lista_alias = ListaExp_crear();
    
    int continua_programa = 1;
    while(continua_programa){
        printf(">");
        continua_programa = analizar_comando(ingresar_buffer(),lista_alias,operadores);
    }
    ListaExp_destruir(lista_alias);
    destruir_tabla_operadores(operadores);
    return 0;
}




