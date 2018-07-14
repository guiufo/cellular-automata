#include "types.h"
#include "generators.cpp"
#include "operators.cpp"
#include "helpers.cpp"
#include "helpers_radius2.cpp"
#include "helpers_radius3.cpp"

void experimentRadius2(char *fileToWrite) {
  Individual2 population[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;

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
      randFatherOne = (rand() % 10) + 90;
      randFatherTwo = (rand() % 10) + 90;
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

void experimentRadius3(char *fileToWrite) {
  Individual3 population[100];
  int i, j, generation;
  int rows[100][ROWSIZE];
  int randFatherOne, randFatherTwo;

  // Begin Genetic Algorithm
  // Generate initial population
  generateRules3(population, 100);
  for(generation=0; generation<NGENERATIONS; generation++) {
    // Reset fitness
    for(i=0; i<100; i++) population[i].fitness = 0;
    generateRows(rows, 100);
    checkPopulation3(rows, population, 0, 99);
    insertionSort3(population, 0, 99);

    // Simple crossover and elitism
    srand(time(NULL));
    for(i=0; i<89; i+=2) {
      randFatherOne = (rand() % 90) + 10;
      randFatherTwo = (rand() % 90) + 10;
      crossOver3(population[randFatherOne].cromossome, population[randFatherTwo].cromossome, population[i].cromossome, population[i+1].cromossome);
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