#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Exercício 1 (alínea a) feita diretamente na main)

typedef struct slist {
int valor;
struct slist * prox;
} Nodo, *LInt;

LInt cons (LInt l, int x) {

    LInt new = malloc(sizeof (struct slist));
    new->valor = x;
    new->prox = l;

    return new;
}

LInt tail (LInt l) {

    LInt temp = l;
    l = l->prox;
    free(temp);

    return l;
}

LInt init (LInt l) {
    LInt aux = l, back = NULL;

    if (!aux) { // Lista é nula
        free(l);
        l = NULL;
    }
    else {
        for (; aux->prox; back = aux, aux = aux->prox);
        if (back) 
            back->prox = NULL;
        else 
            l = NULL;
        free(aux);
    }

    return l;
}

LInt snoc (LInt l, int x) {
    LInt aux = l, temp;
    temp = malloc(sizeof (struct slist));
    temp->valor = x;
    temp->prox = NULL;

    if (!aux) // Lista é nula
        l = temp;
    
    else {
        for (; aux->prox; aux = aux->prox);
        aux->prox = temp;
    }

    return l;
}

LInt concat (LInt a, LInt b) {
    LInt aux = a;

    if (!a) 
        a = b;

    else {
        for (; aux->prox; aux = aux->prox);
        aux->prox = b;
    }

    return a;
}

// Exercício 1 - Alternativo

int cons1 (LInt *l, int x) {
    LInt new = malloc(sizeof (struct slist));

    new->valor = x;
    new->prox = *l;
    *l = new;
	// retorna 1 se a alocação de memória não for possivel
    return !new;
}

int tail1 (LInt *l) {
    int ans = 1;
    
    if (*l) {
        ans = 0;
        LInt temp = *l;
        *l = (*l)->prox;
        free(temp);
    }

    return ans;
}

int init1 (LInt *l) {
    int ans = 1;
    LInt back = NULL;

    if (*l) {
        ans = 0;
        for (; (*l)->prox ; back = *l, l = &(*l)->prox); // l = &(*l)->prox não perde o pointer da lista. *l = (*l)->prox sim
        free(*l);
        if (back)
            back->prox = NULL;
        else {
            *l = NULL;
        }

    }

    return ans;
}

int snoc1 (LInt *l, int x) {
    LInt temp = malloc(sizeof (struct slist));
    temp->valor = x;
    temp->prox = NULL;

    if (*l) {
        for (; (*l)->prox ; l = &(*l)->prox);
        (*l)->prox = temp;
    }
    else 
        *l = temp;
	
    return !temp;
}

void concat1 (LInt *a, LInt b){
    if (!(*a))
        *a = b;
    else {
        for (; (*a)->prox; a = &(*a)->prox);
        (*a)->prox = b;
    }
}

// Exercício 2
typedef struct aluno {
    char nome[60];
    int numero, nota;
} Aluno;

typedef struct sturma {
    Aluno aluno;
    struct sturma *prox;
}*Turma;

Aluno newAluno (char *nome, int numero, int nota) {
    Aluno new = {.numero = numero, .nota = nota};
    strcpy(new.nome, nome);
    return new;
}

Turma vazia () {
	return NULL;
}

int acrescentaAluno (Turma *t, Aluno a) {
    Turma new = malloc(sizeof(struct sturma));
    new->aluno = a;
    
    for (; *t && a.numero > (*t)->aluno.numero; t = &(*t)->prox);
    Turma temp = *t;
    *t = new;
    (*t)->prox = temp;
    return 0;
}

Aluno *procura1 (Turma t, int numero) {
    Aluno *ret = NULL;

    if (t) {
        for (; t && !ret; t = t->prox)
            if (t->aluno.numero == numero)
                ret = &(t->aluno);
    }

    return ret;
}

Aluno *procura (Turma t, int numero) {
    Aluno *ret = NULL;

    for (; t && t->aluno.numero < numero; t = t->prox);
    if (t->aluno.numero == numero) 
        ret = &(t->aluno);
    return ret;
}

int aprovados (Turma t) {
    int counter = 0;

    for (; t; t = t->prox) 
        if (t->aluno.nota >= 10)
            counter++;

    return counter;
}

// Exercício 3
typedef LInt Stack;

void initStack (Stack *s) {
    *s = NULL;
}

int isEmptyS (Stack *s) {
    
    return (!(*s));
}

int push (Stack *s, int x) {
    
    Stack temp = malloc (sizeof (struct slist));
    if (!temp) 
        return 1;
    temp->valor = x;
    temp->prox = *s;
    *s = temp;

    return 0;
}

int pop (Stack *s, int *x) {
    int ans = 1;
    
    if (*s) {
        ans = 0;
        *x = (*s)->valor;
        Stack temp = *s;
        *s = (*s)->prox;
        free(temp);
    }

    return ans;
}

int top (Stack *s, int *x) {
    int ans = 1;

    if (*s) {
        ans = 0;
        *x = (*s)->valor;
    }

    return ans;
}

// Exercício 4
typedef struct queue {
    LInt front, last;
} Queue;

void initQueue (Queue *q) {
    q->front = NULL;
    q->last = NULL;
}

int isEmptyQ (Queue *q) {

    return (!(q->front) && !(q->last));
}

int enqueue (Queue *q, int x) {
    LInt new = malloc(sizeof(struct slist));
    new->valor = x;
    new->prox = NULL;
    
    if (!new) 
        return 1;

    if (!(q->front)) 
        q->front = q->last = new;
         
    else 
        q->last = q->last->prox = new;
    

    return 0;
}

int dequeue (Queue *q, int *x) {
    int ans = 1;

    if (q->front) {
        *x = q->front->valor;
        LInt temp = q->front;
        q->front = q->front->prox;
        if (!(q->front))
            q->last = NULL;
        free(temp);
        ans = 0;
    }

    return ans;
}

int front (Queue *q, int *x) {
    int ans = 1;

    if (q->front) {
        ans = 0;
        *x = q->front->valor;
    }

    return ans;
}

// Exercício 6
typedef struct dlist *DLInt;
typedef struct dlist {
    int valor;
    DLInt ant, prox;
} NodoD;

void inicio (DLInt *l) {
    for (; *l && (*l)->ant; *l = (*l)->ant);
}

void fim (DLInt *l) {
    for (; *l && (*l)->prox; *l = (*l)->prox);
}

void concatDL (DLInt *a, DLInt b) {
    DLInt auxA = *a, auxB = b;
    fim (&auxA);
    inicio(&auxB);
    auxA->prox = auxB;
}

LInt toLInt (DLInt l) {
    inicio(&l);
    LInt list = NULL, head = NULL;

    for (; l; l = l->prox) {
        LInt temp = malloc(sizeof(struct slist));
        temp->valor = l->valor;
        temp->prox = NULL;
        if (!head) 
            head = list = temp;
        else 
            list = list->prox = temp;
    }

    return head;
}

DLInt fromLInt (LInt l) {
    DLInt list = NULL, head = NULL, back = NULL;

    for (; l; l = l->prox) {
        DLInt new = malloc(sizeof(struct dlist));
        new->ant = back;
        new->valor = l->valor;
        new->prox = NULL;
        if (!head) 
            back = list = head = new;
        
        else 
            back = list = list->prox = new;
    }

    return head;
}

// TESTES

int iguais (LInt a, LInt b) {
	// testa se duas listas são iguais
	while (a != NULL && b != NULL && a->valor == b->valor) {
		a = a->prox; b = b->prox;
	}
	return (a==NULL && b==NULL);
}

void printTurma (Turma t) {
    
    for (; t; t = t->prox) {
        printf("%s %d %d\n", t->aluno.nome, t->aluno.numero, t->aluno.nota);
    }
}

void printL (LInt l) {
    LInt aux = l;

    for (; aux; aux = aux->prox)
        printf("%d ", aux->valor);

    putchar('\n');
}

LInt fromArray (int v[], int N){
	LInt r, *e = &r;
	int i;
	for (i=0; i<N; i++){
		*e = malloc(sizeof(struct slist));
		(*e)->valor = v[i];
		e = &((*e)->prox);
	}
	*e = NULL;
	return r;
}

void freeLInt (LInt l) {
	LInt tmp;
	while (l) {
		tmp=l; 
		l=l->prox;
		free (tmp);
	}
}

void printLInt (LInt l){
	while (l) {
		printf ("%d ", l->valor);
		l=l->prox;
	}
	putchar ('\n');
}
DLInt singular (int x){
    DLInt r = malloc (sizeof (struct dlist));
    r->valor = x;
    r->prox = r->ant = NULL;
    return r;
}

void freeDLInt (DLInt l){
    DLInt pt, tmp;
    if (l != NULL){
        pt = l->ant;
        while (pt!=NULL){
            tmp = pt; pt=pt->ant; free (tmp);
        }
        while (l!=NULL){
            tmp = l; l=l->prox; free (tmp);
        }
    }
}

void printDLInt (DLInt l){
    DLInt pt;
    if (l == NULL) printf ("Lista Vazia\n");
    else {
        printf ("Elementos esquerda: ");
        for (pt = l->ant; pt!=NULL; pt=pt->ant)
            printf ("%d ", pt->valor);
        printf ("|\nElemento actual %d\n", l->valor);
        printf ("Elementos direita: ");
        for (pt = l->prox; pt!=NULL; pt=pt->prox)
            printf ("%d ", pt->valor);
        printf ("|\n");
    }
}

int main() {
    printf("Exercício 1: \n");
    printf("Alínea a)\n");
    LInt c = malloc(sizeof (struct slist));
    c->valor = 15;
    c->prox = NULL;
    LInt b = malloc(sizeof (struct slist));
    b->valor = 5;
    b->prox = c;
    LInt z = malloc(sizeof (struct slist));
    z->valor = 10;
    z->prox = b;
    printL(z);

    // NOTA: ALGUMAS FUNÇÕES NÃO FORAM TESTADAS PARA O CASO DE LISTA NULA, DEVEM TESTAR VOCÊS ALGURES
    // cons
    printf("\n\nAlínea b)\n");
    printf("Construção da lista 3->2->1\n");
    LInt l = NULL;
    l = cons(l, 1);
    l = cons(l, 2);
    l = cons(l, 3);
    printL(l);
    LInt s = NULL;
    cons1(&s, 1);
    cons1(&s, 2);
    cons1(&s, 3);
    printL(s);
    printf("Versão alternativa ");
    if (iguais(l, s))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    // tail
    printf("Remoção do 3\n");
    l = tail(l);
    printL(l);
    tail1(&s);
    printL(s);
    printf("Versão alternativa ");
    if (iguais(l, s))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    // init
    printf("Remoção do 1\n");
    l = init(l);
    printL(l);
    init1(&s);
    printL(s);
    printf("Versão alternativa ");
    if (iguais(l, s))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    // snoc
    printf("Inserir o 4 no fim da lista\n");
    l = snoc(l, 4);
    printL(l);
    snoc1(&s, 4);
    printL(s);
    printf("Versão alternativa ");
    if (iguais(l, s))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    printf("Criar lista 6->7->8 usando a snoc\n");
    LInt r = NULL;
    r = snoc(r, 6);
    r = snoc(r, 7);
    r = snoc(r, 8);
    printL(r);
    LInt v = NULL;
    snoc1(&v, 6);
    snoc1(&v, 7);
    snoc1(&v, 8);
    printL(v);
    printf("Versão alternativa ");
    if (iguais(r, v))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    // concat
    printf("Juntar a lista 2->4 e a lista 6->7->8\n");
    l = concat(l, r);
    printL(l);
    concat1(&s, v);
    printL(s);
    printf("Versão alternativa ");
    if (iguais(l, s))
        printf("funciona corretamente.\n\n");
    else 
        printf("não funciona corretamente.\n\n");

    printf("\nExercício 2:\n");
    Turma t;

    t = vazia ();

    acrescentaAluno (&t, newAluno ("Jose",     4444, 10));
    acrescentaAluno (&t, newAluno ("Joao",     4344,  1));
    acrescentaAluno (&t, newAluno ("Maria",    4434, 12));
    acrescentaAluno (&t, newAluno ("Ana",      4443, 15));
    acrescentaAluno (&t, newAluno ("Ramiro",   2444,  8));
    acrescentaAluno (&t, newAluno ("Joaquim",  4244, 14));
    acrescentaAluno (&t, newAluno ("Anabela",  4424, 17));
    acrescentaAluno (&t, newAluno ("Josefina", 4442,  7));
    acrescentaAluno (&t, newAluno ("Rita",     5444, 19));

    printTurma(t);

    Aluno* al;
    al = procura (t, 4442);
    if (al) 
    	printf ("Encontrou: %s %d\n", al->nome, al->nota);
    else printf ("Erro na procura\n");

    al = procura (t, 4545);
    if (al) 
    	printf ("Encontrou: %s %d\n", al->nome, al->nota);
    else printf ("Erro na procura\n");

    printf ("%d aprovados\n", aprovados (t));


    printf("\n\nExercício 3:\n");
    Stack s1; int x;
    initStack (&s1); printf ("Stack inicializada\n");
    if (isEmptyS(&s1)) printf ("Stack está vazia\n");
    if (push (&s1,10)) printf ("Erro no push (%d)\n", 10); else printf ("push %d ok\n",10);
    if (push (&s1,20)) printf ("Erro no push (%d)\n", 20); else printf ("push %d ok\n",20);
    if (push (&s1,30)) printf ("Erro no push (%d)\n", 30); else printf ("push %d ok\n",30);
    if (pop (&s1,&x)) printf ("Erro no pop\n"); else printf ("pop %d ok\n",x);
    if (pop (&s1,&x)) printf ("Erro no pop\n"); else printf ("pop %d ok\n",x);
    if (push (&s1,40)) printf ("Erro no push (%d)\n", 40); else printf ("push %d ok\n",40);
    if (top (&s1,&x)) printf ("Erro no top\n"); else printf ("pop %d ok\n",x);
    

    printf("\n\nExercício 4:\n");
    Queue q1;
    initQueue (&q1); printf ("Queue inicializada\n");
    if (isEmptyQ(&q1)) printf ("Queue está vazia\n");
    if (enqueue (&q1,10)) printf ("Erro no enqueue (%d)\n", 10); else printf ("enqueue %d ok\n",10);
    if (enqueue (&q1,20)) printf ("Erro no enqueue (%d)\n", 20); else printf ("enqueue %d ok\n",20);
    if (enqueue (&q1,30)) printf ("Erro no enqueue (%d)\n", 30); else printf ("enqueue %d ok\n",30);
    if (dequeue (&q1,&x)) printf ("Erro no dequeue\n"); else printf ("dequeue %d ok\n",x);
    if (dequeue (&q1,&x)) printf ("Erro no dequeue\n"); else printf ("dequeue %d ok\n",x);
    if (enqueue (&q1,40)) printf ("Erro no enqueue (%d)\n", 40); else printf ("enqueue %d ok\n",40);
    if (front (&q1,&x)) printf ("Erro no front\n"); else printf ("front %d ok\n",x);
  
    printf("\n\nExercício 5:\n");
    DLInt d1, d2;
    
    int a[10] = {1,11,22,33,44,55,66,77,88,99} ;
    
    l = fromArray (a,5); // Cria a lista 1 -> 11 -> 22 -> 33 -> 44 -> NULL
    d1 = fromLInt (l); // Cria a dlista NULL <- 1 <-> 11 <-> 22 <-> 33 <-> 44 -> NULL
    printf("Lista resultante dos primeiros 5 elementos do array\n");
    printDLInt (d1); // Dirá que o elemento atual é o 1 e à direita estão 11 22 33 44 (Esquerda vazio)
    fim (&d1); // Percorre a lista até chegar ao 44
    printf("\n\nPercorrer essa lista até ao último elemento\n");
    printDLInt (d1); // Dirá que o elemento atual é 44 e à esquerda estão 11 22 33 (Direita vazio)
    inicio (&d1); // Voltará ao 1
    printf("\n\nPercorrer essa lista de volta até ao primeiro elemento\n");
    printDLInt (d1);
    freeLInt (l);
    l = fromArray (a+5,5); // Cria lista 55 -> 66 -> 77 -> 88 -> 99 -> NULL
    d2 = fromLInt (l); // Cria a dlista NULL <- 55 <-> 66 <-> 77 <-> 88 <-> 99 -> NULL
    concatDL (&d1,d2); // Junta as 2 listas
    printf ("\n\nJuntar o resultante de concatenar 2 listas, cada uma correspondente a metade do array\n");
    printDLInt (d1); // Imprime a DLista resultante: NULL <- 1 <-> 11 <-> 22 <-> 33 <-> 44 -> 55 <-> 66 <-> 77 <-> 88 <-> 99 -> NULL
    freeDLInt (d1);
    freeLInt (l);

    return 0;
}
