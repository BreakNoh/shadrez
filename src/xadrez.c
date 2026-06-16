#include <stdbool.h>
#include <stdint.h>

#define ENCONTRADA 1
#define NENHUMA -1
#define AMBIGUO -2

#define u8 uint8_t
#define i8 int8_t

i8 procurar_cavalo(i8 tab[8][8], i8 peca, u8 x2, u8 y2, i8 *x1, i8 *y1) {
    u8 contagem = 0;

    for (i8 i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }
        for (i8 j = -1; j <= 1; j++) {
            if (j == 0) {
                continue;
            }

            i8 dx2 =
                *x1 >= 0 ? *x1 : x2 + j * 2;  // se x ou y já for especificado
                                              // usar esse valor
            i8 dy1 = *y1 >= 0 ? *y1 : y2 + i; //
            i8 dx1 = *x1 >= 0 ? *x1 : x2 + j; //
            i8 dy2 = *y1 >= 0 ? *y1 : y2 + i * 2; //

            if ((dx2 >= 0 && dx2 < 8 && dy1 >= 0 && dy1 < 8) &&
                tab[dy1][dx2] == peca) {
                contagem++;
                *x1 = dx2;
                *y1 = dy1;
            }

            if ((dx1 >= 0 && dx1 < 8 && dy2 >= 0 && dy2 < 8) &&
                tab[dy2][dx1] == peca) {
                contagem++;
                *x1 = dx1;
                *y1 = dy2;
            }
        }
    }

    switch (contagem) {
    case 0:
        *x1 = -1;
        *y1 = -1;
        return NENHUMA;
    case 1:
        return ENCONTRADA;
    default:
        *x1 = -1;
        *y1 = -1;
        return AMBIGUO;
    }
}

i8 encontrar_peca(i8 tab[8][8], i8 peca, u8 x2, u8 y2, u8 *x1, u8 *y1) {}
