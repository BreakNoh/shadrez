#include "xadrez.h"

#define IDX_BRANCA_INICIADO 0
#define IDX_PRETA_INICIADO 1
#define IDX_REI_INICIADO 0
#define IDX_TORRE_ESQ_INICIADO 1
#define IDX_TORRE_DIR_INICIADO 2

bool cmp_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca) {
    if (!esta_dentro(x, y)) {
        return false;
    }
    return cmp_peca(tab->posicoes[y][x], peca);
}
bool cmp_cor_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca) {
    if (!esta_dentro(x, y)) {
        return false;
    }
    return peca.cor == tab->posicoes[y][x].cor;
}
bool cmp_classe_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca) {
    if (!esta_dentro(x, y)) {
        return false;
    }
    return peca.classe == tab->posicoes[y][x].classe;
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

void iniciar_peca(Tabuleiro *tab, i8 x, i8 y) {
    if (!esta_dentro(x, y)) {
        return;
    }
    i8 idx_cor = -1, idx_peca = -1;
    Peca peca = tab->posicoes[y][x];

    switch (peca.cor) {
    case BRANCA:
        idx_cor = IDX_BRANCA_INICIADO;
        break;
    case PRETA:
        idx_cor = IDX_BRANCA_INICIADO;
        break;
    default:
        break;
    }
    switch (peca.classe) {
    case REI:
        idx_peca = IDX_REI_INICIADO;
        break;
    case TORRE:
        idx_peca = x == 0 ? IDX_TORRE_ESQ_INICIADO : IDX_TORRE_DIR_INICIADO;
        break;
    default:
        break;
    }

    if (idx_peca != -1 && idx_cor != -1) {
        tab->iniciadas[idx_cor][idx_peca] = true;
    }
}

void mover_peca(Tabuleiro *tab, i8 x1, i8 y1, i8 x2, i8 y2) {
    if (!esta_dentro(x1, y1) || !esta_dentro(x2, y2)) {
        return;
    }

    iniciar_peca(tab, x1, y1);

    tab->posicoes[y2][x2] = tab->posicoes[y1][x1];
    tab->posicoes[y1][x1] = PECA_VAZIA;

    tab->ultimo_movimento = (Movimento){x1, y1, x2, y2};
}

void iniciar_posicoes(Tabuleiro *tab, Leiaute leiaute) {
    i8 ignorar_ate = -1;
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        if (leiaute == NULL || leiaute[i][0] == '-') {
            ignorar_ate = 8;
        }

        for (int j = 0; j < TAM_TABULEIRO; j++) {
            Peca p = j < ignorar_ate ? PECA_VAZIA : parse_peca(leiaute[i][j]);
            set_pos(tab, j, i, p);
        }
        ignorar_ate = -1;
    }
}

Tabuleiro new_tabuleiro(Leiaute leiaute) {
    Tabuleiro tab = {
        .iniciadas = {0},
        .jogador_atual = BRANCA,
        .estado = ANDAMENTO,
    };

    iniciar_posicoes(&tab, leiaute);

    return tab;
}
