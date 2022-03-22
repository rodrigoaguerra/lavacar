#include "header.h"

/* Working with list*/
ListaServico* criar (void) {
    return NULL;
}

ListaInsumo* criar_list_ins(void){
    return NULL;
}

ListaCliente* criar_list_cli(void){
    return NULL;
}

ListaUsuario* criar_list_usu(void){
    return NULL;
}

ListaServico* inserirList (ListaServico* lista, Servico elem) {
    ListaServico* novo =(ListaServico*)malloc(sizeof(ListaServico));
    novo->info = elem;
    novo->next = lista;
    novo->prev = NULL;
/* verifica se lista nao esta vazia */
    if (lista != NULL)
    lista->prev = novo;
    return novo;
}

ListaInsumo* inserirInsumo(ListaInsumo* lista, Insumo elem){
    ListaInsumo* novo =(ListaInsumo*)malloc(sizeof(ListaInsumo));
    novo->info = elem;
    novo->next = lista;
    novo->prev = NULL;
    /* verifica se lista nao esta vazia */
    if (lista != NULL)
    lista->prev = novo;
    return novo;
}

ListaCliente* inserirlistcli (ListaCliente* lista, Cliente elem) {
    ListaCliente* novo =(ListaCliente*)malloc(sizeof(ListaCliente));
    novo->info = elem;
    novo->next = lista;
    novo->prev = NULL;
    /* verifica se lista nao esta vazia */
    if (lista != NULL)
    lista->prev = novo;
    return novo;
}

ListaUsuario* inserirlistusu (ListaUsuario* lista, Usuario elem) {
    ListaUsuario* novo =(ListaUsuario*)malloc(sizeof(ListaUsuario));
    novo->info = elem;
    novo->next = lista;
    novo->prev = NULL;
    /* verifica se lista nao esta vazia */
    if (lista != NULL)
    lista->prev = novo;
    return novo;
}

void imprimir (ListaServico* lista) {
    ListaServico* v; /*var. para percorrer a lista*/
    for (v = lista; v != NULL; v = v->next) {
        printf("Valor: %d\n", v->info.serId);
    }
}

void imprimir_para_frente (ListaServico* lista) {
    ListaServico* v; /*var. para percorrer a lista*/
    for (v = lista; v != NULL; v = v->next) {
        printf("Valor: %d\n", v->info.serId);
    }
}

void imprime_anteriores (ListaServico* lista) {
    ListaServico* v; /*var. para percorrer a lista*/
    for (v = lista; v != NULL; v = v->prev) {
        printf("Valor: %d\n", v->info.serId);
    }
}

void imprimir_insumos (ListaInsumo* lista){
    ListaInsumo* v; /*var. para percorrer a lista*/
    for (v = lista; v != NULL; v = v->next) {
        printf("Valor: %d\n", v->info.insId);
    }
}

void imprimirlistcli (ListaCliente* lista) {
     ListaCliente* v; /*var. para percorrer a lista*/
     for (v = lista; v != NULL; v = v->next) {
        printf("Valor: %d\n", v->info.id);
     }
}

void imprimirlistusu (ListaUsuario* lista) {
     ListaUsuario* v; /*var. para percorrer a lista*/
     for (v = lista; v != NULL; v = v->next) {
        printf("Valor: %d\n", v->info.userId);
     }
}

ListaServico* procurar (ListaServico* lista, int elem){
    ListaServico* v = lista;
    while (v != NULL) {
        if(v->info.serId == elem){
            return v;
        }
        v = v->next;
    }
    return NULL;
}

ListaInsumo* procurar_insumos (ListaInsumo* lista, int elem){
    ListaInsumo* v = lista;
    while (v != NULL) {
        if(v->info.insId == elem){
            return v;
        }
        v = v->next;
    }
    return NULL;
}

ListaCliente* procurarlistcli (ListaCliente* lista, int elem){
    ListaCliente* v = lista;
    while (v != NULL) {
        if(v->info.id == elem){
            return v;
        }
        v = v->next;
    }
    return NULL;
}

ListaUsuario* procurarlistusu (ListaUsuario* lista, int elem){
    ListaUsuario* v = lista;
    while (v != NULL) {
        if(v->info.userId == elem){
            return v;
        }
        v = v->next;
    }
    return NULL;
}

ListaServico* removerList (ListaServico* lista, int elem){
    ListaServico* no = procurar(lista, elem);
    if(no == NULL){
        printf("nao existe \n");
        return lista;
    }

    /*proximo elemento se torna a cabeça*/
    if(no->prev == NULL){
        if(!(no->next == NULL)){
          printf("cabeça \n id = %d  nome : %s \n", no->info.serId, no->info.nome);
          lista = no->next;
          lista->prev = NULL;
        }else{
          printf("ultimo \n id = %d  nome : %s \n", no->info.serId, no->info.nome);
          free (no);
          return NULL;
        }
    }

    /*o anterior  do elemento se torna a cauda*/
    else if(no->next == NULL){
        printf("cauda \n id = %d  nome : %s \n", no->info.serId, no->info.nome);
        ListaServico* prev = no->prev;
        prev->next = NULL;
    }

    /*nesse caso está no meio*/
    else{
        printf("meio \n id = %d  nome : %s \n", no->info.serId, no->info.nome);
        /*o next do anterior do elemento recebe o proximo elemento do elemento*/
        ListaServico* prev = no->prev;
        prev->next = no->next;
        /*o prev do proximo elemento recebe o anteiror do elemento do elemento*/
        ListaServico* next = no->next;
        next->prev = no->prev;
    }
    /*liberou nó e voltou lista sem o elemento*/
    free (no);
    return lista;
}

ListaInsumo* removerInsumo (ListaInsumo *lista, int elem){
    ListaInsumo* no = procurar_insumos(lista, elem);
    /* não existe */
    if(no == NULL){
        //printf("não existe \n");
        return lista;
    }

    /*proximo elemento se torna a cabeça*/
    if(no->prev == NULL){
        if(!(no->next == NULL)){
          //printf("cabeça \n id = %d  nome : %s \n", no->info.insId, no->info.nome);
          lista = no->next;
          lista->prev = NULL;
        }else{
          //printf("ultimo \n id = %d  nome : %s \n", no->info.insId, no->info.nome);
          free (no);
          return NULL;
        }
    }

    /*o anterior  do elemento se torna a cauda*/
    else if(no->next == NULL){
        //printf("cauda \n id = %d  nome : %s \n", no->info.insId, no->info.nome);
        ListaInsumo* prev = no->prev;
        prev->next = NULL;
    }

    /*nesse caso está no meio*/
    else{
        //printf("meio \n id = %d  nome : %s \n", no->info.insId, no->info.nome);
        /*o next do anterior do elemento recebe o proximo elemento do elemento*/
        ListaInsumo* prev = no->prev;
        prev->next = no->next;
        /*o prev do proximo elemento recebe o anteiror do elemento do elemento*/
        ListaInsumo* next = no->next;
        next->prev = no->prev;
    }
    /*liberou nó e voltou lista sem o elemento*/
    /*é o ultimo elemento*/

    free (no);
    return lista;
}

ListaCliente* removerlistcli (ListaCliente* lista, int elem){
    ListaCliente* no = procurarlistcli(lista, elem);
    if(no == NULL){
        printf("nao existe \n");
        return lista;
    }

    /*proximo elemento se torna a cabeça*/
    if(no->prev == NULL){
        if(!(no->next == NULL)){
          printf("cabeça \n id = %d  nome : %s \n", no->info.id, no->info.nome);
          lista = no->next;
          lista->prev = NULL;
        }else{
          printf("ultimo \n id = %d  nome : %s \n", no->info.id, no->info.nome);
          free (no);
          return NULL;
        }
    }

    /*o anterior  do elemento se torna a cauda*/
    else if(no->next == NULL){
        printf("cauda \n id = %d  nome : %s \n", no->info.id, no->info.nome);
        ListaCliente* prev = no->prev;
        prev->next = NULL;
    }

    /*nesse caso está no meio*/
    else{
        printf("meio \n id = %d  nome : %s \n", no->info.id, no->info.nome);
        /*o next do anterior do elemento recebe o proximo elemento do elemento*/
        ListaCliente* prev = no->prev;
        prev->next = no->next;
        /*o prev do proximo elemento recebe o anteiror do elemento do elemento*/
        ListaCliente* next = no->next;
        next->prev = no->prev;
    }
    /*liberou nó e voltou lista sem o elemento*/
    free (no);
    return lista;
}

ListaUsuario* removerlistusu (ListaUsuario* lista, int elem){
    ListaUsuario* no = procurarlistusu(lista, elem);
    if(no == NULL){
        printf("nao existe \n");
        return lista;
    }

    /*proximo elemento se torna a cabeça*/
    if(no->prev == NULL){
        if(!(no->next == NULL)){
          printf("cabeça \n id = %d  nome : %s \n", no->info.userId, no->info.nome);
          lista = no->next;
          lista->prev = NULL;
        }else{
          printf("ultimo \n id = %d  nome : %s \n", no->info.userId, no->info.nome);
          free (no);
          return NULL;
        }
    }

    /*o anterior  do elemento se torna a cauda*/
    else if(no->next == NULL){
        printf("cauda \n id = %d  nome : %s \n", no->info.userId, no->info.nome);
        ListaUsuario* prev = no->prev;
        prev->next = NULL;
    }

    /*nesse caso está no meio*/
    else{
        printf("meio \n id = %d  nome : %s \n", no->info.userId, no->info.nome);
        /*o next do anterior do elemento recebe o proximo elemento do elemento*/
        ListaUsuario* prev = no->prev;
        prev->next = no->next;
        /*o prev do proximo elemento recebe o anteiror do elemento do elemento*/
        ListaUsuario* next = no->next;
        next->prev = no->prev;
    }
    /*liberou nó e voltou lista sem o elemento*/
    free (no);
    return lista;
}

void liberar (ListaServico* lista){
    ListaServico* v; /*var. para percorrer a lista*/
    v = lista;
    while (v != NULL) {
        ListaServico* aux = v->next; /*guarda ref. p/ prox.*/
        free (v); /*libera a memoria apontada por v*/
        v = aux; /*faz v apontar p/ o prox. elem.*/
    }
}

void liberarInsumos (ListaInsumo *lista){
    ListaInsumo* v; /*var. para percorrer a lista*/
    v = lista;
    while (v != NULL) {
        ListaInsumo *aux = v->next; /*guarda ref. p/ prox.*/
        free (v); /*libera a memoria apontada por v*/
        v = aux; /*faz v apontar p/ o prox. elem.*/
    }
}

void liberarlistcli (ListaCliente* lista){
    ListaCliente* v; /*var. para percorrer a lista*/
    v = lista;
    while (v != NULL) {
        ListaCliente* aux = v->next; /*guarda ref. p/ prox.*/
        free (v); /*libera a memoria apontada por v*/
        v = aux; /*faz v apontar p/ o prox. elem.*/
    }
}

void liberarlistusu (ListaUsuario* lista){
    ListaUsuario* v; /*var. para percorrer a lista*/
    v = lista;
    while (v != NULL) {
        ListaUsuario* aux = v->next; /*guarda ref. p/ prox.*/
        free (v); /*libera a memoria apontada por v*/
        v = aux; /*faz v apontar p/ o prox. elem.*/
    }
}
