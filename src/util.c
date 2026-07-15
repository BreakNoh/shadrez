#include "xadrez.h"
#include <stdarg.h>
#include <stdio.h>

void _debug(char *msg, ...) {
    va_list args;
    va_start(args, msg);

#ifdef TESTE_RUN
    printf("[DEBUG] ");
    vprintf(msg, args);
    printf("\n");
#endif /* ifdef TESTE_RUN */
}

bool esta_dentro(i8 x, i8 y) {
    return x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO;
}

Peca *raycast(Peca tab[TAM_TABULEIRO][TAM_TABULEIRO], Movimento mov, u8 *x,
              u8 *y) {
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
