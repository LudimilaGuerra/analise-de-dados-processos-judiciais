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

void salvarOrdenadoPorId(const char* nomeArquivo, Processo processos[], int n) {
    FILE* f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        printf("Erro ao criar arquivo %s.\n", nomeArquivo);
        return;
    }

    // Cabeçalho
    fprintf(f, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");

    for (int i = 0; i < n; i++) {
        // Escreve os campos do processo no formato correto
        fprintf(f, "%d,\"%s\",\"%s.000\",\"{%s}\",{",
            processos[i].id,
            processos[i].numero,
            processos[i].data_ajuizamento,
            processos[i].id_classe);
            
            

        // Escreve os assuntos, separados por vírgulas
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            fprintf(f, "%d", processos[i].id_assunto[j]);
            if (j < processos[i].qtd_assuntos - 1) {
                fprintf(f, ",");
            }
        }

        // Fecha o campo de assuntos e escreve o ano de eleição
        fprintf(f, "},%d\n", processos[i].ano_eleicao);
    }

    fclose(f);
}


//2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
void ordenarPorData(Processo processos[], int n){
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


//3. Contar quantos processos estão vinculados a um determinado “id_classe”;
int contarPorClasse(Processo processos[], int n, const char* id_classe){
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
    fgets(linha, MAX_LINHA, f); // Lê o cabeçalho e ignora

    while (fgets(linha, MAX_LINHA, f) && i < max) {
        Processo p;
        char* token;

        // ID
        token = strtok(linha, ",");
        p.id = atoi(token);

        // Número
        token = strtok(NULL, ",");
        limparQuebraLinha(token);
        strncpy(p.numero, token + 1, strlen(token) - 2); // Remove aspas
        p.numero[strlen(token) - 2] = '\0';

        // Data de ajuizamento
        token = strtok(NULL, ",");
        limparQuebraLinha(token);
        if (token != NULL && strlen(token) > 0) {
            strncpy(p.data_ajuizamento, token, strlen(token) - 4); // Remove aspas
            p.data_ajuizamento[strlen(token) + 2] = '\0';
        } else {
            strcpy(p.data_ajuizamento, ""); // Inicializa como vazio se não houver valor
        }

        // ID da classe
        token = strtok(NULL, "}");
        limparQuebraLinha(token);
        p.id_classe[0] = '\0';

        if (token != NULL && strlen(token) > 0) {
            // Se começa com aspas, pula a primeira
            if (token[0] == '"') {
                token+=2; // pula a primeira aspa
                // Remove a última aspa se existir
                size_t len = strlen(token);
                if (token[len - 1] == '"') {
                    token[len - 1] = '\0';
                }
            }
            else{
                token++;
            }

        // Agora procura as chaves
        char* inicio = strchr(token, '{');
        char* fim = strchr(token, '}');
        if (inicio && fim && fim > inicio) {
            int tamanho = fim - inicio - 1;
            if (tamanho < sizeof(p.id_classe)) {
                strncpy(p.id_classe, inicio + 1, tamanho);
                p.id_classe[tamanho] = '\0';
            } else {
                printf("Erro: id_classe muito grande na linha %d.\n", i + 1);
                continue;
            }
        } else {
            // Caso não tenha chaves (ou erro de formato), copia como está
            strncpy(p.id_classe, token, sizeof(p.id_classe) - 1);
            p.id_classe[sizeof(p.id_classe) - 1] = '\0';
        }
    }

        // ID dos assuntos
        token = strtok(NULL, ",");
        p.qtd_assuntos = 0;
        if (token != NULL && token[0] == '{') {
            token++;
            char* fim = strchr(token, '}');
            if (fim) *fim = '\0';

            char* sub = strtok(token, ",");
            while (sub != NULL && p.qtd_assuntos < 10) {
                p.id_assunto[p.qtd_assuntos++] = atoi(sub);
                sub = strtok(NULL, ",");
            }
        }

        // Ano da eleição
        token = strtok(NULL, ",\n");
        if (token != NULL) {
            p.ano_eleicao = atoi(token);
        } else {
            p.ano_eleicao = 0; // Inicializa como 0 se não houver valor
        }

        processos[i++] = p;
    }

    fclose(f);
    return i;
}

void limparQuebraLinha(char* str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}
