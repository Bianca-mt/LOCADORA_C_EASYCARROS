#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "locacoes.h"
#include "interface.h"

// Função auxiliar que compara datas
int compararDatas(Data d1, Data d2) {
    if (d1.ano < d2.ano) return -1;
    if (d1.ano > d2.ano) return 1;
    
    // Se anos são iguais, checa mês
    if (d1.mes < d2.mes) return -1;
    if (d1.mes > d2.mes) return 1;
    
    // Se meses são iguais, checa dia
    if (d1.dia < d2.dia) return -1;
    if (d1.dia > d2.dia) return 1;
    
    return 0; // Datas idênticas
}

// Função auxiliar que pega a data atual do sistema
Data obterDataHoje() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Data d;
    d.dia = tm.tm_mday;
    d.mes = tm.tm_mon + 1;
    d.ano = tm.tm_year + 1900;
    return d;
}

// Função auxiliar que converte a Data para o formato time_t
time_t converterParaTime(Data d) {
    struct tm temp = {0};
    temp.tm_mday = d.dia;
    temp.tm_mon = d.mes - 1; // Struct tm usa meses 0-11
    temp.tm_year = d.ano - 1900; // Struct tm usa anos desde 1900
    return mktime(&temp);
}

// Função auxiliar que calcula a diferença em dias entre duas datas
int diferencaDias(Data inicio, Data fim) {
    time_t t_inicio = converterParaTime(inicio);
    time_t t_fim = converterParaTime(fim);
    
    double segundos = difftime(t_fim, t_inicio);
    int dias = segundos / (60 * 60 * 24); // Converte segundos para dias
    
    if (dias < 1) return 1; // Cobramos no mínimo 1 diária
    return dias;
}

// Função auxiliar que lê data de forma inteligente 
Data lerDataInterativa(char* label) {
	//Aceita dd/mm/aaaa ou dd mm aaaa
	
    Data d;
    int valida = 0;
    char entrada[20];

    do {
        printf("%s (dd/mm/aaaa ou dd mm aaaa): ", label);
        fflush(stdin);
        scanf("%[^\n]s", entrada);
        getchar();

        // Tenta ler com barras
        if (sscanf(entrada, "%d/%d/%d", &d.dia, &d.mes, &d.ano) == 3) valida = 1;
        // Se falhar, tenta ler com espaços
        else if (sscanf(entrada, "%d %d %d", &d.dia, &d.mes, &d.ano) == 3) valida = 1;

        if (!valida) {
            printf("Formato inválido. Tente novamente.\n");
        } else {
            // Validação básica de limites
            if (d.dia < 1 || d.dia > 31 || d.mes < 1 || d.mes > 12 || d.ano < 2000) {
                printf("Data impossível. Verifique dia/mês/ano.\n");
                valida = 0;
            }
        }
    } while (!valida);

    return d;
}

// Função auxiliar que chama o sub-menu de data
Data perguntarData(char* textoAcao) {
    int op;
    Data d = obterDataHoje(); // Padrão é hoje

    printf("\n%s\n", textoAcao);
    printf("1. Data de hoje (%02d/%02d/%04d)\n", d.dia, d.mes, d.ano);
    printf("2. Digitar outra data\n");
    printf("Escolha: ");
    scanf("%d", &op);
    fflush(stdin);

    if (op == 2) {
        return lerDataInterativa("Digite a Data");
    }
    return d; // Retorna hoje
}


// Função auxiliar que busca nome do cliente pelo ID
void acharNomeCliente(int id, char *bufferDestino) {
    FILE *f = fopen("clientes.bin", "rb");
    Cliente c;
    strcpy(bufferDestino, "Desconhecido"); // Valor padrão
    if (f == NULL) return;

    while(fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id == id) {
            strcpy(bufferDestino, c.nome);
            break;
        }
    }
    fclose(f);
}

// Função auxiliar que busca modelo/placa do carro pelo ID
void acharDadosCarro(int id, char *bufferDestino) {
    FILE *f = fopen("carros.bin", "rb");
    Carro c;
    strcpy(bufferDestino, "Desconhecido");
    if (f == NULL) return;

    while(fread(&c, sizeof(Carro), 1, f)) {
        if (c.id == id) {
            sprintf(bufferDestino, "%s (%s)", c.modelo, c.placa);
            break;
        }
    }
    fclose(f);
}

// Função que gera relatórios no menu administrativo
void gerarRelatorioFinanceiro() {
    FILE *arquivo = fopen("locacoes.bin", "rb");
    if (arquivo == NULL) {
        system("cls");
        desenharBordaCabecalhoDuplo("      ERRO DE LEITURA", " Arquivo não encontrado");
        printf("\t\t|                                |\n");
        printf("\t\t|  Nenhum dado financeiro        |\n");
        printf("\t\t|  encontrado no sistema.        |\n");
        printf("\t\t|                                |\n");
        desenharBordaRodape();
        _getch();
        return;
    }

    Locacao loc;
    
    // Variáveis acumuladoras
    float faturamentoTotal = 0.0;
    float totalMultas = 0.0;
    float aReceber = 0.0;
    int qtdFinalizadas = 0;
    int qtdAndamento = 0;

    // 1. Processamento dos dados (Lógica de Negócio mantida)
    while (fread(&loc, sizeof(Locacao), 1, arquivo)) {
        if (loc.finalizada == 1) {
            faturamentoTotal += loc.valorTotalFinal;
            totalMultas += loc.valorMultas;
            qtdFinalizadas++;
        } else {
            aReceber += loc.valorTotalPrevisto;
            qtdAndamento++;
        }
    }

    // 2. Exibição do Dashboard (Estilo Visual Novo)
    ocultarCursor();
    system("cls");
    desenharBordaCabecalhoDuplo("    RELATÓRIO FINANCEIRO", "    Visão Geral do Caixa");

    // Formatação alinhada com a largura visual do seu menu (aprox 32 caracteres internos)
    printf("\t\t|                               |\n");
    
    // Seção Faturamento
    printf("\t\t|  FATURAMENTO (Caixa):         |\n");
    printf("\t\t|  ");
    setColor(COR_DESTAQUE); // Verde ou Destaque para dinheiro
    printf("R$ %-26.2f", faturamentoTotal);
    setColor(COR_PADRAO);
    printf("|\n");
    
    printf("\t\t|  Multas: R$ %-15.2f   |\n", totalMultas);
    printf("\t\t|                               |\n");
    printf("\t\t|-------------------------------|\n"); // Divisória visual
    printf("\t\t|                               |\n");

    // Seção A Receber
    printf("\t\t|  A RECEBER (Previsão):        |\n");
    printf("\t\t|  R$ %-26.2f|\n", aReceber);
    printf("\t\t|                               |\n");
    printf("\t\t|-------------------------------|\n");

    // Seção Métricas
    printf("\t\t|  MÉTRICAS OPERACIONAIS:       |\n");
    printf("\t\t|  Finalizadas:       %-10d|\n", qtdFinalizadas);
    printf("\t\t|  Em Andamento:      %-10d|\n", qtdAndamento);
    printf("\t\t|  Total Transações:  %-10d|\n", qtdFinalizadas + qtdAndamento);
    printf("\t\t|                               |\n");

    desenharBordaRodape();

    // 3. Rodapé de Interação
    printf("\n\t\t[ENTER] Ver Detalhes   [ESC] Voltar\n");

    // 4. Captura de Decisão
    int tecla = _getch();

    if (tecla == 13) { // ENTER -> Mostrar Detalhes
        rewind(arquivo); // Reinicia leitura do arquivo
        char nomeCliente[100];
        
        system("cls");
        // Cabeçalho largo para a tabela
        printf("====================================================================================\n");
        printf("                          HISTÓRICO DE LOCAÇÕES FINALIZADAS                         \n");
        printf("====================================================================================\n");
        printf(" ID  | CLIENTE              | RETIRADA   | DEVOLUÇÃO  | TOTAL PAGO     | MULTA    \n");
        printf("-----+----------------------+------------+------------+----------------+----------\n");
        
        int encontrou = 0;
        while (fread(&loc, sizeof(Locacao), 1, arquivo)) {
            if (loc.finalizada == 1) {
                acharNomeCliente(loc.idCliente, nomeCliente); // Função externa assumida
                
                printf(" %-3d | %-20.20s | %02d/%02d/%02d | %02d/%02d/%02d | R$ %-10.2f | R$ %-5.2f\n",
                    loc.id, 
                    nomeCliente,
                    loc.dataRetirada.dia, loc.dataRetirada.mes, loc.dataRetirada.ano % 100, // Ano formatado curto
                    loc.dataDevolucaoReal.dia, loc.dataDevolucaoReal.mes, loc.dataDevolucaoReal.ano % 100,
                    loc.valorTotalFinal,
                    loc.valorMultas);
                encontrou = 1;
            }
        }
        
        if (!encontrou) {
            printf("\n   Nenhuma locação finalizada encontrada para exibir.\n");
        }

        printf("====================================================================================\n");
        printf("\n   Pressione qualquer tecla para voltar...");
        _getch();
    }

    fclose(arquivo);
    // Se tecla foi ESC ou qualquer outra (exceto ENTER), a função termina e volta ao menu anterior
} 
// Função que realiza e registra uma locação
void realizarLocacao() {
    Locacao nova;
    Cliente cliente;
    Carro carro;
    
    char cpfBusca[15];
    char placaBusca[15];
    
    system("cls");
    printf("=== NOVA LOCAÇÃO (Check-Out) ===\n");
    
    // Validar Cliente
    printf("Digite o CPF do Cliente: ");
    scanf("%s", cpfBusca);
    if (!buscarClientePorCpf(cpfBusca, &cliente)) {
        printf("Erro: Cliente não encontrado. Faça o cadastro dele antes.\n");
        system("pause");
        return;
    }
    printf("Cliente selecionado: %s (CNH: %s)\n", cliente.nome, cliente.cnh);

    // Validar Carro
    printf("\nDigite a Placa do Carro: ");
    scanf("%s", placaBusca);
    if (!buscarCarroPorPlaca(placaBusca, &carro)) {
        printf("Erro: Carro não encontrado.\n");
        system("pause");
        return;
    }
    
    // Validar disponibilidade do carro
    if (carro.status != 0) {
    char motivo[50] = "Indefinido";
    if(carro.status == 1) strcpy(motivo, "Alugado");
    if(carro.status == 2) strcpy(motivo, "Em Manutenção");
    printf("Erro: Carro indisponível (Status: %s).\n", motivo);
    printf("O carro só pode ser alugado se estiver disponível no Pátio.\n");
    
    system("pause");
    return;
}
    printf("Carro selecionado: %s %s (R$ %.2f / dia)\n", carro.modelo, carro.marca, carro.valor_diaria);

    // Lógica de datas
	Data dataHoje = obterDataHoje();
    int dataValida = 0;

    // Loop de validação das datas
    do {
        // Validação da data de Retirada
        nova.dataRetirada = perguntarData("--- DATA DE RETIRADA ---");
        
        // Retirada não pode ser no passado (antes de hoje)
        if (compararDatas(nova.dataRetirada, dataHoje) == -1) {
            printf("Erro: A data de retirada não pode ser anterior a hoje (%02d/%02d/%04d).\n", dataHoje.dia, dataHoje.mes, dataHoje.ano);
            printf("Pressione qualquer tecla para tentar novamente...");
            getchar();
			continue; // Volta pro começo do loop
        }

        // Validação da data prevista de Devolução
        printf("\n--- DATA PREVISTA DE DEVOLUÇÃO ---\n");
        nova.dataDevolucaoPrevista = lerDataInterativa("Data Prevista");

        // Devolução deve ser pelo menos um dia depois de retirada
        int dias = diferencaDias(nova.dataRetirada, nova.dataDevolucaoPrevista);
        
        if (compararDatas(nova.dataDevolucaoPrevista, nova.dataRetirada) <= 0) {
            printf("Erro: A devolução deve ser pelo menos 1 dia após a retirada.\n");
        } else {
            dataValida = 1;
        }

    } while (!dataValida);


    // Cálculos Financeiros (Prévia do valor)
    int dias = diferencaDias(nova.dataRetirada, nova.dataDevolucaoPrevista);
    nova.valorDiariaAplicado = carro.valor_diaria;
    nova.valorTotalPrevisto = dias * nova.valorDiariaAplicado;

    printf("\n--- RESUMO DO ORÇAMENTO ---\n");
    printf("Retirada: %02d/%02d/%04d\n", nova.dataRetirada.dia, nova.dataRetirada.mes, nova.dataRetirada.ano);
    printf("Devolução: %02d/%02d/%04d\n", nova.dataDevolucaoPrevista.dia, nova.dataDevolucaoPrevista.mes, nova.dataDevolucaoPrevista.ano);
    printf("Diárias estimadas: %d\n", dias);
    printf("Valor Total a Pagar Agora: R$ %.2f\n", nova.valorTotalPrevisto);
    printf("---------------------------\n");
    
    char confirm;
    printf("Confirmar pagamento e locação? (S/N): ");
    fflush(stdin);
    scanf(" %c", &confirm);

    if (confirm == 'S' || confirm == 's') {
        // Descobrir o próximo ID (Auto Incremento)
        FILE *arquivo = fopen("locacoes.bin", "rb");
        int ultimoId = 0;
        Locacao temp;
        if (arquivo != NULL) {
            while (fread(&temp, sizeof(Locacao), 1, arquivo)) ultimoId = temp.id;
            fclose(arquivo);
        }
        
        // Preencher dados finais
        nova.id = ultimoId + 1;
        nova.idCliente = cliente.id;
        nova.idCarro = carro.id;
        nova.finalizada = 0; // Locação Aberta
        nova.valorMultas = 0;
        nova.valorTotalFinal = 0; // Só define no final

        // Grava a nova locação
        arquivo = fopen("locacoes.bin", "ab");
        fwrite(&nova, sizeof(Locacao), 1, arquivo);
        fclose(arquivo);

        // Atualiza o status do carro para alugado
        atualizarStatusCarro(carro.id, 1);

        printf("\nSucesso! Locação #%d registrada.\n", nova.id);
    } else {
        printf("\nOperação cancelada.\n");
    }
    system("pause");
}

// Função que finaliza uma locação
void finalizarLocacao() {
    char placa[15];
    Locacao loc;
    Carro c;
    int encontrou = 0;
    
    // Abre o arquivo para atualizar a locação como finalizada
    FILE *arqLoc = fopen("locacoes.bin", "rb+");
    if (arqLoc == NULL) {
        printf("\nNenhuma locação encontrada.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("=== DEVOLUÇÃO DE CARRO (Check-In) ===\n");
    printf("Digite a placa do carro sendo devolvido: ");
    scanf("%s", placa);

    // Descobrir qual é o ID do carro pela placa
    if (!buscarCarroPorPlaca(placa, &c)) {
        printf("Carro não encontrado.\n");
        fclose(arqLoc);
        system("pause");
        return;
    }

    // Buscar uma locação ativa para esse carro
    while (fread(&loc, sizeof(Locacao), 1, arqLoc)) {
        if (loc.idCarro == c.id && loc.finalizada == 0) {
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Nenhuma locação ativa encontrada para este carro.\n");
        fclose(arqLoc);
        system("pause");
        return;
    }

    printf("\nLocação encontrada: #%d\n", loc.id);
    printf("Data Prevista: %02d/%02d/%04d\n", loc.dataDevolucaoPrevista.dia, loc.dataDevolucaoPrevista.mes, loc.dataDevolucaoPrevista.ano);

    // Receber a data real de devolução
   	Data dataReal;
    int dataValida = 0;
    
    do {
        dataReal = perguntarData("--- DATA DA DEVOLUCAO REAL ---");

        // Devolução real não pode ser antes da retirada
        if (diferencaDias(loc.dataRetirada, dataReal) < 0) {
             printf("Erro: A data de devolução não pode ser anterior a data de retirada (%02d/%02d/%04d).\n", 
                    loc.dataRetirada.dia, loc.dataRetirada.mes, loc.dataRetirada.ano);
        } else {
            dataValida = 1;
        }
    } while (!dataValida);

    loc.dataDevolucaoReal = dataReal;

    // Calcular Atrasos e Multas
    // Convertemos para time_t para comparar
    time_t t_previsto = converterParaTime(loc.dataDevolucaoPrevista);
    time_t t_real = converterParaTime(dataReal);
    
    float totalPagarExtra = 0;
    
    if (t_real > t_previsto) {
        int diasAtraso = diferencaDias(loc.dataDevolucaoPrevista, dataReal);
        float multaFixa = 50.00; // Valor de multa fixa
        float valorDiariasExtras = diasAtraso * loc.valorDiariaAplicado;
        
        loc.valorMultas = multaFixa + valorDiariasExtras;
        totalPagarExtra = loc.valorMultas;
        
        printf("\nAtenção: Atraso de %d dias detectado.\n", diasAtraso);
        printf("Multa Fixa: R$ %.2f\n", multaFixa);
        printf("Diarias Extras: R$ %.2f\n", valorDiariasExtras);
        printf("TOTAL A PAGAR AGORA: R$ %.2f\n", totalPagarExtra);
    } else {
        printf("\nDevolução dentro do prazo. Nenhum valor adicional.\n");
        loc.valorMultas = 0;
    }

    loc.valorTotalFinal = loc.valorTotalPrevisto + loc.valorMultas;

    char confirm;
    printf("\nConfirmar devolução e recebimento de chaves? (S/N): ");
    fflush(stdin);
    scanf(" %c", &confirm);

    if (confirm == 'S' || confirm == 's') {
        loc.finalizada = 1; // Fecha a locação
        
        // Voltar cursor e salvar locação atualizada
        fseek(arqLoc, -(long)sizeof(Locacao), SEEK_CUR);
        fwrite(&loc, sizeof(Locacao), 1, arqLoc);
        
        // Atualiza o status do carro para disponível
        atualizarStatusCarro(c.id, 0);
        
        printf("\nDevolução concluída com sucesso. Carro liberado.\n");
    } else {
        printf("Operação cancelada.\n");
    }
    
    fclose(arqLoc);
    system("pause");
}

// Função que lista apenas as locações ativas
void listarLocacoesAtivas() {
    FILE *arquivo = fopen("locacoes.bin", "rb");
    if (arquivo == NULL) {
        printf("\nSem locações registradas.\n");
        system("pause");
        return;
    }
    
    Locacao loc;
    int achou = 0;
    char nomeCliente[100];
    char infoCarro[100];
    
    system("cls");
    printf("=== LOCAÇÕES ATIVAS/EM ANDAMENTO  ===\n");
    printf("%-3s | %-20s | %-20s | %-10s | %-10s\n", "ID", "CARRO", "CLIENTE", "DEVOLUÇÃO", "VALOR");
    printf("-------------------------------------------------------------------------------\n");
    
	 while(fread(&loc, sizeof(Locacao), 1, arquivo)) {
        if (loc.finalizada == 0) {
            
            // Busca os nomes reais pelos IDs
            acharNomeCliente(loc.idCliente, nomeCliente);
            acharDadosCarro(loc.idCarro, infoCarro);

            printf("%-3d | %-20.20s | %-20.20s | %02d/%02d/%04d | R$ %.2f\n",
                loc.id, 
                infoCarro,    // Agora mostra "Modelo (Placa)"
                nomeCliente,  // Agora mostra "Nome do Cliente"
                loc.dataDevolucaoPrevista.dia, loc.dataDevolucaoPrevista.mes, loc.dataDevolucaoPrevista.ano,
                loc.valorTotalPrevisto);
            achou = 1;
        }
    }
    printf("-------------------------------------------------------------------------------\n");
    if (!achou) printf("Nenhuma locação ativa no momento.\n");
    
    fclose(arquivo);
    system("pause");
}

// Função que chama o menu de locação
void menuLocacoes() {
    int opcao;
    do {
        system("cls");
       
        printf("=== GESTÃO DE LOCAÇÕES ===\n");
        setColor(COR_VERDE);
        printf("1. Nova Locação (Retirada)\n");
        setColor(COR_PADRAO);
        setColor(COR_VERMELHO);
        printf("2. Finaliza Locação (Devolução)\n");
        setColor(COR_PADRAO);
        printf("3. Relatorio de Carros Alugados\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        setColor(COR_PADRAO);
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao) {
            case 1: realizarLocacao(); break;
            case 2: finalizarLocacao(); break;
            case 3: listarLocacoesAtivas(); break;
        }
    } while (opcao != 0);
}
