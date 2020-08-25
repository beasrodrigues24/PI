#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Exercício 1 

// alínea a)
void function1() {
    int x [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10, 11,12,13,14,15};
    int *y, *z, i;
    y = x; // y aponta para o primeiro elemento do array x
    z = x+3; // z aponta para o quarto elemento do array x
    for (i=0; (i<5); i++) {
        printf ("%d %d %d\n", x[i], *y, *z); 
        y = y+1; 
        z = z+2;
    }
    /* Ciclo:   iteração 0 - 1 1 4
                iteração 1 - 2 2 6
                iteração 2 - 3 3 8
                iteração 3 - 4 4 10
                iteração 4 - 5 5 12 */                                
}

// alínea b)
void function2 () {
    int i, j, *a, *b;
    i=3; j=5;
    a = &i; // Aponta para o número 3
    b = &j; // Aponta para o número 5
    i++; // 
    j = i + *b; // j = 3 + 5 = 8
    b = a; // b = &3
    j = j + *b; // j = 8 + 5 = 14
    printf ("%d\n", j);
}

// Exercício 2
void swapM (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Exercício 3
void swap (int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Exercício 4
int soma(int v[], int N) {
    int i, sum = 0;
    for (i = 0; i < N; i++)
        sum += v[i];
    return sum;
}

// Exercício 5
int maximum (int v[], int N, int *m) {
    int i, ret = 1;

    if (N > 0) {
        ret = 0;
        for (i = 0; i < N; i++) 
            if (!i || v[i] > *m)
                *m = v[i];
    }

    return ret;
}

// Exercício 6
void quadrados (int q[], int N) {
    int i;

    for (i = 1; i <= N; i++)
        q[i-1] = pow(i,2);
}

// Exercicio 7 -- stolen
void pascal (int v[], int N) {
    if (N == 1) 
        v[0] = 1;
    else {
        int prevLine[N - 1];
        pascal(prevLine,N-1);
        v[0] = 1;
        v[N-1] = 1;
        for(int i = 1; i < N-1; i++) {
            v[i] = prevLine[i-1] + prevLine[i];
        }
    }
}

// TESTES

void printV(int v[], int N) {
    int i;
    printf("Array: {");
    for (i = 0; i < N; i++)
       i == N-1 ? printf(" %d }\n", v[i]): printf(" %d,", v[i]);
}

int main() {
    printf("Exercício 1, alínea a)\n");
    function1();

    printf("Exercício 1, alínea b)\n");
    function2();

    printf("\nExercício 2\n");
    int x = 3, y = 5;
    printf("%d %d\n", x, y);
    swapM(&x, &y);
    printf("%d %d\n", x, y);

    printf("\nExercício 3\n");
    int v[6] = {1,2,3,4,5,6};
    printV(v,6);
    x = 1; y = 4;
    printf("Troca dos índices %d e %d\n", x, y);
    swap(v,x,y);
    printV(v,6);

    printf("\nExercício 4\n");
    printf("A soma dos valores do vetor anterior é %d\n", soma(v,6));

    printf("\nExercício 5\n");
    x = 0;
    if (!maximum(v,6,&x))
        printf("O maior elemento do vetor anterior é %d\n", x);
    else 
        printf("Valor de elementos do vetor inválido\n");

    printf("\nExercício 6\n");
    x = 6;
    quadrados(v,x);
    printf("Preenchimento do vetor com os quadrados dos primeiros %d números naturais\n", x);
    printV(v,x);

    printf("\nExercício 7\n");
    x = 6;
    printf("Preenchimento do vetor com a linha %d do triângulo de Pascal\n", x);
    pascal(v,x);
    printV(v,x);
    return 0;
}