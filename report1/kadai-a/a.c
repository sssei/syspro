#include <stdio.h>
#include "b.h"
#include "c.h"

int main(){
  int a = function_C(1) + function_B(2);
  printf("%d\n", a);
  return 0;
}
