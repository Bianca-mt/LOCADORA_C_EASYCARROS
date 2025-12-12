// Quinto arquivo: responsável pelas estruturas da interface

#include "interface.h"

// Localiza o cursor (ponteiro que pisca) na posição indicada
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Define a cor da linha
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Oculta o cursor (ponteiro que pisca) 
void ocultarCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Exibe o cursor (ponteiro que pisca) 
void mostrarCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 20;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Retorna a última posição do cursor
int obterLinhaAtual() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.dwCursorPosition.Y;
    }
    return 0; // Se der erro, retorna 0
}


// Estrutura de caixas/molduras
void desenharBordaCabecalho(char *titulo) {
    system("cls");
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|                               |\n");
    
    printf("\t\t| %-29s |\n", titulo); 
    
    printf("\t\t|                               |\n");
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaCabecalhoDuplo(char *titulo, char *subtitulo) {
    system("cls");
    //setColor(COR_AZUL); 
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|                               |\n");
    
    printf("\t\t| %-29s |\n", titulo); 
    printf("\t\t| %-29s |\n", subtitulo);
    
    printf("\t\t|                               |\n");
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaRodape() {
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|      Setas para navegar       |\n");
    printf("\t\t|     Enter para selecionar     |\n");
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaRodape2() {
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|      Setas para navegar2       |\n");
    printf("\t\t|     Enter para selecionar     |\n");
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaRodapeCartao() {
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|  Pressione Enter para voltar  |\n");
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaRodapeLogin() {
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|    Digite suas credenciais    |\n");
    printf("\t\t|    para acessar sua conta.    |\n"); 
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|      Não tem uma conta?       |\n");
    printf("\t\t|    Volte e crie uma antes.    |\n"); 
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharBordaMensagem(char *mensagem) {
    printf("\n");
    //setColor(COR_AZUL);
    printf("\t\t+-------------------------------+\n");
    
    printf("\t\t| %-29s |\n", mensagem); 
    
    printf("\t\t+-------------------------------+\n");
    //setColor(COR_PADRAO);
}

void desenharRodapeCadastro() {
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|  Preencha todos os campos.    |\n");
    printf("\t\t| No mínimo, 3 caracteres cada. |\n");
    printf("\t\t+-------------------------------+\n");
}


// Exibe uma caixa vermelha de erro e espera Enter
void exibirErroVisual(char *msg1, char *msg2) {
    ocultarCursor();
    printf("\n");
    printf("\t\t+-------------------------------+\n");
    setColor(COR_VERMELHO);
    printf("\t\t| ERRO: %-23s |\n", msg1);
    if (msg2 != NULL) printf("\t\t| %-29s |\n", msg2);
    setColor(COR_PADRAO);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|  Pressione Enter para voltar  |\n");
    printf("\t\t+-------------------------------+\n");
    _getch();
}

// Exibe uma caixa verde de sucesso e saldo
void exibirSucessoVisual(char *msg, float novoSaldo) {
    ocultarCursor();
    printf("\n");
    printf("\t\t+-------------------------------+\n");
    setColor(COR_VERDE);
    printf("\t\t| %-29s |\n", msg);
    setColor(COR_PADRAO);
    printf("\t\t|     Novo Saldo: R$ %-10.2f |\n", novoSaldo);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|  Pressione Enter para voltar  |\n");
    printf("\t\t+-------------------------------+\n");
    _getch();
}

// Exibe uma caixa verde de sucesso
void exibirSucesso(char *msg) {
    ocultarCursor();
    printf("\n");
    printf("\t\t+-------------------------------+\n");
    setColor(COR_VERDE);
    printf("\t\t| %-29s |\n", msg);
    setColor(COR_PADRAO);
    printf("\t\t+-------------------------------+\n");
    printf("\t\t|  Pressione Enter para voltar  |\n");
    printf("\t\t+-------------------------------+\n");
    _getch();
}



