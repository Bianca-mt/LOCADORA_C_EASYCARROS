#ifndef INTERFACE_H
#define INTERFACE_H
#include <windows.h> 
#include <stdio.h>
#include <conio.h> 

// Definições de Cores
#define COR_PADRAO 7
#define COR_DESTAQUE 14 // Amarelo
#define COR_VERDE 10
#define COR_VERMELHO 12
#define COR_AZUL 11

// Ferramentas Visuais
void gotoxy(int x, int y);
void setColor(int color);
void ocultarCursor();
void mostrarCursor();
int obterLinhaAtual();

void desenharBordaCabecalho(char *titulo);
void desenharBordaCabecalhoDuplo(char *titulo, char *subtitulo);
void desenharBordaRodape();
void desenharBordaMensagem(char *mensagem);
void desenharBordaRodapeLogin();
void desenharRodapeCadastro();
void desenharBordaRodapeCartao();

void exibirErroVisual(char *msg1, char *msg2);
void exibirSucessoVisual(char *msg, float novoSaldo);
void exibirSucesso(char *msg);


#endif
