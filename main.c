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

Expression buscar_alias (char *alias , ListaExp lista){
    for (int i = 0; i < lista->filled; i++){
        if (!strcmp( alias , lista->exp[i]->alias))
            return lista->exp[i];
    }
    return NULL;
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
        ListaExp_agregar(lista_alias, Expression_create(primer_palabra , (buffer+9) , operadores));
    }
    else {
        printf("Comando invalido\n");
    }
    return 1;
}

int main() {
    /*
    char exp[] = "87 3 ^ 42 / 3 *";

    int value = ((87 ^ 3) / 42 ) * 3;
    */

    TablaOp operadores = crear_tabla_operadores();
    /*
    printf("Created stack \n");
    ExpNodeStack stack = NULL;

    printf("Parse tree \n");
    ExpTree tree = ExpTree_Parse(exp,stack,operadores);

    printf("Print tree \n");
    printf("%s \n",ExpTree_inorder(tree));

    printf("Evaluate tree \n");
    printf("%d \n",ExpTree_evaluate(tree));
    printf("Evaluate tree \n");
    printf("%d \n",value);*/

    int continua_programa = 1;
    ListaExp lista_alias = ListaExp_crear();
    while(continua_programa){
        printf(">");
        continua_programa = analizar_comando(ingresar_buffer(),lista_alias,operadores);
    }
    ListaExp_destruir(lista_alias);
    destruir_tabla_operadores(operadores);
    return 0;
}




