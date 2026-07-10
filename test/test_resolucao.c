#include "teste.h"

static char MOCK_AMBUIGUIDADE[8][8] = {
    "..C.....", "B.B.....", ".*T.....", "BT......",
    "C...D.D.", "........", "....D.*.", "........",
}; // posicoes concorridas: b3 e g7

INICIAR_TESTE(cavalo_ambiguo)

Tabuleiro tab = new_tabuleiro(MOCK_AMBUIGUIDADE);

struct {
  char *comando;
  struct {
    i8 x;
    i8 y;
  } origem;
  Resolucao resultado_esperado;
} testes[] = {
    {"Cb3", {-1, -1}, AMBIGUO},
    {"Cab3", {0, -1}, ENCONTRADA},
    {"Ccb3", {2, -1}, ENCONTRADA},
};

for (int i = 0; i < 3; i++) {
  Jogada jog = parse_comando(testes[i].comando, BRANCA);

  ASSERT_EQ(jog.origem.x, testes[i].origem.x, d)

  Resolucao resolucao = resolver_jogada(tab.posicoes, &jog);

  ASSERT_EQ(testes[i].resultado_esperado, resolucao, c);
}

FINALIZAR_TESTE
