#include <stdio.h>
#include <string.h>
#include "carros.h"   // pra reconhecer struct Carro
#include "locacoes.h" // declarações de função

void devolverCarro(struct Carro carros[], int qtd) {
    char placa[10];

    printf("\nDigite a placa do veiculo para devolver: ");
    scanf(" %[^\n]", placa);

    for (int i = 0; i < qtd; i++) {

        if (strcmp(carros[i].placa, placa) == 0) {

            if (carros[i].disponivel == 1) {
                printf("Este veiculo ja esta disponivel.\n");
                return;
            }

            carros[i].disponivel = 1;
            printf("Devolucao registrada com sucesso!\n");
            return;
        }
    }

    printf("Placa nao encontrada!\n");
}

void alugarCarro(struct Carro carros[], int qtd) {
    char placa[10];
    int dias;

    printf("\nDigite a placa do carro para alugar: ");
    scanf(" %[^\n]", placa);

    for (int i = 0; i < qtd; i++) {
        if (strcmp(carros[i].placa, placa) == 0) {

            if (carros[i].disponivel == 0) {
                printf("Carro ja alugado!\n");
                return;
            }

            printf("Quantos dias de aluguel? ");
            scanf("%d", &dias);

            float total = carros[i].diaria * dias;
            carros[i].disponivel = 0;

            printf("Aluguel concluido. Total: R$%.2f\n", total);
            return;
        }
    }

    printf("Placa nao encontrada!\n");
}
