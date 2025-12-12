#ifndef LOCACOES_H
#define LOCACOES_H
#include "clientes.h" 
#include "carros.h"  

// Definição da estrutura de DAta
typedef struct {
    int dia, mes, ano;
} Data;

// Definição da estrutura de Locação
typedef struct {
    int id;
    int idCliente;
    int idCarro;
    
    Data dataRetirada;
    Data dataDevolucaoPrevista;
    Data dataDevolucaoReal;
    
    float valorDiariaAplicado;
    float valorTotalPrevisto;
    float valorMultas;
    float valorTotalFinal;
    
    int finalizada; // 0 = Ativa (Carro na rua), 1 = Finalizada (Carro devolvido)
} Locacao;


// Protótipos das funções
void menuLocacoes();
void realizarLocacao(); // Check-out (Retirada)
void finalizarLocacao();    // Check-in (Devolução)
void listarLocacoesAtivas();
void gerarRelatorioFinanceiro();

Data obterDataHoje();
time_t converterParaTime(Data d);
int diferencaDias(Data inicio, Data fim);
Data lerDataInterativa(char* label);
Data perguntarData(char* textoAcao);
int compararDatas(Data d1, Data d2);

void acharNomeCliente(int id, char *bufferDestino);
void acharDadosCarro(int id, char *bufferDestino);

#endif
