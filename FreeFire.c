#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura 
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// funções
void inserirItem(Item mochila[], int *qtdAtual);
void removerItem(Item mochila[], int *qtdAtual);
void listarItens(Item mochila[], int qtdAtual);
void buscarItem(Item mochila[], int qtdAtual);

int main() {
    Item mochila[MAX_ITENS]; // Vetor que armazena os itens
    int qtdAtual = 0;        // Quantidade de itens cadastrados
    int opcao;

    do {
        printf("\n=== Sistema de Inventario ===\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa 

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtdAtual);
                break;
            case 2:
                removerItem(mochila, &qtdAtual);
                break;
            case 3:
                listarItens(mochila, qtdAtual);
                break;
            case 4:
                buscarItem(mochila, qtdAtual);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int *qtdAtual) {
    if (*qtdAtual >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n final

    printf("Tipo do item (arma/municao/cura): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // Limpa 

    mochila[*qtdAtual] = novo;
    (*qtdAtual)++;

    printf("Item inserido com sucesso!\n");
    listarItens(mochila, *qtdAtual);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *qtdAtual) {
    if (*qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *qtdAtual; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Desloca os itens para preencher o espaço
            for (int j = i; j < *qtdAtual - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtdAtual)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }

    listarItens(mochila, *qtdAtual);
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < qtdAtual; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < qtdAtual; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}
