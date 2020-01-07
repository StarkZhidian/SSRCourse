#include <math.h>
#include <stdio.h>

int main() {
  int i = 0b00111111001100000000000000000000;
  float *p = &i;
  printf("%f\n", *p);
  printf("%f", 11/16.0f);
  return 0;
}
