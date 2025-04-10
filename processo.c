#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "processo.h"

//1. Ordenar, em ordem crescente, o conjunto de dados a partir do atributo “id”;
void ordenarPorId(Processo processos[], int esq, int dir){
    //Será usado o quick sort; as outras funções usadas estão no arquivo processo.h
    if(esq < dir) {
        int pivot = particao(processos, esq, dir);
        ordenarPorId(processos, esq, pivot - 1);
        ordenarPorId(processos, pivot, dir);
    }    

}
void swap(Processo *a, Processo *b) {
    Processo temp = *a;
    *a = *b;
    *b = temp;
}
int particao(Processo V[], int esq, int dir){
    int pivot = V[(esq + dir) / 2].id;
    int i = esq;
    int j = dir;
    while(i <= j) {
        while(V[i].id < pivot) i++;
        while(V[j].id > pivot) j--;
        if(i <= j) {
            swap(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}

void salvarOrdenadoPorId(const char* nomeArquivo, Processo processos[], int n){
    FILE* f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        printf("Erro ao criar arquivo %s.\n", nomeArquivo);
        return;
    }

    //cabeçalho
    fprintf(f, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d,%s,%s,{%d},{", processos[i].id, processos[i].numero, processos[i].data_ajuizamento, processos[i].id_classe);
        for (int j = 0; j < processos[i].qtd_assuntos; j++)
        {
            fprintf(f, "%d", processos[i].id_assunto[j]);
            if (j < processos[i].qtd_assuntos - 1) {
                fprintf(f, ",");
            }
        }
        fprintf(f, "},%d\n", processos[i].ano_eleicao);
    }
    fclose(f);
    
}


//2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
void ordenarPorData(Processo processos[], int n){
}

//3. Contar quantos processos estão vinculados a um determinado “id_classe”;
int contarPorClasse(Processo processos[], int n, int id_classe){
}

//4. Identificar quantos “id_assuntos” constam nos processos presentes na base de dados;
int contarAssuntosUnicos(Processo processos[], int n){
}

//5. Listar todos os processos que estão vinculados a mais de um assunto; e
void listarMultiplosAssuntos(Processo processos[], int n){
}

//6. Indicar a quantos dias um processo está em tramitação na justiça.
int calcularDiasTramitando(Processo p, const char* data_atual){
    //É mais usável se verificando todo o arquivo de processos em busca do ID, mas é mais fácil criar passando Processo p, const char* data_atual
    //Passar como parâmetro a data atual ou usar a biblioteca time.h pra fazer isso automaticamente
}

int carregarProcessos(const char* nomeArquivo, Processo processos[], int max) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[MAX_LINHA];
    int i = 0;

    fgets(linha, MAX_LINHA, f); // Pular o cabeçalho

    while (fgets(linha, MAX_LINHA, f) && i < max) {
        Processo p;
        char* token;

        // ID
        token = strtok(linha, ",");
        p.id = atoi(token);

        // Numero
        token = strtok(NULL, ",");
        strcpy(p.numero, token + 1); // Remove a aspa inicial
        p.numero[strlen(p.numero) - 1] = '\0'; // Remove a aspa final

        // Data ajuizamento
        token = strtok(NULL, ",");
        strcpy(p.data_ajuizamento, token);

        // ID classe (entre { })
        token = strtok(NULL, ",");
        sscanf(token, "{%d}", &p.id_classe);

        // ID assunto (pode ter vários!)
        token = strtok(NULL, ",");
        p.qtd_assuntos = 0;

        if (token[0] == '{') {
            token++; // pula o {
            char* fim = strchr(token, '}');
            if (fim) *fim = '\0'; // corta o }

            char* sub = strtok(token, ",");
            while (sub != NULL) {
                p.id_assunto[p.qtd_assuntos++] = atoi(sub);
                sub = strtok(NULL, ",");
            }
        }

        // Ano eleição
        token = strtok(NULL, ",\n");
        p.ano_eleicao = atoi(token);

        // Adiciona ao vetor
        processos[i++] = p;
    }

    fclose(f);
    return i; // número de processos lidos
}

