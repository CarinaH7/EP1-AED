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
typedef int TIPOCUSTO;

typedef struct adjacencia{
    int vert;                   //vertice de destino
    TIPOCUSTO custo;            //Custo dessa aresta
    struct adjacencia *prox;    //Proximo vertice
}ADJACENCIA;

typedef struct{
    ADJACENCIA *cab;            //Onde que as arestas que saem dele chega
}VERTICE;

typedef struct{
    int vet;
    int arestas;
    VERTICE *adj;
}GRAFO;

typedef struct{
    int vet;
    int arestas;
    VERTICE *adj;
}AGM;

GRAFO *criagGrafo(int n,int m){
    GRAFO * g = (GRAFO*) malloc(sizeof(GRAFO));
    g->vet = n;
    g->arestas = m;
    g->adj =(VERTICE *)malloc(n*sizeof(VERTICE));
    int i;
    for(i=0;i<n;i++)
        g->adj[i].cab=NULL;
    return g;
}

ADJACENCIA *criaAdj(int v,int custo){
    ADJACENCIA *temp = (ADJACENCIA*)malloc(sizeof(ADJACENCIA));
    temp->custo = custo;
    temp->vert = v;
    temp->prox = NULL;
    return temp;
}

bool criaAresta(GRAFO *g,int o,int d,TIPOCUSTO custo){
    if(!g) return false;

    ADJACENCIA *novo1 = criaAdj(d,custo);
    novo1->prox = g->adj[o].cab;
    g->adj[o].cab = novo1;

    /*ADJACENCIA *novo2 = criaAdj(o,custo);
    novo2->prox = g->adj[d].cab;
    g->adj[d].cab = novo2;*/
    return true;
}

void recebeArestas(GRAFO * g,FILE * file,int n, int m){
    int i,j;
    int o,d,custo;

    //fscanf(file,"%i %i %i",&o,&d,&custo);
    //criaAresta(g,o,d,custo);

    for(i=0;i<m;i++){
       fscanf(file,"%i %i %i",&o,&d,&custo);
       criaAresta(g,o,d,custo);
    }
    imprimeGrafo(g);
}

void inicializaCusto(GRAFO * g, int *custo, int *p){
    int v;
    for(v=0;v<g->vet;v++){
        custo[v]=INFINITY;
        p[v]=-1;
    }
}

/*Verifica se ainda existe um vertica que nao eh livre( que nao fois selecionado ainda)*/
bool existeLivre(GRAFO*g,bool *livre){//Norton usou int aberto?
    int i;
    for(i=0;i<g->vet;i++){
        if(livre[i]) return true;
    }
    return false;
}

/**Retorna a menor distancia */
int extractMin(GRAFO*g, bool *livre,int *custo){
    int i;
    for(i=0;i<g->vet;i++){
        if(livre[i]) break;    //Busca o primeiro livre
    }
    if(i==g->vet)return -1; //Se varreu o for e nao encontrou o arranjo
    int menor= i;
    for(i=menor;i<g->vet;i++)
        if(livre[i] && custo[menor]>custo[i])
            menor=i;
    return menor;
}

GRAFO *MST_PRIM(GRAFO * g,int raiz){
    AGM *S=criagGrafo(g->vet,g->vet);
    int *custo=(int *) malloc(g->vet*sizeof(int));
    int p[g->vet];
    bool livre[g->vet];

    inicializaCusto(g,custo,&p);
    custo[raiz]=0;

    int i,u;
    for(i=0;i<g->vet;i++){
        livre[i]=true;
    }
    while(existeLivre(g,&livre)){
        int u=extractMin(g,livre,custo);
        criaAresta(S,u,p[u],custo[u]);

        livre[u]=false;
        ADJACENCIA *adj = g->adj[u].cab;
        while(adj){
            if(g->adj->cab->custo<custo[adj->vert]){
                custo[adj->vert]=g->adj->cab->custo;
                p[adj->vert]=u;
            }
            adj= adj->prox;
        }
    }
    return S;
}
void custoGrafo(GRAFO *g,int *custo){
    int i;
    for(i=0;i<g->vet;i++){
       *custo+=g->adj->cab->custo;
    }
}
void imprimeS(GRAFO * S){
    int custo;
    custoGrafo(S,&custo);
    printf("%i\n", custo);
    int i;

    for(i=0;i<S->vet;i++){
        ADJACENCIA *adj=S->adj[i].cab;
        while(adj){
            printf("%i %i\n",i,adj->vert);
            adj=adj->prox;
        }
    }
}
void imprimeGrafo(GRAFO * g){
    printf("%i %i\n",g->vet,g->arestas);
    int i=0;

    for(i=0;i<g->vet;i++){
        ADJACENCIA *adj=g->adj[i].cab;
        while(adj){
            printf("%i %i %i\n",i,adj->vert,adj->custo);
            adj=adj->prox;
        }
    }
}

int main(){

    FILE *file;
    file= fopen("grafo01.txt","r");

    int n,m;
    fscanf(file,"%i %i",&n,&m);

    GRAFO *g = criagGrafo(n,m);

    //printf("%i,%i\n",n,m);

    recebeArestas(g,file,n,m);
    printf("\n");
    AGM *S=MST_PRIM(g,0);
    imprimeS(S);
    return 0;
}
