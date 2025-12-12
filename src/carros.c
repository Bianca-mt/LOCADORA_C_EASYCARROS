#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carros.h"
#include "locacoes.h"
#include "interface.h"

// Função auxiliar para ser usada pelo módulo de locações
void atualizarStatusCarro(int idCarro, int novoStatus) {
    FILE *arquivo = fopen("carros.bin", "rb+");
    if (arquivo == NULL) return;

    Carro c;
    while (fread(&c, sizeof(Carro), 1, arquivo)) {
        if (c.id == idCarro) {
            c.status = novoStatus;
            fseek(arquivo, -((long)sizeof(Carro)), SEEK_CUR); // Volta o cursor
            fwrite(&c, sizeof(Carro), 1, arquivo);    // Sobrescreve
            break;
        }
    }
    fclose(arquivo);
}

// Função auxiliar para validação da placa
int placaJaCadastrada(char *placa) {
    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) return 0; // Se arquivo não existe, placa não existe

    Carro c;
    int existe = 0;
    while (fread(&c, sizeof(Carro), 1, arquivo)) {
        if (strcmp(c.placa, placa) == 0) {
            existe = 1;
            break;
        }
    }
    fclose(arquivo);
    return existe;
}

// Função que cadastra um novo carro
    
    void cadastrarCarro() {
    Carro novo;
    FILE *arquivo = fopen("carros.bin", "rb");
    
    // --- 1. Descobrir o próximo ID (Auto Incremento) ---
    int ultimoId = 0;
    if (arquivo != NULL) {
        while (fread(&novo, sizeof(Carro), 1, arquivo)) {
            ultimoId = novo.id;
        }
        fclose(arquivo);
    }
    novo.id = ultimoId + 1;
    novo.status = 0; // Sempre é criado como "Disponível"

    int dadosValidos = 0;
    
    do {
        // --- 2. Coleta de Dados (Estilizada) ---
        system("cls");
        char subtitulo_id[50];
        snprintf(subtitulo_id, 49, "  ID do carro: %d", novo.id);
        
        desenharBordaCabecalhoDuplo("  CADASTRO DE NOVO VEÍCULO", subtitulo_id);
        printf("\n");
        
        // Coleta de Marca (scanf para string com espaço)
        printf("\t\t> Marca (ex: Fiat): ");
        fflush(stdin);
        if (scanf("%99[^\n]", novo.marca) != 1) strcpy(novo.marca, ""); // Limita a leitura
        while (getchar() != '\n' && getchar() != EOF); // Limpa buffer
        
        // Coleta de Modelo
        printf("\t\t> Modelo (ex: Uno): ");
        fflush(stdin);
        if (scanf("%99[^\n]", novo.modelo) != 1) strcpy(novo.modelo, "");
        while (getchar() != '\n' && getchar() != EOF); 
        
        // Coleta de Placa
        printf("\t\t> Placa (ex: ABC-1234): ");
        scanf("%s", novo.placa);
        while (getchar() != '\n' && getchar() != EOF); 
        
        // Coleta de Categoria
        printf("\t\t> Categoria (Hatch, Sedan, SUV): ");
        scanf("%s", novo.categoria);
        while (getchar() != '\n' && getchar() != EOF); 
        
        // Coleta de Valor Diária (com validação de tipo)
        printf("\t\t> Valor da Diaria (R$): ");
        // Tenta ler o float. Se falhar, exibe erro estilizado.
        if (scanf("%f", &novo.valor_diaria) != 1) {
             printf("\n");
             setColor(COR_VERMELHO);
             printf("\t\t| ERRO: Valor inválido. Digite apenas números. |\n");
             setColor(COR_PADRAO);
             novo.valor_diaria = 0.0f; // Define 0 para falhar na validação de erro
        }
        while (getchar() != '\n' && getchar() != EOF); 
        
        printf("\n");
        // --- 3. VALIDAÇÃO DE DADOS ---
        int erro = 0;

        printf("\t\t|  Validando dados:              |\n");

        // Validação de Tamanho
        if (strlen(novo.marca) < 3) {
            setColor(COR_VERMELHO);
            printf("\t\t| > vermelho: Marca muito curta.     |\n");
            setColor(COR_PADRAO);
            erro = 1;
        }
        if (strlen(novo.modelo) < 2) {
            setColor(COR_VERMELHO);
            printf("\t\t| > vermelho: Modelo muito curto.    |\n");
            setColor(COR_PADRAO);
            erro = 1;
        }
        // Placa Mercosul/Antiga tem 7 caracteres
        if (strlen(novo.placa) < 7 || strlen(novo.placa) > 8) { 
            setColor(COR_VERMELHO);
            printf("\t\t| > erro: Placa inválida (7-8 chars).|\n");
            setColor(COR_PADRAO);
            erro = 1;
        }
        if (strlen(novo.categoria) < 3) { 
            setColor(COR_VERMELHO);
            printf("\t\t| > erro Categoria muito curta. |\n");
            setColor(COR_PADRAO);
            erro = 1;
        }
        if (novo.valor_diaria <= 0.0f) { 
            setColor(COR_VERMELHO);
            printf("\t\t| > erro: Valor da diária inválido.|\n");
            setColor(COR_PADRAO);
            erro = 1;
        }
        

        // Validação de Duplicidade (Placa Única)
        if (!erro && placaJaCadastrada(novo.placa)) {
            setColor(COR_VERMELHO);
            printf("\t\t| > erro: Placa %s já cadastrada. |\n", novo.placa);
            setColor(COR_PADRAO);
            erro = 1;
        }
        
        // --- 4. SUB-MENU DE DECISÃO (Estilizado) ---
        if (erro) {
            printf("\t\t|--------------------------------|\n");
            printf("\t\t| O cadastro possui erros.       |\n");
            
            // Menu de Seleção por Setas
            const char *opcoes_erro[] = {"Tentar novamente", "Cancelar cadastro"};
            int selecao_erro = 0;
            int tecla;
            ocultarCursor();

            do {
                system("cls"); // Limpa para redesenhar, mantendo os erros visíveis

                // Redesenha cabeçalho e erros
                desenharBordaCabecalhoDuplo(" CADASTRO DE NOVO VEÍCULO", " Erros Encontrados!");
                // AQUI VOCÊ DEVERIA REDESENHAR A LISTA DE ERROS DO PASSO 3

                printf("\t\t|-------------------------------|\n");
                printf("\t\t| Selecione uma opção:          |\n");
                printf("\t\t|                               |\n");

                int i ;
				for ( i = 0; i < 2; i++) {
                    printf("\t\t|  ");
                    if (i == selecao_erro) {
                        setColor(COR_DESTAQUE);
                        printf("> %-27s", opcoes_erro[i]);
                        setColor(COR_PADRAO);
                    } else {
                        printf("  %-27s", opcoes_erro[i]);
                    }
                    printf("|\n");
                }
                printf("\t\t|                               |\n");
                desenharBordaRodape();
                
                tecla = _getch();
                if (tecla == 224) { 
                    tecla = _getch();
                    if (tecla == 72) { selecao_erro = (selecao_erro == 0) ? 1 : 0; } // Seta Cima
                    if (tecla == 80) { selecao_erro = (selecao_erro == 1) ? 0 : 1; } // Seta Baixo
                }
                
            } while (tecla != 13); // Repete até ENTER

            if (selecao_erro == 1) { 
                system("cls");
                desenharBordaCabecalhoDuplo("     CADASTRO CANCELADO", "    Operação Descartada");
                printf("\t\t|                               |\n");
                printf("\t\t|      Cadastro cancelado.      |\n");
                printf("\t\t|                               |\n");
                desenharBordaRodape();
                _getch();
                return; // Sai da função sem salvar nada
            }
        } else {
            dadosValidos = 1; // Sai do loop principal e salva
        }

    } while (!dadosValidos);    

    // --- 5. Salva e Confirmação (Estilizada) ---
    arquivo = fopen("carros.bin", "ab");
    
    system("cls");
    desenharBordaCabecalhoDuplo(" REVISÃO E SALVAMENTO", " Detalhes do Novo Veículo");
    
    printf("\t\t|  ID: %-25d |\n", novo.id);
    printf("\t\t|  Placa: %-22s |\n", novo.placa);
    printf("\t\t|  Modelo: %s %-17s |\n", novo.marca, novo.modelo);
    printf("\t\t|  Diária: R$ %-18.2f |\n", novo.valor_diaria);
    printf("\t\t|--------------------------------|\n");
    
    if (arquivo != NULL) {
        fwrite(&novo, sizeof(Carro), 1, arquivo);
        fclose(arquivo);
        printf("\t\t|  ");
        setColor(COR_DESTAQUE);
        printf(" Carro cadastrado!  ");
        setColor(COR_PADRAO);
        printf(" |\n");
    } else {
        printf("\t\t|  ");
        setColor(COR_VERMELHO);
        printf(" ERRO: Falha ao salvar no arquivo! ");
        setColor(COR_PADRAO);
        printf(" |\n");
    }
    
    desenharBordaRodape();
    printf("\n\t\tPressione qualquer tecla para continuar...");
    _getch(); // Substitui system("pause")
}
// Função que lista os carros sem ou com filtros
void listarCarros(int filtroStatus) {
    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum carro cadastrado.\n");
        system("pause");
        return;
    }

    Carro c;
    int encontrou = 0;

    system("cls");
    printf("=== FROTA DE CARROS ===\n");
    printf("%-5s | %-10s | %-15s | %-10s | %-10s | %-10s\n", 
           "ID", "PLACA", "MODELO", "CATEGORIA", "DIÁRIA", "STATUS");
    printf("-------------------------------------------------------------------------\n");

	while (fread(&c, sizeof(Carro), 1, arquivo)) {
	    // Se filtro for -1, mostra tudo. Senão, só mostra se bater o status.
	    if (filtroStatus == -1 || c.status == filtroStatus) {
	        
	        char descStatus[15];
	        
	        // Definição da cor e do texto do status
	        if (c.status == 0){
	            strcpy(descStatus, "DISPONÍVEL");
	            setColor(COR_VERDE);
	        }
	        else if (c.status == 1) {
	            strcpy(descStatus, "ALUGADO");
	            setColor(COR_AZUL);
	        }
	        else if (c.status == 2) {
	            strcpy(descStatus, "EM MANUTENCÃO");
	            setColor(COR_VERMELHO);
	        }
	        
	        // Imprime as colunas iniciais
	        printf("%-5d | %-10s | %-15s | %-10s | R$ %-7.2f | ", 
	               c.id, c.placa, c.modelo, c.categoria, c.valor_diaria);
	        
	        // Imprime apenas o STATUS com a cor definida acima
	        printf("%s", descStatus);
	        setColor(COR_PADRAO);
	        
	        printf("\n"); 
	        
	        encontrou = 1;
	    }
	}
    printf("-------------------------------------------------------------------------\n");
    fclose(arquivo);
    
    if (!encontrou) printf("Nenhum carro encontrado para este filtro.\n");
    system("pause");
}

// Função que busca um carro no arquivo pela placa
int buscarCarroPorPlaca(char *placaBusca, Carro *carroEncontrado) {
    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) return 0;

    Carro c;
    while (fread(&c, sizeof(Carro), 1, arquivo)) {
        if (strcmp(c.placa, placaBusca) == 0) {
            *carroEncontrado = c;
            fclose(arquivo);
            return 1; // Achou
        }
    }
    fclose(arquivo);
    return 0; // Não achou
}

// Função que gerencia o estado de manutenção de um carro
void menuGestaoCarros() {
    // 1. Definição das Opções
    const char *opcoes[] = {
        "Cadastrar Novo Carro",       // case 1
        "Listar Todos Carros",        // case 2 (status -1)
        "Listar Disponíveis",         // case 3 (status 0)
        "Listar Em Locação",          // (status 1) - Adicionado para cobrir todos os status
        "Listar Em Manutenção",       // case 4 (status 2)
        "Controle de Manutenção",     // case 5
        "Remover Carro",              // case 6
        "Voltar"                      // case 0 / return
    };
    int totalOpcoes = 8;
    int linhaSelecionada = 0;
    int tecla;

    // Assumindo que ocultarCursor() está disponível
    ocultarCursor(); 

    do {
        // 2. Renderização Visual
        system("cls");
        
        // Cabeçalho estilizado (Usando o padrão do menuAdministrativo)
        desenharBordaCabecalhoDuplo("  GESTÃO DE FROTA DE CARROS", "    Selecione uma operação");

        printf("\t\t|                               |\n");

        // Loop para desenhar as opções e aplicar o destaque
        int i;
        for (i = 0; i < totalOpcoes; i++) {
            printf("\t\t|  ");

            if (i == linhaSelecionada) {
                // Opção Selecionada: Cor de destaque e indicador ">"
                setColor(COR_DESTAQUE);
                printf("> %-27s", opcoes[i]);
                setColor(COR_PADRAO);
            } else {
                // Opções normais
                printf("  %-27s", opcoes[i]);
            }

            printf("|\n");
        }

        printf("\t\t|                               |\n");
        desenharBordaRodape();

        // 3. Captura e Processamento de Teclas
        tecla = _getch();

        if (tecla == 224) {
            // Tecla especial (Setas)
            tecla = _getch();
            if (tecla == 72) { // Seta Cima
                linhaSelecionada--;
                if (linhaSelecionada < 0) linhaSelecionada = totalOpcoes - 1; // Loop para o final
            }
            if (tecla == 80) { // Seta Baixo
                linhaSelecionada++;
                if (linhaSelecionada >= totalOpcoes) linhaSelecionada = 0; // Loop para o início
            }
        }
        else if (tecla == 13) {
            // Tecla ENTER -> Executa a função
            switch(linhaSelecionada) {
                case 0: cadastrarCarro(); break;
                case 1: listarCarros(-1); break; // Todos
                case 2: listarCarros(0); break;  // Disponíveis
                case 3: listarCarros(1); break;  // Locados (Status 1)
                case 4: listarCarros(2); break;  // Em Manutenção
                case 5: gerenciarManutencao(); break;
                case 6: removerCarro(); break;
                case 7: return; // Voltar / Sair da função
            }
        }

    } while (1); // O loop só é quebrado pelo 'return' no caso "Voltar"
}

// Função que monta o menu de gestão de carros
void gerenciarManutencao() {
    char placa[15];
    Carro c;
    FILE *arquivo;

    arquivo = fopen("carros.bin", "rb+");
    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo ou nenhum carro cadastrado.\n");
        system("pause");
        return;
    }
    
    system("cls");
    printf("=== CONTROLE DE MANUTENÇÃO ===\n");
    printf("Digite a placa do carro: ");
    scanf("%s", placa);

    int encontrado = 0;
    while (fread(&c, sizeof(Carro), 1, arquivo)) {
        if (strcmp(c.placa, placa) == 0) {
            encontrado = 1;
            
            printf("\nCarro encontrado: %s %s\n", c.marca, c.modelo);
            printf("Status atual: %d ", c.status);
            if (c.status == 0) printf("(DISPONÍVEL)\n");
            else if (c.status == 1) printf("(ALUGADO)\n");
            else if (c.status == 2) printf("(EM MANUTENÇÃO)\n");

            // Lógica da troca
            if (c.status == 1) {
                printf("\nERRO: Carro está alugado.\nFaça a devolução antes de enviar para oficina.\n");
            } 
            else if (c.status == 0) {
                char resp;
                printf("\nEnviar para manutenção? (S/N): ");
                scanf(" %c", &resp);
                if (resp == 'S' || resp == 's') {
                    c.status = 2; // Muda para Manutenção
                    
                    // Voltar o cursor do arquivo para o inicio desse registro
                    fseek(arquivo, -((long)sizeof(Carro)), SEEK_CUR);
                    // Sobrescreve o registro
                    fwrite(&c, sizeof(Carro), 1, arquivo);
                    printf("Status alterado para EM MANUTENÇÃO.\n");
                }
            }
            else if (c.status == 2) {
                char resp;
                printf("\nRetirar da manutenção? (S/N): ");
                scanf(" %c", &resp);
                if (resp == 'S' || resp == 's') {
                    c.status = 0; // Volta para Disponível
                    fseek(arquivo, -((long)sizeof(Carro)), SEEK_CUR);
                    fwrite(&c, sizeof(Carro), 1, arquivo);
                    printf("Status alterado para DISPONÍVEL.\n");
                }
            }
            break;
        }
    }

    if (!encontrado) printf("\nPlaca não encontrada.\n");
    fclose(arquivo);
    system("pause");
}

// Função que remove logicamente um carro
void removerCarro() {
    FILE *arquivo = fopen("carros.bin", "rb");
    FILE *temp = fopen("carros.tmp", "wb");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos de carros.\n");
        return;
    }

    int idAlvo;
    int encontrou = 0;
    int excluiu = 0;
    Carro c;

    // Listar carros antes para facilitar a escolha
    listarCarros(-1); 

    printf("\n=== REMOÇÃO DE UM CARRO ===\n");
    printf("Digite o ID do carro que deseja remover\n(Digite 0 para cancelar): ");
    scanf("%d", &idAlvo);
    fflush(stdin);

    if (idAlvo == 0) {
        fclose(arquivo);
        fclose(temp);
        remove("carros.tmp");
        return;
    }

    while (fread(&c, sizeof(Carro), 1, arquivo)) {
        if (c.id == idAlvo) {
            encontrou = 1;

            // VALIDAÇÃO
            if (c.status == 1) {
                // Se estiver alugado, NÃO removemos e mantemos ele
                printf("\nERRO: O carro de placa %s está alugado.\n", c.placa);
                printf("Você deve dar baixa na locação antes de remover o carro do sistema.\n");
                system("pause");
                fwrite(&c, sizeof(Carro), 1, temp); // Mantém o carro
            } 
            else {
                // Se estiver livre ou em manutenção, podemos remover
                printf("\nCarro encontrado: %s %s (Placa: %s)\n", c.marca, c.modelo, c.placa);
                printf("Tem certeza que deseja excluir permanentemente? (S/N): ");
                char confirmacao;
                scanf(" %c", &confirmacao);
                fflush(stdin);

                if (confirmacao == 'S' || confirmacao == 's') {
                    excluiu = 1;
                    printf("Carro removido com sucesso.\n");
                } else {
                    // Usuário desistiu, mantemos o carro
                    fwrite(&c, sizeof(Carro), 1, temp);
                }
            }
        } else {
            // Copia todos os outros carros que não são o alvo
            fwrite(&c, sizeof(Carro), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Finalização
    if (encontrou) {
        if (excluiu) {
            remove("carros.bin");
            rename("carros.tmp", "carros.bin");
        } else {
            remove("carros.tmp");
        }
    } else {
        printf("\nID %d não encontrado.\n", idAlvo);
        remove("carros.tmp");
    }
    system("pause");
}
