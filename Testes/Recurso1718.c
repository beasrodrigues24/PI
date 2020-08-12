#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// PARTE A

typedef struct posicao {
    int x, y;
} Posicao;

typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

// Exercício 1
char *mystrstr (char s1[], char s2[]) {
    int i, j, flag = 1, l;
    char* end = NULL;
    for (i = 0, j = 0; s1[i] && flag; i++, j=0) {
        if (s1[i] == s2[j]) {
            for (l=i; s1[l] == s2[j] && s2[j]; j++,l++);
            if (s2[j] == '\0') {
                flag = 0;
                end = s1 + i;
            }
        }
    }
    if (!(*s2)) 
        end = s1;

    return end;
}

// Exercício 2
void truncW (char t[], int n) {
    int i, count = 0, j;

    for (i = 0; t[i]; i++) {
        if (t[i] != ' ') {
            count++;
        }
        else 
            count = 0;

        if (count > n) {
            for (j = i; t[j]; j++)
                t[j] = t[j+1];
            i--;
        }

    }
}

// Exercício 3
int maisCentral (Posicao pos[], int N) {
    int i, distMin = pos[0].x * pos[0].x + pos[0].y * pos[0].y, ret = 0, dist;

    for (i = 1; i < N; i++) {
        dist = pos[i].x * pos[i].x + pos[i].y * pos[i].y;
        if (dist < distMin) {
            distMin = dist;
            ret = i;
        }
    }

    return ret;
}

// Exercício 4
LInt somasAcL (LInt l) {
    LInt head = NULL, list = NULL;
    int acum = 0;

    for (; l; l = l->prox) {
        acum += l->valor;
        LInt new = malloc(sizeof(struct slist));
        new->valor = acum;
        new->prox = NULL;
        if (!head) 
            head = list = new;
        else 
            list = list->prox = new;
    }

    return head;
}

// Exercício 5
int addOrd (ABin *a, int x) {
    int flag = 0;

    while (*a && !flag) {
        if (x < (*a)->valor)
            a = &(*a)->esq;
        else if (x > (*a)->valor)
            a = &(*a)->dir;
        else 
            flag = 1;
    }

    if (!(*a)) {
        *a = malloc(sizeof(struct nodo));
        (*a)->valor = x;
        (*a)->esq = (*a)->dir = NULL;
    }

    return flag;
}

// PARTE B

typedef struct celula {
    char *palavra;
    int comp;
    struct celula *prox;
} *Palavras;

// Exercício 1
int daPalavra (char *s, int *e) {
    int cmp = 0, spc = 0, flag = 1;

    for (int i = 0; s[i] && flag; i++) {
        if (isspace(s[i])) 
            spc++;
        else {
            for (int j=i; s[j] && !(isspace(s[j])); j++) {
                cmp++;
            }
            flag = 0;
        }
    }
    *e = spc;
    return cmp;
}

// Exercício 2
Palavras words (char *texto) {
    int spc;
    int cmp = daPalavra(texto, &spc);
    Palavras new = malloc(sizeof(struct celula));
    new->palavra = texto + spc;
    new->comp = cmp;
    new->prox = words(texto+spc+cmp);
    return new;
}

// TESTES

void printPalavras (Palavras p) {

    for (; p; p = p->prox) {
        !(p->prox) ? printf(" %s -> NULL\n", p->palavra) : printf(" %s ->", p->palavra);
    }
}

int main() {
    int spc = 0;
    printf("Tem %d de comprimento\n", daPalavra(" roda das trevas", &spc));
    printf("Antecedida por %d espaços\n", spc);
    Palavras p = words(" roda das trevas");
}
