#include "types.h"
#include "generators.cpp"
#include "operators.cpp"
#include "helpers.cpp"
#include "helpers_radius2.cpp"
#include "helpers_radius3.cpp"

// Experimento evolutivo com população e avaliação simples
void experimentRadius2(char *fileToWrite) {
  Individual2 population[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;
  int randNumber1, randNumber2;

  // Begin Genetic Algorithm
  // Generate initial population
  generateRules2(population, 100);
  for(generation=0; generation<NGENERATIONS; generation++) {
    // Generate random, uniform distributed rows of 149 cells
    generateRows(rows, 100);
    // Calculate fitness of population
    checkPopulation2(rows, population, 0, 99);
    // Sorts in ascending order
    insertionSort2(population, 0, 99);
    // Simple crossover and elitism
    srand(time(NULL));
    for(i=0; i<89; i+=2) {
      // Select two random fathers among 10 best
      randNumber1 = (rand() % 10) + 90;
      randNumber2 = (rand() % 10) + 90;
      while(randNumber1 == randNumber2) {
        randNumber1 = (rand() % 10) + 90;
        randNumber2 = (rand() % 10) + 90;
      }
      randFatherOne = randNumber1;
      randFatherTwo = randNumber2;
      // Makes crossover
      crossOver2(
        population[randFatherOne].cromossome, population[randFatherTwo].cromossome,
        population[i].cromossome, population[i+1].cromossome
      );
      mutate2(population[i].cromossome);
      mutate2(population[i+1].cromossome);
    }
  }
  // End Genetic Algorithm

  checkPopulation2(rows, population, 0, 99);
  insertionSort2(population, 0, 99);

  // Print rules without repetition
  for(i=0; i<100; i++) {
    for(j=0; j<i; j++) {
      if(getRule2(population[i]) == getRule2(population[j])) break;
    }
    if(i == j) printRule2(population[i], fileToWrite);
  }
}

// Experimento coevolutivo com avaliação simples
void coevolutiveExperimentRadius2(char *fileToWrite) {
  Individual2 population[100];
  Lattice latticePopulation[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;
  int randNumber1, randNumber2;

  // Begin Genetic Algorithm
  // Generate initial population
  generateRules2(population, 100);
  // Generate random, uniform distributed rows of 149 cells
  generateRowsPopulation(latticePopulation, 100);

  for(generation=0; generation<NGENERATIONS; generation++) {
    // Calculate fitness of populations
    checkPopulationsRadius2(latticePopulation, population, 0, 99);
    // Sorts in ascending order
    insertionSort2(population, 0, 99);
    insertionSortLatticePopulation(latticePopulation, 0, 99);
    // Simple crossover and elitism
    srand(time(NULL));
    // Realiza seleção, crossover e mutação nas regras
    for(i=0; i<89; i+=2) {
      // Select two random fathers among 10 best
      randNumber1 = (rand() % 10) + 90;
      randNumber2 = (rand() % 10) + 90;
      while(randNumber1 == randNumber2) {
        randNumber1 = (rand() % 10) + 90;
        randNumber2 = (rand() % 10) + 90;
      }
      randFatherOne = randNumber1;
      randFatherTwo = randNumber2;
      // Makes crossover
      crossOver2(
        population[randFatherOne].cromossome, population[randFatherTwo].cromossome,
        population[i].cromossome, population[i+1].cromossome
      );
      mutate2(population[i].cromossome);
      mutate2(population[i+1].cromossome);
      // Makes crossover
      crossOverRow(
        latticePopulation[randFatherOne].cromossome, latticePopulation[randFatherTwo].cromossome,
        latticePopulation[i].cromossome, latticePopulation[i+1].cromossome
      );
      mutateLattice(latticePopulation[i].cromossome);
      mutateLattice(latticePopulation[i+1].cromossome);
    }
  }
  // End Genetic Algorithm

  checkPopulationsRadius2(latticePopulation, population, 0, 99);
  insertionSort2(population, 0, 99);
  insertionSortLatticePopulation(latticePopulation, 0, 99);

  // Print rules without repetition
  for(i=0; i<100; i++) {
    for(j=0; j<i; j++) {
      if(getRule2(population[i]) == getRule2(population[j])) break;
    }
    if(i == j) printRule2(population[i], fileToWrite);
  }
}

//*****************************
//*   Experimentos Raio 3
//*****************************

void experimentRadius3(char *fileToWrite) {
  Individual3 population[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;
  int randNumber1, randNumber2;

  // Begin Genetic Algorithm
  // Generate initial population
  generateRules3(population, 100);
  for(generation=0; generation<NGENERATIONS; generation++) {
    generateRows(rows, 100);
    checkPopulation3(rows, population, 0, 99);
    insertionSort3(population, 0, 99);

    // Simple crossover and elitism
    srand(time(NULL));
    for(i=0; i<89; i+=2) {
      // Select two random fathers among 10 best
      randNumber1 = (rand() % 10) + 90;
      randNumber2 = (rand() % 10) + 90;
      while(randNumber1 == randNumber2) {
        randNumber1 = (rand() % 10) + 90;
        randNumber2 = (rand() % 10) + 90;
      }
      randFatherOne = randNumber1;
      randFatherTwo = randNumber2;
      crossOver3(
        population[randFatherOne].cromossome, population[randFatherTwo].cromossome,
        population[i].cromossome, population[i+1].cromossome
      );
      mutate3(population[i].cromossome);
      mutate3(population[i+1].cromossome);
    }
  }

  checkPopulation3(rows, population, 0, 99);
  insertionSort3(population, 0, 99);

  // Print rules without repetition
  for(i=0; i<100; i++) {
    for(j=0; j<i; j++) {
      if(getRule3(population[i]) == getRule3(population[j])) break;
    }
    if(i == j) printHexRule3(population[i], fileToWrite);
  }
}

// Experimento coevolutivo com avaliação simples
void coevolutiveExperimentRadius3(char *fileToWrite) {
  Individual3 population[100];
  Lattice latticePopulation[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;
  int randNumber1, randNumber2;

  // Begin Genetic Algorithm
  // Generate initial population
  generateRules3(population, 100);
  // Generate random, uniform distributed rows of 149 cells
  generateRowsPopulation(latticePopulation, 100);

  for(generation=0; generation<NGENERATIONS; generation++) {
    // Calculate fitness of populations
    checkPopulationsRadius3(latticePopulation, population, 0, 99);
    // Sorts in ascending order
    insertionSort3(population, 0, 99);
    insertionSortLatticePopulation(latticePopulation, 0, 99);
    // Simple crossover and elitism
    srand(time(NULL));
    // Realiza seleção, crossover e mutação nas regras
    for(i=0; i<89; i+=2) {
      // Select two random fathers among 10 best
      randNumber1 = (rand() % 10) + 90;
      randNumber2 = (rand() % 10) + 90;
      while(randNumber1 == randNumber2) {
        randNumber1 = (rand() % 10) + 90;
        randNumber2 = (rand() % 10) + 90;
      }
      randFatherOne = randNumber1;
      randFatherTwo = randNumber2;
      // Makes crossover
      crossOver3(
        population[randFatherOne].cromossome, population[randFatherTwo].cromossome,
        population[i].cromossome, population[i+1].cromossome
      );
      mutate3(population[i].cromossome);
      mutate3(population[i+1].cromossome);
      // Makes crossover
      crossOverRow(
        latticePopulation[randFatherOne].cromossome, latticePopulation[randFatherTwo].cromossome,
        latticePopulation[i].cromossome, latticePopulation[i+1].cromossome
      );
      mutateLattice(latticePopulation[i].cromossome);
      mutateLattice(latticePopulation[i+1].cromossome);
    }
  }
  // End Genetic Algorithm

  checkPopulationsRadius3(latticePopulation, population, 0, 99);
  insertionSort3(population, 0, 99);
  insertionSortLatticePopulation(latticePopulation, 0, 99);

  // Print rules without repetition
  for(i=0; i<100; i++) {
    for(j=0; j<i; j++) {
      if(getRule3(population[i]) == getRule3(population[j])) break;
    }
    if(i == j) printRule3(population[i], fileToWrite);
  }
}