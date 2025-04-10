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
    fprintf(f, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,\"%s\",%s,",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento);
               
                //id_classe
                if(processos[i].qtd_classe == 1){
                    fprintf(f, "{%d},", processos[i].id_classe[0]);
                }
                else{
                    fprintf(f, "\"{");
                        for (int j = 0; j < processos[i].qtd_classe; j++) {
                            fprintf(f, "%d", processos[i].id_classe[j]);
                            if (j < processos[i].qtd_classe - 1) {
                                fprintf(f, ",");
                            }
                        }
                    fprintf(f, "}\",");
                }

        //assuntos
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
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

/* int carregarProcessos(const char* nomeArquivo, Processo processos[], int max) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[MAX_LINHA];
    int i = 0;

    fgets(linha, MAX_LINHA, f); // Pular o cabeçalho

    while (fgets(linha, MAX_LINHA, f) && i < max) {
        Processo p = {0};
        char* token;

        // ID
        token = strtok(linha, ",");
        if (token == NULL) {
            printf("Erro ao processar linha %d do arquivo.\n", i + 1);
            continue; // Pule para a próxima linha
        }
        p.id = atoi(token);

        // Numero
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha %d do arquivo.\n", i + 1);
            continue; // Pule para a próxima linha
        }
        limparQuebraLinha(token);
        strncpy(p.numero, token + 1, strlen(token) - 2); // tira aspas
        p.numero[strlen(token) - 2] = '\0';

        // Data ajuizamento
        token = strtok(NULL, ",");
        limparQuebraLinha(token);
        strcpy(p.data_ajuizamento, token);
        
        // ID classe (pode ter vários)

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha %d do arquivo.\n", i + 1);
            continue; // Pule para a próxima linha
        }
        p.qtd_classe = 0;

        if (token[0] == '"') {
            token+=2; // pula o '{'
            char* fim = strchr(token, '}');
            if (fim) *fim = '\0'; // corta o '}'

            char* sub = strtok(token, ",");
            while (sub != NULL && p.qtd_classe < MAX_CLASSE) {
                p.id_classe[p.qtd_classe++] = atoi(sub);
                sub = strtok(NULL, ",");
            }
        }
        if (p.qtd_classe >= MAX_CLASSE) {
            printf("Erro: número de classes excede o limite na linha %d.\n", i + 1);
            continue;
        }
        
        if (p.qtd_assuntos >= MAX_ASSUNTOS) {
            printf("Erro: número de assuntos excede o limite na linha %d.\n", i + 1);
            continue;
        }
        else{
            p.id_classe[0] = atoi(token);
            p.qtd_classe = 1;
        }
        

        // ID assunto (pode ter vários)
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Erro ao processar linha %d do arquivo.\n", i + 1);
            continue; // Pule para a próxima linha
        }
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
        if (token == NULL) {
            printf("Erro ao processar linha %d do arquivo.\n", i + 1);
            continue; // Pule para a próxima linha
        }
        p.ano_eleicao = atoi(token);

        // Adiciona ao vetor
        processos[i++] = p;
    }

    fclose(f);
    return i; // número de processos lidos
} */

int carregarProcessos(const char* nomeArquivo, Processo processos[], int max) {
    printf("Tentando abrir o arquivo: %s\n", nomeArquivo);

    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[MAX_LINHA];
    int i = 0;

    // Ignorar o cabeçalho
    fgets(linha, MAX_LINHA, f);

    while (fgets(linha, MAX_LINHA, f) && i < max) {
        Processo p = {0};
        char* token;

        // ID
        token = strtok(linha, ",");
        if (!token) continue;
        p.id = atoi(token);

        // Número (remover aspas)
        token = strtok(NULL, ",");
        if (!token) continue;
        limparQuebraLinha(token);
        if (token[0] == '"') token++;
        size_t len = strlen(token);
        if (len > 0 && token[len - 1] == '"') token[len - 1] = '\0';
        strncpy(p.numero, token, sizeof(p.numero));
        p.numero[sizeof(p.numero) - 1] = '\0';

        // Data de ajuizamento
        token = strtok(NULL, ",");
        if (!token) continue;
        limparQuebraLinha(token);
        strncpy(p.data_ajuizamento, token, sizeof(p.data_ajuizamento));
        p.data_ajuizamento[sizeof(p.data_ajuizamento) - 1] = '\0';

        // ID Classe
        token = strtok(NULL, ",");
        if (!token) continue;
        limparQuebraLinha(token);
        p.qtd_classe = 0;

        if (token[0] == '"') token++; // remove aspas externas
        if (token[0] == '{') token++;

        char* fim = strchr(token, '}');
        if (fim) *fim = '\0';

        char* sub = strtok(token, ",");
        while (sub && p.qtd_classe < MAX_CLASSE) {
            p.id_classe[p.qtd_classe++] = atoi(sub);
            sub = strtok(NULL, ",");
        }

        if (p.qtd_classe >= MAX_CLASSE) {
            printf("Erro: número de classes excede o limite na linha %d.\n", i + 1);
            continue;
        }

        // ID Assunto
        token = strtok(NULL, ",");
        if (!token) continue;
        limparQuebraLinha(token);
        p.qtd_assuntos = 0;

        if (token[0] == '"') token++;
        if (token[0] == '{') token++;

        fim = strchr(token, '}');
        if (fim) *fim = '\0';

        sub = strtok(token, ",");
        while (sub && p.qtd_assuntos < MAX_ASSUNTOS) {
            p.id_assunto[p.qtd_assuntos++] = atoi(sub);
            sub = strtok(NULL, ",");
        }

        if (p.qtd_assuntos >= MAX_ASSUNTOS) {
            printf("Erro: número de assuntos excede o limite na linha %d.\n", i + 1);
            continue;
        }

        // Ano da eleição
        token = strtok(NULL, ",\n");
        if (!token) continue;
        p.ano_eleicao = atoi(token);

        // Adiciona o processo ao vetor
        processos[i++] = p;
    }

    fclose(f);
    return i;
}




void limparQuebraLinha(char* str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == ' ')) {
        str[--len] = '\0';
    }
}