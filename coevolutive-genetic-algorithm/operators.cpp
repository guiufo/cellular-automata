#include "types.h"

// Crossover lattices
void crossOverRow(int firstFather[], int secondFather[], int firstChild[], int secondChild[]) {
  int i;
  // Apply one point crossover and generate children
  srand(time(NULL));
  int randomIndex = (rand() % ROWSIZE - 1) + 1;
  for(i = 0; i < randomIndex; i++) {
    firstChild[i] = firstFather[i];
    secondChild[i] = secondFather[i];
  }
  for(i = randomIndex; i < ROWSIZE; i++) {
    firstChild[i] = secondFather[i];
    secondChild[i] = firstFather[i];
  }
}

// Crossover 2 radius 2 rules
void crossOver2(int firstFather[], int secondFather[], int firstChild[], int secondChild[]) {
  int i;
  // Apply one point crossover and generate children
  srand(time(NULL));
  int randomIndex = (rand() % RULESIZE2 - 1) + 1;
  for(i = 0; i < randomIndex; i++) {
    firstChild[i] = firstFather[i];
    secondChild[i] = secondFather[i];
  }
  for(i = randomIndex; i < RULESIZE2; i++) {
    firstChild[i] = secondFather[i];
    secondChild[i] = firstFather[i];
  }
}

// Crossover 2 radius 3 rules
void crossOver3(int firstFather[], int secondFather[], int firstChild[], int secondChild[]) {
  int i;
  // Apply one point crossover and generate children
  srand(time(NULL));
  int randomIndex = (rand() % RULESIZE3 - 1) + 1;
  for(i = 0; i < randomIndex; i++) {
    firstChild[i] = firstFather[i];
    secondChild[i] = secondFather[i];
  }
  for(i = randomIndex; i < RULESIZE3; i++) {
    firstChild[i] = secondFather[i];
    secondChild[i] = firstFather[i];
  }
}

// Mutate an radius 2 rule
void mutate2(int rule[]) {
  srand(time(NULL));
  for(int i=0; i<RULESIZE2; i++) {
    if( ((double)rand() / (double)RAND_MAX) < MUTATIONRATE ) {
      if(rule[i] == 1) rule[i] = 0;
      else rule[i] = 1;
    }
  }
}

// Mutate an radius 3 rule
void mutate3(int rule[]) {
  srand(time(NULL));
  for(int i=0; i<RULESIZE3; i++) {
    if( ((double)rand() / (double)RAND_MAX) < MUTATIONRATE ) {
      if(rule[i] == 1) rule[i] = 0;
      else rule[i] = 1;
    }
  }
}

// Mutate an radius 3 rule
void mutateLattice(int lattice[]) {
  srand(time(NULL));
  for(int i=0; i<ROWSIZE; i++) {
    if( ((double)rand() / (double)RAND_MAX) < MUTATIONRATE ) {
      if(lattice[i] == 1) lattice[i] = 0;
      else lattice[i] = 1;
    }
  }
}
