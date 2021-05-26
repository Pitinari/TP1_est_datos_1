#include "stdlib.h"

typedef struct _Exp *Expression;

// Crea y retorna una expresion, con su alias y su "sentence" (la expresion en si)
// Ademas cada expresion guarda su ExpTree, hay que ver donde computarlo, ya que para computarlo necesitas la tabla de operadores
// En el caso que no tenga alias se setea en '\0'
Expression Expression_create(char *alias, char *sentence);

// recibe una expresion y la evalua, retorna el valor (tambien necesitamos los operadores)
int Expression_evaluate(Expression exp);