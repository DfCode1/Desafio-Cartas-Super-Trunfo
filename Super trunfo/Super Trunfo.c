#define _CRT_SECURE_NO_WARNINGS // Para desabilitar avisos de segurança do scanf no Visual Studio
#include <stdio.h>
#include <stdlib.h> // Para system("cls") ou system("clear") e outras utilidades (não usado aqui)
#include <string.h> // Para manipulação de strings (strcspn)
#include <float.h>  // Para DBL_EPSILON ou para definir nosso próprio epsilon

// --- Constantes Definidas ---
#define DENSITY_EPSILON 0.00001       // Pequeno valor para tratar densidade próxima de zero
#define INVERSE_DENSITY_BONUS_FOR_ZERO 1000000.0 // Bônus para Super Poder se densidade for ~0

// --- Estrutura da Carta ---
typedef struct {
    char estado[50];
    int codigo;
    char nomeCidade[100];
    unsigned long int populacao; // Alterado para unsigned long int
    double pib;
    double area;
    int numPontosTuristicos;
    double densidadePopulacional;
    double pibPerCapita;
    float superPoder;            // Novo campo: float
} CartaSuperTrunfo;

// --- Protótipos das Funções ---
void limparBufferEntrada();
void calcularDadosDerivados(CartaSuperTrunfo* carta);
void calcularSuperPoder(CartaSuperTrunfo* carta);
void cadastrarCarta(CartaSuperTrunfo* carta, int codigoAtual);
void compararEExibirResultados(const CartaSuperTrunfo* c1, const CartaSuperTrunfo* c2);
// void exibirCarta(const CartaSuperTrunfo *carta); // Opcional, se quiser ver dados completos

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para calcular Densidade Populacional e PIB per Capita
void calcularDadosDerivados(CartaSuperTrunfo* carta) {
    if (carta->area > DENSITY_EPSILON) { // Evita divisão por zero ou área muito pequena
        carta->densidadePopulacional = (double)carta->populacao / carta->area;
    }
    else {
        carta->densidadePopulacional = 0.0; // Considera densidade 0 se área for 0 ou insignificante
    }

    if (carta->populacao > 0) {
        carta->pibPerCapita = carta->pib / (double)carta->populacao;
    }
    else {
        carta->pibPerCapita = 0.0; // Evita divisão por zero
    }
}

// Função para calcular o Super Poder
void calcularSuperPoder(CartaSuperTrunfo* carta) {
    double tempSuperPoder = 0.0;

    // Somando atributos com conversão explícita para double para manter precisão na soma
    tempSuperPoder += (double)carta->populacao;
    tempSuperPoder += carta->area;
    tempSuperPoder += carta->pib;
    tempSuperPoder += (double)carta->numPontosTuristicos;
    tempSuperPoder += carta->pibPerCapita;

    // Componente do inverso da densidade populacional
    double contrib_inv_dens = 0.0;
    if (carta->densidadePopulacional > DENSITY_EPSILON) {
        contrib_inv_dens = 1.0 / carta->densidadePopulacional;
    }
    else {
        // Se densidade é zero ou muito próxima de zero, o "poder" deste componente é máximo
        contrib_inv_dens = INVERSE_DENSITY_BONUS_FOR_ZERO;
    }
    tempSuperPoder += contrib_inv_dens;

    carta->superPoder = (float)tempSuperPoder; // Armazena como float
}

// Função para cadastrar os dados de uma carta
void cadastrarCarta(CartaSuperTrunfo* carta, int codigoAtual) {
    printf("\n--- Cadastro da Carta %d ---\n", codigoAtual);
    carta->codigo = codigoAtual;

    printf("Codigo da Carta: %d\n", carta->codigo);

    printf("Digite o nome do Pais/Estado da cidade: ");
    fgets(carta->estado, sizeof(carta->estado), stdin);
    carta->estado[strcspn(carta->estado, "\n")] = 0; // Remove a nova linha

    printf("Digite o nome da Cidade: ");
    fgets(carta->nomeCidade, sizeof(carta->nomeCidade), stdin);
    carta->nomeCidade[strcspn(carta->nomeCidade, "\n")] = 0;

    printf("Digite a Populacao da cidade: ");
    // Usa %lu para unsigned long int
    while (scanf("%lu", &carta->populacao) != 1) {
        printf("Entrada invalida. Digite um numero inteiro positivo para Populacao: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    printf("Digite o PIB da cidade (em bilhoes, ex: 150.75): ");
    while (scanf("%lf", &carta->pib) != 1 || carta->pib < 0) {
        printf("Entrada invalida. Digite um valor numerico positivo para o PIB: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    printf("Digite a Area da cidade (em km2, ex: 570.5): ");
    // Área deve ser > 0 para cálculos significativos de densidade
    while (scanf("%lf", &carta->area) != 1 || carta->area < 0) { // Permitindo area 0, mas densidade tratará
        printf("Entrada invalida. Digite um valor numerico positivo ou zero para a Area: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();


    printf("Digite o Numero de Pontos Turisticos: ");
    while (scanf("%d", &carta->numPontosTuristicos) != 1 || carta->numPontosTuristicos < 0) {
        printf("Entrada invalida. Digite um numero inteiro positivo para Pontos Turisticos: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    // Calcular dados derivados e Super Poder
    calcularDadosDerivados(carta);
    calcularSuperPoder(carta);

    printf("Carta %d cadastrada com sucesso!\n", codigoAtual);
}

// Função para comparar as duas cartas e exibir os resultados
void compararEExibirResultados(const CartaSuperTrunfo* c1, const CartaSuperTrunfo* c2) {
    printf("\nComparacao de Cartas:\n");

    int c1_vence_pop = (c1->populacao > c2->populacao);
    printf("Populacao: Carta %d venceu (%d)\n", (c1_vence_pop ? 1 : 2), c1_vence_pop);

    int c1_vence_area = (c1->area > c2->area);
    printf("Area: Carta %d venceu (%d)\n", (c1_vence_area ? 1 : 2), c1_vence_area);

    int c1_vence_pib = (c1->pib > c2->pib);
    printf("PIB: Carta %d venceu (%d)\n", (c1_vence_pib ? 1 : 2), c1_vence_pib);

    int c1_vence_pontos = (c1->numPontosTuristicos > c2->numPontosTuristicos);
    printf("Pontos Turisticos: Carta %d venceu (%d)\n", (c1_vence_pontos ? 1 : 2), c1_vence_pontos);

    // Para Densidade Populacional, MENOR valor vence.
    // Tratar caso onde uma ou ambas as densidades são zero (zero é o melhor).
    int c1_vence_dens;
    if (c1->densidadePopulacional < DENSITY_EPSILON && c2->densidadePopulacional > DENSITY_EPSILON) {
        c1_vence_dens = 1; // C1 é zero (ou perto), C2 não é -> C1 vence
    }
    else if (c1->densidadePopulacional > DENSITY_EPSILON && c2->densidadePopulacional < DENSITY_EPSILON) {
        c1_vence_dens = 0; // C2 é zero (ou perto), C1 não é -> C2 vence
    }
    else {
        // Ambas são zero (ou perto) ou ambas são não-zero. Comparar normalmente.
        // Se ambas forem zero, c1 < c2 será falso (0), indicando que C1 não vence (empate ou C2 vence).
        c1_vence_dens = (c1->densidadePopulacional < c2->densidadePopulacional);
    }
    printf("Densidade Populacional: Carta %d venceu (%d)\n", (c1_vence_dens ? 1 : 2), c1_vence_dens);


    int c1_vence_pib_pc = (c1->pibPerCapita > c2->pibPerCapita);
    printf("PIB per Capita: Carta %d venceu (%d)\n", (c1_vence_pib_pc ? 1 : 2), c1_vence_pib_pc);

    int c1_vence_sp = (c1->superPoder > c2->superPoder);
    printf("Super Poder: Carta %d venceu (%d)\n", (c1_vence_sp ? 1 : 2), c1_vence_sp);
}

/*
// Opcional: Função para exibir todos os dados de uma carta (para depuração)
void exibirCarta(const CartaSuperTrunfo *carta) {
    printf("\n--- Detalhes da Carta %d ---\n", carta->codigo);
    printf("Pais/Estado: %s\n", carta->estado);
    printf("Cidade: %s\n", carta->nomeCidade);
    printf("Populacao: %lu\n", carta->populacao);
    printf("PIB: %.2f bilhoes\n", carta->pib);
    printf("Area: %.2f km2\n", carta->area);
    printf("Pontos Turisticos: %d\n", carta->numPontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km2\n", carta->densidadePopulacional);
    printf("PIB per Capita: %.2f\n", carta->pibPerCapita);
    printf("Super Poder: %.2f\n", carta->superPoder);
    printf("-----------------------------\n");
}
*/

// --- Função Principal ---
int main() {
    CartaSuperTrunfo carta1, carta2;

    printf("===== SUPER TRUNFO DE PAISES - COMPARACAO DE CARTAS =====\n");

    // Cadastrar primeira carta
    cadastrarCarta(&carta1, 1);

    // Cadastrar segunda carta
    cadastrarCarta(&carta2, 2);

    // Opcional: Exibir dados completos das cartas para verificação
    // exibirCarta(&carta1);
    // exibirCarta(&carta2);

    // Comparar as cartas e exibir os resultados
    compararEExibirResultados(&carta1, &carta2);

    printf("\nFim do programa.\n");
    printf("Pressione Enter para sair...");
    getchar(); // Pausa antes de fechar o console

    return 0;
}