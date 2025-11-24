#ifndef CARROS_H
#define CARROS_H

struct Carro {
    char modelo[50];
    char placa[10];
    float diaria;
    int disponivel;
};

void cadastrarCarro(struct Carro carros[], int *qtd);
void listarCarros(struct Carro carros[], int qtd);

#endif
