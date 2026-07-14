#include "teste.h"
/*
  0 1 2 3 4 5 6 7
  A B C D E F G H
1 . . C . . . . .
2 B . B . . . . .
3 T * T . . . . .
4 B T . . . . . .
5 C . . . D . D .
6 . . . . . . . .
7 . . . . D . * .
8 . . . . . . . .
*/

static Leiaute MOCK_AMBUIGUIDADE = {
    "..C.....", "B.B.....", "T*T.....", "BT......",
    "C...D.D.", "........", "....D.*.", "........",
}; // posicoes concorridas: b3 e g7

TESTE(dama_ambigua) {
    Tabuleiro tab = new_tabuleiro(MOCK_AMBUIGUIDADE);

    struct {
        char *comando;
        struct {
            i8 x;
            i8 y;
        } origem;
        Resolucao resultado_esperado;
    } testes[] = {
        {"Dg7", {-1, -1}, AMBIGUO},    {"Deg7", {4, -1}, AMBIGUO},
        {"D5g7", {-1, 4}, AMBIGUO},    {"D7g7", {-1, 6}, ENCONTRADA},
        {"Dgg7", {6, -1}, ENCONTRADA}, {"De5g7", {4, 4}, ENCONTRADA},
    };

    for (int i = 0; i < 6; i++) {
        Jogada jog = parse_comando(testes[i].comando, BRANCA, NULL);

        ASSERT_EQ(jog.mov.x1, testes[i].origem.x, d)

        Resolucao resolucao = resolver_jogada(&tab, &jog);

        ASSERT_EQ(testes[i].resultado_esperado, resolucao, c);
    }
}

TESTE(cavalo_ambiguo) {
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
        Jogada jog = parse_comando(testes[i].comando, BRANCA, NULL);

        ASSERT_EQ(jog.mov.x1, testes[i].origem.x, d)

        Resolucao resolucao = resolver_jogada(&tab, &jog);

        ASSERT_EQ(testes[i].resultado_esperado, resolucao, c);
    }
}

TESTE(bispo_ambiguo) {

    Tabuleiro tab = new_tabuleiro(MOCK_AMBUIGUIDADE);

    struct {
        char *comando;
        struct {
            i8 x;
            i8 y;
        } origem;
        Resolucao resultado_esperado;
    } testes[] = {
        {"Bb3", {-1, -1}, AMBIGUO},    {"Bcb3", {2, -1}, ENCONTRADA},
        {"Bab3", {0, -1}, AMBIGUO},    {"B2b3", {-1, 1}, AMBIGUO},
        {"Bc2b3", {2, 1}, ENCONTRADA}, {"Ba4b3", {0, 3}, ENCONTRADA},
        {"Ba2b3", {0, 1}, ENCONTRADA},
    };

    for (int i = 0; i < 7; i++) {
        Jogada jog = parse_comando(testes[i].comando, BRANCA, NULL);

        ASSERT_EQ(jog.mov.x1, testes[i].origem.x, d)

        Resolucao resolucao = resolver_jogada(&tab, &jog);

        ASSERT_EQ(testes[i].resultado_esperado, resolucao, c);
    }
}

TESTE(torre_ambigua) {
    Tabuleiro tab = new_tabuleiro(MOCK_AMBUIGUIDADE);

    struct {
        char *comando;
        struct {
            i8 x;
            i8 y;
        } origem;
        Resolucao resultado_esperado;
    } testes[] = {{"Tb3", {-1, -1}, AMBIGUO},
                  {"T3b3", {-1, 2}, AMBIGUO},
                  {"Tbb3", {1, -1}, ENCONTRADA},
                  {"Tcb3", {2, -1}, ENCONTRADA}};

    for (int i = 0; i < 4; i++) {
        Jogada jog = parse_comando(testes[i].comando, BRANCA, NULL);

        ASSERT_EQ(jog.mov.x1, testes[i].origem.x, d)

        Resolucao resolucao = resolver_jogada(&tab, &jog);

        ASSERT_EQ(testes[i].resultado_esperado, resolucao, c);
    }
}
