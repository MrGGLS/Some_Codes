#include <stdio.h>
#include <stdlib.h>

#include "com_assign.parser.h"

int main()
{
  printf("> ");
  return yyparse();
}
