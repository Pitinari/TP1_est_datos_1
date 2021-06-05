#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"
#include "string.h"

// ingresar_buffer : Nada -> *char
// guarda en memoria un string de largo dinamico, almacenando de a 10
// para que no se utilice realloc en cada caracter
char *ingresar_buffer(){
  int c,i;
  int size = 10; 
  char* string = malloc(sizeof(char) * size);
  for(i=0;(c=getchar())!='\n'; i++){ //sigue ingresando mientras no sea enter
      if (size <= i){
        size += 10;
        // realloc de a 10 para no hacerlo en cada iteracion
        string = realloc(string, sizeof(char) * size);  
      }
      string[i] = (char) c;
  }
  // almacenamos siempre 1 extra de espacio para poder guardar el terminador
  string = realloc(string, sizeof(char)*(size+1));
  string[i]='\0';
  return string;
}

// imprimir_alias : *char -> *(struct _ListaExp) -> Nada
// Dado un string de alias, lo busca dentro de una lista de expresiones, si no
// lo encuentra avisa que no existe el alias, en caso opuesto lo muestra inorder
void imprimir_alias (char *alias , ListaExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%s\n", exp->inorder);
    else
        printf("No hay alias guardado con ese nombre\n");
}

// evaluar_alias : *char -> *(struct _ListaExp) -> Nada
// Dado un string de alias, lo busca dentro de una lista de expresiones, si no
// lo encuentra avisa que no existe el alias, en caso opuesto muestra el 
// resultado de evaluar la expresion
void evaluar_alias (char *alias , ListaExp lista_alias){
    Expression exp = buscar_alias(alias , lista_alias);
    if (exp)
        printf("%d\n", Expression_evaluate(exp));
    else
        printf("No hay alias guardado con ese nombre\n");
}

// interpretar : *char -> *(struct _ListaExp) -> *(struct _TablaOp) -> int
// interpreta el comando dado por el usario y determina que opcion elegir
int interpretar (char *buffer , ListaExp lista_alias , TablaOp operadores){
    // separa la primera palabra del buffer
    char *primer_palabra = strsep(&buffer , " ");
    
    // si solo se ingreso salir sin nada mas, retorna 0 para terminar
    if (!strcmp("salir",primer_palabra) && !buffer){
        return 0;
    }
    // si despues de separar la primera palabra no hay mas caracteres
    // y ya se descarto salir, entonces es un comando invalido
    if (!buffer){
        printf("Comando invalido\n");
        return 1;
    }
    // si el buffer "= cargar " intentara cargar la expresion
    if (strstr(buffer, "= cargar ")){
        //si el alias no es valido sale
        if(!validar_alias(primer_palabra)){
            printf("Alias invalido \n");
            return 1;
        }
        // intenta crear la expresion
        Expression exp = Expression_create(primer_palabra , (buffer+9) , operadores);
        if(exp != NULL){ // si se pudo la guarda
            ListaExp_agregar(lista_alias, exp);
        } else { // sino libera memoria y avisa que es invalida la expresion
            free(exp);
            printf("Ecuacion invalida \n");
        }
        return 1;
    } 
    // si la primera palabra es impimir intenta imprimir una expresion con el
    // alias en buffer
    if (!strcmp("imprimir",primer_palabra)){
        imprimir_alias(buffer,lista_alias);
        return 1;
    }
    // lo mismo pero con evaluar
    if (!strcmp("evaluar",primer_palabra)){
        evaluar_alias(buffer,lista_alias);
        return 1;
    }
    //si ninguna opcion se cumplio, el comando no es valido
    printf("Comando invalido\n");
    return 1;
}

int main() {

    TablaOp operadores = crear_tabla_operadores();
    ListaExp lista_alias = ListaExp_crear();
    // inicializamos variables
    int continua_programa = 1;
    char *buffer;

    while(continua_programa){ // continua hasta que la flag sea 0
        printf(">");
        // guardamos el buffer en el main para poder liberarlo completo
        buffer = ingresar_buffer();
        // interpretamos el buffer
        continua_programa = interpretar(buffer,lista_alias,operadores);
        free(buffer);
    }
    // liberamos memoria
    ListaExp_destruir(lista_alias);
    destruir_tabla_operadores(operadores);
    return 0;
}