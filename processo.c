#include <stdio.h>
#include <string.h>
#include <time.h>
#include "processo.h"

void ordenarPorId(Processo processos[], int n){
    //1. Ordenar, em ordem crescente, o conjunto de dados a partir do atributo “id”;
}

void ordenarPorData(Processo processos[], int n){
    
    if (n <= 1) return;
    
    int i, j;
    Processo temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j+1].data_ajuizamento) < 0) {
                temp = processos[j];
                processos[j] = processos[j+1];
                processos[j+1] = temp;
            }
        }
    }
}
}

int contarPorClasse(Processo processos[], int n, int id_classe){
    //3. Contar quantos processos estão vinculados a um determinado “id_classe”;
}

int contarAssuntosUnicos(Processo processos[], int n){
    //4. Identificar quantos “id_assuntos” constam nos processos presentes na base de dados;
}

void listarMultiplosAssuntos(Processo processos[], int n){
    //5. Listar todos os processos que estão vinculados a mais de um assunto; e
}

int calcularDiasTramitando(Processo p, const char* data_atual){
    //6. Indicar a quantos dias um processo está em tramitação na justiça.
    //É mais usável se verificando todo o arquivo de processos em busca do ID, mas é mais fácil criar passando Processo p, const char* data_atual
    //Passar como parâmetro a data atual ou usar a biblioteca time.h pra fazer isso automaticamente
}

int contarLinhas(const char* nomeArquivo){
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) return -1;
    char linha[512];
    int count = 0;

    fgets(linha, sizeof(linha), f); 
    while (fgets(linha, sizeof(linha), f))
    {
        count++;
    }
    fclose(f);
    return count;
} // usado para quando necessário passar em parâmetros

int main() {
    int n = contarLinhas("processo_043_202409032338.csv");
    if (n <= 0 )
    {
        printf("Erro no arquivo");
    }

    Processo processos[n];
    FILE *f = fopen("processo_043_202409032338.csv", "r");
    if (!f) return 1;

    char linha[256];
    fgets(linha, sizeof(linha), f); // Pular cabeçalho
    
    for (int i = 0; i < n; i++) {
        if (!fgets(linha, sizeof(linha), f)) break;
        
        // Parse simplificado (ajuste conforme seu arquivo real)
        sscanf(linha, "%d, \"%[^\"]\", %19[^,], {%d}, {%d}, %d",
               &processos[i].id,
               processos[i].numero,
               processos[i].data_ajuizamento,
               &processos[i].id_classe,
               &processos[i].id_assunto[0],
               &processos[i].ano_eleicao);
    }
    fclose(f);

    ordenarPorData(processos, n);

    FILE *fout = fopen("processos_ordenados_data.csv", "w");
    if (!fout) return 1;

    fprintf(fout, "\"id\", \"numero\", \"data_ajuizamento\", \"id_classe\", \"id_assunto\", \"ano_eleicao\"\n");
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d, \"%s\", %s, {%d}, {%d}, %d\n",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento,
                processos[i].id_classe,
                processos[i].id_assunto[0],
                processos[i].ano_eleicao);
    }
    fclose(fout);

    printf("Ordenação concluída. Verifique 'processos_ordenados_data.csv'\n");
    return 0;
}
    
    
}
