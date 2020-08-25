#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PARTE A

// Exercício 1
char *mystrcat (char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i]; i++);
    int j;
    for (j = 0; s2[j]; j++) 
        s1[i++] = s2[j];
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
    if (n == 1) {
        *v = a->valor;
        return 1;
    }
    int e = nivelV(a->esq, n-1, v);
    int d = nivelV(a->dir, n-1, v+e);
    return e+d;
}

// Exercício 4
int addOrd (ABin *a, int x) {
    int isThere = 0;

    while (*a && !isThere) {
        int cmp = (*a)->valor - x;
        if (cmp < 0) 
            a = &(*a)->dir;
        else if (cmp > 0)
            a = &(*a)->esq;
        else 
            isThere = 1;
    }

    if (!isThere) {
        *a = malloc(sizeof(struct nodo));
        (*a)->valor = x;
        (*a)->esq = (*a)->dir = NULL;
    }

    return isThere;
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

/* Exercício 1
Defina a função float getEntry (Mat m, int linha, int coluna) que retorna a entrada solicitada
na matriz (obs: note que o valor das entradas que não existam em m é implicitamente 0)
*/
float getEntry (Mat m, int linha, int coluna) {
    float num = 0;

    for(; m && m->linha < linha; m = m->prox);
    if (m && m->linha == linha) {
        Colunas col = m->lcol;
        for (; col && col->coluna < coluna; col = col->prox);
        if (col && col->coluna == coluna)
            num = col->valor;
    }

    return num;
}

/* Exercício 2
Defina a função que insere uma nova entrada na matriz (ou altera o valor dessa entrada, se ela já existir)
*/
void setEntry (Mat *m, int linha, int coluna, float valor) {
    for (; *m && (*m)->linha < linha; m = &(*m)->prox);
    if (*m && (*m)->linha == linha) {
        Colunas* col = &(*m)->lcol;
        for (; *col && (*col)->coluna < coluna; col = &(*col)->prox);
        if (*col && (*col)->coluna == coluna)
            (*col)->valor = valor;
        else {
            Colunas temp = *col;
            *col = malloc(sizeof(struct listaC));
            (*col)->valor = valor;
            (*col)->coluna = coluna;
            (*col)->prox = temp;
        }
    }
    else {
        Mat temp = *m;
        *m = malloc(sizeof(struct listaL));
        (*m)->linha = linha;
        (*m)->lcol = malloc(sizeof(struct listaC));
        (*m)->lcol->coluna = coluna;
        (*m)->lcol->valor = valor;
        (*m)->lcol->prox = NULL;
        (*m)->prox = temp;
    }

}

/* Exercício 3
Defina a função que adiciona à matriz *m1 a matriz m2
*/ 

void addTo (Mat *m1, Mat m2) {
    for (; m2; m2 = m2->prox) {
        Colunas col = m2->lcol;
        for (; col; col = col->prox) {
            float x = getEntry(*m1, m2->linha, col->coluna);
            setEntry(m1, m2->linha, col->coluna, x + col->valor);
        }
    }
}

/* Exercício 4
Defina a função que transpõe a matriz *m
*/
void transpose (Mat *m) {
    Mat new = NULL;
    while (*m) {
        Colunas* col = &(*m)->lcol;
        while (*col) {
            setEntry(&new, (*col)->coluna, (*m)->linha, (*col)->valor);
            Colunas temp = *col;
            *col = (*col)->prox;
            free(temp);
        }
        Mat temp = *m;
        *m = (*m)->prox;
        free(temp);
    }
    *m = new;
}

// TESTES

void testEntries(Mat m, int linha, int coluna) {
    printf("A entrada na linha %d e coluna %d é %f\n", linha, coluna, getEntry(m,linha,coluna));
}

int main() {
    Mat m = NULL;
    setEntry(&m, 1, 1, 2.03);
    setEntry(&m, 1, 2, 2.44);
    setEntry(&m, 4, 1, 2.98);
    setEntry(&m, 3, 3, 3.44);
    setEntry(&m, 3, 1, 1.10);
    setEntry(&m, 3, 2, 0.88);
    testEntries(m, 1, 1);
    testEntries(m, 1, 2);
    testEntries(m, 4, 1);
    testEntries(m, 3, 3);
    testEntries(m, 3, 1);
    testEntries(m, 3, 2);
    testEntries(m, 1, 7);
    Mat n = NULL;
    setEntry(&n, 1, 1, 4.22);
    setEntry(&n, 1, 2, 3.09);
    setEntry(&n, 1, 7, 1.19);
    addTo(&m, n);
    printf("Adição\n");
    testEntries(m, 1, 1);
    testEntries(m, 1, 2);
    testEntries(m, 1, 7);
    transpose(&m);
    printf("Transposição\n");
    testEntries(m, 1, 1);
    testEntries(m, 2, 1);
    testEntries(m, 1, 4);
    testEntries(m, 3, 3);
    testEntries(m, 1, 3);
    testEntries(m, 2, 3);
    testEntries(m, 7, 1);
}