#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// PARTE A

// Exercício 1
char *mystrcpy (char *dest, char source[]) {
    int i;

    for (i = 0; source[i]; i++)
        dest[i] = source[i];
    dest[i] = '\0';

    return dest;
}

// Exercício 2
int isVogal (char c) {
    int ans = 0;

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' 
     || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        ans = 1;

    return ans;
}

void strnoV (char s[]) {
    int i, j;

    for (i = 0; s[i]; i++) 
        if (isVogal(s[i])) {
            for (j = i; s[j]; j++)
                s[j] = s[j+1];
            i--;
        }
}

// Exercício 3
typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

int dumpAbin (ABin a, int v[], int N) {
    int count = 0;

    if (a && N) {
        count += dumpAbin(a->esq, v, N);
        if (count < N) {
            v[count] = a->valor;
            return count + dumpAbin(a->dir, v+count+1, N-count-1);
        }
        else return N;

    }

    return count;
}

// Exercício 4
int lookupAB (ABin a, int x) {
    int flag = 0;

    while (a && !flag) {
        if (x < a->valor)
            a = a->esq;
        else if (x > a->valor)
            a = a->dir;
        else 
            flag = 1;
    }

    return flag;
}

// PARTE B

typedef struct listaP{
    char *pal;
    int cont;
    struct listaP *prox;
} Nodo, *Hist;

// Exercício 1
int inc(Hist *h, char *pal) {
    int flag = 0, ret = 1;

    while (*h && !flag) {
        int cmp = strcmp((*h)->pal, pal);
        if (cmp < 0) 
            h = &(*h)->prox;
        else if (cmp > 0)
            break;
        else {
            flag = 1;
            ret = (*h)->cont++;
        }
    }

    if (!flag) {
        Hist temp = NULL;
        if (*h)
            temp = *h;
        *h = malloc(sizeof(Nodo));
        (*h)->pal = strdup(pal);
        (*h)->cont = ret;
        (*h)->prox = temp;
    }

    return ret;
}

// Exercício 2
char *remMaisFreq(Hist *h, int *count) {
    *count = 0;
    Hist curs, back = NULL;
    char* mfq;

    for (curs = *h; curs; curs = curs->prox)
        if (curs->cont > *count) {
            mfq = curs->pal;
            *count = curs->cont;
        }
    
    curs = *h;
    while (curs)
        if (!(strcmp(curs->pal, mfq))) {
            if (back) {
                back->prox = curs->prox;
                back = curs;
                curs = curs->prox;
            }
            else 
                (*h) = (*h)->prox;
            free(curs);
        }
        else {
            back = curs;
            curs = curs->prox;
        }
        
    return mfq;
}

// Exercício 3


// TESTES

void printListaP (Hist h) {
    printf("ListaP:");
    for (; h; h = h->prox)
        !(h->prox) ? printf(" %s (%d) -> NULL\n", h->pal, h->cont) : printf(" %s (%d) ->", h->pal, h->cont);
}

int main() {
    // PARTE B

    // Exercício 1
    Hist h = NULL;
    printf("Inserido 'Teste' com agora %d ocorrências.\n", inc(&h, "Teste"));
    printf("Inserido 'De' com agora %d ocorrências.\n", inc(&h, "De"));
    printf("Inserido 'Programacao' com agora %d ocorrências.\n", inc(&h, "Programacao"));
    printf("Inserido 'Imperativa' com agora %d ocorrências.\n", inc(&h, "Imperativa"));
    printf("Inserido 'Teste' com agora %d ocorrências.\n", inc(&h, "Teste"));
    printListaP(h); // OUTPUT CORRETO: ListaP: De (1) -> Imperativa (1) -> Programacao (1) -> Teste (2) -> NULL
    int num = 0;
    char* mfq = remMaisFreq(&h, &num);
    printf("Removido o elemento %s, com %d ocorrências.\n", mfq, num);
    printListaP(h);

    return 0;
}