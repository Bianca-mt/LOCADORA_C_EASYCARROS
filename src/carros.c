#include <stdio.h>
#include "carros.h"

void cadastrarCarro(struct Carro carros[], int *qtd) {
    printf("\n--- Cadastro de Veiculo ---\n");

    printf("Modelo: ");
    scanf(" %[^\n]", carros[*qtd].modelo);

    printf("Placa: ");
    scanf(" %[^\n]", carros[*qtd].placa);

    printf("Valor da diaria: ");
    scanf("%f", &carros[*qtd].diaria);

    carros[*qtd].disponivel = 1;  // padrão: disponível
    (*qtd)++; // soma +1 no total de carros

    printf("Veiculo cadastrado com sucesso!\n");
}

void listarCarros(struct Carro carros[], int qtd) {
    if (qtd == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Veiculos ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | Placa: %s | Diaria: R$%.2f | %s\n",
               i + 1,
               carros[i].modelo,
               carros[i].placa,
               carros[i].diaria,
               carros[i].disponivel ? "Disponivel" : "Alugado");
    }
}
