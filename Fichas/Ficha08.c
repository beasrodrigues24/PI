#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct entrada{
    char *palavra;
    int ocorr;
    struct entrada *prox;
} *Palavras;

typedef Palavras Dicionario;

void initDic (Dicionario *d) {
    *d = NULL;
}

int acrescentaAlfabetica (Dicionario *d, char *pal) {
    int ans = 1;

    for (; *d && strcmp((*d)->palavra, pal) < 0; d = &(*d)->prox);
    if (*d && !strcmp((*d)->palavra, pal))
        ans = ++(*d)->ocorr;
    else {
        Dicionario new = malloc(sizeof(struct entrada));
        new->palavra = strdup(pal);
        new->prox = *d;
        new->ocorr = 1;
        *d = new;
    }
    return ans;
}

int acrescentaAlfabeticaCAux (Dicionario *d, char *pal) {
    Dicionario aux = *d, back = NULL;
    int ans = 1;

    for (; aux && strcmp(aux->palavra, pal) < 0 ; back = aux, aux = aux->prox);

    if (aux && !strcmp(aux->palavra, pal)) {
        aux->ocorr++;
        ans = aux->ocorr;
    }
    else {
        Dicionario new = malloc(sizeof(struct entrada));
        new->palavra = strdup(pal);
        new->ocorr = 1;
        new->prox = aux;
        if (back)
            back->prox = new;
        else 
            *d = new;
    }
    return ans;   
}

int acrescentaNoFim (Dicionario *d, char *pal) {
    int ret = 1;
    for (; *d && strcmp((*d)->palavra, pal); d = &(*d)->prox);
    
    if (*d)
        ret = ++(*d)->ocorr;
    else {
        *d = malloc(sizeof(struct entrada));
        if (!(*d))
            return -1;
        (*d)->palavra = strdup(pal);
        (*d)->ocorr = 1;
        (*d)->prox = NULL;
    }

    return ret;
}

int acrescentaNoFimCAux (Dicionario *d, char *pal) {
    Dicionario aux = *d;
    int ans = 1;

    for (; aux && aux->prox && strcmp(aux->palavra, pal); aux = aux->prox);
    
    if (aux && !strcmp(aux->palavra, pal)) {
        aux->ocorr++;
        ans = aux->ocorr;
    }
    else {
        Dicionario new = malloc(sizeof(struct entrada));
        new->palavra = strdup(pal);
        new->ocorr = 1;
        new->prox = NULL;
        if (aux) 
            aux->prox = new;
        else 
            *d = new;
    }

    return ans;
}

int acrescentaNoInicio (Dicionario *d, char *pal) {
    Dicionario aux = *d;
    int ans = 1;

    for (; aux && strcmp(aux->palavra, pal); aux = aux->prox);

    if (aux && !strcmp(aux->palavra, pal)) 
        ans = ++(aux->ocorr);
    
    else {
        Dicionario new = malloc(sizeof(struct entrada));
        new->palavra = strdup(pal);
        new->ocorr = 1;
        new->prox = *d;
        *d = new;
    }


    return ans;
}

char *maisFreq (Dicionario d, int *c) {

    char* mfq = NULL;
    *c = 0;

    for (; d; d = d->prox) {
        if (d->ocorr > *c) {
            *c = d->ocorr;
            mfq = d->palavra;
        }
    }

    return mfq;
}

// TESTES
void listaDicionario (Dicionario d){
    for (; d; d = d->prox)
        printf ("%s ocorre %d vezes\n", d->palavra, d->ocorr);
}

int main() {
    Dicionario d; int c=0; char *p;
    // Alfabetico
    printf("Ordem alfabética!!\n");
    initDic (&d);
    acrescentaAlfabetica (&d, "Programacao");
    acrescentaAlfabetica (&d, "Sistemas");
    acrescentaAlfabetica (&d, "Sistemas");
    acrescentaAlfabetica (&d, "Computacao");
    acrescentaAlfabetica (&d, "Sistemas");
    acrescentaAlfabetica (&d, "Logica");
    acrescentaAlfabetica (&d, "Logica");
    listaDicionario (d);
    p = maisFreq (d, &c);
    printf ("A palavra mais frequente (%d ocorrências) é: %s\n\n", c, p);

    // No fim 
    printf("Inserido no fim!!\n");
    initDic (&d);
    acrescentaNoFim (&d, "Programacao");
    acrescentaNoFim (&d, "Sistemas");
    acrescentaNoFim (&d, "Sistemas");
    acrescentaNoFim (&d, "Computacao");
    acrescentaNoFim (&d, "Sistemas");
    acrescentaNoFim (&d, "Logica");
    acrescentaNoFim (&d, "Logica");
    listaDicionario (d);
    p = maisFreq (d, &c);
    printf ("A palavra mais frequente (%d ocorrências) é: %s\n\n", c, p);

    // No início
    printf("Inserido no início!!\n");
    initDic (&d);
    acrescentaNoInicio (&d, "Programacao");
    acrescentaNoInicio (&d, "Sistemas");
    acrescentaNoInicio (&d, "Sistemas");
    acrescentaNoInicio (&d, "Computacao");
    acrescentaNoInicio (&d, "Sistemas");
    acrescentaNoInicio (&d, "Logica");
    acrescentaNoInicio (&d, "Logica");
    listaDicionario (d);
    p = maisFreq (d, &c);
    printf ("A palavra mais frequente (%d ocorrências) é: %s\n", c, p);

    return 0;
}

/* OUTPUT CORRETO
Ordem alfabética!!
Computacao ocorre 1 vezes
Logica ocorre 2 vezes
Programacao ocorre 1 vezes
Sistemas ocorre 3 vezes
A palavra mais frequente (3 ocorrências) é: Sistemas

Inserido no fim!!
Programacao ocorre 1 vezes
Sistemas ocorre 3 vezes
Computacao ocorre 1 vezes
Logica ocorre 2 vezes
A palavra mais frequente (3 ocorrências) é: Sistemas

Inserido no início!!
Logica ocorre 2 vezes
Computacao ocorre 1 vezes
Sistemas ocorre 3 vezes
Programacao ocorre 1 vezes
A palavra mais frequente (3 ocorrências) é: Sistemas
*/
