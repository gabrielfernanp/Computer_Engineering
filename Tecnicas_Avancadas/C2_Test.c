#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DESC 100
#define MAX_DATE 12 // Definido 12 pois estava dando erro na adição de novas tarefas

void inserirTarefa(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char data[MAX_DATE];
    char descricao[MAX_DESC];

    printf("Insira a data da tarefa (dd/mm/aaaa): ");
    fgets(data, MAX_DATE, stdin);
    data[strcspn(data, "\n")] = 0; 

    printf("Insira a descrição da tarefa: ");
    fgets(descricao, MAX_DESC, stdin);
    descricao[strcspn(descricao, "\n")] = 0; 

    fprintf(arquivo, "%s - %s\n", data, descricao);

    fclose(arquivo);
    printf("Tarefa adicionada com sucesso!\n");
}

void mostrarTarefasDoDia(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char data[MAX_DATE];
    char linha[MAX_DATE + MAX_DESC + 3];

    printf("Insira a data das tarefas a serem mostradas (dd/mm/aaaa): ");
    fgets(data, MAX_DATE, stdin);
    data[strcspn(data, "\n")] = 0;

    printf("Tarefas para %s:\n", data);
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strncmp(linha, data, strlen(data)) == 0) {
            printf("%s", linha);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada para esta data.\n");
    }

    fclose(arquivo);
}

int main() {
    const char *nomeArquivo = "Tarefas Diarias.txt";
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova tarefa\n");
        printf("2. Mostrar tarefas do dia\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do stdin

        switch (opcao) {
            case 1:
                inserirTarefa(nomeArquivo);
                break;
            case 2:
                mostrarTarefasDoDia(nomeArquivo);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
