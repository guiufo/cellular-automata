#include "types.h"
#include "experiments.cpp"

// Argumentos:
// 1: Nome do arquivo a ser gravado
// 2: Número de execuções
// 3: Raio da vizinhanca
// 4: Ambiente
// Ambientes:
//   (1) AG simples
//   (2) AG com avaliação por recurso compartilhado
//   (3) AG coevolutivo com avaliação simples
//   (4) AG coevolutivo com avaliação por recurso compartilhado

int main(int argc, char *argv[]) {
  int i, experiments, radius, environment;
  FILE *fp;

  if(argc != 4) {
    printf("Correct usage:\n $ ./main output_file executions neighborhood_size enviroment\n");
    return 1;
  }

  sscanf(argv[2], "%d", &experiments);
  sscanf(argv[3], "%d", &radius);
  sscanf(argv[4], "%d", &environment);

  if(radius != 2 && radius !=3) {
    printf("Neighborhood must be 2 or 3.\n");
    return 1;
  }

  // Imprime cabeçalho com parâmetros de uma execução
  fp = fopen(argv[1], "a");
  fprintf(fp, "*************************************\n");
  fprintf(fp, "*\t\t%d Execuções de Raio %d\n", experiments, radius);
  fprintf(fp, "*************************************\n");
  fprintf(fp, "*\n");
  fprintf(fp, "*\t\tNúmero de gerações: %d\n", NGENERATIONS);
  fprintf(fp, "*\t\tReticulados iniciais: %d\n", NROWS);
  fprintf(fp, "*\t\tTaxa de mutação: %f\n", MUTATIONRATE);
  fprintf(fp, "*\n");
  fclose(fp);

  // Realiza os experimentos de acordo com ambiente e raio
  for(i=0; i<experiments; i++) {
    fp = fopen(argv[1], "a");
    fprintf(fp, "*---------- Execução %d -----------\n", i+1);
    fclose(fp);
    switch(environment) {
      case 1:
        if(radius == 2) experimentRadius2(argv[1]);
        if(radius == 3) experimentRadius3(argv[1]);
        break;
      case 2:
        if(radius == 2) experimentSharedRadius2(argv[1]);
        if(radius == 3) experimentSharedRadius3(argv[1]);
        break;
      case 3:
        // if(radius == 2) experimentSharedRadius2(argv[1]);
        // if(radius == 3) experimentSharedRadius3(argv[1]);
        break;
      case 4:
        // if(radius == 2) experimentSharedRadius2(argv[1]);
        // if(radius == 3) experimentSharedRadius3(argv[1]);
        break;
    };
  }

  return 0;
}