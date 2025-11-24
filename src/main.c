#include <stdio.h>
#include "carros.h"
#include "clientes.h"
#include "locacoes.h"

void menu() {
    int opcao;
    struct Carro carros[100];  // cria um vetor de carros
    int qtd = 0;               // controla quantos carros já foram cadastrados


    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Listar veiculos\n");
        printf("3 - Alugar veiculo\n");
        printf("4 - Devolver veiculo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCarro(carros, &qtd);
                break;
            case 2:
                listarCarros(carros, qtd);
                break;
            case 3:
                alugarCarro(carros, qtd);
                break;
            case 4:
                devolverCarro(carros, qtd);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}
int main() {
    menu();
    return 0;
}
