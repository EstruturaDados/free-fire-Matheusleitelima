#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Limites máximos
#define MAX_COMPONENTES 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Estrutura que guarda as informações de cada componente
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// Limpa o buffer do teclado
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lê uma string de forma segura (sem estourar o tamanho)
void lerStringSegura(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove o '\n'
    } else buffer[0] = '\0';
}

// Exibe o menu principal e o status da mochila
void exibirCabecalho(int qtd, int ordenado) {
    printf("\n=============================================================\n");
    printf("         PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("=============================================================\n");
    printf("Itens na Mochila: %d/%d\n", qtd, MAX_COMPONENTES);
    printf("Status da Ordenacao por Nome: %s\n", ordenado ? "ORDENADO" : "NAO ORDENADO");
    printf("-------------------------------------------------------------\n");
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("6. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("-------------------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// Mostra todos os componentes armazenados
void mostrarComponentes(Componente arr[], int n) {
    if (n == 0) {
        printf("\nNenhum componente na mochila!\n");
        return;
    }
    printf("\n---------------- INVENTARIO ATUAL ----------------\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. %-20s | Tipo: %-10s | Prioridade: %d\n",
               i + 1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("-------------------------------------------------\n");
}

// Adiciona um novo componente à mochila
void cadastrarComponente(Componente arr[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Mochila cheia! (%d itens)\n", MAX_COMPONENTES);
        return;
    }

    Componente c;
    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: ");
    lerStringSegura(c.nome, MAX_NOME);
    printf("Tipo: ");
    lerStringSegura(c.tipo, MAX_TIPO);
    printf("Prioridade (1-10): ");
    scanf("%d", &c.prioridade);
    limparEntrada();

    arr[*n] = c;  // adiciona o novo componente no vetor
    (*n)++;
    printf(">> Componente adicionado com sucesso!\n");
}

// Remove um componente escolhido pelo usuário
void removerComponente(Componente arr[], int *n) {
    if (*n == 0) {
        printf("\nNenhum item para descartar!\n");
        return;
    }

    mostrarComponentes(arr, *n);
    printf("Digite o numero do componente a remover: ");
    int idx;
    scanf("%d", &idx);
    limparEntrada();

    if (idx < 1 || idx > *n) {
        printf("Indice invalido!\n");
        return;
    }

    // Move os elementos para "fechar" o espaço do item removido
    for (int i = idx - 1; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;
    printf(">> Componente removido!\n");
}

// Ordena os componentes pelo nome usando Bubble Sort
void bubbleSort(Componente arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Realiza busca binária por nome (precisa estar ordenado)
int buscaBinaria(Componente arr[], int n, const char chave[]) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(arr[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1; // não encontrado
}

int main() {
    Componente mochila[MAX_COMPONENTES];
    int n = 0, opcao;
    int ordenado = 0;

    do {
        // Exibe o menu principal
        exibirCabecalho(n, ordenado);
        scanf("%d", &opcao);
        limparEntrada();

        switch (opcao) {
            case 1:
                cadastrarComponente(mochila, &n);
                ordenado = 0; // após adicionar, fica desordenado
                break;
            case 2:
                removerComponente(mochila, &n);
                break;
            case 3:
                mostrarComponentes(mochila, n);
                break;
            case 4:
                bubbleSort(mochila, n);
                printf(">> Mochila organizada por nome!\n");
                ordenado = 1;
                break;
            case 5: {
                if (!ordenado) {
                    printf("A mochila deve estar ordenada por nome!\n");
                    break;
                }
                char chave[MAX_NOME];
                printf("Digite o nome do componente-chave: ");
                lerStringSegura(chave, MAX_NOME);
                int pos = buscaBinaria(mochila, n, chave);
                if (pos >= 0)
                    printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].prioridade);
                else
                    printf("Componente NAO encontrado!\n");
                break;
            }
            case 6:
                printf("\n*** TORRE DE FUGA ATIVADA! MISSAO COMPLETA! ***\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 6);

    return 0;
}
