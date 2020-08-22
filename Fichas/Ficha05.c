#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// NÃO ESTÁ BEM FEITO DE TODO AINDA

// Exercício 1
void insere (int v[], int N, int x) {
    int flag = 1;

    for(int i = 0; i < N && flag; i++) {
        if(v[i] > x) {
            for(int j = N; j > i; j--) {
                v[j] = v[j - 1];
            }
            v[i] = x;
            flag = 0;
        }
        if(i == N - 1) {
            v[N] = x;
        }
    }
}

// Exercício 2
void iSort1 (int v[], int N) {
    int i;
    for (i = 1; i <= N; i++)
        insere (v, i, v[i]);
}

void iSort2 (int v[], int N) {
    int i, j, temp;

    for (i = 1; i <= N; i++) {
        for (j = 0; j < i && v[j] < v[i]; j++);

        for (temp = i; j < temp; temp--)
            v[temp] = v[temp-1];
        
        v[j] = v[i];

    }
}


// TESTES

int isSorted (int v[], int N){
	int i;
	for (i=0; i<N-1 && v[i] <= v[i+1]; i++);

	return (i==N-1);
}

void dumpV (int v[], int N){
   int i;

   for (i=0; i<N; printf ("%d ", v[i++]));
   printf("\n");
}

int main () {
   
    int v1[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}; 
    int v2[25] = {25, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
    int v3[25] = { 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25, 1};
    int v4[25] = {25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int v5[25] = { 1,25, 2,24, 3,23, 4,22, 5,21, 6,20, 7,19, 8,18, 9,17,10,16,11,15,12,14,13};
    int v6[25] = { 1, 1, 1,10,10,10, 2, 2, 2, 9, 9, 9, 9, 3, 3, 8, 4, 4, 4, 5, 7, 7, 7, 8, 8};
    int v7[25] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 1};
    int v8[25] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    // TESTAR SO UMA FUNCAO DE CADA VEZ, MANTER O RESTO EM COMENTARIO
/*
    printf("iSort1\n");
    iSort1(v1, 25);
    dumpV(v1, 25);
    iSort1(v2, 25);
    dumpV(v2, 25);
    iSort1(v3, 25);
    dumpV(v3, 25);
    iSort1(v4, 25);
    dumpV(v4, 25);
    iSort1(v5, 25);
    dumpV(v5, 25);
    iSort1(v6, 25);
    dumpV(v6, 25);
    iSort1(v7, 25);
    dumpV(v7, 25);
    iSort1(v8, 25);
    dumpV(v8, 25);
*/
    printf("\niSort2\n");
    iSort2(v1, 25);
    dumpV(v1, 25);
    iSort2(v2, 25);
    dumpV(v2, 25);
    iSort2(v3, 25);
    dumpV(v3, 25);
    iSort2(v4, 25);
    dumpV(v4, 25);
    iSort2(v5, 25);
    dumpV(v5, 25);
    iSort2(v6, 25);
    dumpV(v6, 25);
    iSort2(v7, 25);
    dumpV(v7, 25);
    iSort2(v8, 25);
    dumpV(v8, 25);
    return 0;
}

