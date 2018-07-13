// Program to evaluate rule of radius 2 given 10k initial random row
#include "types.h"
#include "experiments.cpp"
#define ROWS 10000

int main(int argc, char *argv[]) {
  int *binArray = (int *) calloc(32, sizeof(int));
  int rows[ROWS][ROWSIZE];
  int i, j;
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  // Número para contagem de sincronizações em 10.000 reticulados
  int counter = 0;

  binArray = intToBinArray(argv[1]);
  for(i=0; i<32; i++) {
    printf("%d", binArray[i]);
  }
  printf("\n");
  generateRandomRows(rows, ROWS, 1);

  for(i=0; i<ROWS; i++) {
    memcpy(initialRow, rows[i], ROWSIZE*sizeof(int));
    for(j=0; j<300; j++) {
      nextRow2(initialRow, binArray);
      if(j == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
      if(j == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
    }
    counter += checkSync(syncRowOne, syncRowTwo);
  }

  free(binArray);
  printf("Counter: %d\n", counter);
  printf("%s %d\n", argv[1], counter);

  return 0;
}