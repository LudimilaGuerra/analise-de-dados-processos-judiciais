#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "processo.h"
#include <time.h>

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
        fprintf(f, "%d,\"%s\",\"%s.000\",\"{%s}\",%s}\",%d\n",
            processos[i].id,
            processos[i].numero,
            processos[i].data_ajuizamento,
            processos[i].id_classe,
            processos[i].id_assunto,
            processos[i].ano_eleicao);
    }

    fclose(f);
}

//2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
void ordenarPorData(Processo processos[], int esq, int dir) {
    if (esq < dir) {
        int pivot = particaoData(processos, esq, dir);
        ordenarPorData(processos, esq, pivot - 1);
        ordenarPorData(processos, pivot, dir);
    }
}

//Função de partição para datas (decrescente)
int particaoData(Processo V[], int esq, int dir) {
    char* pivot = V[(esq + dir) / 2].data_ajuizamento;
    int i = esq;
    int j = dir;

    while (i <= j) {
        //Comparação invertida para ordem decrescente
        while (strcmp(V[i].data_ajuizamento, pivot) > 0) i++;
        while (strcmp(V[j].data_ajuizamento, pivot) < 0) j--;

        if (i <= j) {
            swap(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}
void salvarOrdenadoPorData(const char* nomeArquivo, Processo processos[], int n) {
    FILE* f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        printf("Erro ao criar arquivo %s.\n", nomeArquivo);
        return;
    }

    // Escreve o cabeçalho do CSV (igual ao original)
    fprintf(f, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");

    // Escreve cada processo no arquivo
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,\"%s\",\"%s.000\",\"{%s}\",\"{%s}\",%d\n",
            processos[i].id,
            processos[i].numero,
            processos[i].data_ajuizamento,
            processos[i].id_classe,
            processos[i].id_assunto,
            processos[i].ano_eleicao);
    }

    fclose(f);
}

//3. Contar quantos processos estão vinculados a um determinado “id_classe”;
int contarPorClasse(Processo processos[], int n, const char* id_classe){
}

//4. Identificar quantos “id_assuntos” constam nos processos presentes na base de dados;


int contarAssuntosUnicos(Processo processos[], int n) {
    char assuntosUnicos[1000][20]; // Array para armazenar assuntos únicos (limite de 1000 assuntos)
    int totalUnicos = 0;

    for (int i = 0; i < n; i++) {
        char* token = strtok(processos[i].id_assunto, ","); // Divide os assuntos por vírgula
        while (token != NULL) {
            int encontrado = 0;

            // Verifica se o assunto já está no array de únicos
            for (int j = 0; j < totalUnicos; j++) {
                if (strcmp(assuntosUnicos[j], token) == 0) {
                    encontrado = 1;
                    break;
                }
            }

            // Se não foi encontrado, adiciona ao array de únicos
            if (!encontrado) {
                strncpy(assuntosUnicos[totalUnicos], token, sizeof(assuntosUnicos[totalUnicos]) - 1);
                assuntosUnicos[totalUnicos][sizeof(assuntosUnicos[totalUnicos]) - 1] = '\0';
                totalUnicos++;
            }

            token = strtok(NULL, ","); // Próximo assunto
        }
    }

    return totalUnicos;
}


//5. Listar todos os processos que estão vinculados a mais de um assunto; e
void listarMultiplosAssuntos(Processo processos[], int total)
 {
    printf("\nProcessos com mais de um assunto:\n");
    printf("==================================\n");
    for (int i = 0; i < total; i++) {
        if (strchr(processos[i].id_assunto, ',') != NULL) {
            printf("ID: %d | Numero: %s | Assuntos: %s}\"\n",
                   processos[i].id,
                   processos[i].numero,
                   processos[i].id_assunto);
        }
    }
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
            p.data_ajuizamento[strlen(token) - 4] = '\0';
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

        // ID do assunto
        char* campo = strtok(NULL, "}");
        p.id_assunto[0] = '\0';

        if (campo != NULL && strlen(campo) > 0) {
            // Remove quebra de linha e aspas se existirem
            limparQuebraLinha(campo);

            // Se começar com aspa, pula ela
            if (campo[0] == '"') {
                campo+=3;  // pula a primeira aspa
                size_t len = strlen(campo);
                if (campo[len - 1] == '"') {
                    campo[len - 1] = '\0';  // remove a última aspa
                }
            }
            else {
                campo++;  // pula a primeira chave
            }

            // Agora procura as chaves
            char* inicio = strchr(campo, '{');
            char* fim = strrchr(campo, '}'); // usa strrchr para pegar a última }

            if (inicio && fim && fim > inicio) {
                int tamanho = fim - inicio - 1;
                if (tamanho < sizeof(p.id_assunto)) {
                    strncpy(p.id_assunto, inicio + 1, tamanho); // Apenas +1 para pular '{'
                    p.id_assunto[tamanho] = '\0';
                } else {
                    printf("Erro: id_assunto muito grande na linha %d.\n", i + 1);
                    continue;
                }
            } else {
                // Caso não tenha chaves, copia como está
                strncpy(p.id_assunto, campo, sizeof(p.id_assunto) - 1);
                p.id_assunto[sizeof(p.id_assunto) - 1] = '\0';
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


//5. Listar todos os processos que estão vinculados a mais de um assunto; e
void listarMultiplosAssuntos(Processo processos[], int total)
 {
    printf("\nProcessos com mais de um assunto:\n");
    printf("==================================\n");
    for (int i = 0; i < total; i++) {
        if (strchr(processos[i].id_assunto, ',') != NULL) {
            printf("ID: %d | Numero: %s | Assuntos: %s\n",
                   processos[i].id,
                   processos[i].numero,
                   processos[i].id_assunto);
        }
    }
}

//6. Indicar a quantos dias um processo está em tramitação na justiça
int calcularDiasTramitando(const char* data_ajuizamento, const char* data_atual) {
    struct tm dt_inicio = {0};
    struct tm dt_final = {0};
    int ano_i, mes_i, dia_i;
    int dia_f, mes_f, ano_f;

    // data_ajuizamento: formato do CSV -> "aaaa-mm-dd"
    if (sscanf(data_ajuizamento, "%d-%d-%d", &ano_i, &mes_i, &dia_i) != 3) {
        printf("Erro: formato inválido de data de ajuizamento.\n");
        return -1;
    }

    // data_atual: formato digitado pelo usuário -> "dd/mm/aaaa"
    if (sscanf(data_atual, "%d/%d/%d", &dia_f, &mes_f, &ano_f) != 3) {
        printf("Erro: formato inválido da data atual.\n");
        return -1;
    }

    dt_inicio.tm_year = ano_i - 1900;
    dt_inicio.tm_mon = mes_i - 1;
    dt_inicio.tm_mday = dia_i;

    dt_final.tm_year = ano_f - 1900;
    dt_final.tm_mon = mes_f - 1;
    dt_final.tm_mday = dia_f;

    time_t t_inicio = mktime(&dt_inicio);
    time_t t_final = mktime(&dt_final);

    if (t_inicio == -1 || t_final == -1) {
        printf("Erro ao converter datas para timestamp.\n");
        return -1;
    }

    double segundos = difftime(t_final, t_inicio);
    return (int)(segundos / (60 * 60 * 24));
}