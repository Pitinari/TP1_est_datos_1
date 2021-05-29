#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"
#include "string.h"

int main() {
    char exp[] = "5 -- 13 + 2 * 7 +";

    printf("Created operators \n");
    TablaOp operadores = crear_tabla_operadores();

    printf("Created stack \n");
    ExpNodeStack stack = NULL;

    printf("Parse tree \n");
    ExpTree tree = ExpTree_Parse(exp,stack,operadores);

    printf("Print tree \n");
    printf("%s",ExpTree_inorder(tree));
}

