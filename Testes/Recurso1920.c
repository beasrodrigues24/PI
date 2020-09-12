#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* Exercício 1

Defina uma função  que dado um número n calcula o número que resulta de inverter a ordem dos dígitos do seu argumento. 
Por exemplo, reverse (1223) deve dar como resultado 3221. 
*/

int reverse(int x) {
	int r=0;
	
    while (x != 0) {
        r *= 10;
        r += x%10;
        x /= 10;
    }

	return r;
}

/* Exercício 2
Defina uma função que percorre a string t e por cada par de vogais iguais e consecutivas remove uma das ocorrências. 
Por exemplo, se t = “Heeello Woorrld”, a invocação vogal (t) deverá colocar em t a string “Heello Worrld”. 
A função deverá retornar o tamanho da string resultante. 
*/

int isVogal (char c) {
    int ans = 0;

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' 
     || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        ans = 1;

    return ans;
}

int vogal (char *t) {
    int i, j;

    for (i = 0; t[i]; i++) 
        if (isVogal(t[i]) && isVogal(t[i+1])) 
            for (j = i; t[j]; j++)
                t[j] = t[j+1];
    
    return i;
}

/* Exercício 3
Defina uma função  que recebe o endereço do nodo mais à direita de uma destas listas e testa se a lista está bem construída.
*/

typedef struct dlist {
    int valor;
    struct dlist *ant, *prox;
} *DList;

int DLIntOk (DList l) {
    DList back = NULL, init = l;
    int ans = 1;

    while (l && l->ant && ans) {
        if (l->prox != back || l->ant == init)
            ans = 0;
        back = l;
        l = l->ant;
    }

    return ans;
}

/* Exercício 4
Defina uma função  que constrói uma destas listas a partir da travessia posorder da árvore argumento.
*/

typedef struct slist { 
    int valor; 
    struct slist *prox;
} *LInt;

typedef struct abin {
    int valor;
    struct abin *esq, *dir;
} *ABin;

typedef struct {
    LInt *front, *last;
} DifList;
/*
DifList imprime (ABin a) {
    DifList dlist;
    dlist.front = NULL;
    dlist.last = NULL;
    if (a) {
        LInt new = malloc(sizeof(struct slist));
        new->valor = a->valor;
        new->prox = NULL;
        DifList left = imprime(a->esq);
        DifList right = imprime(a->dir);
        if (*left.front) {
            dlist.front = left.front;
            if (*right.front) 
                (*left.last)->prox = *right.front;
            
            else 
                (*left.last)->prox = new;
            (*right.last)->prox = new;
        }
        else if (*right.front) {
            dlist.front = right.front;
            (*right.last)->prox = new;
        }
        else 
            dlist.front = dlist.last = &new;
    }
    return dlist;
}*/

/*
DifList imprime (ABin a) { // WRONG
    DifList dlist;
    dlist.front = NULL;
    dlist.last = NULL;
    
    if (a) {
        LInt new = malloc(sizeof(struct slist));
        new->valor = a->valor;
        new->prox = NULL;
        DifList left = imprime(a->esq);
        DifList right = imprime(a->dir);
        if (left.front) {
            dlist.front = left.front;
            LInt* lastE = left.last;
            (*lastE)->prox = *right.front; // ACHO QUE O PROBLEMA É ESTA LINHA
            
            if (right.front) { // left.front != NULL e right.front != NULL
                LInt* lastD = right.last;
                (*lastD)->prox = new;
            }
            else // left.front != NULL e right.front == NULL
                (*lastE)->prox = new;
    
            dlist.last = &new;
        }
        else if (right.front) { // left.front == NULL e right.front != NULL
            dlist.front = right.front;
            LInt* lastD = right.last;
            (*lastD)->prox = new;
            dlist.last = &new;
        }
        else // left.front == NULL e right.front == NULL
            dlist.front = dlist.last = &new;
    }

    return dlist;
}*/

/* Exercício 5
Defina uma função que recebe uma árvore de procura de inteiros e um inteiro x e escreve no écran, por ordem crescente e 
separados por um espaço, todos os elementos da árvore menores ou iguais a x. 
Note que a árvore pode ter elementos repetidos. 
Serão valorizadas soluções que não percorram obrigatoriamente a totalidade dos elementos.
*/

void imprimeAte (ABin a, int x) {
    if (a) {
        imprimeAte(a->esq, x);
        if (x >= a->valor)
            printf("%d ", a->valor);
        imprimeAte(a->dir, x);
    }
}

/* Exercício 6
Defina uma função que recebe uma árvore binária de procura a e um elemento x e calcula 
a lista dos valores do caminho desde a raiz até ao elemento x. A função deverá retornar
NULL se o elemento não existir na árvore.
*/

LInt caminho (ABin a, int x) {
    LInt head, *r = &head;
    int flag = 1;
    for (; a && flag; r = &(*r)->prox) {
        *r = malloc(sizeof(struct slist));
        (*r)->valor = a->valor;
        if (a->valor < x)
            a = a->dir;
        else if (a->valor > x) 
            a = a->esq;
        else 
            flag = 0;
    }
    *r = NULL;
    if (flag)
        head = NULL;
    return head;
}

/* Exercício 7
Considere o seguinte formato de compressão de strings: um dígito n seguido de uma string
(possivelmente comprimida) entre parêntesis representa n cópias dessa string. 
Por exemplo a string “ab3(c2(d))” corresponde à string “abcddcddcdd” após descompressão. 
Implemente uma função  que valida se a string comprimida s obedece ao formato de
compressão indicado.
*/

int valida(char s[]) {
    return -1;
}

/* Exercício 8
Defina uma função que descomprime uma string i (que obedece ao formato comprimido 
apresentado na pergunta anterior) colocando o resultado em o. Assuma que o tem espaço 
suficiente para armazenar a string resultante. 
*/

void descomprime(char i[], char o[]) {

}

// TESTES

void printDifL (DifList dl) {
    printf("DifList:");
    for (LInt* aux = dl.front; *aux; aux = &(*aux)->prox) 
        (*aux)->prox == NULL ? printf(" %d -> NULL\n", (*aux)->valor) :printf(" %d ->", (*aux)->valor);
}

void print_lista (LInt l) {

    printf("Lista:");
    for (; l; l = l->prox)
        !(l->prox) ? printf(" %d -> NULL\n", l->valor) : printf(" %d ->", l->valor);
}

int main() {
    // Exercício 1
    printf("Exercício 1\n");
    printf("O inverso de 1223 é %d\n", reverse(1223));

    // Exercício 2
    printf("\nExercício 2\n");
    char t[sizeof("Heeello Woorrld") + 1] = "Heeello Woorrld";
    printf("String inicial: %s\n", t);
    printf("String final: %s, de comprimento %d.\n", t, vogal(t));

    // Exercício 3
    printf("\nExercício 3\n");
    DList dl = malloc(sizeof(struct dlist));
    dl->ant = NULL;
    dl->valor = 1;
    DList node2 = malloc(sizeof(struct dlist));
    node2->valor = 2;
    node2->ant = dl;
    dl->prox = node2;
    DList nodoDireita = malloc(sizeof(struct dlist));
    nodoDireita->valor = 3;
    nodoDireita->prox = NULL;
    nodoDireita->ant = node2;
    node2->prox = nodoDireita;
    //Tirar estas linha de comentário (uma de cada vez) para testar um caso falso na função DLIntOk: 
    //dl->ant = nodoDireita;
    //nodoDireita->prox = dl;
    if (DLIntOk(nodoDireita))
        printf("A lista duplamente ligada está bem construída!\n");
    else 
        printf("A lista duplamente ligada não está bem construída!\n");

    // Exercício 4
    printf("\nExercício 4\n");
    ABin tree = malloc(sizeof(struct abin));
    tree->valor = 4;
    tree->esq = malloc(sizeof(struct abin));
    tree->esq->valor = 1;
    tree->esq->esq = NULL;
    tree->esq->dir = NULL;
    tree->dir = malloc(sizeof(struct abin));
    tree->dir->valor = 6;
    tree->dir->esq = malloc(sizeof(struct abin));
    tree->dir->esq->valor = 5;
    tree->dir->esq->esq = NULL;
    tree->dir->esq->dir = NULL;
    tree->dir->dir = malloc(sizeof(struct abin));
    tree->dir->dir->valor = 8;
    tree->dir->dir->esq = NULL;
    tree->dir->dir->dir = NULL;
    //DifList dflist = imprime(tree);
    //printDifL(dflist);

    // Exercício 5
    printf("\nExercício 5\n");
    imprimeAte(tree, 6);
    printf("\n");

    // Exercício 6
    printf("\nExercício 6\n");
    LInt l = caminho(tree, 5);
    print_lista(l);
    l = caminho(tree,8);
    print_lista(l);
    l = caminho(tree,1);
    print_lista(l);
    l = caminho(tree, 4);
    print_lista(l);

    return 0;
}
