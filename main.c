#include <stdio.h>
#include <stdlib.h>
#include "simpio.h"
#include "random.h"
#include "vutil.h"

#define TAM_INI 10
#define TAM_MAX 1000
#define INC 10

void insercao (int, int *);
void mergesort (int, int, int *);
int buscaDC(int, int, int, veti);
int busca (int, int, int *);
int buscaBinaria (int, int, int *);

// simpio.h e random.h veem da biblioteca de
// Eric Roberts, acessível por exemplo em
// https://www.ime.usp.br/~pf/Roberts/C-library/standard/

typedef int *veti; // Apelida de "veti" ("vetor de inteiros") o tipo "int *".

long long NOP;

int main() {

    int n, k, x, r;
    veti v;

    Randomize();

    FILE *saida;
    saida = fopen ("dados.dat", "w");

    for(n = TAM_INI; n <= TAM_MAX; n += INC) {
        v = vdecresc(n);

        NOP = 0;
        //x = -1;
        // mergesort(0, n, v);
        // buscaBinaria(x, n, v);
        // insercao(n, v);
        fprintf(saida, "%d %d\n", n, NOP);

        free(v);
    }

    fclose(saida);

    return 0;
}

// Devolve um índice j no intervalo p..r
// tal que x == v[k].
// Se tal k não existe, devolve -1.
int buscaDC(int p, int r, int x, veti v) {

    int q, z1, z2;
    if(p > r)
        return -1;
    q = (p + r) / 2;
    if(x == v[q])
        return q;
    z1 = buscaDC(p, q - 1, x, v);
    z2 = buscaDC(q + 1, r, x, v);
    return z1 > z2? z1 : z2;

}


// As funções a seguir foram tiradas do site
// "Projeto de Algoritmos em C" de P. Feofiloff
// https://www.ime.usp.br/~pf/algoritmos/


// A função recebe x, n >= 0 e v e devolve
// um índice k em 0..n-1 tal que x == v[k].
// Se tal k não existe, devolve -1.
int
busca (int x, int n, int v[])
{
   int k;
   k = n-1;
   while (k >= 0 && v[k] != x)
      k -= 1;
   return k;
}


// Esta função rearranja o vetor v[0..n-1]
// em ordem crescente.

void
insercao (int n, int v[])
{
   for (int j = 1; j < n; ++j) {
      int x = v[j];
      int i;
      for (i = j-1; i >= 0 && v[i] > x; --i, NOP++)
         v[i+1] = v[i];
      v[i+1] = x;
   }
}


// A função recebe vetores crescentes v[p..q-1]
// e v[q..r-1] e rearranja v[p..r-1] em ordem
// crescente.

static void
intercala (int p, int q, int r, int v[])
{
   int *w;                                 //  1
   w = malloc ((r-p) * sizeof (int));      //  2
   int i = p, j = q;                       //  3
   int k = 0;                              //  4

   while (i < q && j < r) {                //  5
      if (v[i] <= v[j])  w[k++] = v[i++];  //  6
      else  w[k++] = v[j++];               //  7
   }                                       //  8
   while (i < q)  w[k++] = v[i++];         //  9
   while (j < r)  w[k++] = v[j++];         // 10
   for (i = p; i < r; ++i)  v[i] = w[i-p]; // 11
   free (w);                               // 12
}


// A função mergesort rearranja o vetor
// v[p..r-1] em ordem crescente.

void
mergesort (int p, int r, int v[])
{
   if (p < r-1) {                 // 1
      int q = (p + r)/2;          // 2
      mergesort (p, q, v);        // 3
      mergesort (q, r, v);        // 4
      intercala (p, q, r, v);     // 5
   }
}


// Esta função recebe um inteiro x
// e um vetor crescente v[0..n-1]
// e devolve um índice j em 0..n
// tal que v[j-1] < x <= v[j].

int
buscaBinaria (int x, int n, int v[]) {
   int e = -1, d = n; // atenção!
   while (e < d-1) {
      int m = (e + d)/2;
      if (v[m] < x) e = m;
      else d = m;
   }
   return d;
}
