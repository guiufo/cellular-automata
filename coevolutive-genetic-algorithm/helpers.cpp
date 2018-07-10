#include "types.h"

// Imprime um reticulado
void printRow(int row[]) {
  for(int i=0; i<ROWSIZE; i++) {
    if(row[i] == 1) printf("\u2588");
    else printf(" ");
  }
  printf("\n");
}

// Verifica a convergência comparando dois reticulados
int checkSync(int firstRow[ROWSIZE], int secondRow[ROWSIZE]) {
  int i;
  if(firstRow[0] == 0) {
    for(i = 0; i < ROWSIZE; i++) {
      if(firstRow[i] != 0) return 0;
      if(secondRow[i] != 1) return 0;
    }
    return 1;
  }
  if(firstRow[0] == 1) {
    for(i = 0; i < ROWSIZE; i++) {
      if(firstRow[i] != 1) return 0;
      if(secondRow[i] != 0) return 0;
    }
    return 1;
  }
}
