#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define INFINITY INT_MAX/2
#define MAX 50
#define true 1
#define false 0

typedef int bool;
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
void inicializaKey(GRAFO * g, int *key, int *p){
    int v;
    for(v=0;v<g->numVert;v++){
        key[v]=INFINITY;
        p[v]=-1;
    }
}
/*Verifica se ainda existe um vertica que nao eh livre( que nao fois selecionado ainda)*/
bool existeLivre(GRAFO*g,bool *livre){//Norton usou int aberto?
    int i;
    for(i=0;i<g->numVert;i++){
        if(livre[i]) return true;
    }
    return false;
}
/**Retorna a menor distancia */
int extractMin(GRAFO*g, bool *livre,int *key){
    int i;
    for(i=0;i<g->numVert;i++){
        if(livre[i]) break;    //Busca o primeiro livre
    }
    if(i==g->numVert)return -1; //Se varreu o for e nao encontrou o arranjo
    int menor= i;
    for(i=menor;i<g->numVert;i++)
        if(livre[i] && key[menor]>key[i])
            menor=i;
}
void MST_PRIM(GRAFO * g,int raiz){
    int *key=(int *) malloc(g->numVert*sizeof(int));
    int p[g->numVert];
    bool livre[g->numVert];
    inicializaKey(g,key,&p);
    key[raiz]=0;

    int i;
    for(i=0;i<g->numVert;i++){
        livre[i]=true;
    }
    while(existeLivre(g,&livre)){
        int u=extractMin(g,livre,key);
        livre[u]=false;
    /***PAREI AQUII***/
    }

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
