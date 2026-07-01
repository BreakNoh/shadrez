#include "xadrez.h"

typedef enum { ENCONTRADA, NENHUMA, AMBIGUO } Resolucao;

Resolucao procurar_cavalo(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x,
                          i8 *y) {
    u8 contagem = 0;

    for (i8 i = -1; i <= 1; i++) {
        if (i == 0) {
            continue;
        }
        for (i8 j = -1; j <= 1; j++) {
            if (j == 0) {
                continue;
            }

            i8 dx2 = // (D)escolamento horizontal(X)/vertical(Y)
                     // duplo(2)/unico(1)
                *x >= 0 ? *x : x2 + j * 2;      // se x ou y já for especificado
                                                // usar esse valor
            i8 dy1 = *y >= 0 ? *y : y2 + i;     //
            i8 dx1 = *x >= 0 ? *x : x2 + j;     //
            i8 dy2 = *y >= 0 ? *y : y2 + i * 2; //

            if (esta_dentro(dx2, dy1) && sao_mesma_peca(tab[dy1][dx2], peca)) {
                contagem++;
                *x = dx2;
                *y = dy1;
            }

            if (esta_dentro(dx1, dy2) && sao_mesma_peca(tab[dy2][dx1], peca)) {
                contagem++;
                *x = dx1;
                *y = dy2;
            }
        }
    }

    switch (contagem) {
    case 0:
        *x = -1;
        *y = -1;
        return NENHUMA;
    case 1:
        return ENCONTRADA;
    default:
        *x = -1;
        *y = -1;
        return AMBIGUO;
    }
}

Resolucao procurar_peca_raio(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x,
                             i8 *y, i8 (*dirs)[2], u8 dirs_len) {
    u8 contagem = 0;

    i8 x_res = -1, y_res = -1;
    i8 x_ori = *x;
    i8 y_ori = *y;

    for (u8 i = 0; i < dirs_len; i++) {
        i8 px = dirs[i][0];
        i8 py = dirs[i][1];

        // calcula a distancia maxima do raio
        i8 dist_max = 0;
        if (abs(px) == abs(py)) { // diagonal
            i8 lim_x = (px == -1) ? x2 : 7 - x2;
            i8 lim_y = (py == -1) ? y2 : 7 - y2;
            dist_max = MIN(lim_x, lim_y);
        } else { // reto
            if (px != 0) {
                dist_max = (px == -1) ? x2 : 7 - x2;
            } else {
                dist_max = (py == -1) ? y2 : 7 - y2;
            }
        }

        if (dist_max == 0)
            continue;

        Movimento mov = {x2, y2, x2 + px * dist_max, y2 + py * dist_max};

        u8 x_col, y_col;
        Peca *colisao = raycast(tab, mov, &x_col, &y_col);

        if (colisao == NULL) {
            continue;
        }

        if (colisao->classe == peca.classe && colisao->cor == peca.cor) {
            if (x_ori >= 0 && x_col != x_ori)
                continue;
            if (y_ori >= 0 && y_col != y_ori)
                continue;

            contagem++;
            x_res = x_col;
            y_res = y_col;
        }
    }

    if (contagem == 1) {
        *x = x_res;
        *y = y_res;
        return ENCONTRADA;
    }

    *x = -1;
    *y = -1;
    return (contagem == 0) ? NENHUMA : AMBIGUO;
}

Resolucao procurar_torre(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x,
                         i8 *y) {
    i8 dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 4);
}
Resolucao procurar_bispo(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x,
                         i8 *y) {
    i8 dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 4);
}
Resolucao procurar_rainha(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x,
                          i8 *y) {
    i8 dirs[8][2] = {{1, 0}, {0, 1},  {-1, 0}, {0, -1},
                     {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 8);
}

// Resolucao procurar_peao(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x, i8
// *y,
//                         Jogada jogada) {
//     u8 contagem = 0;
//     i8 cor = peca.cor;
//
//     if (jogada == AVANCO) {
//     }
//     if (jogada == EN_PASSANT) {
//     }
//     if (jogada == CAPTURA) {
//     }
//
//     if (captura) {
//         for (i8 i = -1; i <= 1; i++) {
//             if (i == 0) {
//                 continue;
//             }
//
//             if (tab[y2 - cor][x2 + i] == peca) {
//                 contagem++;
//                 *x = x2 + i;
//                 *y = y2 - cor;
//             }
//         }
//     } else {
//         for (i8 i = 1; i <= 2; i++) {
//             i8 visitada = tab[y2 - (i * cor)][x2];
//             if (visitada == peca) {
//                 contagem++;
//                 *x = x2;
//                 *y = y2 - (i * cor);
//             } else if (visitada != 0) {
//                 break;
//             }
//         }
//     }
//     switch (contagem) {
//     case 0:
//         *x = -1;
//         *y = -1;
//         return NENHUMA;
//     case 1:
//         return ENCONTRADA;
//     default:
//         *x = -1;
//         *y = -1;
//         return AMBIGUO;
//     }
// }

i8 procurar_rei(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x1, i8 *y1) {
    u8 contagem = 0;

    for (i8 i = -1; i <= 1; i++) {
        for (i8 j = -1; j <= 1; j++) {
            if (j == 0 && i == 0) {
                continue;
            }

            if (sao_mesma_peca(tab[y2 + i][x2 + j], peca)) {
                contagem++;
                *x1 = x2 + j;
                *y1 = y2 + i;
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

Resolucao resolver_jogada(Peca tab[8][8], Jogada *jog) {
    switch (jog->peca.classe) {
    case PEAO:
        // [TODO]
        return NENHUMA;
    case CAVALO:
        return procurar_cavalo(tab, jog->peca, jog->alvo.x, jog->alvo.y,
                               &jog->origem.x, &jog->origem.y);
    case BISPO:
        return procurar_bispo(tab, jog->peca, jog->alvo.x, jog->alvo.y,
                              &jog->origem.x, &jog->origem.y);
    case TORRE:
        return procurar_torre(tab, jog->peca, jog->alvo.x, jog->alvo.y,
                              &jog->origem.x, &jog->origem.y);
    case RAINHA:
        return procurar_rainha(tab, jog->peca, jog->alvo.x, jog->alvo.y,
                               &jog->origem.x, &jog->origem.y);
    case REI:
        return procurar_rei(tab, jog->peca, jog->alvo.x, jog->alvo.y,
                            &jog->origem.x, &jog->origem.y);
    default:
        return NENHUMA;
    }
}

// Resolucao encontrar_peca(Peca tab[8][8], Peca peca, i8 x2, i8 y2, i8 *x1,
//                          i8 *y1) {
//     switch (classe_peca(peca)) {
//     case PEAO:
//         return procurar_peao(tab, peca, false, x2, y2, x1, y1);
//     case BISPO:
//         return procurar_bispo(tab, peca, x2, y2, x1, y1);
//     case CAVALO:
//         return procurar_cavalo(tab, peca, x2, y2, x1, y1);
//     case TORRE:
//         return procurar_torre(tab, peca, x2, y2, x1, y1);
//     case RAINHA:
//         return procurar_rainha(tab, peca, x2, y2, x1, y1);
//     case REI:
//         return procurar_rei(tab, peca, x2, y2, x1, y1);
//     };
//     return NENHUMA;
// }
