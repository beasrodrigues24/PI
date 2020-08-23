#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// PARTE A

typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} *ABin;

// Exercício 1

int retiraNeg (int v[], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        if (v[i] < 0) {
            for (j = i; j < N; j++) 
                v[j] = v[j+1];
            i--;
            N--;
        }
    }

    return i;
}

// Exercício 2

int not_in_prev(char str[], int k, int n) {
    int ans = 1, i;
    for(i = k; i < n; i++) {
        if(str[i] == str[n]) {
            return 0;
        }
    }
    return ans;
}

int difConsecutivos(char s[]) {
    int ans = 0, i, j, flag = 1;
    for(i = 0; s[i]; i++, flag = 1) {
        int consec = 0;
        for(j = i; s[j] && flag; j++) {
            if(not_in_prev(s,i,j)) 
                consec++;
            else 
                flag = 0;;
        }
        if (consec > ans) ans = consec;
    }
    return ans;
}

// Exercício 3

int maximo (LInt l) {
    int max;
    if (l) {

        LInt aux;
        max = l->valor;

        for (aux = l->prox; aux; aux = aux->prox) 
            if (aux->valor > max)
                max = aux->valor;
    }

    return max;
}

// Exercício 4

int removeAll (LInt *l, int x) {
    LInt aux = *l, back = NULL;
    int counter = 0;

    while(aux) {
        if (aux->valor == x) {
            if (!back) {
                *l = aux->prox;
                free(aux);
                aux = *l;
            }
            else {
                back->prox = aux->prox;
                free(aux);
                aux = back->prox;
            }
            counter++;
        }
        else {
            back = aux;
            aux = aux->prox;
        }  
    }

    return counter;
}

// Exercício 5

LInt arrayToList (int v[], int N) {
    LInt new, head = NULL, list = NULL;
    int i;

    for (i = 0; i < N; i++) {
        new = malloc(sizeof(struct slist));
        new->valor = v[i];
        new->prox = NULL;
        if (!head) 
            head = list = new;
        else {
            list = list->prox = new;
        }
        
    }

    return head;
}

// PARTE B

// Exercício 1

int minheapOK (ABin a) {
    int ans = 1;

    if (a && a->esq && a->dir) {
        if (a->valor > a->esq->valor || a->valor > a->dir->valor)
            ans = 0;
        return ans && minheapOK(a->esq) && minheapOK(a->dir);
    }
    
    return ans;   
}

// Exercício 2

int maxHeap (ABin a) {

    if (a && !(a->esq) && !(a->dir))
        return a->valor;

    int esq, dir;
    if (a && a->esq && a->dir) {
        esq = maxHeap(a->esq);
        dir = maxHeap(a->dir);
    }

    if (esq > dir)
        dir = esq;
    return esq;
}

// Exercício 3

void removeMin (ABin *a) {

    if (!((*a)->esq)) {
        ABin temp = *a;
        (*a) = (*a)->dir;
        free(temp);
    }

    else if (!(*a)->dir) {
        ABin temp = *a;
        (*a) = (*a)->esq;
        free(temp);
    }

    else if ((*a)->esq->valor > (*a)->dir->valor) {
        (*a)->valor = (*a)->dir->valor;
        removeMin(&((*a)->dir));
    }

    else if ((*a)->esq->valor < (*a)->dir->valor) {
        (*a)->valor = (*a)->esq->valor;
        removeMin(&((*a)->esq));
    }
}

void add (ABin *a, int x) { // STOLEN
    ABin new = malloc(sizeof(struct nodo));
    new->esq = new->dir = NULL;

    if (!(*a))
        *a = new;
    else {
        if(!(*a)->esq) {
            if(x > (*a)->valor) add(&((*a)->esq),x);
            else {
                new->esq = (*a);
                new->dir = (*a)->dir;
                (*a)->dir = NULL;
                (*a) = new;
            }
        }
        else if(!(*a)->dir) {
            if(x > (*a)->valor) add(&((*a)->dir),x);
            else {
                new->esq = (*a)->esq;
                (*a)->esq = NULL;
                new->dir = (*a);
                (*a) = new;
            }
        }
        else {
            if(x > (*a)->dir->valor) add(&((*a)->dir),x);
            else if(x > (*a)->esq->valor) add(&((*a)->esq),x);
            else {
                ABin new = malloc(sizeof(struct nodo));
                new->valor = x;
                if(x < (*a)->valor) {
                    new->esq = (*a);
                    (*a) = new;
                }
                else {
                    new->esq = (*a)->esq;
                    (*a)->esq = new;
                }
                new->dir = NULL;
            }
        }
    }
}

void heapSort (int v[], int N) { // ERRADO
    int i;
    ABin a = NULL;

    for (i = 0; i < N; i++)
        add(&a, v[i]);
    
    for (i = 0; i < N; i++) {
        v[i] = a->valor;
        removeMin(&a);
    }
}

// Exercício 5



// TESTES

void printArray (int v[], int N) {
    int i;

    for (i = 0; i < N; i++) 
        printf("%d ", v[i]);

    putchar ('\n'); 
}  

void printLista (LInt l) {
    LInt aux;
    for (aux = l; aux; aux = aux->prox)
        printf("%d ", aux->valor);
    putchar('\n');
}

void drawsABin (ABin a) {
    if (a) {
        printf("%d\n", a->valor);
        printf("Left of %d: ", a->valor);
        drawsABin(a->esq);
        putchar('\n');
        printf("Right of %d: ", a->valor);
        drawsABin(a->dir);
        putchar('\n');
    }
}

int main() {
    int v[12] = {4,-1, 4, 5, 2, -4, 8, 1, 7, -3, -1, 4};
    printf("Array antes da remoção dos número negativos: ");
    printArray(v, 12);
    int n = retiraNeg(v, 12);
    printf("Array após remoção dos números negativos: ");
    LInt l = arrayToList(v, n);
    printArray(v, n);
    printLista(l);
    printf("O máximo da lista é %d\n", maximo(l));
    
    printf("Remoções: %d\n", removeAll(&l, 4));
    printLista(l);


    ABin new = malloc(sizeof(struct nodo));
    new->valor = 20;
    new->esq = malloc(sizeof(struct nodo));
    new->esq->valor = 35;
    new->esq->esq = malloc(sizeof(struct nodo));
    new->esq->esq->valor = 80;
    new->esq->dir = malloc(sizeof(struct nodo));
    new->esq->dir->valor = 43;
    new->esq->dir->esq = NULL;
    new->esq->dir->dir = NULL;
    new->esq->esq->esq = NULL;
    new->esq->esq->dir = NULL;

    new->dir = malloc(sizeof(struct nodo));
    new->dir->valor = 22;
    new->dir->esq = malloc(sizeof(struct nodo));
    new->dir->esq->valor = 23;
    new->dir->esq->esq = NULL;
    new->dir->esq->dir = NULL;
    new->dir->dir = malloc(sizeof(struct nodo));
    new->dir->dir->valor = 25;
    new->dir->dir->esq = NULL;
    new->dir->dir->dir = NULL;


    if (minheapOK(new))
        printf("É minheap!\n");
    else 
        printf("Não é minheap!\n");


    printf("O maior elemento é %d!\n", maxHeap(new));
    printf("Remocao\n");
    removeMin(&new);
    drawsABin(new);
    printf("Remocao\n");
    removeMin(&new);
    drawsABin(new);
    printf("Remocao\n");
    removeMin(&new);
    drawsABin(new);

    int r[12] = {4,-1, 4, 5, 2, -4, 8, 1, 7, -3, -1, 4};
    heapSort(r, 12);
    printArray(r, 12);
    
}