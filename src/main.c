/* Gabriela Akemi Shima (RA 135819)
 * Lab 6 - Quicksort em Mutithread
 *
 */

#include <stdio.h>
#define MAX_ELEMENTOS 10

int vetor[MAX_ELEMENTOS];

void quicksort(int primeiro, int ultimo) {
  int pivo, j, temp, i;
  printf("olar 1 !\n");
  if(primeiro < ultimo){
    pivo = primeiro;
    i = primeiro;
    j = ultimo;
    while (i < j) {
      while( (vetor[i] <= vetor[pivo]) && (i < ultimo)) {
        i ++;
      }

      while (vetor[j] > vetor[pivo]) {
        j --;
      }

        if( i < j ){
          temp = vetor[i];
          vetor[i] = vetor[j];
          vetor[j] = temp;
        }
    }
    temp = vetor[pivo];
    vetor[pivo] = vetor[j];
    vetor[j] = temp;
    printf("olar 4 !\n");
    quicksort(primeiro, j-1);
    quicksort(j+1, ultimo);
  }
}

int main() {
  int qtde_elementos = 0, numero_recebido;
  do {
    scanf("%d", &numero_recebido);
    vetor[qtde_elementos] = numero_recebido;
    qtde_elementos++;
  }while ( getchar() != '\n' && qtde_elementos < MAX_ELEMENTOS);

  quicksort(0, qtde_elementos);

  for(int i = 1; i <= qtde_elementos; ++i) {
    printf("%d ", vetor[i]);
  }
  printf("\n");

  return 0;
}
