#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Exercício 1
typedef struct abin {
    char *pal;
    int ocorr;
    struct abin *esq, *dir;
} *Dicionario;

void initDic (Dicionario *d) {
    *d = NULL;
}

int acrescenta (Dicionario *d, char *pal) {
    int flag = 1, ret = 1;
    while (*d && flag) {
        int r = strcmp((*d)->pal, pal);
        if (r < 0)
            d = &(*d)->dir;
        else if (r > 0)
            d = &(*d)->esq;
        else {
            flag = 0;
            ret = ++(*d)->ocorr;
        }
    }

    if (!(*d)) {
        *d = malloc(sizeof(struct abin));
        (*d)->pal = strdup(pal);
        (*d)->ocorr = 1;
        (*d)->esq = (*d)->dir = NULL;
    }

    return ret;
}

int acrescentaCAux (Dicionario *d, char *pal) {
    Dicionario aux = *d, back = NULL;
    int ans = 1, flag = 1;

    while (aux && flag) {
        back = aux;
        int cmp = strcmp(aux->pal, pal);
        if (cmp < 0)
            aux = aux->dir;
        else if (cmp > 0)
            aux = aux->esq;
        else {
            ans = ++(aux->ocorr); 
            flag = 0;
        }
    }
    if (!aux) {
        Dicionario new = malloc(sizeof(struct abin));
        new->pal = strdup(pal);
        new->ocorr = 1;
        new->esq = NULL;
        new->dir = NULL;
        if (back) {
            if (strcmp (back->pal, pal) > 0)
                back->esq = new;
            else 
                back->dir = new;
        }
            
        else 
            *d = new;

    } 
    return ans;
}

char *maisFreq (Dicionario d, int *c) {
    char* mfq, *mfqe, *mfqd;
    int fe = 0, fd = 0;

    if (d) {
        if (d->ocorr > *c) {
            *c = d->ocorr;
            mfq = d->pal;
        }
        mfqe = maisFreq(d->esq, &fe);
        mfqd = maisFreq(d->dir, &fd);
    }

    if (fe > *c) {
        mfq = mfqe;
        *c = fe;
    }

    if (fd > *c) {
        mfq = mfqd;
        *c = fd;
    }

    return mfq;
}

// Exercício 2

typedef struct abinaria {
    int valor;
    struct abinaria *esq, *dir;
} *ABin;

typedef struct lista {
    int valor;
    struct lista *prox;
} *LInt;

int length (LInt l) {
    int count;

    for (count = 0; l; l = l->prox, count++);
    return count;
}

int acrescentaElem (ABin *a, int x) {
    int flag = 1;
    
    while (*a && flag) {
        int r = (*a)->valor - x;
        if (r < 0) 
            a = &(*a)->dir;
        else if (r > 0)
            a = &(*a)->esq;
        else 
            flag = 0;
    }

    if (!(*a)) {
        *a = malloc(sizeof(struct abinaria));
        (*a)->valor = x;
        (*a)->esq = (*a)->dir = NULL;
    }

    return !flag;
}

ABin fromList (LInt l);
ABin fromListAux (LInt l, int cmp) {
    LInt aux = l, init = l;
    ABin new = NULL;
    int mid = cmp>>1;

    if (aux && mid >= 0) { // Não sei porquê que isto resulta
        int num;
        if (mid > 1)
            for (num = mid; num > 0; num--, aux = aux->prox);
        else 
            init = NULL;
        
        acrescentaElem(&new, aux->valor);
        new->esq = fromListAux(init, mid);
        new->dir = fromListAux(aux->prox, cmp - 1 - mid);
        
    }
    return new;
}

ABin fromList (LInt l) {
    return fromListAux (l, length(l));
}

LInt inorderL (ABin a) {
    LInt l = NULL, aux;

    if (a) {
        l = inorderL(a->esq);
        aux = l;

        while (aux && aux->prox)
            aux = aux->prox;
        
        LInt new = malloc(sizeof(struct lista));
        new->valor = a->valor;
        new->prox = NULL;
        if (aux) 
            aux = aux->prox = new;
        else 
            l = aux = new;
        
        aux->prox = inorderL(a->dir);
    }

    return l;
}

// Exercício 3

typedef struct dlista {
    int valor;
    struct dlista *prox, *ant;
} *DLInt;

DLInt inorderDL (ABin a) {
    DLInt new = NULL, begin = NULL, cursor = NULL;

    if (a) {
        begin = inorderDL(a->esq);
        new = malloc(sizeof(struct dlista));
        new->valor = a->valor;
        
        if (!begin) {
            begin = new;
            begin->ant = NULL;
        }
        else {
            cursor = begin;
            while (cursor && cursor->prox) 
                cursor = cursor->prox;
            cursor->prox = new;
        }
        new->prox = inorderDL(a->dir);
            
    }

    return begin;
}

// TESTES
void listaDicionario (Dicionario d){
    if (d){
        listaDicionario (d->esq);
        printf ("%s ocorre %d vezes\n", d->pal, d->ocorr);
        listaDicionario (d->dir);
    }
}

LInt newLInt (int x, LInt xs){
    LInt l = malloc (sizeof (struct lista));
    if (l!=NULL) {
        l->valor = x;
        l->prox  = xs;
    }
    return l;
}

int LIguais (LInt a, LInt b) {

    while (a!= NULL && b!=NULL && a->valor == b->valor) {
        a = a->prox; b=b->prox;
    }
    return (a == NULL && b==NULL);
}

LInt LfromV (int v[], int N){
    int i;
    LInt r=NULL;
    
    for (i=N-1; i>=0; i--)
        r = newLInt (v[i],r);
    return r;
}

int VfromL (LInt l, int v[], int N){
    int i;
    for (i=0; l!=NULL && i<N; i++, l=l->prox)
        v[i] = l->valor;
    return i;
}

void concat (LInt *a, LInt b){
    if (!(*a))
        *a = b;
    else {
        for (; (*a)->prox; a = &(*a)->prox);
        (*a)->prox = b;
    }
}

int LLength (LInt l){
    LInt aux;
    int count;

    for (aux = l, count = 0; aux; aux = aux->prox, count++);
    return count;
}

void printLInt (LInt l){
    LInt aux = l;
    for (aux = l; aux; aux = aux->prox)
       printf ("%d ", aux->valor); 
    putchar('\n');
}

void imprimeDL (DLInt l){
    DLInt pt;
    if (l == NULL) printf ("Lista Vazia\n");
    else {
        printf ("Elementos esquerda: ");
        for (pt = l->ant; pt!=NULL; pt=pt->ant)
            printf ("%d ", pt->valor);
        printf ("|\nElemento actual %d\n", l->valor);
        printf ("Elementos direita: ");
        for (pt = l->prox; pt!=NULL; pt=pt->prox)
            printf ("%d ", pt->valor);
        printf ("|\n");
    }
}

ABin newABin (int r, ABin e, ABin d){
    ABin a = malloc (sizeof (struct abinaria));
    if (a!=NULL) {
        a->valor = r;
        a->esq = e; a->dir = d;
    }
    return a;
}

int AIguais (ABin a, ABin b){
    int left, right;
    if (a && b) {
        left = AIguais(a->esq, b->esq);
        right = AIguais(a->dir, b->dir);
        
        return ((a->valor == b->valor) && left && right);
    }
    else if (!a && !b)
        return 1;

    else 
        return 0;
 
}

ABin AfromV (int v[], int N){
    ABin a=NULL;
    int m;
    if (N>0){
        m=N/2;
        a = malloc (sizeof(struct abinaria));
        a->valor = v[m];
        a->esq = AfromV (v,m);
        a->dir = AfromV (v+m+1,N-m-1);
    }
    return a;
}

int VfromA (ABin a, int v[], int N){
    // preenche no maximo N elementos de v
    // a partir de uma travessia inorder de a
    // retorna o numero de elementos preenchidos
    // ...
    return -1;
}

int ALength (ABin a){
    int num = 0;
    
    if (a) {
        num++;
        num += ALength(a->esq) + ALength(a->dir);
    }

    return num;
}

int Aequilibrada (ABin a){
    // testa se uma ´árvore est´á equilibrada
    // a diferença entre o numero de elementos a esq e dir
    // difere no máaximo de 1
    // e ambas as subarvores est~ão equilibradas
    // ...
    int dif;
    if (a) {
        dif = ALength(a->esq) - ALength(a->dir);
        if (dif >= -1 && dif <= 1) 
            return Aequilibrada(a->esq) && Aequilibrada(a->dir);
        else 
            return 0;  
    }
    
    else 
        return 1;
}

void imprimeABin (ABin a) {
    if (a) {
        imprimeABin(a->esq);
        printf("%d ", a->valor);
        imprimeABin(a->dir);
    }
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
    Dicionario d; int c=0; char *p;

    printf("Exercício 1\n");
    initDic (&d);
    acrescenta (&d, "Programacao");
    acrescenta (&d, "Sistemas");
    acrescenta (&d, "Sistemas");
    acrescenta (&d, "Computacao");
    acrescenta (&d, "Sistemas");
    acrescenta (&d, "Logica");
    acrescenta (&d, "Logica");
    listaDicionario (d);
    p = maisFreq (d, &c);
    printf ("a palavra mais frequente (%d) é: %s\n", c, p);

    printf("\n\nExercício 2\n");
    int arr [10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    
    LInt l1 = LfromV (arr,10), l2;
    printLInt(l1);

    ABin arv1 = fromList (l1);

    DLInt dl;
    printf("Árvore imprimida inOrder: ");
    imprimeABin(arv1);
    putchar('\n');
    drawsABin(arv1);
    if (ALength (arv1) == 10) 
         printf ("Passou o teste 1\n");
    else printf ("Falhou o teste 1\n");

    if (Aequilibrada (arv1)) 
         printf ("Passou o teste 2\n");
    else printf ("Falhou o teste 2\n");
    
    l2 = inorderL (arv1);
    printf("LISTA1: ");
    printLInt(l1);
    printf("LISTA2: ");
    printLInt(l2);

    if (LIguais (l1,l2)) 
         printf ("Passou o teste 3\n");
    else printf ("Falhou o teste 3\n");
    
    printf ("conversão para uma lista duplamente ligada: ");
    dl = inorderDL (arv1);
    imprimeDL (dl);
    return 0;
}
