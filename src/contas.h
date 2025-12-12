#ifndef CONTAS_H
#define CONTAS_H

// Definição da estrutura de Usuário
typedef struct {
    int id;
    char nome[50];
    char login[50];
    char senha[50];
    int nivel; //1 = Funcionario, 2 = Gerente, 3 = Administrador
} Usuario;


// Protótipos das funções
void inicializarSistema();
int realizarLogin(Usuario *usuarioLogado);

void cadastrarUsuario(Usuario usuarioLogado);
void listarUsuarios();
void removerUsuario(Usuario usuarioLogado);
void menuGestaoUsuarios(Usuario usuarioLogado);

#endif
