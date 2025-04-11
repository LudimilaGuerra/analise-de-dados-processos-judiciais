#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

void contar_processos_por_classe(Processo *processos, int total_processos) {
    int contagem[1000] = {0}; // Supondo no máximo 1000 id_classe diferentes
    int max_id_classe = 0;

    for (int i = 0; i < total_processos; i++) {
        int id = processos[i].id_classe;
        contagem[id]++;
        if (id > max_id_classe) {
            max_id_classe = id;
        }
    }

    printf("\nQuantidade de processos por id_classe:\n");
    for (int i = 0; i <= max_id_classe; i++) {
        if (contagem[i] > 0) {
            printf("id_classe %d: %d processo(s)\n", i, contagem[i]);
        }
    }
}

int main() {
    Processo processos[20000];
    int n = carregarProcessos("processo_043_202409032338.csv", processos, 20000);
    if (n <= 0) {
        printf("Erro ao carregar os processos.\n");
        return -1;
    }
   
    printf("Total de processos carregados: %d\n", n);
    int escolha = 0;
    printf("Escolha uma opção:\n");
    printf("1. Ordenar por ID (crescente)\n");
    printf("2. Ordenar por data (decrescente)\n");
    printf("3. Contar por classe\n");
    printf("4. Identificar quantos assuntos constam\n");
    printf("5. Listar processos que estão vinculados a mais de um assunto\n");
    printf("6. Calcular dias tramitando\n");
    printf("7. Sair\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            ordenarPorId(processos, 0, n - 1);
            salvarOrdenadoPorId("processos_ordenados_por_id.csv", processos, n);
            printf("Processos ordenados por ID. Novo arquivo criado\n");
            break; 
        
    //Os cases são feitos assim pra facilitar a leitura, mas não é necessário fazer assim, só pra ficar mais fácil de entender o que cada um faz
        case 2:
            ordenarPorData(processos, 0, n - 1); 
            salvarOrdenadoPorData("processos_ordenados_por_data.csv", processos, n); 
            printf("Processos ordenados por data. Novo arquivo criado\n");
            break;
            
            case 3:
            contar_processos_por_classe(processos, total_processos);
            break;
        }
        case 4:{
            int total_assuntos = contarAssuntosUnicos(processos, n);
            printf("Total de assuntos unicos: %d\n", total_assuntos);
            break;
        }
        case 5:
            listarMultiplosAssuntos(processos, n);
            break;
        case 6:{
            char data_atual[11];
            printf("Digite a data atual (dd/mm/aaaa): ");
            scanf("%s", data_atual);
            for (int i = 0; i < n; i++) {
                int dias = calcularDiasTramitando(processos[i], data_atual);
                printf("Processo ID %d está em tramitação ha %d dias.\n", processos[i].id, dias);
            }
            break;
        }
        case 7:
            printf("Saindo...\n");
            return 0;
    
        default:
            break;
    }
        return 0;
}
