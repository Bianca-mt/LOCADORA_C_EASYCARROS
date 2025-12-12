#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "interface.h"

// Função auxiliar para verificar duplicidade de cliente
int cpfJaCadastrado(char *cpf) {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) return 0;

    Cliente c;
    int existe = 0;
    while (fread(&c, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(c.cpf, cpf) == 0) {
            existe = 1;
            break;
        }
    }
    fclose(arquivo);
    return existe;
}

// Função para cadastrar um novo cliente
void cadastrarCliente() {
    Cliente novo;
    int dadosValidos = 0;
    int opcao;

    // Descobrir o próximo ID (Auto Incremento)
    FILE *arquivo = fopen("clientes.bin", "rb");
    int ultimoId = 0;
    if (arquivo != NULL) {
        while (fread(&novo, sizeof(Cliente), 1, arquivo)) {
            ultimoId = novo.id;
        }
        fclose(arquivo);
    }
    novo.id = ultimoId + 1;

    // Loop de Coleta e Validação
    do {
        system("cls");
        printf("=== CADASTRO DE NOVO CLIENTE ===\n");
        printf("ID de Cliente: %d\n", novo.id);

        printf("Nome Completo: ");
        fflush(stdin);
        scanf("%[^\n]s", novo.nome);
        getchar();

        printf("CPF: ");
        fflush(stdin);
        scanf("%s", novo.cpf);
        getchar();

        printf("Número da CNH: ");
        fflush(stdin);
        scanf("%s", novo.cnh);
        getchar();

        printf("Telefone/Celular: ");
        fflush(stdin);
        scanf("%[^\n]s", novo.telefone);
        getchar();

        printf("Endereço: ");
        fflush(stdin);
        scanf("%[^\n]s", novo.endereco);
        getchar();

        // --- VALIDAÇÃO ---
        int erro = 0;

		// Verifica tamanho
        if (strlen(novo.nome) < 3) {
            printf("\nErro: Nome muito curto. (min. 3 letras)");
            erro = 1;
        }
        if (strlen(novo.cpf) < 3) {
            printf("\nErro: CPF inválido (min. 3 números).");
            erro = 1;
        }
        if (strlen(novo.cnh) < 3) {
            printf("\nErro: CNH inválida (min. 3 números).");
            erro = 1;
        }

        // Verifica duplicidade do CPF
        if (!erro && cpfJaCadastrado(novo.cpf)) {
            printf("\nErro: Este CPF já possui cadastro no sistema.");
            erro = 1;
        }

        // --- DECISÃO ---
        if (erro) {
            printf("\n\nO cadastro possui erros.\n");
            printf("1. Tentar novamente\n");
            printf("2. Cancelar\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            fflush(stdin);
            
            if (opcao == 2) return;
        } else {
            dadosValidos = 1;
        }

    } while (!dadosValidos);

    // Salvo no arquivo
    arquivo = fopen("clientes.bin", "ab");
    if (arquivo != NULL) {
        fwrite(&novo, sizeof(Cliente), 1, arquivo);
        fclose(arquivo);
        printf("\nCliente cadastrado com sucesso.\n");
    } else {
        printf("Erro ao gravar arquivo.\n");
    }
    system("pause");
}

// Função para listar todos os clientes cadastrados
void listarClientes() {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum cliente cadastrado.\n");
        system("pause");
        return;
    }

    Cliente c;
    system("cls");
    printf("=== LISTA DE CLIENTES ===\n");
    printf("%-4s | %-20s | %-14s | %-12s | %-15s\n", "ID", "NOME", "CPF", "CNH", "TELEFONE");
    printf("------------------------------------------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, arquivo)) {
        printf("%-4d | %-20.20s | %-14s | %-12s | %-15s\n", 
               c.id, c.nome, c.cpf, c.cnh, c.telefone);
    }
    printf("------------------------------------------------------------------------------\n");
    fclose(arquivo);
    system("pause");
}

// Função que exclui fisicamente um cliente do arquivo
void removerCliente() {
    FILE *arquivo = fopen("clientes.bin", "rb");
    FILE *temp = fopen("clientes.tmp", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    int idAlvo;
    int encontrou = 0;
    char confirmacao;
    Cliente c;

	// Mostra a lista antes para facilitar a escolha
    listarClientes(); 
    
    printf("\n=== REMOÇÃO DE UM CLIENTE ===\n");
    printf("Digite o ID do cliente para remover\n(Digite 0 para cancelar): ");
    scanf("%d", &idAlvo);
    fflush(stdin);

    if (idAlvo == 0) {
        fclose(arquivo); fclose(temp); remove("clientes.tmp"); return;
    }

    while (fread(&c, sizeof(Cliente), 1, arquivo)) {
        if (c.id == idAlvo) {
            encontrou = 1;
            printf("\nCliente: %s (CPF: %s)\n", c.nome, c.cpf);
            
            // PARA O FUTURO -> Verificar se cliente tem locação ativa em 'locacoes.bin'
            // Se tiver, impedir a exclusão. Por enquanto, permitimos.
            
            printf("Tem certeza que deseja excluir esse cliente? (S/N): ");
            scanf(" %c", &confirmacao);
            fflush(stdin);

            if (confirmacao == 'S' || confirmacao == 's') {
                printf("Cliente removido com sucesso.\n");
            } else {
                fwrite(&c, sizeof(Cliente), 1, temp); // Mantém o cliente
            }
        } else {
            fwrite(&c, sizeof(Cliente), 1, temp); // Mantém os outros
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrou) {
        remove("clientes.bin");
        rename("clientes.tmp", "clientes.bin");
    } else {
        printf("ID não encontrado.\n");
        remove("clientes.tmp");
    }
    system("pause");
}

// Função para buscar dados do cliente por CPF
int buscarClientePorCpf(char *cpfBusca, Cliente *clienteEncontrado) {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) return 0;

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(c.cpf, cpfBusca) == 0) {
            *clienteEncontrado = c; // Retorna os dados por ponteiro
            fclose(arquivo);
            return 1; // Achou
        }
    }
    fclose(arquivo);
    return 0; // Não achou
}

// Função que chama o menu de gestão de clientes
void menuGestaoClientes() {
    
    const char *opcoes[] = {
        "Cadastrar Cliente",
        "Listar Clientes",
        "Remover Cliente",
        "Voltar"
    };
    int totalOpcoes = 4;
    int linhaSelecionada = 0;
    int tecla;

    ocultarCursor(); 

    do {
        // 2. Renderização Visual
        system("cls");
        
        // Cabeçalho estilizado (Mantendo o padrão do menu administrativo)
        desenharBordaCabecalhoDuplo("     GESTÃO DE CLIENTES", "   Selecione uma operação");

        printf("\t\t|                               |\n");

        // Loop para desenhar as opções
        int i;
        for (i = 0; i < totalOpcoes; i++) {
            printf("\t\t|  "); // Margem esquerda dentro da caixa

            if (i == linhaSelecionada) {
                // Opção Selecionada: Muda cor e adiciona indicador ">"
                setColor(COR_DESTAQUE);
                printf("> %-27s", opcoes[i]); 
                setColor(COR_PADRAO);
            } else {
                // Opção Normal
                printf("  %-27s", opcoes[i]);
            }

            printf("|\n"); 
        }

        printf("\t\t|                               |\n");
        desenharBordaRodape();

        // 3. Captura e Processamento de Teclas
        tecla = _getch(); // Captura sem precisar de Enter

        if (tecla == 224) { 
            // Teclas de navegação (Setas retornam dois códigos: 224 seguido da direção)
            tecla = _getch();
            
            if (tecla == 72) { 
                linhaSelecionada--;
                if (linhaSelecionada < 0) linhaSelecionada = totalOpcoes - 1; 
            }
            if (tecla == 80) { 
                linhaSelecionada++;
                if (linhaSelecionada >= totalOpcoes) linhaSelecionada = 0; 
            }
        }
        else if (tecla == 13) { 
            // Tecla ENTER
            switch(linhaSelecionada) {
                case 0: // Cadastrar
                    cadastrarCliente();
                    // Opcional: system("pause"); se a função não tiver pausa interna
                    break;
                case 1: // Listar
                    listarClientes();
                    // system("pause"); // Geralmente listagens precisam de pausa aqui
                    break;
                case 2: // Remover
                    removerCliente();
                    break;
                case 3: // Voltar
                    return; // Sai da função e volta para o menu anterior
            }
        }

    } while (1);
}
