#ifndef PROCESSO_H
#define PROCESSO_H
#define MAX_LINHA 256

typedef struct {
    int id;
    char numero[21];
    char data_ajuizamento[20]; // formato YYYY-MM-DD HH:MM:SS
    char id_classe[20];
    int id_assunto[5]; // assume no máximo 10 assuntos
    int qtd_assuntos;
    int ano_eleicao;
} Processo;

void ordenarPorId(Processo processos[], int esq, int dir);
void swap(Processo *a, Processo *b);
int particao(Processo V[], int esq, int dir);
void salvarOrdenadoPorId(const char* nomeArquivo, Processo processos[], int n);
void ordenarPorData(Processo processos[], int n);
int contarPorClasse(Processo processos[], int n, const char* id_classe);
int contarAssuntosUnicos(Processo processos[], int n);
void listarMultiplosAssuntos(Processo processos[], int n);
int calcularDiasTramitando(Processo p, const char* data_atual);
int carregarProcessos(const char* nomeArquivo, Processo processos[], int max);
void limparQuebraLinha(char* str);



#endif