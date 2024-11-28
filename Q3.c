#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int idConta;
    char clienteNome[50];
    char clienteCpf[15];
    char clienteTelefone[20];
    float contaSaldo;
} Conta;

int encontrarConta(Conta contas[], int totalContas, int idConta) {
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].idConta == idConta) {
            return i;
        }
    }
    return (totalContas == 0) ? -1 : -2;
}

void adicionarConta(Conta contas[], int *totalContas) {
    if (*totalContas >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }
    
    int id;
    printf("Digite o número da nova conta: ");
    scanf("%d", &id);
    
    if (encontrarConta(contas, *totalContas, id) >= 0) {
        printf("Conta com número repetido. Não é possível cadastrar.\n");
        return;
    }

    contas[*totalContas].idConta = id;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", contas[*totalContas].clienteNome);
    printf("Digite o CPF do cliente: ");
    scanf("%s", contas[*totalContas].clienteCpf);
    printf("Digite o telefone de contato: ");
    scanf("%s", contas[*totalContas].clienteTelefone);
    contas[*totalContas].contaSaldo = 0.0;
    (*totalContas)++;
}

void verificarSaldo(Conta contas[], int totalContas) {
    int id;
    printf("Digite o número da conta para consultar o saldo: ");
    scanf("%d", &id);
    
    int indice = encontrarConta(contas, totalContas, id);
    if (indice >= 0) {
        printf("Saldo da conta %d: %.2f\n", id, contas[indice].contaSaldo);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void realizarDeposito(Conta contas[], int totalContas) {
    int id;
    float montante;
    printf("Digite o número da conta para depósito: ");
    scanf("%d", &id);
    
    int indice = encontrarConta(contas, totalContas, id);
    if (indice >= 0) {
        printf("Digite o valor a depositar: ");
        scanf("%f", &montante);
        if (montante > 0) {
            contas[indice].contaSaldo += montante;
            printf("Depósito realizado com sucesso. Novo saldo: %.2f\n", contas[indice].contaSaldo);
        } else {
            printf("Valor inválido.\n");
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void realizarSaque(Conta contas[], int totalContas) {
    int id;
    float montante;
    printf("Digite o número da conta para saque: ");
    scanf("%d", &id);
    
    int indice = encontrarConta(contas, totalContas, id);
    if (indice >= 0) {
        printf("Digite o valor a sacar: ");
        scanf("%f", &montante);
        if (montante > 0 && montante <= contas[indice].contaSaldo) {
            contas[indice].contaSaldo -= montante;
            printf("Saque realizado com sucesso. Novo saldo: %.2f\n", contas[indice].contaSaldo);
        } else {
            printf("Saldo insuficiente ou valor inválido.\n");
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void listarInformacoesContas(Conta contas[], int totalContas) {
    printf("Informações das contas cadastradas:\n");
    for (int i = 0; i < totalContas; i++) {
        printf("Conta: %d, Nome: %s, Telefone: %s\n", 
               contas[i].idConta, contas[i].clienteNome, contas[i].clienteTelefone);
    }
}

int main() {
    Conta contasCorrente[MAX_CONTAS];
    Conta contasPoupanca[MAX_CONTAS];
    int totalCorrente = 0, totalPoupanca = 0;

    adicionarConta(contasCorrente, &totalCorrente);
    verificarSaldo(contasCorrente, totalCorrente);
    realizarDeposito(contasCorrente, totalCorrente);
    realizarSaque(contasCorrente, totalCorrente);
    listarInformacoesContas(contasCorrente, totalCorrente);
    
    return 0;
}