// Program to evaluate rule of radius 3 given 10k initial random row

#include "types.h"
#include "experiments.cpp"
#define ROWS 10000

int main(int argc, char *argv[]) {
  char *binArray = (char *) malloc( 128 * sizeof(char));
  int *intArray = (int *) malloc( 128 * sizeof(int));
  int rows[ROWS][ROWSIZE];
  int i, j;
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  float counter = 0;

  binArray = hexToBinArray(argv[1]);
  for(i=0; i<128; i++) intArray[127-i] = (int) binArray[i] - 48;
  generateRandomRows(rows, ROWS, 1);

  for(i=0; i<ROWS; i++) {
    memcpy(initialRow, rows[i], ROWSIZE*sizeof(int));
    for(j=0; j<300; j++) {
      nextRow3(initialRow, intArray);
      if(j == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
      if(j == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
    }
    counter += checkSync(syncRowOne, syncRowTwo);
  }

  free(binArray);
  free(intArray);
  printf("%s\t%06.2f%%\n", argv[1], counter/100);

  return 0;
}