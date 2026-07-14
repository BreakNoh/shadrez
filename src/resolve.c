#include "xadrez.h"

Resolucao procurar_cavalo(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x,
                          i8 *y) {
    u8 contagem = 0;
    bool encontrados[8][8] = {0};

    i8 dirs[8][2] = {{1, 2},  {-1, 2},  {2, 1},  {2, -1},
                     {1, -2}, {-1, -2}, {-2, 1}, {-2, -1}};

    i8 x_ori = *x, y_ori = *y;

    for (int i = 0; i < 8; i++) {
        i8 dx = x_ori != -1 ? x_ori : x2 + dirs[i][0];
        i8 dy = y_ori != -1 ? y_ori : y2 + dirs[i][1];

        if (!esta_dentro(dx, dy)) {
            continue;
        }

        if (cmp_pos(tab, dx, dy, peca)) {
            if (!encontrados[dy][dx]) {
                encontrados[dy][dx] = true;
                contagem++;
                *x = dx;
                *y = dy;
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

Resolucao procurar_peca_raio(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x,
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
        Peca *colisao = raycast(tab->posicoes, mov, &x_col, &y_col);

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

Resolucao procurar_torre(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x,
                         i8 *y) {
    i8 dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 4);
}
Resolucao procurar_bispo(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x,
                         i8 *y) {
    i8 dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 4);
}
Resolucao procurar_rainha(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x,
                          i8 *y) {
    i8 dirs[8][2] = {{1, 0}, {0, 1},  {-1, 0}, {0, -1},
                     {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    return procurar_peca_raio(tab, peca, x2, y2, x, y, dirs, 8);
}

Resolucao procurar_peao(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x, i8 *y) {
    u8 contagem = 0;
    i8 cor = peca.cor == BRANCA ? 1 : -1;

    i8 x_ori = *x;
    bool capturando = x_ori != -1; // x_inicial especificado axb

    if (capturando) {
        if (cmp_pos(tab, x_ori, y2 - cor, peca)) {
            contagem++;
            *x = x_ori;
            *y = y2 - cor;
        }
    } else {
        u8 x_col = -1, y_col = -1;
        Movimento mov = (Movimento){x2, y2, x2, y2 - (cor * 2)};
        Peca *colisao = raycast(tab->posicoes, mov, &x_col, &y_col);

        if (colisao == NULL) {
            return NENHUMA;
        }

        if (cmp_peca(*colisao, peca)) {
            contagem++;
            *x = x_col;
            *y = y_col;
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

i8 procurar_rei(Tabuleiro *tab, Peca peca, i8 x2, i8 y2, i8 *x1, i8 *y1) {
    u8 contagem = 0;

    for (i8 i = -1; i <= 1; i++) {
        for (i8 j = -1; j <= 1; j++) {
            if (j == 0 && i == 0) {
                continue;
            }

            if (cmp_pos(tab, x2 + j, y2 + i, peca)) {
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

Resolucao resolver_jogada(Tabuleiro *tab, Jogada *jog) {
    Resolucao res = NENHUMA;

    switch (jog->peca.classe) {
    case PEAO:
        res = procurar_peao(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                            &jog->mov.x1, &jog->mov.y1);
        break;
    case CAVALO:
        res = procurar_cavalo(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                              &jog->mov.x1, &jog->mov.y1);
        break;
    case BISPO:
        res = procurar_bispo(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                             &jog->mov.x1, &jog->mov.y1);
        break;
    case TORRE:
        res = procurar_torre(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                             &jog->mov.x1, &jog->mov.y1);
        break;
    case RAINHA:
        res = procurar_rainha(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                              &jog->mov.x1, &jog->mov.y1);
        break;
    case REI:
        res = procurar_rei(tab, jog->peca, jog->mov.x2, jog->mov.y2,
                           &jog->mov.x1, &jog->mov.y1);
        break;
    default:
        break;
    }

    jog->res = res;
    return res;
}
