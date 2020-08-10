#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* Exercício 1 
verifica se os números armazenados num array s são os primeiros N números de uma 
progressão geométrica (exponencial), ou seja, existem números inteiros a e b (positivo) 
tal que s[i] == a * b^i para todo o 0 <= i < N.

Por exemplo, 

verifica ({2,6,18,54}, 4) deve retornar 1 (True) (a=2, b=3), enquanto que 

verifica ({1,4,8,13,19}, 5) deve retornar 0 (False).
*/

int verifica(int s[], int N) {
    int ans = 1, b, a;

    for (int i = 1; i < N && ans; i++) {
        if (i == 1) {
            a = s[0];
            b = s[1]/s[0];
        }
        if (s[i] != a * pow(b, i))
            ans = 0;
    }

    return ans;
}

/* Exercício 2
Defina uma função que cria uma lista com os primeiros N factoriais (1,1,2,6,24,...).
*/

typedef struct slist { 
    int valor; 
    struct slist *prox;
} *LInt;

void gera(LInt *l, int N) {
    int fac = 1;
    for (int i = 1; i <= N; i++) {
        *l = malloc(sizeof(struct slist));
        (*l)->valor = fac;
        l = &(*l)->prox;
        fac *= i;
    }
    *l = NULL;
}

/* Exercício 3
Defina uma função que devolve o endereço do nó anterior ao nó apontado por l numa 
lista ligada circular (i.e. uma lista em que o campo prox do último elemento tem o 
valor do endereço do primeiro elemento).
*/

LInt anterior(LInt l) {
    LInt init = l;

    for (; l && l->prox != init; l = l->prox);
    return l;
}

/* Exercício 4
Defina uma função que testa se uma destas listas tem a mesma sequência de valores 
quando percorrida nos dois sentidos.
*/

typedef struct dlist { 
    int valor; 
    struct dlist *ant, *prox;
} NodoD;

typedef struct {
    NodoD *front, *last;
} DLint;

int capicua(DLint l) {
    int ans = 1;

    if (l.front && l.last && ans) {
        for (; l.front != l.last; l.front = l.front->prox, l.last = l.last->ant) 
            if (l.front->valor != l.last->valor)
                ans = 0;
    }

    return ans;  
}

/* Exercício 5
Defina uma função que dada uma árvore binária imprime segundo uma travessia posorder os 
valores da árvore, um por linha, precedidos do caminho para chegar a esse valor (no 
caminho um caracter ‘<’ representa uma ida para a esquerda e o caracter ‘>’ para a 
direita). Por exemplo, a árvore 

..4
./.\
1...6
.../.\
..5...8

deveria ser impressa como:

<1
><5
>>8
>6
4
*/

typedef struct abin {
    int valor;
    struct abin *esq, *dir;
} *ABin;

void percurso (ABin t, char* perc, int ind) {
    
    if (t) {
        perc[ind] = '<';
        percurso(t->esq, perc, ind+1);
        perc[ind] = '>';
        percurso(t->dir, perc, ind+1);
        perc[ind] = '\0';
        printf("%s%d\n", perc, t->valor);
    }
}

void imprime(ABin t) {
    char perc[100];
    percurso(t, perc, 0);
}

/* Exercício 6
	
Defina uma função que recebe um texto com p palavras e acrescenta N espaços entre cada uma das palavras do texto. 
Por exemplo, se o array t contiver “teste de Programacao Imperativa”, a chamada pad (t,4,2) deve fazer com que o array t 
passe a ter “teste   de   Programacao   Imperativa”.
Assuma que o array recebido como argumento tem espaço suficiente para alojar os caracteres adicionais.
*/

int length(char* texto) {
    int i;
    for (i = 0; texto[i]; i++);
    return i;
}

void insereEspacos (char* texto, int i, int N) {
    int cmp = length(texto);
    int tot = N;

    for (; N > 0; N--) {
        for (int num = cmp; i < num; num--) 
            texto[num] = texto[num-1];  
        texto[i] = ' ';
        cmp += tot;
    }
          
}

void pad (char *texto, int p, int N) {
    int i, inWord = 0;;

    for (i = 0; texto[i]; i++) {
        if (!isspace(texto[i]) && !inWord)
            inWord = 1;
        else if (isspace(texto[i]) && inWord) {
            insereEspacos(texto, i, N);
            inWord = 0;
        }
    }
}

/* Exercício 7
No campo quantos será armazenado o número de elementos da sub-árvore esquerda.
Defina uma função que preenche o campo quantos de cada nodo da árvore. 
Diga ainda qual o significado do valor de retorno da função que definir.
Serão valorizadas respostas que obtenham o resultado pretendido percorrendo a árvore uma única vez.
*/

typedef struct nodo { 
    char *raiz; 
    int quantos; 
    struct nodo *esq, *dir; 
} *Palavras;

int calculaQuantos (Palavras p) { // Devolve o número de elementos da subárvore esquerda
    if (!p)
        return 0;
    
    int e = calculaQuantos(p->esq);
    p->quantos = e;

    return 1 + e + calculaQuantos(p->dir);
}

/* Exercício 8
Defina uma função que recebe uma destas árvores em *e e uma palavra p e a insere no conjunto das palavras.
Note que essa inserção vai alterar o campo quantos de alguns (não necessariamente todos) nodos da árvore.
A função deverá retornar 0 se a inserção for bem sucedida ou um valor diferente de zero se não houver memória disponível ou 
a palavra a inserir já se encontrar no conjunto.
*/

int acrescenta (Palavras *e, char *p) {
    int flag = 1;
    Palavras init = *e;
    while (*e && flag) {
        int cmp = strcmp((*e)->raiz, p); // Para eficiência (o valor não tem de ser calculado 2x)
        if (cmp < 0)
            e = &(*e)->dir;
        else if (cmp > 0) {
            e = &(*e)->esq;
        }
        else 
            flag = 0;
    }

    if (flag) {
        *e = malloc(sizeof(struct nodo));
        if (!(*e))
            return 2;
        (*e)->raiz = strdup(p);
        (*e)->esq = NULL;
        (*e)->dir = NULL;
        (*e)->quantos = 0;

    }
    calculaQuantos(init);

    return 0;
}

/* Exercício 9
Defina uma função char *atRank (Palavras p, int k) que, recebendo um conjunto de palavras nesta representação (e com o campo 
quantos de cada nodo correctamente calculado) calcula a palavra que se encontra na posição k (isto é, a palavra para a qual 
existem exactamente k palavras menores do que ela).  
No caso de k ser superior ao número de palavras do conjunto a função deverá retornar NULL.
*/

char *atRank (Palavras p, int k) {
    char* ans = NULL;
    int count = 0;

    while (p && !ans) {
        count += p->quantos;
        if (count < k) {
            p = p->dir;
            count++;
        }
        else if (count > k) {
            p = p->esq;
            count--;
        }
        else 
            ans = strdup(p->raiz);
    }
    
    return ans;
}

// TESTES

void print_array(int v[], int N) {

    printf("Array: [");
    for (int i = 0; i < N; i++)
        i == N-1 ? printf("%d]\n", v[i]) : printf("%d, ", v[i]);
}

void print_lista (LInt l) {

    printf("Lista:");
    for (; l; l = l->prox)
        !(l->prox) ? printf(" %d -> NULL\n", l->valor) : printf(" %d ->", l->valor);
}

void listToCirc (LInt l) {
    LInt init = l;

    for (; l && l->prox; l = l->prox);
    l->prox = init;
}

void print_dlista (DLint dl) {
    printf("DLista: NULL <-");
    for (; dl.front; dl.front = dl.front->prox)
        (dl.front == dl.last) ? printf(" %d -> NULL\n", dl.front->valor) : printf(" %d <->", dl.front->valor);
}

void print_palavras (Palavras p) {
    if (p) {    
        print_palavras(p->esq);
        printf("Palavra %s, com %d palavra(s) na sub-árvore esquerda.\n", p->raiz, p->quantos);
        print_palavras(p->dir);
    }
}

int main() {
    // Exercício 1
    printf("Exercício 1\n");
    int v[5] = {2,4,8,16,32};
    print_array(v,5);
    if (verifica(v, 5)) 
        printf("É progressão geométrica!\n");
    else 
        printf("Não é progressão geométrica!\n");
    v[2] = 5;
    print_array(v,5);
    if (verifica(v, 5)) 
        printf("É progressão geométrica!\n");
    else 
        printf("Não é progressão geométrica!\n");
    v[2] = 8;
    v[1] = 7;
    print_array(v,5);
    if (verifica(v, 5)) 
        printf("É progressão geométrica!\n");
    else 
        printf("Não é progressão geométrica!\n");
    v[1] = 4;
    v[4] = 33;
    print_array(v,5);
    if (verifica(v, 5)) 
        printf("É progressão geométrica!\n");
    else 
        printf("Não é progressão geométrica!\n");

    // Exercício 2
    printf("\nExercício 2\n");
    printf("Insira o numero de nodos da lista de fatoriais: ");
    int n;
    scanf("%d", &n);
    LInt l = NULL;
    gera (&l, n);
    print_lista(l);

    // Exercício 3
    printf("\nExercício 3\n");
    listToCirc(l);
    LInt r = anterior(l);
    if (r) 
        printf("Anterior ao nodo dado %d\n", r->valor);
    else 
        printf("Lista nula\n");

    // Exercício 4
    printf("\nExercício 4\n");
    DLint dl;
    dl.front = malloc(sizeof(struct dlist));
    dl.front->valor = 1;
    NodoD* new = malloc(sizeof(struct dlist));
    new->valor = 2;
    new->ant = dl.front;
    dl.front->prox = new;

    NodoD* end = malloc(sizeof(struct dlist));
    end->valor = 1;
    end->ant = new;
    end->prox = NULL;
    new->prox = end;
    dl.last = end;
    print_dlista(dl);

    if (capicua(dl))
        printf("É capicua!\n");
    else 
        printf("Não é capicua!\n");

    // Exercício 5
    printf("\nExercício 5\n");
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
    imprime(tree);

    // Exercício 6
    printf("\nExercício 6\n");
    char t[sizeof("teste   de   Programacao   Imperativa") + 1] = "teste de Programacao Imperativa";
    printf("String inicial: %s\n", t);
    pad(t, 4, 2);
    printf("String resultante: %s\n", t);

    // Exercício 7, 8 e 9
    printf("\nExercícios restantes sobre palavras\n");
    Palavras p = NULL;
    acrescenta(&p, "Ana");
    acrescenta(&p, "Joao");
    acrescenta(&p, "Sara");
    acrescenta(&p, "Patricia");
    acrescenta(&p, "Carlos");
    print_palavras(p);
    /* Constrói o seguinte:
            Ana
            (0)
              \
               Joao
                (1) 
              /   \
          Carlos  Sara 
           (0)    (1)
                  /
              Patricia
                 (0)
    */
    printf("A palavra %s tem 0 palavras menores que ela\n", atRank(p, 0));//R: ANA
    printf("A palavra %s tem 1 palavras menores que ela\n", atRank(p, 1));//R: CARLOS
    printf("A palavra %s tem 2 palavras menores que ela\n", atRank(p, 2));//R: JOAO
    printf("A palavra %s tem 3 palavras menores que ela\n", atRank(p, 3));//R: SARA
    printf("A palavra %s tem 4 palavras menores que ela\n", atRank(p, 4));//R: PATRICIA
    printf("A palavra %s tem 5 palavras menores que ela\n", atRank(p, 5));//R: NULL

    return 0;
}