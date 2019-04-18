#include <stdio.h>
#include <stdlib.h>

void transformInt(char [] c1){
    int n1[cl.length];
    int n2=0;
    int j;
    for(j=0;j<10;j++){
        if(tam[j]!= '0'){
            n1[j]=tam[j];
        }else break;
    return n1;
    }
}
int main(){
    FILE *file;
    file= fopen("grafo01.txt","r");
    int i=0;
    int j;
    char tam[10];
    int tama[2];
    int x=0;
    fgets(tam, 10,file);

    int teste[100];
    teste=trasformInt(tam);
    for(i=0;i<teste.length;i++){
        printf("%i",teste[i]);
    }
    //tama[0]=tam[0]-'0';
    printf("%i",tama[0]);
    //printf("%s",tam);
    char arr[100];
    char matriz[100];
    int l=0;
    int c=0;
    /*while(fgets(arr, sizeof(arr),file)!=NULL){
        for(l=0;l<sizeof(arr);l++){
            matriz[l][c]=arr[i];
            i++;
        }
        c++;
    }*/

    /*for(i=0;i<2;i++){
        printf("%i",tam[i]);
    }*/

    return 0;
}
