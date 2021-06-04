#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"
#include "string.h"

char *ingresar_buffer(){
  int c,i;
  int size = 10; 
  char* string = malloc(sizeof(char) * size);
  for(i=0;(c=getchar())!='\n'; i++){
      if (size <= i){
        size += 10;
        string = realloc(string, sizeof(char) * size);
      }
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
    // Agregue !buffer por si ingresan "salir a"
    if (!strcmp("salir",primer_palabra) && !buffer){
        return 0;
    }
    /*if (!strcmp("salir",primer_palabra)){
        printf("Comando invalido\n");
        free(primer_palabra);
        free(buffer);
        return 0;
    }*/
    if (!buffer){
        printf("Comando invalido\n");
        return 1;
    }
    if (strstr(buffer, "= cargar ")){
        if(!validar_alias(primer_palabra)){
            printf("Alias invalido \n");
            return 1;
        }
        Expression exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        if(exp != NULL){
            ListaExp_agregar(lista_alias, exp);
        } else {
            free(exp);
            printf("Ecuacion invalida \n");
        }
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

    printf("Comando invalido\n");
    return 1;
}

int main() {

    TablaOp operadores = crear_tabla_operadores();
    ListaExp lista_alias = ListaExp_crear();
    
    int continua_programa = 1;
    char *buffer;
    while(continua_programa){
        printf(">");
        buffer = ingresar_buffer();
        continua_programa = analizar_comando(buffer,lista_alias,operadores);
        free(buffer);
    }
    ListaExp_destruir(lista_alias);
    destruir_tabla_operadores(operadores);
    return 0;
}