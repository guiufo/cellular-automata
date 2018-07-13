#include "types.h"

// Runs a rule against an array of initial rows and calculate its fitness
void checkPopulation2(int rows[][ROWSIZE], Individual2 population[], int initIndex, int endIndex) {
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  int i, currentRule, currentRow, currentStep;
  // Reset fitness
  for(i=0; i<100; i++) population[i].fitness = 0;
  for(currentRule=initIndex; currentRule<=endIndex; currentRule++) {
    // Executa uma regra sobre os 100 reticulados
    for(currentRow=0; currentRow<100; currentRow++) {
      memcpy(initialRow, rows[currentRow], ROWSIZE*sizeof(int));
      // Evolui o autômato celular 300 vezes
      for(currentStep=0; currentStep<300; currentStep++) {
        nextRow2(initialRow, population[currentRule].cromossome);
        if(currentStep == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
        if(currentStep == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
      }
      population[currentRule].fitness += checkSync(syncRowOne, syncRowTwo);
    }
  }
}

// Runs a rule against an array of initial rows and calculate its fitness
void checkPopulationsRadius2(Lattice latticePopulation[], Individual2 population[], int initIndex, int endIndex) {
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  int i, check, currentRule, currentRow, currentStep;

  // Reset rules fitness
  for(i=0; i<100; i++) population[i].fitness = 0;
  // Reset lattices fitness
  for(i=0; i<100; i++) latticePopulation[i].fitness = 0;

  for(currentRule=initIndex; currentRule<=endIndex; currentRule++) {
    // Executa uma regra sobre os 100 reticulados
    for(currentRow=0; currentRow<100; currentRow++) {
      memcpy(initialRow, latticePopulation[currentRow].cromossome, ROWSIZE*sizeof(int));
      // Evolui o autômato celular 300 vezes
      for(currentStep=0; currentStep<300; currentStep++) {
        nextRow2(initialRow, population[currentRule].cromossome);
        if(currentStep == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
        if(currentStep == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
      }
      check = checkSync(syncRowOne, syncRowTwo);
      population[currentRule].fitness += check;
      if(!check) latticePopulation[currentRow].fitness += check;
    }
  }
}

// Runs a rule against an array of initial rows and calculate its fitness
void checkPopulation2Shared(int rows[][ROWSIZE], Individual2 population[], int initIndex, int endIndex) {
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  int i, j, row, column, check;
  int currentRule, currentRow, currentStep;
  // Matriz de recurso compartilhado
  // Reticulados (Linhas) X Regras (Colunas)
  int sharedResource[101][101] = {0};

  // Reset fitness
  for(i=0; i<100; i++) population[i].fitness = 0;
  for(currentRule=initIndex; currentRule<=endIndex; currentRule++) {
    // Executa uma regra sobre os 100 reticulados
    for(currentRow=0; currentRow<100; currentRow++) {
      memcpy(initialRow, rows[currentRow], ROWSIZE*sizeof(int));
      // Evolui o autômato celular 300 vezes
      for(currentStep=0; currentStep<300; currentStep++) {
        nextRow2(initialRow, population[currentRule].cromossome);
        if(currentStep == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
        if(currentStep == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
      }
      // Preenche matriz de recurso compartilhado
      check = checkSync(syncRowOne, syncRowTwo);
      sharedResource[currentRow][currentRule] = check;
      if(check == 0) sharedResource[currentRow][100] += 1;
      sharedResource[100][currentRule] += check;
    }
  }
  // Calcula fitness das regras
  for(column=0; column<100; column++) {
    for(row=0; row<100; row++) {
      if(sharedResource[row][column]) {
        population[column].fitness += sharedResource[row][100];
      }
    }
  }

}

// Mostra a evolução de uma regra, imprimindo cada reticulado com um delay
void scrollRule2(int *rule, int numberOfRows) {
  Individual2 population[1];
  int row[1][ROWSIZE];
  unsigned int microseconds = 30000;
  generateRandomRows(row, 1, 0);
  generateRules2(population, 1);
  memcpy(population[0].cromossome, rule, 32*sizeof(int));
  for(int i=0; i<numberOfRows;i++){
    printRow(row[0]);
    nextRow2(row[0], population[0].cromossome);
    usleep(microseconds);
  }
}

// Insertion sort in ascending order
void insertionSort2(Individual2 population[], int initIndex, int endIndex) {
  int i, key, j;
  Individual2 keyStruct;
  for (i = initIndex+1; i <= endIndex; i++) {
    keyStruct = population[i];
    j = i-1;
    while (j >= 0 && population[j].fitness > keyStruct.fitness) {
      population[j+1] = population[j];
      j = j-1;
    }
    population[j+1] = keyStruct;
  }
}

// Insertion sort in ascending order
void insertionSortLatticePopulation(Lattice population[], int initIndex, int endIndex) {
  int i, key, j;
  Lattice keyStruct;
  for (i = initIndex+1; i <= endIndex; i++) {
    keyStruct = population[i];
    j = i-1;
    while (j >= 0 && population[j].fitness > keyStruct.fitness) {
      population[j+1] = population[j];
      j = j-1;
    }
    population[j+1] = keyStruct;
  }
}

// Print rule in binary
void printBinaryRule2(int rule[], char *fileToWrite) {
  FILE *fp;
  fp = fopen(fileToWrite, "a");
  int myrule[32];

  for(int i = 0; i < RULESIZE2; i++) myrule[i] = rule[RULESIZE2-i-1];
  for(int i = 0; i < RULESIZE2; i++) {
    fprintf(fp, "%d", myrule[i]);
  }
  fprintf(fp, "\n");
  fclose(fp);
}

// Print rule in decimal
void printRule2(Individual2 rule, char *fileToWrite) {
  FILE *fp;
  fp = fopen(fileToWrite, "a");
  int myrule[32];

  int64_t multiplier = 1;
  int64_t bigint = 0;
  for(int i = 0; i < RULESIZE2; i++) {
    myrule[i] = rule.cromossome[RULESIZE2-i-1];
  }
  for(int i = 0; i < RULESIZE2; i++) {
    bigint += multiplier * myrule[RULESIZE2-i-1];
    multiplier *= 2;
  }
  fprintf(fp, "%" PRId64 , bigint);
  fprintf(fp, " %d\n", rule.fitness);
  fclose(fp);
}

// Return rule in decimal
int64_t getRule2(Individual2 rule) {
  int myrule[32];
  int64_t multiplier = 1;
  int64_t bigint = 0;
  for(int i = 0; i < RULESIZE2; i++) {
    myrule[i] = rule.cromossome[RULESIZE2-i-1];
  }
  for(int i = 0; i < RULESIZE2; i++) {
    bigint += multiplier * myrule[RULESIZE2-i-1];
    multiplier *= 2;
  }
  return bigint;
}

int* intToBinArray(char *input) {
  int number, i, r;
  int *binArray = (int *) calloc(32, sizeof(int));
  int temp[32];

  number = strtol(input, NULL, 10);

  for(i=0;;i++) {
    r = number % 2;
    binArray[i] = r;
    number = number / 2;
    if (number < 2) {
      binArray[i+1] = number;
      break;
    }
  }

  // for(i=0; i<32; i++) temp[31-i] = binArray[i];
  // for(i=0; i<32; i++) binArray[i] = temp[i];

  return binArray;
}