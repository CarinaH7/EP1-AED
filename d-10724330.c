#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define INFINITY INT_MAX/2
#define MAX 50
typedef int * POINT;
typedef struct{
    int o[MAX];
    int d[MAX];
    int custo[MAX];
}ARESTA;
typedef struct{
    ARESTA a;
    int vert[MAX];
    int numVert;
}GRAFO;

void inicializaGrafo(GRAFO * g,int m){
    int i;
    for(i=0;i<MAX;i++){
        g->a.o[i]=-1;
        g->a.d[i]=-1;
        g->a.custo[i]=-1;
        g->vert[i]=-1;
    }
    g->numVert=-1;
}
void recebeArestas(GRAFO * g,FILE * file,int n, int m){
    int i,j;
    fscanf(file,"%i %i %i",&g->a.o[0],&g->a.d[0],&g->a.custo[0]);
    for(i=1;i<m;i++){
       fscanf(file,"%i %i %i",&g->a.o[i],&g->a.d[i],&g->a.custo[i]);
    }
    for(j=0;j<n;j++){
        g->vert[j]=j;
    }
    g->numVert=n;
}
void inicializaPD(GRAFO * g, int *d, int *p){
    int v;
    for(v=0;v<g->numVert;v++){
        d[v]=INFINITY;
        p[v]=-1;
    }
}
void MST_PRIM(GRAFO * g){
    int *d=(int *) malloc(g->numVert*sizeof(int));
    int p[g->numVert];
    inicializaPD(g,d,&p);
}
int main(){

    FILE *file;
    file= fopen("grafo01.txt","r");
    GRAFO g;
    int i,j,x;

    int n,m;
    fscanf(file,"%i %i",&n,&m);

    inicializaGrafo(&g,m);
    printf("%i,%i\n",n,m);

    recebeArestas(&g,file,n,m);
    for(i=0;i<m;i++){
        printf("%i %i %i\n",g.a.o[i],g.a.d[i],g.a.custo[i]);
    }

    return 0;
}
