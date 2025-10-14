#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ===================== Estruturas =====================

// Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ===================== Contadores =====================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===================== Funções para Vetor =====================
void inserirItemVetor(Item mochila[], int *qtdAtual) {
    if (*qtdAtual >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtdAtual] = novo;
    (*qtdAtual)++;
    printf("Item inserido no vetor!\n");
}

void removerItemVetor(Item mochila[], int *qtdAtual) {
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
            for (int j = i; j < *qtdAtual - 1; j++)
                mochila[j] = mochila[j + 1];
            (*qtdAtual)--;
            encontrado = 1;
            printf("Item removido!\n");
            break;
        }
    }

    if (!encontrado) printf("Item nao encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("Itens no vetor:\n");
    for (int i = 0; i < qtdAtual; i++) {
        printf("%d. %s | %s | %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Ordena vetor por nome (Bubble Sort)
void ordenarVetor(Item mochila[], int qtdAtual) {
    for (int i = 0; i < qtdAtual - 1; i++) {
        for (int j = 0; j < qtdAtual - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome!\n");
}

// Busca sequencial
void buscarSequencialVetor(Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    comparacoesSequencial = 0;
    int encontrado = 0;
    for (int i = 0; i < qtdAtual; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado! %s | %s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) printf("Item nao encontrado!\n");
    printf("Comparacoes na busca sequencial: %d\n", comparacoesSequencial);
}

// Busca binária (vetor deve estar ordenado)
void buscarBinariaVetor(Item mochila[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0, fim = qtdAtual - 1, meio;
    comparacoesBinaria = 0;
    int encontrado = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("Item encontrado! %s | %s | %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) printf("Item nao encontrado!\n");
    printf("Comparacoes na busca binaria: %d\n", comparacoesBinaria);
}

// ===================== Funções para Lista Encadeada =====================
void inserirItemLista(No **inicio) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Nome do item: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item inserido na lista!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No *atual = *inicio;
    No *anterior = NULL;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL) *inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido da lista!\n");
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (!encontrado) printf("Item nao encontrado!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("Itens na lista:\n");
    int i = 1;
    while (inicio != NULL) {
        printf("%d. %s | %s | %d\n", i++, inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

void buscarSequencialLista(No *inicio) {
    if (inicio == NULL) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    comparacoesSequencial = 0;
    int encontrado = 0;

    while (inicio != NULL) {
        comparacoesSequencial++;
        if (strcmp(inicio->dados.nome, nomeBusca) == 0) {
            printf("Item encontrado! %s | %s | %d\n", inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
            encontrado = 1;
            break;
        }
        inicio = inicio->proximo;
    }

    if (!encontrado) printf("Item nao encontrado!\n");
    printf("Comparacoes na busca sequencial (lista): %d\n", comparacoesSequencial);
}

// ===================== Menu Principal =====================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No *inicioLista = NULL;
    int opcao, estrutura;

    do {
        printf("\nEscolha a estrutura:\n1. Vetor\n2. Lista Encadeada\n0. Sair\nOpcao: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 0) break;

        do {
            printf("\n=== Sistema de Inventario ===\n");
            printf("1. Inserir Item\n2. Remover Item\n3. Listar Itens\n4. Buscar Sequencial\n5. Ordenar (vetor) / N/A (lista)\n6. Buscar Binaria (vetor)\n0. Voltar\nEscolha: ");
            scanf("%d", &opcao);
            getchar();

            switch(opcao) {
                case 1:
                    if (estrutura == 1) inserirItemVetor(mochilaVetor, &qtdVetor);
                    else inserirItemLista(&inicioLista);
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor(mochilaVetor, &qtdVetor);
                    else removerItemLista(&inicioLista);
                    break;
                case 3:
                    if (estrutura == 1) listarItensVetor(mochilaVetor, qtdVetor);
                    else listarItensLista(inicioLista);
                    break;
                case 4:
                    if (estrutura == 1) buscarSequencialVetor(mochilaVetor, qtdVetor);
                    else buscarSequencialLista(inicioLista);
                    break;
                case 5:
                    if (estrutura == 1) ordenarVetor(mochilaVetor, qtdVetor);
                    else printf("Ordenacao nao aplicavel para lista encadeada!\n");
                    break;
                case 6:
                    if (estrutura == 1) buscarBinariaVetor(mochilaVetor, qtdVetor);
                    else printf("Busca binaria nao aplicavel para lista encadeada!\n");
                    break;
                case 0:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }

        } while(opcao != 0);

    } while(estrutura != 0);

    printf("Saindo do sistema...\n");
    return 0;
}

