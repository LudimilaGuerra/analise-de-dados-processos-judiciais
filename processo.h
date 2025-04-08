#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct {
    int id;
    char numero[21];
    char data_ajuizamento[20];
    int id_classe;
    int id_assunto[10]; // assume no máximo 10 assuntos
    int ano_eleicao;
} Processo;

void ordenarPorId(Processo processos[], int n);
void ordenarPorData(Processo processos[], int n);
int contarPorClasse(Processo processos[], int n, int id_classe);
int contarAssuntosUnicos(Processo processos[], int n);
void listarMultiplosAssuntos(Processo processos[], int n);
int calcularDiasTramitando(Processo p, const char* data_atual);

#endif