#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

int **gerar_matriz(int tam){

    /*----- ALOCA DINÂMICAMENTE UMA MATRIZ -----*/
    int **m;    /* ponteiro para a matriz */
    int i, j;   /* variaveis auxiliares */

    /* aloca as linhas da matriz */
    m = (int **) calloc (tam, sizeof(int *));   /* Um vetor de tam ponteiros para inteiro */
    if (m==NULL){                               /* memória insuficiente */
        printf ("*** ERRO ***");
        return NULL;
    }

    /* aloca as colunas da matriz */
    for (i=0;i<tam;i++){
        m[i] = (int *) calloc (tam, sizeof(int));   /* tam vetores de tam inteiros */
        if (m[i]==NULL){                            /* memória insuficiente */
            printf ("*** ERRO ***");
            return NULL;
        }
    }

    /*---- RETORNA PONTEIRO PARA A MATRIZ GERADA -----*/
    return m;
}

int **liberar_matriz(int **m, int tam){

    int  i;             /* variavel auxiliar */

    if (m==NULL)
        return NULL;

    for(i=0;i<tam;i++)
        free(m[i]);     /* libera as linhas da matriz */

    free(m);            /* libera a matriz (vetor de ponteiros) */

    return NULL;        /* retorna um ponteiro nulo */
}

int **insere_valores(int **m, int tam){

    int i, j;   /* variaveis auxiliares */

    /* preenche a matriz com valores aleatórios entre 500 e 5000*/
    srand(time(NULL));
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++)
            m[i][j] = 500 + (rand() % 5000);
    }
    return m;
}

void imprimir_matriz(int **m, int tam){

    int i, j;

    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    return;
}

int **soma_matriz(int **mat1, int **mat2, int tam){

    /*----- ALOCA DINÂMICAMENTE UMA MATRIZ RESULTADO -----*/
    int **resultado;    /* ponteiro para a matriz */
    int i, j;           /* variaveis auxiliares */

    /* aloca as linhas da matriz */
    resultado = (int **) calloc (tam, sizeof(int *));   /* Um vetor de tam ponteiros para inteiro */
    if (resultado==NULL){                               /* memória insuficiente */
        printf ("*** ERRO ***");
        return NULL;
    }

    /* aloca as colunas da matriz */
    for (i=0;i<tam;i++){
        resultado[i] = (int *) calloc (tam, sizeof(int));   /* tam vetores de tam inteiros */
        if (resultado[i]==NULL){                            /* memória insuficiente */
            printf ("*** ERRO ***");
            return NULL;
        }
    }

    /*----- SOMA DUAS MATRIZES -----*/
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            resultado[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    return resultado;
}

int **subtrai_matriz(int **mat1, int **mat2, int tam){

    /*----- ALOCA DINÂMICAMENTE UMA MATRIZ RESULTADO -----*/
    int **resultado;    /* ponteiro para a matriz */
    int i, j;           /* variaveis auxiliares */

    /* aloca as linhas da matriz */
    resultado = (int **) calloc (tam, sizeof(int *));   /* Um vetor de tam ponteiros para inteiro */
    if (resultado==NULL){                               /* memória insuficiente */
        printf ("*** ERRO ***");
        return NULL;
    }

    /* aloca as colunas da matriz */
    for (i=0;i<tam;i++){
        resultado[i] = (int *) calloc (tam, sizeof(int));   /* tam vetores de tam inteiros */
        if (resultado[i]==NULL){                            /* memória insuficiente */
            printf ("*** ERRO ***");
            return NULL;
        }
    }

    /*----- SUBTRAI DUAS MATRIZES -----*/
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            resultado[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    return resultado;
}

int **multiplica_matriz(int **mat1, int **mat2, int tam){

    /*----- ALOCA DINÂMICAMENTE UMA MATRIZ RESULTADO -----*/
    int **resultado;    /* ponteiro para a matriz */
    int i, j, k;           /* variaveis auxiliares */

    /* aloca as linhas da matriz */
    resultado = (int **) calloc (tam, sizeof(int *));   /* Um vetor de tam ponteiros para inteiro */
    if (resultado==NULL){                           /* memória insuficiente */
        printf ("*** ERRO ***");
        return NULL;
    }

    /* aloca as colunas da matriz */
    for (i=0;i<tam;i++){
        resultado[i] = (int *) calloc (tam, sizeof(int));   /* tam vetores de tam inteiros */
        if (resultado[i]==NULL){                            /* memória insuficiente */
            printf ("*** ERRO ***");
            return NULL;
        }
    }

    /*----- MULTIPLICA DUAS MATRIZES -----*/
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            resultado[i][j] = 0;
            for(k=0;k<tam;k++)
                resultado[i][j] = resultado[i][j] + mat1[i][k] * mat2[k][j];
        }
    }

    return resultado;
}

int **strassen(int **mat1, int **mat2, int **mat3, int tam){

    if(tam/2==0){
        mat3[0][0] = mat1[0][0] * mat2[0][0];
        return mat3;
    }

    int i, j;
    int **a, **b, **c, **d;                         /* submatrizes de mat1*/
    int **e, **f, **g, **h;                         /* submatrizes de mat2 */
    int **p1, **p2, **p3, **p4, **p5, **p6, **p7;   /* matrizes para chamadas recusrsivas */

    /*----- ALOCA DINAMINCAMENTE AS MATRIZES */
    a = gerar_matriz(tam/2);    e = gerar_matriz(tam/2);
    b = gerar_matriz(tam/2);    f = gerar_matriz(tam/2);
    c = gerar_matriz(tam/2);    g = gerar_matriz(tam/2);
    d = gerar_matriz(tam/2);    h = gerar_matriz(tam/2);

    p1 = gerar_matriz(tam/2);   p5 = gerar_matriz(tam/2);
    p2 = gerar_matriz(tam/2);   p6 = gerar_matriz(tam/2);
    p3 = gerar_matriz(tam/2);   p7 = gerar_matriz(tam/2);
    p4 = gerar_matriz(tam/2);

    /*----- PREENCHE AS SUBMATRIZES -----*/
    for(i=0;i<tam/2;i++){
        for(j=0;j<tam/2;j++){
            a[i][j] = mat1[i][j];
            b[i][j] = mat1[i][(tam/2)+j];
            c[i][j] = mat1[(tam/2)+i][j];
            d[i][j] = mat1[(tam/2)+i][(tam/2)+j];
            e[i][j] = mat2[i][j];
            f[i][j] = mat2[i][(tam/2)+j];
            g[i][j] = mat2[(tam/2)+i][j];
            h[i][j] = mat2[(tam/2)+i][(tam/2)+j];
        }
    }

    /*----- CHAMADAS RECURSIVAS -----*/
    p1 = strassen(a,(subtrai_matriz(f,h,tam/2)),p1,tam/2);                      /* P1 = A(F-H)     */
    p2 = strassen(soma_matriz(a,b,tam/2),h,p2,tam/2);                           /* P2 = (A+B)H     */
    p3 = strassen(soma_matriz(c,d,tam/2),e,p3,tam/2);                           /* P3 = (C+D)E     */
    p4 = strassen(d,subtrai_matriz(g,e,tam/2),p4,tam/2);                        /* P4 = D(G-E)     */
    p5 = strassen(soma_matriz(a,d,tam/2),soma_matriz(e,h,tam/2),p5,tam/2);      /* P5 = (A+D)(E+H) */
    p6 = strassen(subtrai_matriz(b,d,tam/2),soma_matriz(g,h,tam/2),p6,tam/2);   /* P6 = (B-D)(G+H) */
    p7 = strassen(subtrai_matriz(a,c,tam/2),soma_matriz(e,f,tam/2),p7,tam/2);   /* p7 = (A-C)(E+F) */

    /*----- ATRIBUIÇÃO DOS RESULTADOS -----*/
    for(i=0;i<tam/2;i++){
        for(j=0;j<tam/2;j++){
            mat3[i][j] = p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];                   /* P5+P4-P2+P6 */
            mat3[i][(tam/2)+j] = p1[i][j]+p2[i][j];                             /* P1+P2 */
            mat3[(tam/2)+i][j] = p3[i][j]+p4[i][j];                             /* P3+P4 */
            mat3[(tam/2)+i][(tam/2)+j] = p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];   /* P1+P5-P3-P7 */
        }
    }

    /*----- LIBERA AS MATRIZES ALOCADAS -----*/
    liberar_matriz(a,tam/2);
    liberar_matriz(b,tam/2);
    liberar_matriz(c,tam/2);
    liberar_matriz(d,tam/2);
    liberar_matriz(e,tam/2);
    liberar_matriz(f,tam/2);
    liberar_matriz(g,tam/2);
    liberar_matriz(h,tam/2);
    liberar_matriz(p1,tam/2);
    liberar_matriz(p2,tam/2);
    liberar_matriz(p3,tam/2);
    liberar_matriz(p4,tam/2);
    liberar_matriz(p5,tam/2);
    liberar_matriz(p6,tam/2);
    liberar_matriz(p7,tam/2);

    /*---- RETORNA O RESULTADO DA MULTIPLICAÇÃO -----*/
    return mat3;
}
