/* Gabriela Akemi Shima (RA 135819)
 * Lab 6 - Quicksort em Mutithread
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <pthread.h>

 #define MAX_WORKERS 2
 #define ATIVO 1
 #define INATIVO 0
 #define MAX_ELEMENTOS 200000

int vetor[MAX_ELEMENTOS];


 typedef struct {
   int indice_inicio_esquerda;
   int indice_inicio_direita;
   int indice_fim_esquerda;
   int indice_fim_direita;
   int ID;
 } thread_args;

 pthread_mutex_t trava;
 int n_workers = 0;
 pthread_t workers[MAX_WORKERS];
 int worker_status[MAX_WORKERS];

 void* worker(void *arg) {
   thread_args *info = (thread_args *)arg;
   quicksort(info->indice_inicio_esquerda, info->indice_fim_esquerda);
   quicksort(info->indice_inicio_direita, info->indice_fim_direita);
   pthread_mutex_lock(&trava);
   n_workers -= 1;
   worker_status[info->ID] = INATIVO;
   free(info);
   pthread_mutex_unlock(&trava);
   return NULL;
 }


void quicksort(int primeiro, int ultimo) {
  int pivo, j, temp, i;
  thread_args *send_args;
  int k;

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
    if (n_workers >= MAX_WORKERS) {
      //printf("Muitas tarefas sendo executadas. Ingnorando entrada\n");
      quicksort(primeiro, j-1);
      quicksort(j+1, ultimo);
    } else {
      pthread_mutex_lock(&trava);
      //printf("Iniciando nova thread\n");
      send_args = (thread_args*)malloc(sizeof(thread_args));
      send_args->indice_inicio_esquerda = primeiro;
      send_args->indice_fim_esquerda = j-1;
      send_args->indice_inicio_direita = j+1;
      send_args->indice_fim_direita = ultimo;
      /* Procura espaco para thread livre */
      k = 0;
      while (worker_status[k] == ATIVO) k++;
      send_args->ID = k;
      worker_status[k] = ATIVO;
      n_workers += 1;
      //printf("Threads ativas: %d de %d\n", n_workers, MAX_WORKERS);
      pthread_create(& (workers[j]), NULL, worker, (void*) send_args);
      pthread_mutex_unlock(&trava);
    }
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
