#include "xadrez.h"
#include <stdbool.h>
#include <stdio.h>

static Peca PECA_VAZIA = {VAZIO, INDEFINIDA};

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
    tab->posicoes[y2][x2] = tab->posicoes[y1][x1];
    tab->posicoes[y1][x1] = PECA_VAZIA;
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

Tabuleiro new_tabuleiro() {
    Tabuleiro tab = {{}, 0, BRANCA};
    iniciar_posicoes_padrao(&tab);
    return tab;
}
