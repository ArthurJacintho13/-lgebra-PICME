#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

// ----- Definir o tamanho total das matrizes e vetores ----
#define TAM 4000

//---------- Prototipos das funcoes ----------------
int retornaDimensaoMatriz();
void leitura_criacao_matriz(int n);
void leitura_vetor_b(int n);
void algoritmo_de_Cholesky(int n);
void substituicaoProgressiva(int n);
void substituicaoRegressiva(int n);
void imprimeVetor(int n);

//------------- Variaveis globais ----------
double L[TAM][TAM];
double vetorb[TAM];
double vetory[TAM];
double vetorFINAL[TAM];

// -------------- Funcao Main -------------
int main() {

    int n = 0;
    clock_t t;
    t = clock();
// ---------- Entrada para saber o tamanho da matriz/vetor ----------    
    n = retornaDimensaoMatriz();

// --------- Chamando as funcoes --------------
    leitura_criacao_matriz(n);
    leitura_vetor_b(n);
    algoritmo_de_Cholesky(n);
    substituicaoProgressiva(n);
    substituicaoRegressiva(n);
    imprimeVetor(n);
    t = clock() - t;
    printf("\nTempo total foi de: %lf\n\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    return 0;
}

// ----------- Funcao para saber a dimensao da matriz -------------
int retornaDimensaoMatriz(){
    char x;
    double contador = 0;
    FILE *fk;
    if ((fk = fopen("A6.txt", "r")) == NULL){
        printf("Erro ao abrir o arquivo!");
    }
    else{
        while (!feof(fk)){
            x = fgetc(fk);
            if (x != '\n' && x != '-' && x != ',') {
                contador++;
            }
        }
    }
    fclose(fk);
    return sqrt(contador);
}

//----------------- Leitura da matriz inicial ----------
void leitura_criacao_matriz(int n){
    FILE *fp;
    int i = 0, j = 0;
    char lixo;
    if ((fp = fopen("A6.txt","r")) == NULL){
        printf("Erro ao abrir o arquivo!\n");
    }   
    else{
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                fscanf(fp, "%lf%c", &L[i][j], &lixo);
            }
        }
    }
    fclose(fp);
}

// ------------ Leitura do vetor b ---------------
void leitura_vetor_b(int n){
    FILE *fk;
    if ((fk = fopen ("b6.txt", "r")) == NULL){
        printf("Erro ao abrir o arquivo!\n");
    }
    else{
        for (int i = 0; i < n; i++){
            fscanf(fk, "%lf", &vetorb[i]);
        }
    }
    fclose(fk);
}

// ----------- Funcao para obter G e G transposta -------------
void algoritmo_de_Cholesky(int n){
    for (int k = 0; k < n; k++){
        if(L[k][k] > 0){
            L[k][k] = sqrt(L[k][k]);
        }
        for (int i = k + 1; i <= n; i++){
            if (L[k][k] != 0){
                L[i][k] = L[i][k]/L[k][k];
            }
        }
        for (int j = k + 1; j <= n; j++){
            for (int p = j; p <= n; p++){
                L[p][j] = L[p][j] - L[p][k] * L[j][k];
            }
        }
     }
     for (int k = 0; k < n; k++){
        for (int i = k + 1; i < n; i++){
            L[k][i] = L[i][k];
        }
    }
}

//-------- Funcao para substituicao progressiva -----
void substituicaoProgressiva(int n){
   
    for (int k = 0; k < n; k++){
        vetory[k] = 0;
    }
    for (int i = 0; i < n; i++){
        double Somatorio = 0;
        for (int j = 0; j < i; j++){
            Somatorio = Somatorio + (L[i][j]*vetory[j]);
        }
        if (L[i][i] != 0){
            vetory[i] = (vetorb[i]-Somatorio)/(L[i][i]); 
        }
    }
}

//-------- Funcao para substituicao regressiva -----
void substituicaoRegressiva(int n){

    for (int k = 0; k < n; k++){
        vetorFINAL[k] = 0;
    }
    for (int i = n-1; i >= 0; i--){
        double Somatorio = 0;
        for (int j = n-1; j > i; j--){
            Somatorio += L[i][j]*vetorFINAL[j];
        }
        if (L[i][i] != 0){
            vetorFINAL[i] = (vetory[i]-Somatorio)/(L[i][i]);
        }
    }
}

// ------------------ Impressao do Vetor Solucao ----------------
void imprimeVetor(int n){
    FILE *tk;
    if ((tk = fopen("vetorX6_teste_Cholesky.txt", "w")) == NULL){
        printf ("Erro ao abrir o arquivo!\n");
    }
    else{
        for (int i = 0; i < n; i++){
            fprintf(tk, "%.20g\n", vetorFINAL[i]);
        }
    }
    fclose(tk);
}