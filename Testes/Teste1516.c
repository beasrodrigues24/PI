#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// PARTE A

// Exercício 1

char *mystrcat (char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i]; i++);
    for (j = 0; s2[j]; j++, i++) 
        s1[i] = s2[j];
    s1[i] = '\0';
    return s1;    
}

// Exercício 2

int remRep (char x[]) {
    int i, j;

    for (i = 0; x[i]; i++) 
        if (x[i] == x[i+1]) {
            for (j = i+1; x[j]; j++)
                x[j] = x[j+1];
            i--;
        }

    return i;
}

// Exercício 3


typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

int nivelV (ABin a, int n, int v[]) {

    if (!a || n < 1)
        return 0;

    else if (n == 1) {
        *v = a->valor;
        return 1;
    }
    else {
        int e = nivelV(a->esq, n-1, v);
        int d = nivelV(a->dir, n-1, v+e);
        return e + d;
    }
}

// Exercício 4

int addOrdRec (ABin *a, int x) {
    ABin new = malloc(sizeof(struct nodo));
    new->valor = x;
    new->esq = new->dir = NULL;

    if (!(*a)) {
        *a = new;
        return 0;
    }
    else if (x < (*a)->valor) 
        return addOrdRec(&(*a)->esq, x);

    else if (x > (*a)->valor)
        return addOrdRec(&(*a)->dir, x);
    
    else 
        return 1;   
}

int addOrd (ABin *a, int x) {
    while (*a) {
        if (x < (*a)->valor)
            a = &(*a)->esq;
        else if (x > (*a)->valor)
            a = &(*a)->dir;
        else 
            return 1;
    }
    ABin new = malloc(sizeof(struct nodo));
    new->valor = x;
    new->esq = new->dir = NULL; 
    *a = new;
    return 0;
}

// PARTE B

typedef struct listaC {
    int coluna;
    float valor;
    struct listaC *prox;
} *Colunas;

typedef struct listaL {
    int linha;
    Colunas lcol;
    struct listaL *prox;
} *Mat;

// Exercício 1

float getEntry (Mat m, int linha, int coluna) {
    float ans = 0;
    Mat aux;

    for (aux = m; aux && aux->linha < linha; aux = aux->prox);
    if (aux && aux->linha == linha) {
        Colunas curs;
        for (curs = aux->lcol; curs && curs->coluna < coluna; curs = curs->prox);
        if (curs && curs->coluna == coluna)
            ans = curs->valor;
    }

    return ans;
}

// Exercício 2

void setEntry (Mat *m, int linha, int coluna, float valor) {

    for (; *m && (*m)->linha < linha; m = &(*m)->prox);
    if (*m && (*m)->linha == linha) {
        Colunas curs = (*m)->lcol, back = NULL;
        for (;curs && curs->coluna < coluna; back = curs, curs = curs->prox);
        if (curs && curs->coluna == coluna) 
            curs->valor = valor;
        else {
            Colunas newC = malloc(sizeof(struct listaC));
            newC->coluna = coluna;
            newC->valor = valor;
            newC->prox = curs;
            if (back) 
                back->prox = newC;
            else 
                (*m)->lcol = newC;
        }
    }
    else {
        Mat new = malloc(sizeof(struct listaL));
        new->linha = linha;
        new->prox = (*m);
        new->lcol = malloc(sizeof(struct listaC));
        new->lcol->coluna = coluna;
        new->lcol->valor = valor;
        new->lcol->prox = NULL;
        *m = new;
    }
}

// Exercício 3

void addTo (Mat *m1, Mat m2) {

    while (*m1 || m2) {
        if (*m1 && m2 && (*m1)->linha == m2->linha) {
            Colunas curs = m2->lcol, colunas_m1 = (*m1)->lcol;
            while (curs && curs->coluna) {
                if (curs->coluna == colunas_m1->coluna) {
                    colunas_m1->valor += curs->valor;
                    curs = curs->prox;
                    colunas_m1 = colunas_m1->prox;
                }
                else if (curs->coluna < colunas_m1->coluna) {
                    setEntry(m1, m2->linha, curs->coluna, curs->valor);
                    curs = curs->prox;
                }
                else {
                    setEntry(m1, m2->linha, curs->coluna, curs->valor);
                    colunas_m1 = colunas_m1->prox;
                }
            }
            m1 = &(*m1)->prox;
            m2 = m2->prox;
        }
        else if (!(*m1) || (m2 && m2->linha < (*m1)->linha)) {
            for (Colunas curs = m2->lcol; curs; curs = curs->prox)
                setEntry(m1, m2->linha, curs->coluna, curs->valor);
            m2 = m2->prox;
        }

        else 
            m1 = &(*m1)->prox;
    }
}

// Exercício 4

void transpose (Mat *m) {

}

// TESTES

int main() {
    
    Mat m = malloc(sizeof(struct listaL));
    m->linha = 1;
    m->prox = NULL;
    m->lcol = malloc(sizeof(struct listaC));
    m->lcol->valor = 1.3;
    m->lcol->coluna = 2;
    m->lcol->prox = NULL;

    printf("Inserido em m %f\n", getEntry(m, 1, 2));
    setEntry(&m, 3, 4, 1.70);
    printf("Inserido em m %f\n", getEntry(m,3,4));
    setEntry(&m, 1, 1, 1.23);
    printf("Inserido em m %f\n", getEntry(m,1,1));

    Mat n = NULL;
    setEntry(&n, 1, 1, 4.33);
    printf("Inserido em n %f\n", getEntry(n,1,1));
    setEntry(&n, 1, 2, 1.23);
    printf("Inserido em n %f\n", getEntry(n,1,2));
    setEntry(&n, 2, 4, 2.1);
    printf("Inserido em n %f\n", getEntry(n,2,4));
    setEntry(&n, 4, 4, 0.11);
    printf("Inserido em n %f\n", getEntry(n,4,4));

    addTo(&m, n);
    printf("Encontrado em m %f\n", getEntry(m,1,1));
    printf("Encontrado em m %f\n", getEntry(m,1,2));
    printf("Encontrado em m %f\n", getEntry(m,2,4));
    printf("Encontrado em m %f\n", getEntry(m,4,4));
    return 0;
}