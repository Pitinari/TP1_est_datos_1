#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"
#include "string.h"

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
}

