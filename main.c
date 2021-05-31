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
    string[0]='\0';
    return string;
}

Expression buscar_alias (char *alias , LListExp lista){
    while(lista){
        if (!strcmp( alias , lista->exp->alias ))
            return lista->exp;
        lista = lista->sig;
    }
    return NULL;
}

void imprimir_alias (char *alias , LListExp lista_alias){
    Expression exp buscar_alias(alias , lista_alias);
    if (exp)
        printf("%s\n", exp->inorder);
    else
        printf("No hay alias guardado con ese nombre\n", );
}

void evaluar_alias (char *alias , LListExp lista_alias){
    Expression exp buscar_alias(alias , lista_alias);
    if (exp)
        printf("%d\n", Expression_evaluate(exp));
    else
        printf("No hay alias guardado con ese nombre\n", );
}

int analizar_comando (char *buffer , LListExp lista_alias , TablaOp operadores){
    char *primer_palabra = strsep(&buffer , " ");

    if (!strcmp("salir",primer_palabra))
        return 0;

    if (!strcmp("imprimir",primer_palabra)){
        imprimir_alias(buffer,lista_alias);
        return 1;
    }
    if (!strcmp("evaluar",primer_palabra)){
        evaluar_alias(buffer,lista_alias);
        return 1;
    }
    if (strstr(buffer, "= cargar ")){
        while (lista_alias)
            lista_alias = lista_alias->sig;
        lista_alias = malloc(sizeof(struct _ListaExp));
        lista_alias->exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        lista_alias->sig;
    }
    else {
        printf("Comando invalido\n");

    }
    free(primer_palabra);
    free(buffer);
    return 1;
}

int main() {
    char exp[] = "87 3 ^ 42 / 3 *";

    int value = ((87 ^ 3) / 42 ) * 3;

    printf("Created operators \n");
    TablaOp operadores = crear_tabla_operadores();

    printf("Created stack \n");
    ExpNodeStack stack = NULL;

    printf("Parse tree \n");
    ExpTree tree = ExpTree_Parse(exp,stack,operadores);

    printf("Print tree \n");
    printf("%s \n",ExpTree_inorder(tree));

    printf("Evaluate tree \n");
    printf("%d \n",ExpTree_evaluate(tree));
    printf("Evaluate tree \n");
    printf("%d \n",value);
    
    int continua_programa = 1;
    LListExp lista_alias;
    while(continua_programa)
        printf(">");
        continua_programa = analizar_comando(ingresar_buffer(),lista_alias,operadores);

    return 0;
}
