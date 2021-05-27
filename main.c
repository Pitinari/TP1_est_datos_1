#include "stdio.h"
#include "ExpTree.h"
#include "operadores.h"
#include "Expression.h"
#include "ExpTree.h"

int main() {
    char exp[] = "5 - 13 + 2 * 7 +";

    TablaOp operadores = crear_tabla_operadores();

    ExpNodeStack stack = NULL;

    ExpTree tree = ExpTree_Parse(exp,stack,operadores);

    printf("%s",ExpTree_inorder(tree));

}

