#ifndef CARROS_H
#define CARROS_H

// Definição da estrutura de Carros
typedef struct {
    int id;
    char modelo[50];
    char marca[50];
    char placa[15];
    char categoria[20]; // Ex: Sedan, SUV, Conversível, Econômico
    float valor_diaria;
    int status; // 0 = Disponivel, 1 = Alugado, 2 = Em manutenção
} Carro;


// Protótipos das funções
void menuGestaoCarros();
void cadastrarCarro();
void listarCarros(int filtroStatus);
void gerenciarManutencao();
int buscarCarroPorPlaca(char *placaBusca, Carro *carroEncontrado);
int placaJaCadastrada(char *placa);
void removerCarro();
void atualizarStatusCarro(int idCarro, int novoStatus);

#endif
