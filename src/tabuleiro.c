#include "xadrez.h"
#include <stdbool.h>
#include <stdio.h>

#define TO_LOWER(ch) (ch - ('A' - 'a'))

static Peca PECA_VAZIA = {VAZIO, INDEFINIDA};

Peca parse_peca_leiaute(char ch) {
    if (ch < 'a' && ch > 'z' && ch < 'A' && ch > 'Z') {
        return PECA_VAZIA;
    }

    bool maiscula = ch >= 'A' && ch <= 'Z';
    Cor cor = maiscula ? BRANCA : PRETA;

    switch (ch) {
    case 'c':
    case 'C':
        return (Peca){CAVALO, cor};
    case 'b':
    case 'B':
        return (Peca){BISPO, cor};
    case 't':
    case 'T':
        return (Peca){TORRE, cor};
    case 'p':
    case 'P':
        return (Peca){PEAO, cor};
    case 'd':
    case 'D':
        return (Peca){RAINHA, cor};
    case 'r':
    case 'R':
        return (Peca){REI, cor};
    default:
        return PECA_VAZIA;
    }
}

void avancar_turno(Tabuleiro *tab) { tab->turno++; }

void alternar_jogador(Tabuleiro *tab) {
    if (tab->jogador == PRETA) {
        tab->jogador = BRANCA;
    } else {
        tab->jogador = PRETA;
    }
}

void set_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca) {
    if (!esta_dentro(x, y)) {
        return;
    }
    tab->posicoes[y][x] = peca;
}

Peca *get_pos(Tabuleiro *tab, i8 x, i8 y) {
    if (!esta_dentro(x, y)) {
        return NULL;
    }

    return &tab->posicoes[y][x];
}

void mover_peca(Tabuleiro *tab, i8 x1, i8 y1, i8 x2, i8 y2) {
    if (!esta_dentro(x1, y1) || !esta_dentro(x2, y2)) {
        return;
    }
    Peca movida = tab->posicoes[y1][x1];

    if (movida.classe == REI) {
        if (movida.cor == BRANCA) {
            tab->reis_iniciados[0] = true;
        } else {
            tab->reis_iniciados[1] = true;
        }
    } else if (movida.classe == TORRE) {
        if (movida.cor == BRANCA) {
            if (x1 == 0) {
                tab->torres_iniciadas[0][0] = true;
            } else if (x1 == 7) {
                tab->torres_iniciadas[0][1] = true;
            }
        } else {
            if (x1 == 0) {
                tab->torres_iniciadas[1][0] = true;
            } else if (x1 == 7) {
                tab->torres_iniciadas[1][1] = true;
            }
        }
    }

    tab->posicoes[y2][x2] = tab->posicoes[y1][x1];
    tab->posicoes[y1][x1] = PECA_VAZIA;

    tab->ultimo_movimento = (Movimento){x1, y1, x2, y2};
}

static Classe LEIAUTE_PECAS[8] = {TORRE, CAVALO, BISPO,  RAINHA,
                                  REI,   BISPO,  CAVALO, TORRE};

void iniciar_posicoes(Tabuleiro *tab) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tab->posicoes[i][j] = PECA_VAZIA;
        }
    }
}

void carregar_leiaute(Tabuleiro *tab, char leiaute[9][9]) {
    for (int i = 0; i < 8; i++) {
        if (leiaute[i][0] == '-') {
            for (int j = 0; j < 8; j++) {
                set_pos(tab, j, i, PECA_VAZIA);
            }
            continue;
        }

        for (int j = 0; j < 8; j++) {
            set_pos(tab, j, i, parse_peca_leiaute(leiaute[i][j]));
        }
    }
}

void iniciar_posicoes_padrao(Tabuleiro *tab) {
    iniciar_posicoes(tab);
    for (int i = 0; i < 8; i++) {
        tab->posicoes[0][i] = (Peca){LEIAUTE_PECAS[i], BRANCA};
        tab->posicoes[1][i] = (Peca){PEAO, BRANCA};
        tab->posicoes[6][i] = (Peca){PEAO, PRETA};
        tab->posicoes[7][i] = (Peca){LEIAUTE_PECAS[i], PRETA};
    }
}

void print_tab(Tabuleiro *tab, bool brancas_embaixo) {
    for (int i = 0; i < 8; i++) {
        if (brancas_embaixo) {
            printf("%d ", 8 - i);
        } else {
            printf("%d ", i + 1);
        }
        for (int j = 0; j < 8; j++) {
            Peca p;
            if (brancas_embaixo) {
                p = tab->posicoes[8 - 1 - i][j];
            } else {
                p = tab->posicoes[i][j];
            }
            printf("%c%c", p.classe, p.cor);
        }
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}

Tabuleiro new_tabuleiro(char leiaute[9][9]) {
    Tabuleiro tab = {{},
                     0,
                     BRANCA,
                     false,
                     {false, false},
                     {{false, false}, {false, false}},
                     {-1, -1, -1, -1}};
    if (leiaute == NULL) {
        carregar_leiaute(&tab, LEIAUTE_PADRAO);
    } else {
        carregar_leiaute(&tab, leiaute);
    }
    return tab;
}
