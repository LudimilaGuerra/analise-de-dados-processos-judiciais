#ifndef PROCESSO_H
#define PROCESSO_H
#define MAX_LINHA 512

typedef struct {
    int id;
    char numero[21];
    char data_ajuizamento[24]; // formato YYYY-MM-DD HH:MM:SS
    char id_classe[20];
    char id_assunto[20];
    int ano_eleicao; 
} Processo;

void ordenarPorId(Processo processos[], int esq, int dir);
void swap(Processo *a, Processo *b);
int particao(Processo V[], int esq, int dir);
void salvarOrdenadoPorId(const char* nomeArquivo, Processo processos[], int n);
void ordenarPorData(Processo processos[], int esq, int dir); 
int particaoData(Processo V[], int esq, int dir); 
int contarPorClasse(Processo processos[], int n, const char* id_classe);
int contarAssuntosUnicos(Processo processos[], int n);
void listarMultiplosAssuntos(Processo processos[], int n);
int calcularDiasTramitando(const char* data_ajuizamento, const char* data_atual);
int carregarProcessos(const char* nomeArquivo, Processo processos[], int max);
void limparQuebraLinha(char* str);
void listarMultiplosAssuntos(Processo processos[], int total);

#endif
