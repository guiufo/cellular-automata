#include <stdio.h>

int main() {
  int m[10][10] = {0};

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      printf("%2d", m[i][j]);
    }
    printf("\n");
  }
  return 0;
}