#include <stdio.h>
#include <string.h>
#include "processo.h"

void ordenarPorId(Processo processos[], int n){
    //1. Ordenar, em ordem crescente, o conjunto de dados a partir do atributo “id”;
}

void ordenarPorData(Processo processos[], int n){
    //2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
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
    
    
}