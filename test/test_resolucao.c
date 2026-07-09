#include "teste.h"
#include <assert.h>

static char MOCK_AMBUIGUIDADE[8][8] = {
    "..C.....", "B.B.....", ".*T.....", "BT......",
    "C...D.D.", "........", "....D.*.", "........",
}; // posicoes concorridas: b3 e g7

typedef struct {
    char *comando;
    Resolucao resultado_esperado;
} TesteResolucao;

void test_cavalo_ambiguo() {
    Tabuleiro tab = new_tabuleiro(MOCK_AMBUIGUIDADE);

    TesteResolucao testes[] = {
        {"Cxb3", AMBIGUO},
        {"Caxb3", ENCONTRADA},
        {"Ccxb3", ENCONTRADA},
    };

    for (int i = 0; i < 3; i++) {
        Jogada jog = parse_comando(testes[i].comando, BRANCA);
        Resolucao resolucao = resolver_jogada(tab.posicoes, &jog);

        assert(resolucao == testes[i].resultado_esperado);
    }
}
