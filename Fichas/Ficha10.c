#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Fiz o que não envolvia ficheiros

typedef struct aluno {
    int numero;
    char *nome;
    int nota;
} Aluno;

typedef struct arv {
    Aluno a;
    struct arv *esq, *dir;
} *Turma;

// Exercício 1 

int acrescentaAluno (Turma *t, Aluno a) {
    int flag = 1;

    while (*t && flag) {
        int cmp = (*t)->a.numero - a.numero;
        if (cmp < 0)
            t = &(*t)->dir;
        else if (cmp > 0)
            t = &(*t)->esq;
        else 
            flag = 0;
    }

    if (!(*t)) {
        *t = malloc(sizeof(struct arv));
        (*t)->a = a;
        (*t)->esq = (*t)->dir = NULL;
    }

    return !flag;
}

// Extra: Ordem alfabética 
int acrescentaAlunoAlfabetica (Turma *t, Aluno a) {
    int flag = 1;

    while (*t && flag) {
        int cmp = strcmp((*t)->a.nome, a.nome);
        if (cmp < 0)
            t = &(*t)->dir;
        else if (cmp > 0)
            t = &(*t)->esq;
        else 
            flag = 0;
    }

    if (!(*t)) {
        *t = malloc(sizeof(struct arv));
        (*t)->a = a;
        (*t)->esq = (*t)->dir = NULL;
    }

    return !flag;
}

Aluno *procura (Turma t, int numero) {
    Aluno* ret = NULL; 
    while (t && !ret) {
        int cmp = t->a.numero - numero;
        if (cmp < 0) 
            t = t->dir;
        else if (cmp > 0)
            t = t->esq;
        else 
            ret = &(t->a);
    }
    return ret;
}

int aprovados (Turma t) {
    int ans = 0;
    if (t) 
        ans += (t->a.nota > 9) + aprovados(t->esq) + aprovados(t->dir);

    return ans;
}

void printTurma (Turma t) {

    if (t) {
        printTurma(t->esq);
        printf("Aluno %s, de número %d, tem nota %d.\n", t->a.nome, t->a.numero, t->a.nota);
        printTurma(t->dir);
    }
}

// TESTES

void initTurma (Turma *t) {
    *t = NULL;
}

int turmaIsVazia (Turma *t) {
    return (*t == NULL);
}

void testaProcura (Aluno* a, int x) {
    
    printf("O aluno número %d ", x);
    if (a != NULL)
        printf("existe na turma e corresponde ao/à aluno(a) %s com a nota %d.\n", (*a).nome, (*a).nota);
    else 
        printf("não existe na turma.\n");
}

int main() {

    Turma t;
    initTurma(&t);
    if (turmaIsVazia(&t))
        printf("A turma está vazia!!\n");
    else 
        printf("A turma não está vazia!!\n");

    printf("Enumera-se a constituição da turma:\n");
    acrescentaAluno(&t, (Aluno) {1000, "João", 17});
    acrescentaAluno(&t, (Aluno) {1009, "Sandra", 10});
    acrescentaAluno(&t, (Aluno) {837, "Carlos", 13});
    acrescentaAluno(&t, (Aluno) {2006, "Bernardo", 12});
    acrescentaAluno(&t, (Aluno) {302, "Vítor", 4});
    printTurma(t);

    printf("\nProcuram-se agora alunos na turma:\n");
    int x = 1009;
    Aluno* a = procura (t, 1009);
    testaProcura(a, x);
    x = 300;
    a = procura(t, x);
    testaProcura(a, x);

    printf("\nTestam-se o número de aprovações:\n");
    x = aprovados(t);
    if (x == 4)
        printf("Correto. Há %d aprovados.\n", 4);
    else 
        printf("Incorreto. Há 4 aprovados, não %d.\n", x);
    
    return 0;  
}