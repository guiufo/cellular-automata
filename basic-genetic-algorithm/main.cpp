#include "types.h"
#include "experiments.cpp"

// Argumentos:
// 1: nome do arquivo a ser gravado
// 2: numero de execucoes
// 3: raio da vizinhanca

int main(int argc, char *argv[]) {
  int i, experiments, radius;
  FILE *fp;

  sscanf(argv[2], "%d", &experiments);
  sscanf(argv[3], "%d", &radius);

  if(radius != 2 && radius !=3) {
    printf("Correct usage:\n $ ./main output_file executions neighborhood_size\n");
    return 1;
  }

  fp = fopen(argv[1], "a");
  fprintf(fp, "\n\n*************************************\n");
  fprintf(fp, "\t\t\t%d Experimentos de Raio %d\n", experiments, radius);
  fprintf(fp, "*************************************\n");
  fprintf(fp, "Número de gerações: %d\n", NGENERATIONS);
  fprintf(fp, "Reticulados iniciais: %d\n", NROWS);
  fprintf(fp, "Taxa de mutação: %f\n ", MUTATIONRATE);
  fclose(fp);
  for(i=0; i<experiments; i++) {
    fp = fopen(argv[1], "a");
    fprintf(fp, "----------- Experimento %d -----------\n", i+1);
    fclose(fp);
    if(radius == 2) experimentRadius2(argv[1]);
    if(radius == 3) experimentRadius3(argv[1]);
  }

  return 0;
}