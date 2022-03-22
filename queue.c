#include "header.h"

/* OPEN  TAD FILA  */
//functions Fila
Fila* criarFila (void) {
    return NULL;
}

/*int return_ultId(Fila *fila){
    Fila* cabeca = fila;
    //verifiica se fila não é vazia
    if(fila != NULL){
        while( fila != NULL){
            //Cria uma nova posição no final da fila
            if(fila->next == NULL){
                return fila->info.id;
            }
            fila = fila->next;
        }
    }else{
        return 0;
    }
}*/

Fila* enqueueFila (Fila* fila, Veiculo elem){
    Fila* cabeca = fila;
    //verifiica se fila não é vazia
    if(fila != NULL){
        while( fila != NULL){
            //Cria uma nova posição no final da fila
            if(fila->next == NULL){
                Fila* novo =(Fila*)malloc(sizeof(Fila));
                novo->info = elem;
                novo->next = NULL;
                novo->prev = fila;
                fila->next = novo;
                return cabeca;
            }
            fila = fila->next;
        }
    }else{
        //Cria uma cabeça na fila
        Fila* novo =(Fila*)malloc(sizeof(Fila));
        novo->info = elem;
        novo->next = NULL;
        novo->prev = fila;
        return novo;
    }
}

int emptyFila(Fila* fila){
    return (fila->prev == fila->next); //Analisa se a fila é vazia !
}

//tira da frente
Fila* dequeueFila (Fila *fila){
       Fila* v = fila;
       if (emptyFila(fila)){
            // se a fila for vazia retorna ela mesma
            printf("vazia");
            return NULL;
       }else{
           // Retira o elemento da fila
           fila = fila->next;
           fila->prev = NULL;
           free(v);
           return fila;
       }
}

Veiculo frontFila(Fila* fila){
    if (fila == NULL){
        Veiculo car;
        return car; // se fila vazia retorna 0
    }
    return fila->info;// retorna um valor inteiro do elemento da cabeça
}

//search element of fila
Fila* procurar_Ele (char* elem){
    Fila* v = vehiclesEqueue;
    while (v != NULL) {
        if(strcmp(v->info.placa, elem) == 0){
            return v;
        }
        v = v->next;
    }
    return NULL;
}

//delete element of fila
Fila* remover_daFila(Fila *fila, char* elem) {

   Fila* no = procurar_Ele (elem);

   if (no == NULL) {
      /*O elemento não existe: */
      return vehiclesEqueue;
   }
   else if (no->prev == NULL) {
      /*O elemento está na cabeça*/
      return(dequeueFila(fila));
   }
   else if (no->next == NULL) {
      /*O elemento está na  cauda*/
      Fila *anterior = no->prev;
      anterior->next = NULL;
      free(no);
      return fila;
   }else {
      /*O elemento está no meio */
      Fila *anterior = no->prev;
      anterior->next = no->next;
      Fila *proximo = no->next;
      proximo->prev = no->prev;
      free(no);
      return fila;
   }
}

void imprimirFila(void){
     Veiculo car;
     if(vehiclesEqueue != NULL){
        while(!emptyFila(vehiclesEqueue)){
          car =  frontFila(vehiclesEqueue);
          printf(" placa: %s \n id_cli: %d \n modelo: %s\n", car.placa,  car.cli_id, car.modelo);
          vehiclesEqueue = dequeueFila(vehiclesEqueue);
        }
        car =  frontFila(vehiclesEqueue);
        printf(" placa: %s \n id_cli: %d \n modelo: %s\n", car.placa,  car.cli_id, car.modelo);
     }
}

/* CLOSE TAD FILA */
