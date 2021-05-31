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

int evaluar_comando (char *buffer){
    char *primer_palabra = strsep(&buffer , " ");

    if (!strcmp("salir",primer_palabra))
        return 0;

    if (!strcmp("imprimir",primer_palabra)){
        imprimir_alias(buffer+1);
    }

    free(primer_palabra);
    free(buffer);
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

    while(continua_programa)
        continua_programa = evaluar_comando(ingresar_buffer());

    return 0;
}
