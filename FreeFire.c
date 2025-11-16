#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
} Item;

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

void limparBufferEntrada();
int comparaItens(const Item *a, const Item *b, CriterioOrdenacao criterio);

int main() {
    int opcao;

    printf("*** Ilha Free Fire - Mochila ***\n");

    do {
        limparTela();
        exibirMenu();
        printf("Escolha sua opcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            limparBufferEntrada();
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nSaindo. Boa fuga!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente de novo.\n");
                break;
        }

        if (opcao != 0 && opcao != 3) {
            printf("\nPressione ENTER para continuar...\n");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n*** Menu da Mochila ***\n");
    printf("Itens atuais: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenado por Nome: %s\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("--------------------------\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar por nome (Binaria)\n");
    printf("0. Sair\n");
    printf("--------------------------\n");
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao cabe mais nada.\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome (Ex: Madeira): ");
    scanf("%29s", novo.nome);
    limparBufferEntrada();

    printf("Tipo (Ex: Recurso): ");
    scanf("%19s", novo.tipo);
    limparBufferEntrada();

    printf("Quantidade: ");
    while (scanf("%d", &novo.quantidade) != 1 || novo.quantidade <= 0) {
        printf("Quantidade invalida. Tente de novo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    
    printf("Prioridade (1=Baixa a 5=Alta): ");
    while (scanf("%d", &novo.prioridade) != 1 || novo.prioridade < 1 || novo.prioridade > 5) {
        printf("Prioridade invalida (1 a 5). Tente de novo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    mochila[numItens] = novo;
    numItens++;
    ordenadaPorNome = false;
    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
}

void removerItem() {
    if (numItens == 0) {
        printf("A mochila esta vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[MAX_NOME];
    printf("\n--- Remover Item ---\n");
    printf("Nome do item para remover: ");
    scanf("%29s", nomeRemover);
    limparBufferEntrada();

    int indiceEncontrado = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1) {
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        ordenadaPorNome = false;
        printf("Item '%s' removido.\n", nomeRemover);
    } else {
        printf("Item '%s' nao encontrado na mochila.\n", nomeRemover);
    }
}

void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Lista de Itens ---\n");
    printf("| # | Nome        | Tipo      | Qtd | Prioridade |\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("| %-1d | %-11s | %-9s | %-3d | %-10d |\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("--------------------------------------------------\n");
}

int comparaItens(const Item *a, const Item *b, CriterioOrdenacao criterio) {
    if (criterio == NOME) {
        return strcmp(a->nome, b->nome);
    } else if (criterio == TIPO) {
        return strcmp(a->tipo, b->tipo);
    } else if (criterio == PRIORIDADE) {
        return b->prioridade - a->prioridade;
    }
    return 0;
}

void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    int i, j;
    Item chave;

    for (i = 1; i < numItens; i++) {
        chave = mochila[i];
        j = i - 1;

        while (j >= 0 && comparaItens(&mochila[j], &chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j = j - 1;
            comparacoes++;
        }
        
        if (j >= 0) {
            comparacoes++;
        } else {
            comparacoes++;
        }
        
        mochila[j + 1] = chave;
    }

    ordenadaPorNome = (criterio == NOME);
}

void menuDeOrdenacao() {
    int escolha;
    printf("\n--- Escolher Criterio de Ordenacao ---\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (5-1)\n");
    printf("Escolha (1, 2 ou 3): ");
    
    if (scanf("%d", &escolha) != 1) {
        printf("Escolha invalida.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    CriterioOrdenacao criterio;
    switch (escolha) {
        case 1:
            criterio = NOME;
            break;
        case 2:
            criterio = TIPO;
            break;
        case 3:
            criterio = PRIORIDADE;
            break;
        default:
            printf("Opcao invalida, voltando ao menu.\n");
            return;
    }

    insertionSort(criterio);
    printf("\nOrdenacao completa por %s.\n", (escolha == 1) ? "Nome" : (escolha == 2) ? "Tipo" : "Prioridade");
    printf("Desempenho (Comparacoes): %d\n", comparacoes);
}

void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\nERRO: A mochila DEVE ser ordenada por Nome (Opcao 4 -> 1) antes de usar a busca binaria.\n");
        return;
    }

    char nomeBuscado[MAX_NOME];
    printf("\n--- Busca Binaria por Nome ---\n");
    printf("Nome do item para buscar: ");
    scanf("%29s", nomeBuscado);
    limparBufferEntrada();

    int esquerda = 0;
    int direita = numItens - 1;
    int indiceEncontrado = -1;
    int passos = 0;

    while (esquerda <= direita) {
        passos++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultadoComparacao = strcmp(mochila[meio].nome, nomeBuscado);

        if (resultadoComparacao == 0) {
            indiceEncontrado = meio;
            break;
        } else if (resultadoComparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (indiceEncontrado != -1) {
        printf("\nItem ENCONTRADO em %d passos!\n", passos);
        printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               mochila[indiceEncontrado].nome, mochila[indiceEncontrado].tipo,
               mochila[indiceEncontrado].quantidade, mochila[indiceEncontrado].prioridade);
    } else {
        printf("\nItem '%s' NAO encontrado (%d passos).\n", nomeBuscado, passos);
    }
}
