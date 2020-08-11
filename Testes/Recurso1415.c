#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// PARTE A

typedef struct slist {
    int valor;
    struct slist *prox;
}*LInt ;

// Exercício 1
int bitsUm (unsigned int n) {
    int count = 0;

    while (n > 0) {
        count += n%2;
        n = n>>1;
    }

    return count;
}

// Exercício 2
int limpaEspacos (char t[]) {
    int i, j;

    for (i = 0; t[i]; i++) 
        if (t[i] == ' ' && t[i+1] == ' ') {
            for (j = i; t[j]; j++)
                t[j] = t[j+1];
            i--;
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

/* Exercício 4
se a lista x tiver os elementos {12,22,32,42,52,62} a chamada y = parte (x), coloca na lista y os elementos {22,42,62} 
ficando em x apenas os elementos {12,32,52}
*/
LInt parte (LInt l) {
    int i;
    LInt back = NULL, new, head = NULL, list = NULL;

    for (i = 1; l; i++) {
        if (!(i%2)) {
            // CRIAÇAO DA LISTA NOVA
            new = malloc(sizeof(struct slist));
            new->valor = l->valor;
            new->prox = NULL;
            if (!head)
                head = list = new;
            else 
                list = list->prox = new;
            // REMOCAO NA LISTA ANTIGA
            if (back) {
                back->prox = l->prox;
                free(l);
                l = back->prox;
            }
            else {
                LInt temp = l;
                l = l->prox;
                free(temp);
            }
            
            
        }

        else {
            back = l;
            l = l->prox;
        } 
    }

    return head;
}

// PARTE B

typedef struct nodo {
    char nome[50];
    int numero;
    int nota; // >=0, <=20
    struct nodo *esq, *dir;
}*Alunos;

// Exercício 1
int fnotasAux(Alunos a, int notas [21]) {
    Alunos aux = a; 

    if (aux) {
        notas[aux->nota]++;
        return 1 + fnotasAux(a->esq, notas) + fnotasAux(a->dir, notas);
    }

    return 0;
}

int fnotas (Alunos a, int notas [21]) {
    int i;
    for (i = 0; i < 21; i++)
        notas[i] = 0;
    
    return fnotasAux(a, notas);  
}

// Exercício 2
int rankNota (int nota, int fnotas[21]) {
    int count = 1, i;

    for (i = 20; nota < i; i--) 
        count += fnotas[i];

    return count;
}

int rankAluno (Alunos a, int numero, int fnotas[21]) {
    int ans = -1, found = 0;

    while (a && !found) {
        if (numero < a->numero)
            a = a->esq;
        else if (numero > a->numero)
            a = a->dir;
        else 
            found = 1;
    }

    if (found) 
        ans = rankNota(a->nota, fnotas);  
    
    return ans;
}

// Exercício 3
typedef struct strlist {
    char* string;
    struct strlist *prox;
}*StrList;

int comNota (Alunos a, int nota, StrList *l) {
    int ans = 0;
    *l = NULL;
    
    if (a) {
        ans = comNota(a->esq, nota, l);
        while (*l) 
            l = &(*l)->prox;
        if (a->nota == nota) {
            *l = malloc(sizeof(struct strlist));
            (*l)->string = a->nome;
            (*l)->prox = NULL;
            ans++;
            return ans + comNota(a->dir, nota, &(*l)->prox);
        }
        else 
            return ans + comNota(a->dir, nota, l);
        
    }

    return ans;
}

// Exercício 4
int sumAC (int v[], int N) {
    int i, sum = 0;

    for (i = 0; i < N; i++)
        sum += v[i];

    return sum;
}

void preenche (Alunos a, Alunos t[], int freq[21]) { // às vezes dá bem outras vezes dá mal, não entendo
    
    if (a) {
        int i, j, numAlunos = sumAC(freq, 21);
        for (i = 0; i < numAlunos && a->nota < t[i]->nota; i++);
        for (j = numAlunos; i < j; j--)
            t[j] = t[j-1];
        t[i] = a;  
        preenche(a->esq, t, freq);
        preenche(a->dir, t, freq);
              
    }  
}

void imprime(Alunos a) {
    int i;
    int notas[21];
    int quantos = fnotas(a, notas);
    Alunos todos[quantos];

    preenche(a, todos, notas);

    for (i = 0; i < quantos; i++)
        printf("%d %s %d\n",
                todos[i]->numero,
                todos[i]->nome,
                todos[i]->nota);
}

// TESTES

LInt arrayToList (int v[], int N) {
    int i;
    LInt new, list = NULL, head = NULL;
    for (i = 0; i < N; i++) {
        new = malloc(sizeof(struct slist));
        new->valor = v[i];
        new->prox = NULL;
        
        if (!list) 
            list = head = new;
        else {
            list->prox = new;
            list = list->prox;
        }  
    }

    return head;
}

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

int acrescentaAluno (Alunos* a, int nota, char nome[50], int numero) {
    int isThere = 0;

    while (*a && !isThere) {
        if (numero < (*a)->numero)
            a = &(*a)->esq;
        else if (numero > (*a)->numero)
            a = &(*a)->dir;
        else 
            isThere = 1;
    }

    if (!isThere) {
        Alunos new = malloc(sizeof(struct nodo));
        new->numero = numero;
        strcpy(new->nome, nome);
        new->nota = nota;
        new->esq = NULL;
        new->dir = NULL;
        *a = new;
    }

    return !isThere;
}

void print_Alunos(Alunos a) {

    if (a) {
        print_Alunos(a->esq);
        printf("Aluno %s, de número %d e nota %d.\n", a->nome, a->numero, a->nota);
        print_Alunos(a->dir);
    }
}

void print_strlist(StrList l) {
    
    if (!l) 
        printf("NULL\n");
    else {
        printf("StrList:");
        for (; l; l = l->prox)
            !(l->prox) ? printf(" %s -> NULL\n", l->string) : printf(" %s ->", l->string);
    }
}

int main() {
    // PARTE A
    // Exercício 2
    printf("PARTE A Exercício 2\n");
    char t[sizeof("Teste   de   Programacao   Imperativa") + 1] = "Teste   de   Programacao   Imperativa";
    printf("String inicial: %s\n", t);
    int x = limpaEspacos(t);
    printf("String resultante: %s de comprimento %d.\n", t, x);

    // Exercício 4
    int v[6] = {1, 3, 4, 6, 7, 9};
    LInt l = arrayToList(v, 6);
    print_lista(l);
    LInt r = parte(l);
    print_lista(l);
    print_lista(r);

    // PARTE B
    printf("PARTE B Exercício 1\n");
    Alunos a = NULL;
    acrescentaAluno(&a, 20, "Joao", 1000);
    acrescentaAluno(&a, 14, "Sara", 333);
    acrescentaAluno(&a, 9, "Carlos", 521);
    acrescentaAluno(&a, 14, "Filipe", 987);
    acrescentaAluno(&a, 11, "Marta", 98);
    acrescentaAluno(&a, 11, "Carla", 1003);
    acrescentaAluno(&a, 3, "Ana", 765);
    print_Alunos(a);
    // Exercício 1
    int vNotas[21] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    fnotas(a, vNotas);
    print_array(vNotas, 21);
    // Exercício 2
    printf("\nExercício 2\n");
    int num = 1000;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 765;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 521;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 333;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 987;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 98;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 1003;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    num = 10;
    printf("O aluno de número %d tem rank %d.\n", num, rankAluno(a, num, vNotas));
    /* OUTPUT CORRETO
    O aluno de número 1000 tem rank 1.
    O aluno de número 765 tem rank 7.
    O aluno de número 521 tem rank 6.
    O aluno de número 333 tem rank 2.
    O aluno de número 987 tem rank 2.
    O aluno de número 98 tem rank 4.
    O aluno de número 1003 tem rank 4.
    O aluno de número 10 tem rank -1.
    */

    // Exercício 3
    printf("\nExercício 3\n");
    StrList sl = NULL;
    num = 14;
    x = comNota(a, num, &sl);
    printf("Lista de alunos com nota %d\n", num);
    print_strlist(sl);
    num = 10;
    x = comNota(a, num, &sl);
    printf("Lista de alunos com nota %d\n", num);
    print_strlist(sl);
    num = 3;
    x = comNota(a, num, &sl);
    printf("Lista de alunos com nota %d\n", num);
    print_strlist(sl);
    num = 11;
    x = comNota(a, num, &sl);
    printf("Lista de alunos com nota %d\n", num);
    print_strlist(sl);
   
    // Exercício 4
    printf("\nExercício 4\n");
    imprime(a);


    return 0;
}