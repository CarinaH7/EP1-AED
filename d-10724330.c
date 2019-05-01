#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define INFINITY INT_MAX / 2
#define MAX 100
#define true 1
#define false 0
#define AN -1

typedef int bool;
typedef int TipoPeso;

typedef struct
{
    int numVet;
    int numArestas;
    TipoPeso peso[MAX + 1][MAX + 1];
} TIPOGRAFO;

void inicializaGrafo(TIPOGRAFO *g, int nv)
{
    g->numVet = nv;
    g->numArestas = 0;
    int x, y;
    for (x = 0; x <= nv; x++)
    {
        for (y = 0; y <= nv; y++)
        {
            g->peso[x][y] = AN;
        }
    }
}

void insereAresta(TIPOGRAFO *g, int v1, int v2, TipoPeso peso)
{
    g->peso[v1][v2] = peso;
    g->peso[v2][v1] = peso;
    g->numArestas++;
}

void recebeArestas(TIPOGRAFO *g, FILE *file, int n, int m)
{

    int i, v1, v2, peso;

    for (i = 0; i < m; i++)
    {
        fscanf(file, "%i %i %i", &v1, &v2, &peso);
        insereAresta(g, v1, v2, peso);
    }
}

bool verificaAdjacente(TIPOGRAFO *g, int v1, int v2)
{
    if (g->peso[v1][v2] != AN || g->peso[v2][v1] != AN)
        return true;
    return false;
}

void algoritmoDePrim(TIPOGRAFO *g, int *pesoS, int *ant)
{
    int i, j, qtdAnt, v1, v2;
    double menorPeso = INFINITY;
    int nv = g->numVet;
    int auxPeso = 0;

    for (i = 0; i < nv; i++)
    {

        ant[i] = -1;
        printf("%d", ant[i]);
    }
    qtdAnt = 0;
    ant[0] = 0;
    qtdAnt++;

    while (qtdAnt != nv)
    {
        for (int i = 0; i < nv; i++)
        {
            if (ant[i] != -1)
            {
                for (j = 0; j < nv; j++)
                {
                    if ((ant[j] == -1) && verificaAdjacente(g, i, j))
                    {
                        if (menorPeso > g->peso[i][j])
                        {
                            menorPeso = g->peso[i][j];
                            v1 = i;
                            v2 = j;
                        }
                    }
                }
            }
        }
        ant[v2] = v1;
        auxPeso += g->peso[v1][v2];
        qtdAnt++;
        menorPeso = INFINITY;
    }
    *pesoS = auxPeso;
}

int main(int argc, char *argv[])
{

    FILE *file;
    file = fopen(argv[1], "r");

    int n, m;
    fscanf(file, "%i %i", &n, &m);

    TIPOGRAFO *g = (TIPOGRAFO *)malloc(sizeof(TIPOGRAFO));
    inicializaGrafo(g, n);

    recebeArestas(g, file, n, m);

    FILE *saida;
    saida = fopen(argv[2], "w");

    int i, pesoS = 0;
    int ant[g->numVet];
    algoritmoDePrim(g, &pesoS, ant);

    fprintf(saida, "%i\n", pesoS);
    for (i = 1; i < g->numVet; i++)
    {
        fprintf(saida, "%i %i\n", ant[i], i);
    }

    printf("\n");

    return 0;
}
