#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no* prox;
}Lista;

int vazia(Lista* l){
    return (l == NULL);
}

Lista* insere (Lista* l, int info){
    Lista* aux = malloc (sizeof(Lista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

Lista* insereFila (Lista *l, int info){
    if(vazia(l)){
        Lista* aux = malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        return aux;
    }
 
    l->prox = insereFila(l->prox, info);
    return l;
    
}

Lista* insereOrdenado(Lista* l, int info) {
    if (vazia(l) || info < l->info) {
        Lista* aux = (Lista*) malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = l;
        return aux;
    }

    l->prox = insereOrdenado(l->prox, info);
    return l;
}

Lista* removeLista(Lista* l, int info){
    if(!vazia(l)){
        if(l->info == info){
            Lista* aux;
            aux = l->prox;
            free(l);
            return aux;
        }
        l->prox = removeLista(l->prox, info);
    }
    return l;
}

Lista* removeOcorrencias(Lista* l, int info){ //remove todas as ocorrencias de info
    if(!vazia(l)){
        if(l->info == info){
            Lista* aux = l->prox;
            free(l);

            return removeOcorrencias(aux, info);
        }  
        l->prox = removeOcorrencias(l->prox, info);
        return l;
    }
    return NULL;   
}

int buscaLista(Lista* l, int info){
    if(!vazia(l)){
        if(info == l->info){
            return l->info;
        }  
        return buscaLista(l->prox, info);
    }
    return -1;
}

int somaIntervalo(Lista* l, int a, int b){
    if(!vazia(l)){
        if(l->info >= a && l->info <= b){
            return l->info + somaIntervalo (l->prox, a, b);
        }
 
        return somaIntervalo(l->prox, a , b);
    } 
    
    return 0;
}

void printLista (Lista* l){
    if(!vazia(l)){
        printf("%d ", l->info);
        printLista(l->prox);
    } 
    else    
        printf("\n");   
}

Lista* obter_sublista2(Lista* l, int a, int b){ 
    if(vazia(l)) return NULL;

    Lista* aux = NULL;
    if(b == 0){
        return insereFila(aux, l->info);
    }
    if(a == 0){
        aux = insereFila(aux, l->info);
        aux->prox = obter_sublista2(l->prox, a, --b);
        return aux;
    }
    return obter_sublista2(l->prox, --a, --b);
}

void imprimeIntervalo(Lista *l, int a, int b){
    if(!vazia(l)){
        if(l->info >= a && l->info <= b){
            printf("%d ", l->info);
            imprimeIntervalo(l->prox, a, b);
        }
        else {
            imprimeIntervalo(l->prox, a, b);
        }
    }
    printf("\n");
}

Lista* concatena(Lista* l1, Lista* l2){
    Lista* l3 = NULL;
    if(!vazia(l1)){
        l3 = insereFila (l3, l1->info);
        l3->prox = concatena (l1->prox, l2);
    }
    else{
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info);
            l3->prox = concatena(l1, l2->prox);
        }
    }
    return l3;
}

Lista* intercala(Lista* l1, Lista* l2){//casos: se a l1 for menor ent continua inserindo// se a l1 eh maior
    Lista* l3 = NULL;

    if(!vazia(l1)){
        l3 = insereFila(l3, l1->info);
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info);
            l3->prox->prox = intercala(l1->prox, l2->prox);
        }
        else
            l3->prox = intercala(l1->prox, l2);
    }
    else {
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info);
            l3->prox = intercala(l1, l2->prox);
        }
    }
    return l3;
}

void liberaLista(Lista* l){
    Lista* aux;
    while(l != NULL){
        aux = l;
        l = l->prox;
        free(aux);
    }
}

int main (){
    Lista* l = NULL;
    Lista* l2 = NULL;
    Lista* l3 = NULL;

    l = insereFila(l, 11);
    l = insereFila(l, 7);
    l = insereFila(l, 5);
    l = insereFila(l, 9);
    l = insereFila(l, 2);

    l2 = insereFila(l2, 6);
    l2 = insereFila(l2, 8);
    l2 = insereFila(l2, 1);
    l2 = insereFila(l2, 3);
    l2 = insereFila(l2, 15);
    l2 = insereFila(l2, 22);
    
    printLista(l);
    printLista(l2);

    //l = removeOcorrencias(l, 2);
    //l2 = obter_sublista(l, 0, 3);

    l3 = intercala(l, l2);
    printLista(l3);

    //printf("%d\n", somaIntervalo(l, 2, 5));

    liberaLista(l);
    liberaLista(l2);
    liberaLista(l3);


    return 0;
}