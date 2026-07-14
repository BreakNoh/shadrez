#include "xadrez.h"
#include <stdlib.h>

typedef enum { LIVRE, ATAQUE, BLOQUEADO, FORA_TABULEIRO } Colisao;
Colisao checar_colisao(Peca tab[8][8], Movimento mov) {
    u8 x, y;
    Peca *colisao = raycast(tab, mov, &x, &y);

    if (colisao == NULL) {
        return FORA_TABULEIRO;
    }

    if (colisao->classe == VAZIO) {
        return LIVRE;
    }

    if (colisao->cor == tab[mov.y1][mov.x1].cor) {
        return BLOQUEADO;
    }

    if (colisao->classe != VAZIO && mov.x2 == x && mov.y2 == y) {
        return ATAQUE;
    }

    return BLOQUEADO; // bloqueado por inimigo
}

bool validar_peao(Tabuleiro *tab, Movimento mov, Peca peca) {
    if (cmp_pos(tab, mov.x1, mov.y1, peca)) {
        return false;
    }

    i8 dy = mov.y2 - mov.y1;
    i8 dx = mov.x2 - mov.x1;

    if (dy == 0) {
        // sem avanço vertical
        return false;
    }
    if (abs(dx) > 1) {
        // movimento horizontal maior que 1
        return false;
    }
    if (abs(dy) > 2) {
        // avanço vertical maior que 2
        return false;
    }

    bool casa_inicial = (peca.cor == PRETA && mov.y1 == 6) ||
                        (peca.cor == BRANCA && mov.y1 == 1);

    if ((dy > 0 && peca.cor == PRETA) || (dy < 0 && peca.cor == BRANCA)) {
        // branca descendo ou preta subindo
        return false;
    }

    if (abs(dy) == 2 && !casa_inicial) {
        // avanco duplo fora da casa incial
        return false;
    }

    Cor cor_alvo = get_pos(tab, mov.x2, mov.y2)->cor;

    if (dx != 0 && (cor_alvo == INDEFINIDA || cor_alvo == peca.cor)) {
        // movimento diagonal num espaço amigo ou livre
        // [TODO] impossibilita en passant
        return false;
    }

    return true;
} // [TODO]

bool validar_bispo(Tabuleiro *tab, Movimento mov, Peca peca) {
    if (cmp_pos(tab, mov.x1, mov.y1, peca)) {
        return false;
    }
    i8 dx = mov.x2 - mov.x1;
    i8 dy = mov.y2 - mov.y1;

    if (!esta_dentro(mov.x2, mov.y2)) {
        return false;
    }
    if (abs(dx) != abs(dy) || (dx == 0 && dy == 0)) {
        return false;
    } // movimento não diagonal ou não sai do lugar

    if ((checar_colisao(tab->posicoes, mov) != LIVRE) &&
        (checar_colisao(tab->posicoes, mov) != ATAQUE)) {
        // movimento bloqueado ou fora do tabuleiro
        return false;
    }

    return true;
}

bool validar_torre(Tabuleiro *tab, Movimento mov, Peca peca) {
    if (cmp_pos(tab, mov.x1, mov.y1, peca)) {
        return false;
    }
    i8 dx = mov.x2 - mov.x1;
    i8 dy = mov.y2 - mov.y1;

    if (!esta_dentro(mov.x2, mov.y2)) {
        return false;
    }

    if ((dx == 0) == (dy == 0)) {
        return false;
    } // movimento não reto ou parado

    if ((checar_colisao(tab->posicoes, mov) != LIVRE) &&
        (checar_colisao(tab->posicoes, mov) != ATAQUE)) {
        // movimento bloqueado ou fora do tabuleiro
        return false;
    }

    return true;
}

bool validar_cavalo(Tabuleiro *tab, Movimento mov, Peca peca) {
    if (cmp_pos(tab, mov.x1, mov.y1, peca)) {
        return false;
    }
    i8 dx = mov.x2 - mov.x1;
    i8 dy = mov.y2 - mov.y1;

    if (!esta_dentro(mov.x2, mov.y2)) {
        return false;
    }
    if (cmp_cor_pos(tab, mov.x2, mov.y2, peca)) {
        return false;
    }

    return dx * dx + dy * dy == 5; // pitagoras
}

bool validar_rainha(Tabuleiro *tab, Movimento mov, Peca peca) {
    return validar_bispo(tab, mov, peca) || validar_torre(tab, mov, peca);
}

bool validar_rei(Tabuleiro *tab, Movimento mov, Peca peca) {
    if (cmp_pos(tab, mov.x1, mov.y1, peca)) {
        return false;
    }

    i8 dx = mov.x2 - mov.x1;
    i8 dy = mov.y2 - mov.y1;

    if (!esta_dentro(mov.x2, mov.y2)) {
        return false;
    }
    if (cmp_cor_pos(tab, mov.x2, mov.x2, peca)) {
        return false;
    }

    return abs(dx) <= 1 && abs(dy) <= 1;
}

bool validar_jogada(Tabuleiro *tab, Jogada jog) {
    switch (jog.peca.classe) {
    case BISPO:
        return validar_bispo(tab, jog.mov, jog.peca);
    case CAVALO:
        return validar_cavalo(tab, jog.mov, jog.peca);
    case TORRE:
        return validar_torre(tab, jog.mov, jog.peca);
    case PEAO:
        return validar_peao(tab, jog.mov, jog.peca);
    case REI:
        return validar_rei(tab, jog.mov, jog.peca);
    case RAINHA:
        return validar_rainha(tab, jog.mov, jog.peca);
    default:
        return false;
    }
}
