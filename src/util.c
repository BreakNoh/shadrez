#include "xadrez.h"

bool esta_dentro(i8 x, i8 y) {
    return x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO;
}
bool sao_mesma_peca(Peca a, Peca b) {
    return a.classe == b.classe && a.cor == b.cor;
}
Peca *raycast(Peca tab[8][8], Movimento mov, u8 *x, u8 *y) {
    if (!esta_dentro(mov.x2, mov.y2) || !esta_dentro(mov.x1, mov.y1)) {
        return NULL;
    }

    i8 passo_x = sign(mov.x2 - mov.x1);
    i8 passo_y = sign(mov.y2 - mov.y1);

    *x = mov.x1 + passo_x;
    *y = mov.y1 + passo_y;

    while (*x != mov.x2 || *y != mov.y2) {
        if (tab[*y][*x].classe != VAZIO) {
            return &tab[*y][*x];
        }

        if (*x != mov.x2) {
            *x += passo_x;
        }
        if (*y != mov.y2) {
            *y += passo_y;
        }
    }

    return &tab[*y][*x];
}
