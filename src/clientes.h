#ifndef CLIENTES_H
#define CLIENTES_H

struct Cliente {
    char nome[50];
    char cpf[15];
    char telefone[20];
};

void cadastrarCliente(struct Cliente clientes[], int *qtd);
void listarClientes(struct Cliente clientes[], int qtd);

#endif
