#include "types.h"
#include "experiments.cpp"

int main(int argc, char *argv[]) {
  char *bin = (char *) malloc(128 * sizeof(char));
  int *intArray = (int *) malloc(128 * sizeof(int));

  bin = hexToBinArray(argv[1]);

  printf("Rule number: %s\n", argv[1]);
  printf("Rule in binary: ");

  for(int i=0; i<128; i++) intArray[127-i] = (int) bin[i] - 48;
  for(int i=0; i<128; i++) printf("%d", intArray[i]);

  printf("\n");
  scrollRule3(intArray, 300);

  return 0;
}