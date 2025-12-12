#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "contas.h"
#include "carros.h"
#include "clientes.h"
#include "locacoes.h"
#include "interface.h"

// --- PROTÓTIPOS DOS FUNÇÕES ---
void menuComercial(Usuario u);
void menuAdministrativo(Usuario u);
void executarSistema();


// --- FUNÇÕES---
void menuComercial(Usuario u) {
    
    const char *opcoes[] = {
        "Gestão de Carros",
        "Gestão de Clientes",
        "Gestão de Locações",
        "Voltar"
    };
    int totalOpcoes = 4;
    int linhaSelecionada = 0;
    int tecla;

    ocultarCursor();

    do {
        // Monta o cabeçalho personalizado
        char subtitulo[50];
        snprintf(subtitulo, 49, " Bem-vindo(a), %.30s", u.nome);

        system("cls");
        
        // Desenha o cabeçalho no padrão administrativo
        desenharBordaCabecalhoDuplo("      PAINEL COMERCIAL", subtitulo);

        printf("\t\t|                               |\n");

        // Loop para listar as opções
        int i;
        for (i = 0; i < totalOpcoes; i++) {
            printf("\t\t|  ");

            if (i == linhaSelecionada) {
                
                setColor(COR_DESTAQUE);
                printf("> %-27s", opcoes[i]); 
                setColor(COR_PADRAO);
            } else {
                
                printf("  %-27s", opcoes[i]);
            }

            printf("|\n");
        }

        printf("\t\t|                               |\n");
        desenharBordaRodape();

        // Navegação por Teclas
        tecla = _getch();

        if (tecla == 224) {
            // Tecla especial (Setas)
            tecla = _getch();
            if (tecla == 72) { 
                linhaSelecionada--;
                if (linhaSelecionada < 0) linhaSelecionada = totalOpcoes - 1; // Loop para o final
            }
            if (tecla == 80) { 
                linhaSelecionada++;
                if (linhaSelecionada >= totalOpcoes) linhaSelecionada = 0; // Loop para o início
            }
        }
        else if (tecla == 13) {
            // Tecla ENTER -> Executa a função
            switch(linhaSelecionada) {
                case 0: // Gestão de Carros
                    menuGestaoCarros();
                    break;
                case 1: // Gestão de Clientes
                    menuGestaoClientes();
                    break;
                case 2: // Gestão de Locações
                    menuLocacoes();
                    break;
                case 3: // Voltar
                    return;
            }
        }

    } while (1); 
}

void menuAdministrativo(Usuario u) {
    //Lista das Opções e Variáveis de Controle
    const char *opcoes[] = {
        "Gestão de Usuários",
        "Relatórios",
        "Painel Comercial",
        "Sair / Deslogar"
    };
    int totalOpcoes = 4;
    int linhaSelecionada = 0;
    int tecla;
    
    
    ocultarCursor(); 

    do {
        // Monta o cabeçalho personalizado
        char subtitulo[50];
        snprintf(subtitulo, 49, " Bem-vindo(a), %.30s", u.nome);
        
        system("cls"); 
        desenharBordaCabecalhoDuplo("    PAINEL ADMINISTRATIVO", subtitulo);

        printf("\t\t|                               |\n");

        // Listagem das opções
        int i;
        for (i = 0; i < totalOpcoes; i++) {
            printf("\t\t|  "); 
            
            if (i == linhaSelecionada) {
                // Opção selecionada: Cor de destaque e indicador ">"
                setColor(COR_DESTAQUE);
                printf("> %-27s", opcoes[i]);
                setColor(COR_PADRAO);
            } else {
                // Opções normais: Espaço e texto normal
                printf("  %-27s", opcoes[i]);
            }
            
            printf("|\n");
        }
        
        printf("\t\t|                               |\n");
        desenharBordaRodape();

        // Navegação por teclas
        tecla = _getch();
        
        if (tecla == 224) { 
            // Tecla especial (Setas)
            tecla = _getch();
            if (tecla == 72) { // Seta Cima
                linhaSelecionada--;
                if (linhaSelecionada < 0) linhaSelecionada = totalOpcoes - 1; // Volta ao final
            }
            if (tecla == 80) { // Seta Baixo
                linhaSelecionada++;
                if (linhaSelecionada >= totalOpcoes) linhaSelecionada = 0; // Volta ao início
            }
        }
        else if (tecla == 13) { 
            // Enter
            switch(linhaSelecionada) {
                case 0: // Gestão de Usuários
                    menuGestaoUsuarios(u);
                    break;
                case 1: // Relatórios
                    gerarRelatorioFinanceiro();
                    break;
                case 2: // Painel Comercial
                    menuComercial(u);
                    break;
                case 3: // Sair / Deslogar
                    printf("\t\t+-------------------------------+\n");
                    printf("\t\t|   Pressione para deslogar...  |\n");
                    printf("\t\t+-------------------------------+\n");
                    _getch();
                    getchar();
                    return; 
            }
        }
        
    } while (1);
}

void executarSistema() {
    Usuario usuarioAtual;
    int sairDoSistema = 0;

    // // 1. Início garantido
    inicializarSistema();

    // 2. Loop Principal de Login/Logout
    while (!sairDoSistema) {
        
        if (realizarLogin(&usuarioAtual)) {
            // Login Sucesso -> Direciona para o Menu Correto
            if (usuarioAtual.nivel == 1) {
                menuComercial(usuarioAtual);
            } else {
                menuAdministrativo(usuarioAtual);
            }
        } else {
            // Login Falhou ou Cancelado
            char resp;
            system("cls");
            printf("\n\t\tDeseja encerrar o sistema? (S/N): ");
            scanf(" %c", &resp);
            getchar();
            if (resp == 'S' || resp == 's') {
                sairDoSistema = 1;
            }
        }
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    
    executarSistema();

	system("cls"); 
    printf("\t\tSistema encerrado com sucesso.\n");
    return 0;
}
