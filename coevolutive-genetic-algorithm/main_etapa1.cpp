#include "types.h"
#include "experiments.cpp"

// Argumentos:
// 1: Nome do arquivo a ser gravado
// 2: Número de execuções
// 3: Raio da vizinhanca

int main(int argc, char *argv[]) {
  int i, experiments, radius;
  FILE *fp;

  if(argc != 4) {
    printf("Correct usage:\n $ ./main output_file executions neighborhood_size\n");
    return 1;
  }

  sscanf(argv[2], "%d", &experiments);
  sscanf(argv[3], "%d", &radius);

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

  // Realiza os experimentos de acordo com raio
  for(i=0; i<experiments; i++) {
    fp = fopen(argv[1], "a");
    fprintf(fp, "*---------- Execução %d -----------\n", i+1);
    fclose(fp);
    if(radius == 2) experimentRadius2(argv[1]);
    if(radius == 3) experimentRadius3(argv[1]);
  }

  return 0;
}