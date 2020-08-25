#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PARTE A
typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;

// Exercício 1
int bitsUm (unsigned int n) {
    int r = 0;
    for (; n > 0; n>>=1) 
        r += n%2;
    return r;
}

// Exercício 2
int limpaEspacos (char t[]) {
    int i, j;
    for (i = 0; t[i]; i++) {
        if (t[i] == ' ' && t[i+1] == ' ') {
            for (j = i+1; t[j]; j++)
                t[j] = t[j+1];
            i--;
        }
    }
    return i;
}

// Exercício 3
int dumpL (LInt l, int v[], int N) {
    int i;
    for (i = 0; i < N && l; i++, l = l->prox)
        v[i] = l->valor;
    return i;
}

// Exercício 4
LInt parte (LInt l) {
    LInt head, *r = &head, *cl = &l;
    int i;
    for (i = 1; *cl; i++) {
        if (!(i%2)) {
            *r = *cl;
            r = &(*r)->prox;
            *cl = (*cl)->prox;
        }
        else 
            cl = &(*cl)->prox;
    }
    *r = NULL;
    return head;
}

// PARTE B
typedef struct nodo {
    char nome[50];
    int numero;
    int nota;
    struct nodo *esq, *dir;
}*Alunos;

/* Exercício 1
Defina uma função que preenche o array notas com a frequência das notas da turma (por exemplo, em notas[12] deve ser colocado 
o número de alunos que tiveram nota 12). A função deverá retornar o número de alunos da turma.
*/

void zeroArray(int v[], int N) {
    int i;
    for (i = 0; i < N; i++)
        v[i] = 0;
}

int fnotasAux (Alunos a, int notas [21]) {
    int nalunos = 0;

    if (a) {
        nalunos += 1 + fnotasAux(a->esq, notas) + fnotasAux(a->dir, notas);
        notas[a->nota]++;
    }
    
    return nalunos;
}

int fnotas(Alunos a, int notas[21]) {
    zeroArray(notas, 21);
    return fnotasAux(a, notas);
}

/* Exercício 2
Defina uma função que, dada uma turma, a frequência de notas (tal como calculado na alínea anterior) e o número de um aluno da 
turma, calcula o rank de um dado aluno numa turma. Um aluno tem rank N sse existirem N-1 alunos com nota superior.
Sugestão: Comece por definir uma função que, dada uma nota e a frequência de notas calcula o rank dessa nota.
*/
int rankNota (int nota, int fnotas[21]) {
    int i, count = 1;
    for (i = 20; i > nota; i--)
        count += fnotas[i];
    return count;
}

int rankAluno (Alunos a, int numero, int fnotas[21]) {
    int found = 0, rank = 0;
    while (a && !found) {
        int cmp = a->numero - numero;
        if (cmp < 0)
            a = a->dir;
        else if (cmp > 0)
            a = a->esq;
        else 
            found = 1;
    }
    if (found) {
        int nota = a->nota;
        rank = rankNota(nota, fnotas);
    }
    return rank;
}

/* Exercício 3
Defina uma função que coloca em *l a lista dos nomes dos alunos da turma a que tiveram essa nota. A função deve retornar o 
número de alunos nessas condições (i.e., o comprimento da lista produzida)
*/
typedef struct strlist {
    char *string;
    struct strlist *prox;
}*StrList;

int comNota (Alunos a, int nota, StrList *l) {
    int num = 0;
    if (a) {
        num += comNota(a->esq, nota, l);
        while (*l)
           l = &(*l)->prox;
        if (a->nota == nota) {
            *l = malloc(sizeof(struct strlist));
            (*l)->string = strdup(a->nome);
            (*l)->prox = NULL;
            num += 1 + comNota(a->dir, nota, &(*l)->prox);
        }
        else 
            num += comNota(a->dir, nota, l);
    }
    return num;
}

/* Exercício 4
Apresente uma definição da função preenche de forma a que a função acima imprima por ordem decrescente da nota a informação 
sobre os alunos guardada
na árvore. Note que o array deve ser preenchido com os endereços dos vários nodos da árvore sem que seja alocada qualquer 
memória adicional.
Se possível, use a informação presente no array freq para optimizar a função.
*/

Alunos procuraAluno(Alunos a, char* nome) {
    Alunos ret = NULL;
    
    if (a) {
        ret = procuraAluno(a->esq, nome);
        if (!ret && !strcmp(a->nome,nome))
            ret = a;
        else if (!ret)
            ret = procuraAluno(a->dir, nome);
    }
    return ret;
}

void preenche (Alunos a, Alunos t[], int freq[21]) {
    int i, l;

    for (i = 20, l = 0; i >= 0; i--) {
        if (freq[i] > 0) {
            StrList sl = NULL;
            comNota(a, i, &sl);
            for (; sl; sl = sl->prox, l++) 
                t[l] = procuraAluno(a, sl->string);
        }
    }
}

void imprime(Alunos a) {
    int i, notas[21], quantos = fnotas(a,notas);
    Alunos todos[quantos];
    preenche(a, todos, notas);
    for (i=0; i<quantos; i++)
        printf("%d %s %d\n",
                todos[i]->numero,
                todos[i]->nome,
                todos[i]->nota);
}

// TESTES
int acrescentaAlunos(Alunos* a, char nome[50], int nota, int numero) {
    int flag = 1;

    while (*a && flag) {
        int cmp = (*a)->numero - numero;
        if (cmp < 0)
            a = &(*a)->dir;
        else if (cmp > 0)
            a  = &(*a)->esq;
        else 
            flag = 0;
    }

    if (!(*a)) {
        *a = malloc(sizeof(struct nodo));
        (*a)->nota = nota;
        (*a)->numero = numero;
        strcpy((*a)->nome, nome);
        (*a)->esq = (*a)->dir = NULL;
    }

    return !flag;
}

void printV(int v[], int N) {
    int i;
    printf("Notas: {");
    for (i = 0; i < N; i++)
        i == N-1 ? printf(" %d }\n", v[i]) : printf(" %d,", v[i]);
}

void printAlunos (Alunos a) {
    
    if (a) {
        printAlunos(a->esq);
        printf("Aluno %s, de nota %d e número %d\n", a->nome, a->nota, a->numero);
        printAlunos(a->dir);
    }
}

void testRank(Alunos a, int num, int fnotas[21]) {
    int rank = rankAluno(a,num,fnotas);
    if (rank)
        printf("O aluno de número %d tem rank %d\n", num, rank);
    else 
        printf("Não há nenhum aluno com esse número na turma\n");
}

void printStrList(StrList sl) {
    
    for (; sl; sl = sl->prox) 
        !(sl->prox) ? printf("%s -> NULL\n", sl->string):printf("%s -> ", sl->string);
}

void testComNota(Alunos a, int nota) {
    StrList sl = NULL;
    int num = comNota(a, nota, &sl);
    if (num) {
        printf("%d aluno(s) teve/tiveram nota %d:\n", num, nota);
        printStrList(sl);
    }
    else 
        printf("Nenhum aluno teve nota %d\n", nota);
    free(sl);
}

int main() {
    int notas[21] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    Alunos a = NULL;
    acrescentaAlunos(&a, "João", 18, 9010);
    acrescentaAlunos(&a, "Sara", 10, 9601);
    acrescentaAlunos(&a, "Carlos", 5, 9904);
    acrescentaAlunos(&a, "Vitor", 10, 9308);
    acrescentaAlunos(&a, "Andreia", 15, 9703);
    printAlunos(a);
    fnotas(a, notas);
    printV(notas,21);
    testRank(a, 9904, notas);
    testRank(a, 9900, notas);
    testRank(a, 9601, notas);
    testRank(a, 9703, notas);
    testRank(a, 9010, notas);
    testRank(a, 9308, notas);
    testComNota(a, 10);
    testComNota(a, 5);
    testComNota(a, 1);
    testComNota(a, 15);
    testComNota(a, 18);
    imprime(a);
}
