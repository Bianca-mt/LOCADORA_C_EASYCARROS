#ifndef CLIENTES_H
#define CLIENTES_H

// Definição da estrutura de Clientes
typedef struct {
    int id;
    char nome[100];
    char cpf[15];      
    char cnh[15];      
    char telefone[20];
    char endereco[100];
} Cliente;


// Protótipos das funções
void menuGestaoClientes();
void cadastrarCliente();
void listarClientes();
void removerCliente();
int buscarClientePorCpf(char *cpfBusca, Cliente *clienteEncontrado);
int cpfJaCadastrado(char *cpf);

#endif
