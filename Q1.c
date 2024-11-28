#include <stdio.h>
#include <string.h>

#define ESTADOS 26

typedef struct {
    char nome[30];
    int veiculos;
    int acidentes;
} Estado;

void obterDados(Estado estados[]) {
    for (int i = 0; i < ESTADOS; i++) {
        printf("Digite o nome do estado %d: ", i + 1);
        scanf(" %[^\n]s", estados[i].nome);
        printf("Digite o número de veículos no estado %s: ", estados[i].nome);
        scanf("%d", &estados[i].veiculos);
        printf("Digite o número de acidentes de trânsito em %s: ", estados[i].nome);
        scanf("%d", &estados[i].acidentes);
    }
}

void encontrarAcidentes(Estado estados[], char maior[], char menor[], int *max, int *min) {
    *max = estados[0].acidentes;
    *min = estados[0].acidentes;
    int indiceMax = 0, indiceMin = 0;

    for (int i = 1; i < ESTADOS; i++) {
        if (estados[i].acidentes > *max) {
            *max = estados[i].acidentes;
            indiceMax = i;
        }
        if (estados[i].acidentes < *min) {
            *min = estados[i].acidentes;
            indiceMin = i;
        }
    }
    strcpy(maior, estados[indiceMax].nome);
    strcpy(menor, estados[indiceMin].nome);
}

float calcularPercentual(Estado estado) {
    return (estado.veiculos != 0) ? (float)estado.acidentes / estado.veiculos * 100.0f : 0.0f;
}

float calcularMedia(Estado estados[]) {
    int totalAcidentes = 0;

    for (int i = 0; i < ESTADOS; i++) {
        totalAcidentes += estados[i].acidentes;
    }

    return (float)totalAcidentes / ESTADOS;
}

void mostrarEstadosAcimaMedia(Estado estados[], float media) {
    printf("Estados com acidentes acima da média nacional:\n");
    for (int i = 0; i < ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s\n", estados[i].nome);
        }
    }
}

int main() {
    Estado estados[ESTADOS];
    char maior[30], menor[30];
    int maxAcidentes, minAcidentes;
    float mediaAcidentes;

    obterDados(estados);
    encontrarAcidentes(estados, maior, menor, &maxAcidentes, &minAcidentes);
    printf("Maior número de acidentes: %d, Estado: %s\n", maxAcidentes, maior);
    printf("Menor número de acidentes: %d, Estado: %s\n", minAcidentes, menor);
    printf("Percentual de acidentes no estado %s: %.2f%%\n", estados[0].nome, calcularPercentual(estados[0]));
    mediaAcidentes = calcularMedia(estados);
    printf("Média de acidentes no país: %.2f\n", mediaAcidentes);
    mostrarEstadosAcimaMedia(estados, mediaAcidentes);

    return 0;
}

