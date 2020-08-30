#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PARTE 1 

// Q1
int largestElem() {
    int num = 0, big = 0;
    scanf("%d", &num);
    big = num;

    while (num) {
        scanf("%d", &num);
        if (num > big) {
            big = num;
        }
    }

    return big;
}

// Q2
int average() {
    int result = 0, num = 1, counter = 0;
    
    while(num) {
        scanf("%d", &num);
        if (num != 0) counter++;
        result += num;
    }
    if (!counter)
        result = 0;
    else 
        result /= counter;

    return result;
}

// Q3
int secondLargest() {
    int num = 0, big = 0, secBig = 0;
    scanf("%d", &num); 
    big = num;
    secBig = num;

    while (num) {
        scanf("%d", &num);
        if (num > big) {
            secBig = big;
            big = num;
        } 
        else if (num > secBig) 
            secBig = num;
    }

    return secBig;
}

// Q4
int bitsUm (unsigned int n) {
    int count = 0;
    
    for (; n > 0; n >>= 1)
        count += n%2;

    return count;
}

// Q5
int trailingZ (unsigned int n) {
    if (n == 0)
        return 32;
    int count = 0;
    
    while (n > 0) {
        if (n%2 == 0)
            count++;
        n >>= 1;
    }
    return count;
}


// Q6
int qDig (unsigned int n) {
    int count = 0;
    
    while (n) {
        count++;
        n /= 10;
    }

    return count;
}

// Q7
char *mystrcat (char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i]; i++);
    for (j = 0; s2[j]; j++, i++) 
        s1[i] = s2[j];
    s1[i] = '\0';
    return s1;    
}

// Q8
char *mystrcpy (char *dest, char source[]) {
    int i;
    
    for (i = 0; source[i]; i++) 
        dest[i] = source[i];
    dest[i] = '\0';

    return dest;
}

// Q9
int mystrcmp(char s1[], char s2[]) {
    int i;

    for (i = 0; s1[i] == s2[i] && s1[i]; i++);
    
    return s1[i] - s2[i];
}

// Q10
char *mystrstr (char s1[], char s2[]) {
    int i, j, flag = 1, l;
    char* end = NULL;
    for (i = 0, j = 0; s1[i] && flag; i++, j=0) {
        if (s1[i] == s2[j]) {
            for (l=i; s1[l] == s2[j] && s2[j]; j++,l++);
            if (s2[j] == '\0') {
                flag = 0;
                end = s1 + i;
            }
        }
    }
    if (!(*s2)) 
        end = s1;

    return end;
}

// Q11
void strrev (char s[]) {
    int i,j;
    
    for (i = 0; s[i]; i++);
    i--;
    
    for (j = 0; j < i; j++, i--) {
        char temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}

// Q12
int isVogal(char c) {
    int ans = 0;
    
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
    || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') 
        ans = 1;

    return ans;  
}

void strnoV (char s[]) {
    int i, j;

    for (i = 0; s[i]; i++) 
        if (isVogal(s[i])) {
            for (j = i; s[j]; j++) 
                s[j] = s[j+1];
            i--;
        }  
}

// Q13
void truncW (char t[], int n) {
    int i, count = 0, j;

    for (i = 0; t[i]; i++) {
        if (t[i] != ' ') {
            count++;
        }
        else 
            count = 0;

        if (count > n) {
            for (j = i; t[j]; j++)
                t[j] = t[j+1];
            i--;
        }

    }
}

// Q14
char charMaisfreq (char s[]) {
    int freq = 0, i, j, count = 0;
    char cmf = '\0';

    for (i = 0; s[i]; i++, count = 0) {
        for (j = i; s[j]; j++) {
            if (s[i] == s[j])
                count++; 
        }

        if (count > freq) {
            cmf = s[i];
            freq = count;
        }
    }
    
    return cmf;
}

// Q15
int iguaisConsecutivos (char s[]) {
    int i, j, streak = 1, max = 0;
    
    for (i = 0; s[i]; i = ++j) {
        for (j = i; s[j] && s[j] == s[j+1]; j++, streak++);
        if (streak > max)
            max = streak;
        streak = 1;
    }
    return max;
}

// Q16 -- stolen
int not_in_prev(char str[], int k, int n) {
    int ans = 1, i;
    for(i = k; i < n && ans; i++) {
        if(str[i] == str[n])
            ans = 0;
    }
    return ans;
}

int difConsecutivos(char s[]) {
    int ans = 0, i, j, flag = 1;
    for(i = 0; s[i]; i++, flag = 1) {
        int consec = 0;
        for(j = i; s[j] && flag; j++) {
            if(not_in_prev(s,i,j)) 
                consec++;
            else 
                flag = 0;;
        }
        if (consec > ans) ans = consec;
    }
    return ans;
}

// Q17
int maiorPrefixo (char s1 [], char s2 []) {
    int i;
    
    for (i = 0; s1[i] == s2[i]; i++);
    
    return i;
}

// Q18
int maiorSufixo (char s1 [], char s2 []) {
    int l1, l2, count=0;
    
    for (l1 = 0; s1[l1]; l1++);
    for (l2 = 0; s2[l2]; l2++);
    l1--; l2--;
    
    for (; s1[l1] == s2[l2]; l1--, l2--, count++);
    
    return count;
}

// Q19
int sufPref (char s1[], char s2[]) {
    int i, count, j;

    for (i = 0, j = 0; s1[i]; i++) {
        if (s1[i] == s2[j]) {
            j++;
            count++;
        }
        else {
            count = j = 0;
        }
    }
    return count;
}

// Q20
int contaPal (char s[]) {
    int inWord = 0, i, count = 0;
    
    for (i = 0; s[i]; i++) {
        if (inWord && s[i] == ' ')
            inWord = 0;
        else if (!inWord && s[i] != ' ' && s[i] != '\n') {
            inWord = 1;
            count++;
        }
    }
    return count;
}

// Q21
int contaVogais (char s[]) {
    int i, count = 0;

    for (i = 0; s[i]; i++) 
        if (isVogal(s[i]))
            count++;

    return count;
}

// Q22
int contida (char a[], char b[]) {
    int i, j, ans = 1, isThere = 0;

    for (i = 0; a[i] && ans; i++, isThere = 0) {
        for (j = 0; b[j]; j++) 
            if (a[i] == b[j])
                isThere = 1;
        if (!isThere)
            ans = 0;
    }

    return ans;
}

int contida2 (char a[], char b[]) {
    int i, j, ans = 1;
    
    for (i = 0; a[i] && ans; i++) {
        for (j = 0; b[j] && a[i] != b[j]; j++);
        if (!b[j])
            ans = 0;
    }
    
    return ans;
}

// Q23
int palindroma (char s[]) {
    int i, j, ans = 1;
    
    for (i = 0; s[i]; i++);
    i--;
    
    for (j = 0; j < i && ans; j++, i--)
        if (s[j] != s[i])
            ans = 0;
            
    return ans;
}

// Q24
int remRep (char x[]) {
    int i, j;

    for (i = 0; x[i]; i++) {
        if (x[i] == x[i+1]) {
            for (j = i+1; x[j]; j++) 
                x[j] = x[j+1];
            i--;
        }
    }

    return i;
}

// Q25
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

// Q26 
void insere(int v[], int N, int x) {
    int i;
    for (i = 0; i < N && v[i] < x; i++);
    for (; N > i; N--)
        v[N] = v[N-1];
    v[i] = x;
}

// Q27
void merge (int r [], int a[], int b[], int na, int nb){
    int i, ca, cb;
    
    for (i = ca = cb = 0; i < na + nb; i++) {
        if ((ca < na && cb < nb && b[cb] < a[ca]) || ca >= na) {
            r[i] = b[cb];
            cb++;
        }
        else {
            r[i] = a[ca];
            ca++;
        }
    }
}

// Q28
int crescente (int a[], int i, int j) {
    int ans = 1;
    
    for (; i < j && ans; i++) {
        if (a[i] > a[i+1])
            ans = 0;
    }

    return ans;
}

// Q29
int retiraNeg (int v[], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        if (v[i] < 0) {
            for (j = i; j < N; j++) 
                v[j] = v[j+1];
            i--;
            N--;
        }
    }

    return i;
}

// Q30
int menosFreq (int v[], int N){
    int i, j, count = 1, min = N, mf = v[0];
    
    for (i = 0; i < N; i = j) {
        for (j = i+1; j < N && v[i] == v[j]; j++, count++);
        if (count < min) {
            min = count;
            mf = v[i];
        }
        count = 1;
    }
    return mf;
}

// Q31
int maisFreq (int v[], int N){
    int i, j, max = 0, count = 1, mf = v[0];
    
    for (i = 0; i < N; i = j) {
        for (j = i+1; j < N && v[j] == v[i]; j++, count++);
        if (count > max) {
            max = count;
            mf = v[i];
        }
        count = 1;
    }

    return mf;
}


// Q32
int maxCresc (int v[], int N) {
    int i, j, count = 1, max = 0;
    
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N && v[j] >= v[j-1]; j++, count++);
        if (count > max) 
            max = count;
        count = 1;
    }
    return max;
}

// Q33
int elimRep (int v[], int n) {
    int i, j, l;

    for (i = 0; i < n; i++) 
        for (j = i+1; j < n; j++) 
            if (v[i] == v[j]) {
                for (l = j; l < n; l++) 
                    v[l] = v[l+1];
                j--;
                n--;
            }
    
    return i;   
}

// Q34
int elimRepOrd (int v[], int n) {
    int i, j, l;

    for (i = 0; i < n; i++) 
        for (j = i+1; j < n && v[i] == v[j]; j++) {
           for (l = j; l < n; l++) 
                v[l] = v[l+1];
            j--;
            n--;
        }
            
    
    return i;   
}

// Q35
int comunsOrd (int a[], int na, int b[], int nb) {
    int i = 0, j = 0, count = 0;
    while(i < na && j < nb) {
        if(a[i] == b[j]) {
            count++;
            i++;
            j++;
        }
        else if(a[i] > b[j]) j++;
        else i++;
    }
    return count;
}

// Q36
int comuns (int a[], int na, int b[], int nb) {
    int i, j, counter = 0, flag = 1;

    for (i = 0; i < na; i++, flag = 1) 
        for (j = 0; j < nb && flag; j++) 
            if (a[i] == b[j]) {
                counter++;
                flag = 0;
            }
    
    return counter;
}

// Q37
int minInd (int v[], int n) {
    int r = -1, min, i;
    
    for (i = 0; i < n; i++)
        if (!i || v[i] < min) {
            min = v[i];
            r = i;
        }
    return r;
}

// Q38
void somasAc (int v[], int Ac [], int N) {
    int acum = 0, i;

    for (i = 0; i < N; i++) {
        acum += v[i];
        Ac[i] = acum;
    }
}

// Q39
int triSup (int N, float m [N][N]) {
    int i, j, ans = 1;
    
    for (i = 0; i < N && ans; i++) 
        for (j = 0; j < i && ans; j++)
            if (m [i][j] != 0)
                ans = 0;
    

    return ans;
}

// Q40
void transposta (int N, float m [N][N]) {
    int i, j;
    float temp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++) {
            temp = m [i][j];
            m [i][j] = m [j][i];
            m [j][i] = temp;  
        }
    }
}

// Q41
void addTo (int N, int M, int a [N][M], int b[N][M]) {
    int i, j;
    for (i = 0; i < N; i++) 
        for (j = 0; j < M; j++)
            a [i][j] += b [i][j];
}

// Q42
int unionSet (int N, int v1[N], int v2[N], int r[N]){
    int contador = 0, i;

    for (i = 0; i < N; i++) 
        if (v1[i] || v2[i]) {
            contador++;
            r[i] = 1;
        }

    return contador;
}

// Q43
int intersectSet (int N, int v1[N], int v2[N], int r[N]){
    int contador = 0, i;

    for (i = 0; i < N; i++) 
        if (v1[i] && v2[i]) {
            contador++;
            r[i] = 1;
        }

    return contador;
}

// Q44
int intersectMSet (int N, int v1[N], int v2[N], int r[N]){
    int i;
    
    for (i = 0; i < N; i++) {
        
        if (v1[i] && v2[i]) {
            if (v1[i] > v2[i])
                r[i] = v2[i];
            else 
                r[i] = v1[i];
        }
    }
    
    return i;
}

// Q45
int unionMSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (v1[i]>v2[i]) 
            r[i] = v1[i]; 
        else r[i] = v2[i];
    }
    return i; 
}

// Q46
int cardinalMSet (int N, int v[N]) {
    int i, res = 0;

    for (i = 0; i < N; i++) {
        res += v[i];
    }

    return res;
}

// Q47
typedef enum movimento {
    Norte, Oeste, Sul, Este
} Movimento;

typedef struct posicao {
    int x, y;
}Posicao;

Posicao posFinal (Posicao inicial, Movimento mov[], int N) {
    int i;
    
    for (i = 0; i < N; i++) {
        switch (mov[i]) {
            case Norte: 
                inicial.y++;
                break;
            case Oeste:
                inicial.x--;
                break;
            case Este:
                inicial.x++;
                break;
            case Sul:
                inicial.y--;
                break;
        }
    }
    return inicial;
}

// Q48
int caminho (Posicao inicial, Posicao final, Movimento mov[], int N) {
    int i;
    
    for (i=0; i<=N; i++) {
        
        if ((inicial.x == final.x) && (inicial.y == final.y)) 
            return i;
        
        if (inicial.y > final.y) {
            mov[i] = Sul;
            inicial.y--;
        } 
        else if (inicial.y < final.y) {
            mov[i] = Norte;
            inicial.y++;
        } 
        else if (inicial.x > final.x) {
            mov[i] = Oeste;
            inicial.x--;
        } 
        else if (inicial.x < final.x) {
            mov[i] = Este;
            inicial.x++;
        }
    }
    
    return -1;
}

// Q49
int maiscentral (Posicao pos[], int N) {
    int central = 0, i;
    int dist = pos[0].x*pos[0].x + pos[0].y*pos[0].y, curr;

    for (i = 0; i < N; i++) {
        curr = pos[i].x*pos[i].x + pos[i].y*pos[i].y;
        if (dist > curr) {
            dist = curr;
            central = i;
        }
    }
    return central;
}

// Q50
int vizinhos (Posicao p, Posicao pos[], int N) {
    int i, contador = 0;

    for (i = 0; i < N; i++) {
        if (p.y == pos[i].y && p.x == pos[i].x) {;}
        else if (sqrt((p.x - pos[i].x)*(p.x - pos[i].x) + (p.y - pos[i].y)*(p.y - pos[i].y)) <= 1)
            contador++;
    }
    return contador;
}

// PARTE 2

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

// Q1
int length (LInt l) {
    int counter;
    
    for (counter = 0; l; l = l->prox, counter++);

    return counter;
}

// Q2
void freeL (LInt l) {
    LInt aux;

    while (l) {
        aux = l->prox;
        free(l);
        l = aux;
    }
}

// Q3
void imprimeL (LInt l) {

    while (l) {
        printf("%d", l->valor);
        l = l->prox; 
    }
}

// Q4
LInt reverseL (LInt l) {
    LInt front, back = NULL;

    while (l) {
        front = l->prox;
        l->prox = back;
        back = l;
        l = front;
    }

    return back;
}

// Q5
void insertOrd (LInt *l, int x){
    for (; *l && (*l)->valor < x; l = &(*l)->prox);
    LInt temp = *l;
    *l = malloc (sizeof (struct lligada));
    (*l)->valor = x;
    (*l)->prox = temp;
}

// Q6
int removeOneOrd (LInt *l, int x){
    int ans = 1;
    
    for (; *l && (*l)->valor < x; l = &(*l)->prox);
    
    if (*l && (*l)->valor == x) {
        ans = 0;
        LInt temp = *l;
        *l = (*l)->prox;
        free(temp);
    }
    
    return ans;
}


// Q7
void mergeL (LInt *r, LInt l1, LInt l2){
    for (; l1 || l2; r = &(*r)->prox) {
        if ((l1 && l2 && l1->valor < l2->valor) || !(l2)) {
            *r = l1;
            l1 = l1->prox;
        }
        else {
            *r = l2;
            l2 = l2->prox;
        }
    }
    *r = NULL;
}

// Q8
void splitQS (LInt l, int x, LInt *mx, LInt *Mx){
    
    for (; l; l = l->prox) {
        if (l->valor < x) {
            *mx = l;
            mx = &(*mx)->prox;
        }
        else {
            *Mx = l;
            Mx = &(*Mx)->prox;
        }  
    }
    *mx = *Mx = NULL;
}

// Q9
LInt parteAmeio (LInt *l){
    int mid = length(*l)>>1;
    LInt head, *r = &head;
    for (; mid > 0; mid--, *l = (*l)->prox, r = &(*r)->prox)
        *r = *l;
    *r = NULL;
    return head;
}

// Q10
int removeAll (LInt *l, int x){
    int count = 0;
    while (*l) {
        if ((*l)->valor == x) {
            LInt temp = *l;
            *l = (*l)->prox;
            free(temp);
            count++;
        }
        else 
            l = &(*l)->prox;
    }
    
    return count;
}

// Q11
int removeDups (LInt *l){
    int count = 0;
    
    for (; *l; l = &(*l)->prox) {
        LInt *curs = &(*l)->prox;
        while (*curs) {
            if ((*curs)->valor == (*l)->valor) {
                LInt temp = *curs;
                *curs = (*curs)->prox;
                free(temp);
                count++;
            }
            else 
                curs = &(*curs)->prox;
        }
        
    }
    return count;
}

// Q12
int removeMaiorL (LInt *l){
    LInt curs = *l;
    int maior = (*l)->valor;
    for (; curs; curs = curs->prox) 
        if (curs->valor > maior)
            maior = curs->valor;
            
    for (; (*l)->valor != maior; l = &(*l)->prox);
    LInt temp = *l;
    *l = (*l)->prox;
    free(temp);
    return maior;
}

// Q13
void init (LInt *l){
    for (; *l && (*l)->prox; l = &(*l)->prox);
    free(*l);
    *l = NULL;
}


// Q14
void appendL (LInt *l, int x){
    for (; *l; l = &(*l)->prox);
    *l = malloc(sizeof(struct lligada));
    (*l)->valor = x;
    (*l)->prox = NULL;
}

// Q15
void concatL (LInt *a, LInt b){
    for (; *a; a = &(*a)->prox);
    *a = b;
}

// Q16
LInt cloneL (LInt l) {
    LInt new = NULL, head = NULL;;
    if (l) {
        for (; l; l = l->prox) {
            new = malloc(sizeof(struct lligada));
            new->valor = l->valor;
            new->prox = NULL;
            if (!head)
                head = new;
            new = new->prox;
        }
        new->prox = NULL;
    }

    return head;
}

LInt cloneLMelhorada(LInt l) {
    LInt head, *r = &head;
    for (; l; l = l->prox, r = &(*r)->prox) {
        *r = malloc(sizeof(struct lligada));
        (*r)->valor = l->valor;
    }
    *r = NULL;
    return head;
}

// Q17
LInt cloneRev (LInt l) {
    LInt new = NULL, list = NULL;

    for (; l; l = l->prox) {
        new = malloc(sizeof(struct lligada));
        new->valor = l->valor;
        new->prox = list;
        list = new;
    }
    
    return list;
}

// Q18
int maximo (LInt l) {
    int max = l->valor;
    
    for (; l; l = l->prox)
        if (l->valor > max)
            max = l->valor;

    return max;
}

// Q19
int take (int n, LInt *l){
    int count = 0;
    for (; *l && n > 0; l = &(*l)->prox, n--, count++);
    while (*l) {
        LInt temp = *l;
        *l = (*l)->prox;
        free(temp);
    }
    return count;
}

// Q20
int drop (int n, LInt *l) {
    int counter=0;
    
    for (; *l && n > 0; counter++, n--) {
        LInt temp = *l;
        *l = (*l)->prox;
        free(temp);
    }
    
    return counter;
}

// Q21
LInt Nforward (LInt l, int N) {

    for (; N;  l = l->prox, N--);
       
    return l;
}

// Q22
int listToArray (LInt l, int v[], int N) {
    int i;

    for (i = 0; l && i < N; i++, l = l->prox)
        v[i] = l->valor;

    return i;
}

// Q23
LInt arrayToList (int v[], int N){
    LInt head, *r = &head;
    int i;
    for (i = 0; i < N; i++) {
        *r = malloc(sizeof(struct lligada));
        (*r)->valor = v[i];
        r = &(*r)->prox;
    }
    *r = NULL;
    return head;
}

// Q24
LInt somasAcL (LInt l) {
    LInt head, *r = &head;
    int acum = 0;
    for (; l; l = l->prox, r = &(*r)->prox) {
        acum += l->valor;
        *r = malloc(sizeof(struct lligada));
        (*r)->valor = acum;
    }
    *r = NULL;
    return head;
}

// Q25
void remreps (LInt l) {
    LInt back = NULL;

    while (l) {
        LInt curs, front;
        back = l;
        for (curs = l->prox; curs && curs->valor == l->valor; curs = front) {
            front = curs->prox;
            back->prox = curs->prox;
            free(curs);
        }
        l = l->prox;
    }
}

void remrepsAlt (LInt l){
    for (; l; l = l->prox) {
        LInt *c = &(l->prox);
        while (*c && (*c)->valor == l->valor) {
            LInt temp = *c;
            *c = (*c)->prox;
            free(temp);
        }
    }
}

// Q26
LInt rotateL (LInt l){
    LInt head = l;
    
    if (l && l->prox) {
        LInt init = l;
        l = head = l->prox;
        for (; l && l->prox; l = l->prox);
        l->prox = init;
        init->prox = NULL;
    }
    
    return head;
}

// Q27
LInt parte (LInt l){
    LInt head, *i = &head, *p = &l;
    int j;
    for (j = 1; *p; j++) {
        if (!(j%2)) {
            *i = *p;
            i = &(*i)->prox;
            *p = (*p)->prox;
        }
        else 
            p = &(*p)->prox;
    }
    *i = NULL;
    return head;
}

// Q28
typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

int altura (ABin a){
    if (!a)
        return 0;
    int e = altura(a->esq);
    int d = altura(a->dir);
    return (e > d ? 1 + e : 1 + d);
}

// Q29
ABin cloneAB (ABin a) {
    if (!a)
        return NULL;
    ABin new_tree;
    new_tree = malloc(sizeof(struct nodo));
    new_tree->valor = a->valor;
    new_tree->esq = cloneAB(a->esq);
    new_tree->dir = cloneAB(a->dir);
    
    return new_tree;
}

// Q30
void mirror (ABin *a) {
    if (*a) {
        ABin temp = (*a)->esq;
        (*a)->esq = (*a)->dir;
        (*a)->dir = temp;
        mirror(&(*a)->dir);
        mirror(&(*a)->esq);
    }
}

// Q31
void inorder (ABin a, LInt *l) {
    if (a) {
        inorder(a->esq, l);
        while (*l)
            l = &(*l)->prox;
        *l = malloc(sizeof(struct nodo));
        (*l)->valor = a->valor;
        inorder(a->dir,&(*l)->prox);
    }
    else 
        *l = NULL;
}

// Q32
void preorder (ABin a, LInt *l) {
    if (a) {
        *l = malloc(sizeof(struct nodo));
        (*l)->valor = a->valor;
        preorder(a->esq,&(*l)->prox);
        while (*l)
            l = &(*l)->prox;
        preorder(a->dir, l);
    }
    else
        *l = NULL;
}

// Q33
void posorder (ABin a, LInt *l) {
    if (a) {
        posorder(a->esq, l);
        while (*l)
            l = &(*l)->prox;
        posorder(a->dir, l);
        while (*l)
            l = &(*l)->prox;
        *l = malloc(sizeof(struct nodo));
        (*l)->valor = a->valor;
        (*l)->prox = NULL;
    }
    else 
        *l = NULL;
}

// Q34
int depth (ABin a, int x) {

    if (!a) 
        return -1;

    if (a->valor == x) 
        return 1;
    
    int esq = depth(a->esq, x);
    int dir = depth(a->dir, x);
    if (esq == -1 && dir == -1)
        return -1;
    if (esq == -1 || (esq != -1 && dir != -1 && dir < esq)) 
        return 1 + dir;
    return 1 + esq;

}

// Q35
int freeAB (ABin a) {
    int count = 0;
    
    if (a) {
        count += 1 + freeAB(a->esq) + freeAB(a->dir);
        free(a);
    }
    
    return count;
}

// Q36
int pruneAB (ABin *a, int l) {
    int count = 0;

    if (*a && l == 0) {
        count += 1 + pruneAB(&(*a)->esq, 0) + pruneAB(&(*a)->dir, 0);
        free(*a);
        *a = NULL;
    }
    else if (*a) 
        count += pruneAB(&(*a)->esq, l-1) + pruneAB(&(*a)->dir, l-1);
    
    return count;
        
}

// Q37
int iguaisAB (ABin a, ABin b) {
    int ret = 1;
    
    if ((!a && b) || (a && !b))
        ret = 0;
    
    else if (a && b) 
        ret = a->valor == b->valor && iguaisAB(a->esq, b->esq) && iguaisAB(a->dir, b->dir);
        
    return ret;
}

// Q38
LInt concat(LInt a, LInt b) {
    if(!a) 
        return b;
    LInt temp = a;
    while(temp->prox) 
        temp = temp->prox;
    temp->prox = b;
    
    return a;
}

LInt nivelL (ABin a, int n) {
    if (!a || n < 1) 
        return NULL;

    if (n == 1) {
        LInt new = malloc(sizeof(struct lligada));
        new->valor = a->valor;
        new->prox = NULL;
        return new;
    }else 
        return concat(nivelL(a->esq, n-1), nivelL(a->dir, n-1));
}

// Q39
int nivelV (ABin a, int n, int v[]) {
    if (!a || n < 1)
        return 0;

    if (n == 1) {
        *v = a->valor;
        return 1;
    }

    else {
        int e = nivelV(a->esq,n - 1,v);
        int d = nivelV(a->dir,n - 1, v+e);
        return e + d;
    }
}

// Q40
int dumpAbin (ABin a, int v[], int N) {
    if (!a || N < 0)
        return 0;
    
    int esq = dumpAbin(a->esq, v, N);
    if (esq < N) {
        *(v+esq) = a->valor;
        return esq + dumpAbin(a->dir, v+esq+1, N-esq-1) + 1;
    }
    else 
        return N;
}

// Q41
ABin somasAcA (ABin a) {
    if (!a)
        return NULL;
    
    ABin new = malloc(sizeof(struct nodo));
    new->esq = somasAcA(a->esq);
    new->dir = somasAcA(a->dir);
    new->valor = a->valor + (new->esq ? new->esq->valor : 0) + (new->dir ? new->dir->valor : 0);

    return new;      
}

// Q42
int contaFolhas (ABin a) {
    if (!a)
        return 0;
    
    return (!(a->esq) && !(a->dir)) + contaFolhas(a->esq) + contaFolhas(a->dir);
}

// Q43
ABin cloneMirror (ABin a) {
    ABin new = NULL;
    
    if (a) {
        new = malloc(sizeof(struct nodo));
        new->valor = a->valor;
        new->esq = cloneMirror(a->dir);
        new->dir = cloneMirror(a->esq);
    }
    
    return new;
}

// Q44
int addOrdRec (ABin *a, int x) {
    
    if (!(*a)) {
        ABin new = malloc(sizeof(struct nodo));
        new->valor = x;
        new->esq = new->dir = NULL;
        *a = new;
        return 0;
    }
    else if (x < (*a)->valor) 
        return addOrdRec(&(*a)->esq, x);

    else if (x > (*a)->valor)
        return addOrdRec(&(*a)->dir, x);
    
    else 
        return 1;   
}

int addOrd (ABin *a, int x) {
    int isThere = 0;
    while (*a && !isThere) {
        if (x < (*a)->valor)
            a = &(*a)->esq;
        else if (x > (*a)->valor)
            a = &(*a)->dir;
        else 
            isThere = 1;
    }
    
    if (!isThere) {
        *a = malloc(sizeof(struct nodo));
        (*a)->valor = x;
        (*a)->esq = (*a)->dir = NULL;
    }

    return isThere;
}

// Q45
int lookupAB (ABin a, int x) {
    int ans = 0;

    while (a && !ans) {
        if (x < a->valor)
            a = a->esq;
        else if (x > a->valor)
            a = a->dir;
        else 
            ans = 1;
    }

    return ans;
}

// Q46
int depthOrd (ABin a, int x) {
    int dep = 0, isThere = 0;

    while (a && !isThere) {
        dep++;
        if (x < a->valor)
            a = a->esq;
        else if (x > a->valor)
            a = a->dir;
        else 
            isThere = 1;
    }

    return (isThere ? dep : -1);
}

// Q47
int maiorAB (ABin a) {
    while (a && a->dir)
        a = a->dir;

    return a->valor;
}

// Q48
void removeMaiorA (ABin *a) {
    while (*a && (*a)->dir)
        a = &(*a)->dir;
    
    ABin temp = (*a)->esq;
    free(*a);
    *a = temp;
}

// Q49
int quantosMaiores (ABin a, int x) {
    if(!a) return 0;
    
    if(a->valor <= x) return quantosMaiores(a->dir,x);
    else return 1 + quantosMaiores(a->esq,x) + quantosMaiores(a->dir,x);
}

// Q50
void listToBTree (LInt l, ABin *a) {
   if (!l) 
        *a = NULL;
    else {
        int mid = length(l)>>1;
        LInt *c = &l;
        for (; mid > 0; mid--, c = &(*c)->prox);
        *a = malloc(sizeof(struct nodo));
        (*a)->valor = (*c)->valor;
        (*a)->esq = (*a)->dir = NULL;
        LInt next = (*c)->prox;
        *c = NULL;
        listToBTree(l, &(*a)->esq);
        listToBTree(next, &((*a)->dir));
    }
}

// Q51

// Versão kinda stupid
int compare(ABin a, int num, char c) {
    int ans = 1;

    if (a) {
        ans = compare(a->esq, num, c) && compare(a->dir, num, c);
        ans = ans && ((c == '<') ? a->valor < num : a->valor > num);
    }
    return ans;
}

int deProcura (ABin a) {
    int ans = 1;

    if (a && (!(compare(a->esq, a->valor, '<') && compare(a->dir, a->valor, '>'))))
        ans = 0;
    else if (a)
        ans = deProcura(a->esq) && deProcura(a->dir);

    return ans;
}

// Versão com mais sentido
int maior(ABin a, int x) {
    return (!a || (a && a->valor > x && maior(a->esq, x) && maior(a->dir, x)));
} 

int menor(ABin a, int x) {
    return (!a || (a && a->valor < x && menor(a->esq, x) && menor(a->dir, x)));
}

int deProcura1 (ABin a) {
    if (a) {
        int ans = menor(a->esq, a->valor) && maior(a->dir, a->valor);
        return ans && deProcura(a->esq) && deProcura(a->dir);
    }
    
    return 1;
}
    
// Testes

void printTree(ABin a) {
    if (a) {
        printTree(a->esq);
        printf("%d ", a->valor);
        printTree(a->dir);
    }
}

void printLista(LInt l) {

    for (LInt aux = l; aux; aux = aux->prox)
        printf("%d ", aux->valor);

    putchar('\n');
}

int main() {
    printf("Largest Element: %d\n", largestElem());
    printf("Average: %d\n", average());
    printf("Second Largest Element: %d\n", secondLargest());

    printf("Teste de conversão de uma lista para uma btree:\n");
    int v[10] = {1,2,3,4,5,6,7,8,9,10};
    LInt l = arrayToList(v, 10);
    ABin a = NULL;
    listToBTree(l, &a);

    LInt r = NULL;
    posorder(a, &r);
    printLista(r);

    printTree(a);
    putchar('\n');

    return 0;
}