#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Exercício 1
#define MAX 100
typedef struct queue {
    int inicio, tamanho;
    int valores [MAX];
} QUEUE;

void initQueue (QUEUE *q) {
    q->tamanho = 0;
    q->inicio = 0;
}

int isEmptyQ (QUEUE *q) {
    return q->tamanho == 0;
}

int enqueue (QUEUE *q, int x) {
    int ans = 1;
    
    if (q->tamanho + q->inicio < MAX) {
        ans = 0;
        q->valores[q->inicio + q->tamanho] = x;
        q->tamanho++;
    }

    return ans;
}

int dequeue (QUEUE *q, int *x) {
    int ans = 1;

    if (q->tamanho) {
        ans = 0;
        *x = q->valores[q->inicio];
        q->inicio++;
        q->tamanho--;
    }

    return ans;
}

int front (QUEUE *q, int *x) {
    int ans = 1;

    if (q->tamanho) {
        ans = 0;
        *x = q->valores[q->inicio];
    }

    return ans;
}

void printQ(QUEUE *q) {
    int i;
    
    printf("[");
    for(i = 0; i < q->tamanho; i++) 
        printf("%d%s", q->valores[q->inicio + i], i == q->tamanho - 1 ? "" : ", ");
    printf("] %d - start index\n",q->inicio);
}


// Exercício 2
typedef struct dqueue {
    int size; // guarda o tamanho do array valores
    int inicio, tamanho;
    int *valores;
} DQUEUE;

void initDQueue (DQUEUE *q) {
    q->size = 0;
    q->inicio = 0;
    q->tamanho = 0;
}

int isEmptyDQ (DQUEUE *q) {
    return (q->tamanho == 0);
}

int enDqueue (DQUEUE *q, int x) {
    
    if (q->tamanho == q->size) 
        q->valores = malloc(2*sizeof(int*));

    q->valores[q->tamanho+q->inicio] = x;
    q->tamanho++; 

    return 0;
}

int deDqueue (DQUEUE *q, int *x) { // FALTA UM FREE que nao sei colocar
    int ans = 1;

    if (q->tamanho) {
        ans = 0;
        *x = q->valores[q->inicio];
        q->inicio++;
        q->tamanho--;
    }

    return ans;
}

int frontD (DQUEUE *q, int *x) {
    int ans = 1;

    if (q->tamanho) {
        ans = 0;
        *x = q->valores[q->inicio];
    }

    return ans;
}

void printDQ(DQUEUE *q) {
    int i;
    
    printf("[");
    for(i = 0; i < q->tamanho; i++) 
        printf("%d%s", q->valores[q->inicio + i], i == q->tamanho - 1 ? "" : ", ");
    printf("] %d - start index\n",q->inicio);
}

// MAIN
int main() {
    // QUEUE ESTÁTICA
    printf("Queue Estática");

    QUEUE q;
    initQueue(&q);

    int insert = 1;
    if (isEmptyQ(&q))
        printf("Queue está vazia!\n");

    if (!enqueue(&q, insert))
        printf("Inserido %d com sucesso.\n", insert);

    printQ(&q);

    insert = 2;
    if (!enqueue(&q, insert))
        printf("Inserido %d com sucesso!\n", insert);

    printQ(&q);

    int removed;
    if (!dequeue(&q, &removed)) 
        printf("Removido %d com sucesso.\n", removed);

    printQ(&q);

    if (!dequeue(&q, &removed)) 
        printf("Removido %d com sucesso.\n", removed);

    printQ(&q);

    insert = 3;
    if (!enqueue(&q, insert))
        printf("Inserido %d com sucesso!\n", insert);

    printQ(&q);

    int top;
    if (!(front(&q, &top)))
        printf("Frente da fila: %d\n", top);

    printQ(&q); 

    // QUEUE DINÂMICA
    DQUEUE dq;
    initDQueue(&dq);
    printf("\n\n\nQueue Dinâmica\n");
    
    insert = 1;
    if (isEmptyDQ(&dq))
        printf("DQueue está vazia!\n");

    if (!enDqueue(&dq, insert))
        printf("Inserido %d com sucesso.\n", insert);

    printDQ(&dq);

    insert = 2;
    if (!enDqueue(&dq, insert))
        printf("Inserido %d com sucesso!\n", insert);

    printDQ(&dq);

    if (!deDqueue(&dq, &removed)) 
        printf("Removido %d com sucesso.\n", removed);

    printDQ(&dq);

    if (!deDqueue(&dq, &removed)) 
        printf("Removido %d com sucesso.\n", removed);

    printDQ(&dq);

    insert = 3;
    if (!enDqueue(&dq, insert))
        printf("Inserido %d com sucesso!\n", insert);

    printDQ(&dq);

    if (!(frontD(&dq, &top)))
        printf("Frente da fila: %d\n", top);

    printDQ(&dq); 


    return 0;
}
