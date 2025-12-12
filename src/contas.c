#include <stdio.h>
#include <string.h>
#include "contas.h"
#include "interface.h"

// Função auxiliar para ler senha trocando caracteres por asteriscos
void lerSenhaMascarada(char *senha, int tamanhoMax) {
    int i = 0;
    char c;

    while (1) {
        c = _getch(); // Lê o caractere sem mostrar na tela

        if (c == 13) { // 13 é o código ASCII do ENTER
            break;
        } 
        else if (c == 8) { // 8 é o código ASCII do BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b"); // Apaga o caractere visualmente: volta, espaço, volta
            }
        } 
        else if (i < tamanhoMax - 1) { // Se ainda cabe caracteres
            senha[i] = c;
            i++;
            printf("*"); // Imprime o asterisco no lugar da letra
        }
    }
    senha[i] = '\0'; // Finaliza a string corretamente
    printf("\n"); // Pula para a linha de baixo ao final
}


// Função que verifica se existe o arquivo de usuários e cria o usuário administrador
void inicializarSistema() {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    
    // Tenta ler o primeiro registro para ver se o arquivo existe
    Usuario teste;
    int existe = 0;
    
    if (arquivo != NULL) {
        if (fread(&teste, sizeof(Usuario), 1, arquivo) == 1) {
            existe = 1;
        }
        fclose(arquivo);
    }

    // Se não existe ou está vazio, cria o usuário administrador
    if (!existe) {
        printf("--- SISTEMA INICIADO PELA PRIMEIRA VEZ ---\n");
        
        Usuario admin;
        admin.id = 1;
        strcpy(admin.nome, "Administrador");
        strcpy(admin.login, "admin"); // Usuário padrão
        strcpy(admin.senha, "admin"); // Senha padrão
        admin.nivel = 3;

		// Cria ou sobrescreve o usuário
        arquivo = fopen("usuarios.bin", "wb"); 
        if (arquivo != NULL) {
            fwrite(&admin, sizeof(Usuario), 1, arquivo);
            fclose(arquivo);
            printf("Usuário administrador criado com sucesso.\n");
            printf("------------------------------------------\n");
            system("pause");
        } else {
            printf("ERRO: Não foi possível criar o arquivo de usuários.\n");
        }
    }
}

// Função que coleta credenciais e verifica o login
int realizarLogin(Usuario *usuarioLogado) {
    char loginInput[50];
    char senhaInput[50];
    Usuario u;
    int encontrado = 0;
    
    // Monta o cabeçalho personalizado
     system("cls"); 
    desenharBordaCabecalho("      LOGIN DE USUÁRIOS");
    
    // Monta o corpo do formulário vázio
    printf("\t\t|                               |\n"); 
    setColor(COR_AZUL);
    printf("\t\t|  Usuário:                     |\n"); 
    setColor(COR_PADRAO);
    printf("\t\t|                               |\n"); 
    setColor(COR_AZUL);
    printf("\t\t|  Senha:                       |\n");
    setColor(COR_PADRAO);
    printf("\t\t|                               |\n"); 
    
    // Monta o rodapé
    desenharBordaRodapeLogin(); 


    // Coleta as credenciais
    // Usuário
    gotoxy(28, 6); // Posiciona o cursor para digitar o login
    mostrarCursor();
    fgets(loginInput, 50, stdin);
    loginInput[strcspn(loginInput, "\n")] = 0; 

    // Senha
    gotoxy(26, 8); // Posiciona o cursor para digitar a senha
    lerSenhaMascarada(senhaInput, 50); 

    ocultarCursor();


    // Abre e busca no arquivo
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        gotoxy(16, 11);
        setColor(COR_VERMELHO);
        printf("|  ERRO: Arquivo de usuários não encontrado! |\n");
        gotoxy(16, 12);
        printf("|  Clique uma tecla para voltar |");
        setColor(COR_PADRAO);
        _getch();
        return 0;
    }

    // Busca sequencial no arquivo de usuários
    while (fread(&u, sizeof(Usuario), 1, arquivo)) {
        if (strcmp(loginInput, u.login) == 0 && strcmp(senhaInput, u.senha) == 0) {
            // Copia os dados do arquivo para a variável de retorno
            *usuarioLogado = u;
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);

    // Resultado do login

    if (encontrado) {
        return 1;  // Sucesso
    } else {
        gotoxy(16, 11);
        setColor(COR_VERMELHO);
        printf("|  Usuário ou senha inválidos!  |\n");
        gotoxy(16, 12);
        printf("|  Clique uma tecla para voltar |");
        setColor(COR_PADRAO);
        _getch();
        return 0; // Falha
    }
}

// Função que lista todos os usuários
void listarUsuarios() {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo ou nenhum usuário cadastrado.\n");
        return;
    }

    Usuario u;
    system("cls");
    printf("=== LISTA DE USUÁRIOS ===\n");
    printf("%-5s | %-20s | %-15s | %-10s\n", "ID", "NOME", "LOGIN", "CARGO");
    printf("------------------------------------------------------------\n");

    while (fread(&u, sizeof(Usuario), 1, arquivo)) {
        char cargo[20];
        if (u.nivel == 1) strcpy(cargo, "Funcionário");
        else if (u.nivel == 2) strcpy(cargo, "Gerente");
        else if (u.nivel == 3) strcpy(cargo, "Adminstrador");
        
        printf("%-5d | %-20s | %-15s | %-10s\n", u.id, u.nome, u.login, cargo);
    }
    printf("------------------------------------------------------------\n");
    fclose(arquivo);
}

// Função que cadastra um usuário novo
void cadastrarUsuario(Usuario usuarioLogado) {

    Usuario novo;
    FILE *arquivo = fopen("usuarios.bin", "rb");
    
    // --- 1. Descobrir o próximo ID (Auto Incremento) ---
    int ultimoId = 0;
    if (arquivo != NULL) {
        while (fread(&novo, sizeof(Usuario), 1, arquivo)) {
            ultimoId = novo.id; 
        }
        fclose(arquivo);
    }
    novo.id = ultimoId + 1;
    
    // Preparação do Subtítulo para o cabeçalho
    char subtitulo[50];
    snprintf(subtitulo, 49, " ID do cliente: %d", novo.id);
    
    // --- 2. Coleta de Dados (Estilizada) ---
    system("cls");
    desenharBordaCabecalhoDuplo(" CADASTRO DE NOVO USUÁRIO", subtitulo);
    printf("\n");
    
    // Coleta de Nome
    printf("\t\t> Nome completo: ");
    fflush(stdin);
    // Usando fgets para ler o nome com espaços de forma mais segura
    if (fgets(novo.nome, sizeof(novo.nome), stdin) != NULL) {
        novo.nome[strcspn(novo.nome, "\n")] = 0; // Remove o '\n'
    } else {
        strcpy(novo.nome, "N/A");
    }

    // Coleta de Login
    printf("\t\t> Nome de usuário/email: ");
    scanf("%s", novo.login);
    
    // Coleta de Senha
    printf("\t\t> Senha: ");
    scanf("%s", novo.senha);
    
    // Limpar o buffer (necessário após scanf)
    while (getchar() != '\n' && getchar() != EOF); 

    // --- 3. Seleção de Cargo/Permissões (Menu de Seleção) ---
    const char *niveis[] = {
        "1 - Funcionário", 
        "2 - Gerente",     
    };
    // O Administrador (Nível 3) pode criar até Gerentes (Nível 2), o que corresponde a 2 opções no array
    int maxNivelOpcoes = (usuarioLogado.nivel == 3) ? 2 : 1; 
    int linhaSelecionada = 0;
    int tecla;

    ocultarCursor(); // Esconde o cursor durante a seleção

    // Loop de Seleção de Nível
    do {
        system("cls"); // Limpa a tela para redesenhar o menu
        desenharBordaCabecalhoDuplo("  CADASTRO DE NOVO USUÁRIO", "  Definição de Permissões");
        
        printf("\t\t|  Selecione o cargo:           |\n");
        printf("\t\t|-------------------------------|\n");
        printf("\t\t|                               |\n");
        
        int i ;
        for( i = 0; i < maxNivelOpcoes; i++) {
           
            // Renderiza apenas as opções permitidas
            printf("\t\t|  ");
            if (i == linhaSelecionada) {
                // Opção Selecionada: Destaque
                setColor(COR_DESTAQUE);
                printf("> %-27s", niveis[i]);
                setColor(COR_PADRAO);
            } else {
                // Opção Normal
                printf("  %-27s", niveis[i]);
            }
            printf("|\n");
        }
        
        printf("\t\t|                               |\n");
        desenharBordaRodape();
        printf("\n\t\t[ENTER] Confirmar  [ESC] Cancelar\n");
        
        // Navegação por Teclas
        tecla = _getch();
        if (tecla == 224) { 
            tecla = _getch();
            if (tecla == 72) { // Seta Cima
                linhaSelecionada--;
                if (linhaSelecionada < 0) linhaSelecionada = maxNivelOpcoes - 1;
            }
            if (tecla == 80) { // Seta Baixo
                linhaSelecionada++;
                if (linhaSelecionada >= maxNivelOpcoes) linhaSelecionada = 0;
            }
        }
        
    } while (tecla != 13 && tecla != 27); // Repete até pressionar ENTER (13) ou ESC (27)

    if (tecla == 27) { // Se ESC for pressionado, cancela a operação
        system("cls");
        desenharBordaCabecalhoDuplo("      CADASTRO CANCELADO", "     Operação Descartada");
        printf("\t\t|                               |\n");
        printf("\t\t|      Cadastro cancelado.      |\n");
        printf("\t\t|                               |\n");
        desenharBordaRodape();
        _getch();
        return;
    }
    
    // Mapeia o índice selecionado para o Nível correto (Índice 0 -> Nível 1; Índice 1 -> Nível 2)
    novo.nivel = linhaSelecionada + 1; 

    // --- 4. Salvar no Arquivo e Confirmação (Estilizada) ---
    arquivo = fopen("usuarios.bin", "ab");
    
    system("cls");
    desenharBordaCabecalhoDuplo("    REVISÃO E SALVAMENTO", "  Detalhes do Novo Registro");
    
    printf("\t\t|  ID: %-25d|\n", novo.id);
    printf("\t\t|  Nome: %-23s|\n", novo.nome);
    printf("\t\t|  Login: %-22s|\n", novo.login);
    printf("\t\t|  Nível: %-22d|\n", novo.nivel);
    printf("\t\t|-------------------------------|\n");
    
    if (arquivo != NULL) {
        fwrite(&novo, sizeof(Usuario), 1, arquivo);
        fclose(arquivo);
        printf("\t\t|  ");
        setColor(COR_DESTAQUE);
        printf("    Usuário cadastrado!     ");
        setColor(COR_PADRAO);
        printf(" |\n");
    } else {
        printf("\t\t|  ");
        setColor(COR_DESTAQUE);
        printf(" ERRO: Falha ao salvar no arquivo! ");
        setColor(COR_PADRAO);
        printf(" |\n");
    }
    
    desenharBordaRodape();
    printf("\n\t\tPressione qualquer tecla para continuar...");
    _getch(); // Substitui system("pause")
}

// Função que remove fisicamente um usuário do arquivo
void removerUsuario(Usuario usuarioLogado) {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    FILE *temp = fopen("usuarios.tmp", "wb"); // Arquivo temporário
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos de dados.\n");
        return;
    }

    int idParaRemover;
    int encontrou = 0;
    Usuario u;

    // Mostra a lista antes para facilitar
    listarUsuarios(); 
    
    printf("\n=== REMOVER USUÁRIO ===\n");
    printf("Digite o ID do usuário que deseja remover\n(Digite 0 para cancelar): ");
    scanf("%d", &idParaRemover);

    if (idParaRemover == 0) {
        fclose(arquivo);
        fclose(temp);
        remove("usuarios.tmp"); // Limpa o lixo
        return;
    }

    // REGRAS DE SEGURANÇA
    
    // Não pode remover a si mesmo
    if (idParaRemover == usuarioLogado.id) {
        printf("\nERRO: Você não pode remover sua própria conta.\n");
        fclose(arquivo);
        fclose(temp);
        remove("usuarios.tmp");
        system("pause");
        return;
    }

    // Não pode remover o administrador
    if (idParaRemover == 1) {
        printf("\nERRO: O administrador (ID 1) não pode ser removido.\n");
        fclose(arquivo);
        fclose(temp);
        remove("usuarios.tmp");
        system("pause");
        return;
    }

    // Loop de cópia
    while (fread(&u, sizeof(Usuario), 1, arquivo)) {
        if (u.id == idParaRemover) {
            encontrou = 1;
            
            // VALIDAÇÃO 
            // Gerente só pode remover funcionário, se ele tentar remover outro cargo deve bloquear.
            if (usuarioLogado.nivel == 2 && u.nivel >= 2) {
                printf("ERRO: Gerentes só podem remover funcionários.\n");
                // Copia o usuário de volta para não perder o dado, pois a operação foi cancelada
                fwrite(&u, sizeof(Usuario), 1, temp); 
            } else {
                // Se passou aqui, o usuário SERÁ REMOVIDO
                printf("Usuário '%s' removido com sucesso.\n", u.nome);
            }
        } else {
            // Copia usuários que NÃO são o alvo para o novo arquivo
            fwrite(&u, sizeof(Usuario), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrou) {
        // Apaga o velho e renomeia o novo
        remove("usuarios.bin");
        rename("usuarios.tmp", "usuarios.bin");
    } else {
        printf("Usuário com ID %d não encontrado.\n", idParaRemover);
        remove("usuarios.tmp");
    }
    system("pause");
}

void menuGestaoUsuarios(Usuario usuarioLogado) {
    const char *opcoes[] = {
        "Listar Usuários",
        "Cadastrar Novo Usuário",
        "Remover Usuário",
        "Voltar"
    };
    int totalOpcoes = 4;
    int linhaSelecionada = 0;
    int tecla;
    
    ocultarCursor();

    do {
        char subtitulo[50];
        snprintf(subtitulo, 49, " Logado como: %.20s", usuarioLogado.login); 

        // 2. Renderização Visual
        system("cls");
        // Desenha o cabeçalho no padrão administrativo
        desenharBordaCabecalho("     GESTÃO DE USUÁRIOS");

        printf("\t\t|                               |\n");

        // Loop para desenhar as opções e aplicar o destaque
        int i;
        for (i = 0; i < totalOpcoes; i++) {
            printf("\t\t|  ");

            if (i == linhaSelecionada) {
                // Opção Selecionada: Cor de destaque + indicador ">"
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
                case 0: // Listar Usuários
                    listarUsuarios();
                    // Assumindo que listarUsuarios() tem sua própria pausa, se não, adicione _getch() ou system("pause") aqui
                    system("pause"); // Mantive o system("pause") da versão original
                    break;
                case 1: // Cadastrar Novo Usuário
                    cadastrarUsuario(usuarioLogado);
                    break;
                case 2: // Remover Usuário
                    removerUsuario(usuarioLogado);
                    break;
                case 3: // Voltar
                    return; // Sai da função
            }
        }
        // Tratamento de Opção inválida não é mais necessário, pois só aceitamos Setas e Enter.

    } while (1); // Loop é encerrado apenas pelo 'return' no case 3
}
