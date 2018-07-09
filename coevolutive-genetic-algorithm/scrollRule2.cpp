#include "types.h"
#include "experiments.cpp"

int main(int argc, char *argv[]) {
  int *binArray = (int *) malloc( 32 * sizeof(int));
  binArray = intToBinArray(argv[1]);

  printf("Rule number: %s\n", argv[1]);
  printf("Rule in binary: ");

  for(int i=0; i<32; i++) printf("%d", binArray[i]);

  printf("\n");

  scrollRule2(binArray, 300);

  return 0;
}