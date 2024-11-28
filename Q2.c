#include <stdio.h>
#include <string.h>

#define LIMITE_PRODUTOS 40

typedef struct {
    int id_produto;
    char nome_produto[50];
    float preco_unitario;
    int quantidade_estoque;
} ItemEstoque;

void registrarItem(ItemEstoque estoque[], int *total_itens) {
    if (*total_itens >= LIMITE_PRODUTOS) {
        printf("Limite de itens atingido.\n");
        return;
    }
    printf("Digite o ID do item: ");
    scanf("%d", &estoque[*total_itens].id_produto);
    printf("Digite o nome do item: ");
    scanf(" %[^\n]s", estoque[*total_itens].nome_produto);
    printf("Digite o preço unitário: ");
    scanf("%f", &estoque[*total_itens].preco_unitario);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &estoque[*total_itens].quantidade_estoque);
    (*total_itens)++;
}

void modificarPrecoItem(ItemEstoque estoque[], int total_itens) {
    int id_item, encontrado = 0;
    float novo_preco;
    printf("Digite o ID do item para alterar o preço: ");
    scanf("%d", &id_item);
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].id_produto == id_item) {
            printf("Digite o novo preço unitário: ");
            scanf("%f", &novo_preco);
            estoque[i].preco_unitario = novo_preco;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

float obterPrecoItem(ItemEstoque estoque[], int total_itens) {
    int id_item;
    printf("Digite o ID do item para consultar o preço: ");
    scanf("%d", &id_item);
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].id_produto == id_item) {
            return estoque[i].preco_unitario;
        }
    }
    printf("Item não encontrado.\n");
    return 0.0;
}

int obterQuantidadeItem(ItemEstoque estoque[], int total_itens) {
    int id_item;
    printf("Digite o ID do item para consultar a quantidade em estoque: ");
    scanf("%d", &id_item);
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].id_produto == id_item) {
            return estoque[i].quantidade_estoque;
        }
    }
    printf("Item não encontrado.\n");
    return -1;
}

void realizarVenda(ItemEstoque estoque[], int total_itens) {
    int id_item, quantidade_desejada, encontrado = 0;
    printf("Digite o ID do item para venda: ");
    scanf("%d", &id_item);
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].id_produto == id_item) {
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade_desejada);
            if (estoque[i].quantidade_estoque >= quantidade_desejada) {
                estoque[i].quantidade_estoque -= quantidade_desejada;
                printf("Venda realizada. Total a pagar: %.2f\n", quantidade_desejada * estoque[i].preco_unitario);
            } else {
                printf("Quantidade insuficiente em estoque. Deseja comprar %d unidades e zerar o estoque? (1-Sim / 0-Não): ", estoque[i].quantidade_estoque);
                int opcao;
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Venda realizada. Total a pagar: %.2f\n", estoque[i].quantidade_estoque * estoque[i].preco_unitario);
                    estoque[i].quantidade_estoque = 0;
                } else {
                    printf("Venda não realizada.\n");
                }
            }
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

void ajustarEstoque(ItemEstoque estoque[], int total_itens) {
    int id_item, nova_quantidade, encontrado = 0;
    printf("Digite o ID do item para atualizar o estoque: ");
    scanf("%d", &id_item);
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].id_produto == id_item) {
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &nova_quantidade);
            estoque[i].quantidade_estoque = nova_quantidade;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

void listarTodosItens(ItemEstoque estoque[], int total_itens) {
    printf("Lista de todos os itens:\n");
    for (int i = 0; i < total_itens; i++) {
        printf("ID: %d, Nome: %s\n", estoque[i].id_produto, estoque[i].nome_produto);
    }
}

void listarItensSemEstoque(ItemEstoque estoque[], int total_itens) {
    printf("Itens com estoque zerado:\n");
    for (int i = 0; i < total_itens; i++) {
        if (estoque[i].quantidade_estoque == 0) {
            printf("ID: %d, Nome: %s\n", estoque[i].id_produto, estoque[i].nome_produto);
        }
    }
}

int main() {
    ItemEstoque estoque[LIMITE_PRODUTOS];
    int total_itens = 0;

    registrarItem(estoque, &total_itens);
    modificarPrecoItem(estoque, total_itens);
    printf("Preço consultado: %.2f\n", obterPrecoItem(estoque, total_itens));
    printf("Quantidade consultada: %d\n", obterQuantidadeItem(estoque, total_itens));
    realizarVenda(estoque, total_itens);
    ajustarEstoque(estoque, total_itens);
    listarTodosItens(estoque, total_itens);
    listarItensSemEstoque(estoque, total_itens);

    return 0;
}