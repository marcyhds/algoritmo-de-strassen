#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"
#define TAM 250

int main(){

    int **mat1, **mat2, **mat3; /* matrizes a serem alocadas */
    int i, j;                   /* variaveis auxiliares */
    clock_t t;                  /* variavel para armazenar o tempo */
    FILE *arq1, *arq2;          /* ponteiro para arquivo */


    arq1 = fopen("strassen.txt", "w");
    if(arq1==NULL){
        printf("Arquivo 1 não abriu.\n");
        return 1;
    }
    arq2 = fopen("tradicional.txt", "w");
    if(arq2==NULL){
        printf("Arquivo 2 não abriu.\n");
        return 1;
    }

    for(i=0;i<30;i++){
        /* GERA MATRIZES ALEATÓRIAS */
        mat1 = gerar_matriz(TAM);
        mat1 = insere_valores(mat1,TAM);
        mat2 = gerar_matriz(TAM);
        mat2 = insere_valores(mat2,TAM);
        mat3 = gerar_matriz(TAM);


        /* MULTIPLICAÇÃO COM ALGORITMO DE STRASSEN */
        t = clock();
        mat3 = strassen(mat1,mat2,mat3,TAM);
        t = clock() - t;
        fprintf(arq1,"%f\n",((float)t)/CLOCKS_PER_SEC);

        t = clock();
        mat3 = multiplica_matriz(mat1,mat2,TAM);
        t = clock() - t;
        fprintf(arq2,"%f\n",((float)t)/CLOCKS_PER_SEC);


        /* LIBERA AS MATRIZES ALOCADAS */
        mat1 = liberar_matriz(mat1,TAM);
        mat2 = liberar_matriz(mat2,TAM);
        mat3 = liberar_matriz(mat3,TAM);
    }

    fclose(arq1);
    fclose(arq2);

    return 0;
}
