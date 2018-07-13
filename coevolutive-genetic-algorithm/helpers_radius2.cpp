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
void checkPopulationShared2(int rows[][ROWSIZE], Individual2 population[], int initIndex, int endIndex) {
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  int i, j, check, currentRule, currentRow, currentStep;
  int shared[101][101] = {0};
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
      shared[currentRow][currentRule] = check;
      if(check == 0) shared[currentRow][100] += 1;
      shared[100][currentRule] += check;
    }
  }

  // Preenche fitness de acordo com recurso compartilhado
  for(i=0; i<100; i++) {
    for(j=0; j<100; j++) {
      if(shared[i][j]) {
        population[j].fitness += shared[i][100];
      }
    }
  }

}

// Mostra a evolução de uma regra, imprimindo cada reticulado com um delay
void scrollRule2(int *rule, int numberOfRows) {
  Individual2 population[1];
  int row[1][ROWSIZE];
  unsigned int microseconds = 30000;
  generateRandomRows(row, 1);
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
  int *binArray = (int *) malloc( 32 * sizeof(int));

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

  return binArray;
}