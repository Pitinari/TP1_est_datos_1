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

Expression buscar_alias (char *alias , LListExp lista){
    while(lista){
        if (!strcmp( alias , lista->exp->alias ))
            return lista->exp;
        lista = lista->sig;
    }
    return NULL;
}

void imprimir_alias (char *alias , LListExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%s\n", exp->inorder);
    else
        printf("No hay alias guardado con ese nombre\n");
}

void evaluar_alias (char *alias , LListExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%d\n", Expression_evaluate(exp));
    else
        printf("No hay alias guardado con ese nombre\n");
}

int analizar_comando (char *buffer , LListExp lista_alias , TablaOp operadores){
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
        if(lista_alias->exp == NULL){
            lista_alias->exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        }
        while (lista_alias->sig)
            lista_alias = lista_alias->sig;
        lista_alias->sig = malloc(sizeof(struct _ListaExp));
        lista_alias->sig->exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        lista_alias->sig->sig;
    }
    else {
        printf("Comando invalido\n");
    }
    return 1;
}

void liberar_lista_expresiones (LListExp lista_alias){
    if (lista_alias->sig)
        liberar_lista_expresiones(lista_alias->sig);
    Expression_destruir(lista_alias->exp);
    free(lista_alias);
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
    LListExp lista_alias = malloc(sizeof(struct _ListaExp));
    lista_alias->exp = NULL;
    lista_alias->sig = NULL;
    while(continua_programa){
        printf(">");
        continua_programa = analizar_comando(ingresar_buffer(),lista_alias,operadores);
    }
    liberar_lista_expresiones(lista_alias);
    destruir_tabla_operadores(operadores);
    return 0;
}
