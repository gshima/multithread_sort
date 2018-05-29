/* Gabriela Akemi Shima (RA 135819)
 * Lab 6 - Quicksort em Mutithread
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <pthread.h>

 #define MAX_WORKERS 4
 #define ATIVO 1
 #define INATIVO 0
 #define MAX_ELEMENTOS 200000

int vetor[MAX_ELEMENTOS];

 // typedef struct {
 //   int N;
 //   int ID;
 // } thread_args;

 // pthread_mutex_t trava;
 // int n_workers = 0;
 // pthread_t workers[MAX_WORKERS];
 // int worker_status[MAX_WORKERS];

 // int fibo(int N) {
 //   if (N<=2) return 1;
 //   else return (fibo(N-1) + fibo(N-2));
 // }

 // void* worker(void *arg) {
 //   thread_args *info = (thread_args *)arg;
 //   int M = fibo(info->N);
 //   printf("Fibo(%d)=%d\n", info->N, M);
 //   pthread_mutex_lock(&trava);
 //   n_workers -= 1;
 //   worker_status[info->ID] = INATIVO;
 //   free(info);
 //   pthread_mutex_unlock(&trava);
 //   return NULL;
 // }


void quicksort(int primeiro, int ultimo) {
  int pivo, j, temp, i;

  if(primeiro < ultimo){
    pivo = primeiro;
    i = primeiro;
    j = ultimo;
    while (i < j) {
      while( (vetor[i] <= vetor[pivo]) && (i < ultimo)) {
        i ++;
      }

      while ( vetor[j] > vetor[pivo] ) {
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
  }while ( getchar() != '\n' );

  quicksort(0, qtde_elementos-1);

  for(int i = 0; i < qtde_elementos; ++i) {
    printf("%d", vetor[i]);
    if (i < qtde_elementos -1)
      printf(" ");
  }
  printf("\n");

  return 0;
}
