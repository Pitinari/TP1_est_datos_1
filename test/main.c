#include "stdio.h"
#include "stdlib.h"
#include "test_Expression.h"
#include "test_ExpTree.h"
#include "test_operadores.h"

int main(){
    test_operadores();
    printf("Tests de Operadores hechos");
    test_Exptree();
    printf("Tests de ExpTree hechos");
    test_Expression();
    printf("Test de Expression hechos");
    return 0;
}