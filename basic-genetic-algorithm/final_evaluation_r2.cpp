// Program to evaluate rule of radius 2 given 10k initial random row

#include "types.h"
#include "experiments.cpp"
#define ROWS 10000

int main(int argc, char *argv[]) {
  int *binArray = (int *) malloc( 32 * sizeof(int));
  int rows[ROWS][ROWSIZE];
  int i, j;
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  float counter = 0;

  binArray = intToBinArray(argv[1]);
  generateRandomRows(rows, ROWS);

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
  printf("%s\t%06.2f%%\n", argv[1], counter/100);

  return 0;
}