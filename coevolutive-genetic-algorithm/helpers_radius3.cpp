#include "types.h"

void checkPopulation3(int rows[][ROWSIZE], Individual3 population[], int initIndex, int endIndex) {
  int syncRowOne[ROWSIZE];
  int syncRowTwo[ROWSIZE];
  int initialRow[ROWSIZE];
  int i, currentRule, currentRow, currentStep;
  // Reset population fitness
  for(i=0; i<100; i++) population[i].fitness = 0;
  for(currentRule=0; currentRule<=endIndex; currentRule++) {
    for(currentRow=0; currentRow<100; currentRow++) {
      memcpy(initialRow, rows[currentRow], ROWSIZE*sizeof(int));
      for(currentStep=0; currentStep<300; currentStep++) {
        nextRow3(initialRow, population[currentRule].cromossome);
        if(currentStep == 298) for(i=0; i<ROWSIZE; i++) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
        if(currentStep == 299) for(i=0; i<ROWSIZE; i++) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
      }
      population[currentRule].fitness += checkSync(syncRowOne, syncRowTwo);
    }
  }
}

// Calcula fitness das populações no AG coevolutivo de avaliação simples
void checkPopulationsRadius3(Lattice latticePopulation[], Individual3 population[], int initIndex, int endIndex) {
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
        nextRow3(initialRow, population[currentRule].cromossome);
        if(currentStep == 298) memcpy(syncRowOne, initialRow, ROWSIZE*sizeof(int));
        if(currentStep == 299) memcpy(syncRowTwo, initialRow, ROWSIZE*sizeof(int));
      }
      check = checkSync(syncRowOne, syncRowTwo);
      population[currentRule].fitness += check;
      if(!check) latticePopulation[currentRow].fitness += check;
    }
  }
}

// Scroll given rule 3 for numberOfRow times
void scrollRule3(int *rule, int numberOfRows) {
  Individual3 population[1];
  int row[1][ROWSIZE];
  unsigned int microseconds = 30000;
  generateRandomRows(row, 1, 0);
  generateRules3(population, 1);
  memcpy(population[0].cromossome, rule, 128*sizeof(int));
  for(int i=0; i<numberOfRows;i++){
    printRow(row[0]);
    nextRow3(row[0], population[0].cromossome);
    usleep(microseconds);
  }
}

// Sort population by fitness in ascending order
void insertionSort3(Individual3 population[], int initIndex, int endIndex) {
  int i, key, j;
  Individual3 keyStruct;
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

// Print radius 3 rule in hexadecimal
void printHexRule3(Individual3 rule, char *fileToWrite) {
  FILE *fp;
  fp = fopen(fileToWrite, "a");
  int myrule[128];
  char four[4];
  int i, j;

  for(i = 0; i < RULESIZE3; i++) myrule[i] = rule.cromossome[RULESIZE3-i-1];
  for(i = 0; i < RULESIZE3; i += 4) {
    for(j=0; j<4; j++) {
      four[j] = myrule[j+i] + '0';
    }
    fprintf(fp, "%lx", strtol(four, NULL, 2));
  }
  fprintf(fp, " %d\n", rule.fitness);
  fclose(fp);
}

// Print radius 3 rule in binary
void printBinaryRule3(Individual3 rule, char *fileToWrite) {
  FILE *fp;
  fp = fopen(fileToWrite, "a");
  int myrule[128];

  for(int i = 0; i < RULESIZE3; i++) myrule[i] = rule.cromossome[RULESIZE3-i-1];
  for(int i = 0; i < RULESIZE3; i++) fprintf(fp, "%d", myrule[i]);
  fprintf(fp, " %d\n", rule.fitness);
  fclose(fp);
}

// Print radius 3 rule in hexadecimal
void printRule3(Individual3 rule, char *fileToWrite) {
  FILE *fp;
  fp = fopen(fileToWrite, "a");
  int myrule[128];

  __uint128_t multiplier = 1;
  __uint128_t bigint = 0;
  for(int i = 0; i < RULESIZE3; i++) {
    myrule[i] = rule.cromossome[RULESIZE3-i-1];
  }
  for(int i = 0; i < RULESIZE3; i++) {
    bigint += multiplier * myrule[RULESIZE3-i-1];
    multiplier *= 2;
  }

  fprintf(fp, "%llx", (unsigned long long)(bigint & 0xFFFFFFFFFFFFFFFF));
  fprintf(fp, " %d\n", rule.fitness);
  fclose(fp);
}

// Return rule in decimal
__uint128_t getRule3(Individual3 rule) {
  int myrule[128];
  __uint128_t multiplier = 1;
  __uint128_t bigint = 0;
  for(int i = 0; i < RULESIZE3; i++) {
    myrule[i] = rule.cromossome[RULESIZE3-i-1];
  }
  for(int i = 0; i < RULESIZE3; i++) {
    bigint += multiplier * myrule[RULESIZE3-i-1];
    multiplier *= 2;
  }
  return bigint;
}

char* hexToBinArray(char *input) {
  char *bin = (char *)malloc(128 * sizeof(char));

  for(int i=0; i<32; i++) {
    switch(input[i]) {
      case '0':
          strcat(bin, "0000");
          break;
      case '1':
          strcat(bin, "0001");
          break;
      case '2':
          strcat(bin, "0010");
          break;
      case '3':
          strcat(bin, "0011");
          break;
      case '4':
          strcat(bin, "0100");
          break;
      case '5':
          strcat(bin, "0101");
          break;
      case '6':
          strcat(bin, "0110");
          break;
      case '7':
          strcat(bin, "0111");
          break;
      case '8':
          strcat(bin, "1000");
          break;
      case '9':
          strcat(bin, "1001");
          break;
      case 'a':
      case 'A':
          strcat(bin, "1010");
          break;
      case 'b':
      case 'B':
          strcat(bin, "1011");
          break;
      case 'c':
      case 'C':
          strcat(bin, "1100");
          break;
      case 'd':
      case 'D':
          strcat(bin, "1101");
          break;
      case 'e':
      case 'E':
          strcat(bin, "1110");
          break;
      case 'f':
      case 'F':
          strcat(bin, "1111");
          break;
      default:
          strcat(bin, "0000");
          break;
    }
  }

  return bin;
}
