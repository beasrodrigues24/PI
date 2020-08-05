#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Exercício 1
int minusculas (char s[]) { 
    int counter = 0, i;
    for (i = 0; s[i]; i++) 
        if (s[i] >= 'A' && s[i] <= 'Z') { 
            s[i] += 32;
            counter++;
        }
    
    return counter;
}

// Exercício 2
int contalinhas (char s[]) {
    int counter = 1, i;

    for (i = 0; s[i]; i++)
        if (s[i] == '\n')
            counter++;

    return counter;
}

// Exercício 3
int contaPal (char s[]) {
    int counter = 0, i;
    char c = s[0];
    
    if (!(isspace(c)))
        counter++;

    for (i = 1; s[i]; i++) {
        if (isspace(c) && !(isspace(s[i])))
            counter++;
        c = s[i];
    }
        
    return counter;
}

// Exercício 4
int procura (char *p, char *ps[], int N) {
    int i, ans = 0;

    for (i = 0; i < N && !ans; i++) 
        if (!(strcmp(p, ps[i])))
            ans = 1;

    return ans;
}

// Exercício 5
typedef struct stack {
int sp;
int valores [MAX];
} STACK;

void initStack (STACK *s) {
    s->sp = -1;
}

int isEmptyS (STACK *s) {
    int ans = 0;

    if (s->sp < 0)
        ans = 1;

    return ans;
}

int push (STACK *s, int x) {
    int ans = 0;

    if (s->sp == 99)
        ans = 1;
    else {
        s->sp++;
        s->valores[s->sp] = x;
    }

    return ans;
}

int pop (STACK *s, int *x) {
    int ans = 0;

    if (s->sp < 0)
        ans = 1;
    else {
        *x = s->valores[s->sp];
        s->sp--;
    }

    return ans;
}

int top (STACK *s, int *x) {
    int ans = 0;

    if (s->sp < 0)
        ans = 1;
    else 
        *x = s->valores[s->sp];

    return ans;
}

// Main
int main() {
    STACK s;
    initStack(&s);
    int a = push (&s, 1);
    if (!a) 
        printf("Inserido: %d\n", 1);
    a = push (&s, 2);
    if (!a) 
        printf("Inserido: %d\n", 2);
    int remove;
    a = pop (&s, &remove);
    if (!a) 
        printf("Removido: %d\n", remove);
    a = pop (&s, &remove);
    if (!a) 
        printf("Removido: %d\n", remove);

    a = push (&s, 4);
    if (!a) 
        printf("Inserido: %d\n", 4);
    a = top(&s, &remove);
    if (!a) 
        printf("Topo: %d\n", remove);

    return 0;
}