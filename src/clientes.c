#include <stdio.h>
#include "clientes.h"

void cadastrarCliente(struct Cliente clientes[], int *qtd) {
    printf("\n--- Cadastro de Cliente ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", clientes[*qtd].nome);

    printf("CPF: ");
    scanf(" %[^\n]", clientes[*qtd].cpf);

    printf("Telefone: ");
    scanf(" %[^\n]", clientes[*qtd].telefone);

    (*qtd)++;

    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes(struct Cliente clientes[], int qtd) {
    if (qtd == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | CPF: %s | Telefone: %s\n",
               i + 1,
               clientes[i].nome,
               clientes[i].cpf,
               clientes[i].telefone);
    }
}
