#include "header.h"

int verifica_arv_vazia(Arvore* a){
    return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
    if (!verifica_arv_vazia(a)) {
        arv_libera (a->esq);
        arv_libera (a->dir);
        free(a);
    }
    return NULL;
}

Arvore* inserir (Arvore *a, Veiculo v) {
    if (a == NULL) {
        a = (Arvore*)malloc(sizeof(Arvore));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if (strcmp(v.placa , a->info.placa) < 0) {
        a->esq = inserir (a->esq, v);
    }
    else { a->dir = inserir (a->dir, v); }
    return a;
}

Arvore* buscar (Arvore* a, const char* v) {
    if((a == NULL) || (strcmp(v, a->info.placa) == 0)){
        return a;
    }else if (strcmp(v, a->info.placa) < 0) {
        return buscar (a->esq, v);
    }else{
        return buscar (a->dir, v);
    }
}

Arvore* remover_vehicle(Arvore *a, Veiculo v){
    if (a == NULL) {
       return NULL;
    }else{
        if(strcmp(v.placa, a->info.placa) < 0){
             a->esq = remover_vehicle(a->esq, v);
        }else if(strcmp(v.placa, a->info.placa) > 0){
             a->dir = remover_vehicle(a->dir, v);
        }else{
            //folha
            if(a->dir == NULL && a->esq == NULL){
                    free(a);
                    return NULL;
            }
            //só tem um elemento
            else if(a->dir == NULL){
                 Arvore* esq = a->esq;
                 free (a);
                 return esq;
            }
            else if(a->esq == NULL){
                 Arvore* dir = a->dir;
                 free (a);
                 return dir;
            }
            //tem dois elementos
            else{
                Arvore* esq = a->esq;
                while(esq->dir != NULL){
                   esq = esq->dir;
                }
                a->info = esq->info;
                esq->info = v;
                a->esq = remover_vehicle(a->esq, v);
            }
        }
    }
    return a;
}

void delete_veh_cli(Arvore* a, int id_clien){
    if(!verifica_arv_vazia(a)){
       Veiculo veiculos = a->info;
       if(id_clien == veiculos.cli_id){
        vehicles = remover_vehicle(vehicles, veiculos);
       }
       delete_veh_cli(a->esq, id_clien);
       delete_veh_cli(a->dir, id_clien);
    }
}
