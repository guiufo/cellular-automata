#include "types.h"

//***********************************************
// Generators of rules
//***********************************************

// Generate uniform distributed rules of radius 2
void generateRules2(Individual2 population[], int size) {
  int i, j;
  double step = 1/size;
  double randNumber;
  double pzero = 0.1;

  srand(time(NULL));
  for (i = 0; i < size; ++i) {
    for (j = 0; j < RULESIZE2; j++) {
      randNumber = (double)rand() / (double)RAND_MAX ;
      if(randNumber > pzero) population[i].cromossome[j] = 1;
      else population[i].cromossome[j] = 0;
    }
    pzero += step;
  }
}

// Generate random rules of radius 2
void generateRandomRules2(Individual2 population[], int size) {
  int i, j;
  srand(time(NULL));
  for (i = 0; i < size; ++i) {
    for (j = 0; j < RULESIZE2; j++) {
      population[i].cromossome[j] = random()%2;
    }
  }
}

// Generate uniform distributed rules of radius 3
void generateRules3(Individual3 population[], int size) {
  int i, j;
  double step = 1/size;
  double randNumber;
  double pzero = 0.1;

  srand(time(NULL));
  for (i = 0; i < size; ++i) {
    for (j = 0; j < RULESIZE3; j++) {
      randNumber = (double)rand() / (double)RAND_MAX ;
      if(randNumber > pzero) population[i].cromossome[j] = 1;
      else population[i].cromossome[j] = 0;
    }
    pzero += step;
  }
}

// Generate random rules of radius 3
void generateRandomRules3(Individual3 population[], int size) {
  int i, j;
  srand(time(NULL));
  for (i = 0; i < size; ++i) {
    for (j = 0; j < RULESIZE3; j++) {
      population[i].cromossome[j] = random()%2;
    }
  }
}
//***********************************************
// Generators of initial rows
//***********************************************

// Generate uniform distributed random rows
void generateRows(int rows[][ROWSIZE], int number) {
  int i, j;
  double step = 1/number;
  double randNumber;
  double pzero = 0.1;

  srand(time(NULL));

  for (i = 0; i < number; ++i) {
    for (j = 0; j < ROWSIZE; j++) {
      randNumber = (double)rand() / (double)RAND_MAX ;
      if(randNumber > pzero) rows[i][j] = 1;
      else rows[i][j] = 0;
    }
  }
}

// Generate random rows
void generateRandomRows(int rows[][ROWSIZE], int number) {
  int i, j;
  srand(time(NULL));
  for (i = 0; i < number; ++i) {
    for (j = 0; j < ROWSIZE; j++) {
      rows[i][j] = rand()%2;
    }
  }
}

//***********************************************
// Generators of next row of cellular automata
//***********************************************
void nextRow2(int row[ROWSIZE], int rule[RULESIZE2]) {
  int i, key;
  int newRow[ROWSIZE];
  for(i = 0; i < ROWSIZE; i++) newRow[i] = row[i];
  for(i = 0; i < ROWSIZE; i++) {
      key = 16*row[(i-2+ROWSIZE)%ROWSIZE] + 8*row[(i-1+ROWSIZE)%ROWSIZE] +
            4*row[i] +
            2*row[(i+1)%ROWSIZE] + row[(i+2)%ROWSIZE];
      newRow[i] = rule[key];
  }
  for(i=0; i<ROWSIZE; i++) row[i] = newRow[i];
}

void nextRow3(int row[ROWSIZE], int rule[RULESIZE3]) {
  int i, key;
  int newRow[ROWSIZE];
  for(i = 0; i < ROWSIZE; i++) newRow[i] = row[i];
  for(i = 0; i < ROWSIZE; i++) {
      key = 64*row[(i-3+ROWSIZE)%ROWSIZE] + 32*row[(i-2+ROWSIZE)%ROWSIZE] + 16*row[(i-1+ROWSIZE)%ROWSIZE] +
            8*row[i] +
            4*row[(i+1)%ROWSIZE] + 2*row[(i+2)%ROWSIZE] + row[(i+3)%ROWSIZE];
      newRow[i] = rule[key];
  }
  for(i=0; i<ROWSIZE; i++) row[i] = newRow[i];
}