#include "xadrez.h"
#include <stdbool.h>
#include <stdio.h>

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
    if (!cmp_pos(tab, mov.x1, mov.y1, peca)) {
        Peca *p = get_pos(tab, mov.x1, mov.y1);
        _debug("peca na posicão inicial (%c, %d) não condiz (%c%c != %c%c)",
               'A' + mov.x1, mov.y1 + 1, p->classe, p->cor, peca.classe,
               peca.cor);
        return false;
    }

    i8 dy = mov.y2 - mov.y1;
    i8 dx = mov.x2 - mov.x1;

    if (dy == 0) {
        _debug("sem avanço vertical");
        return false;
    }
    if (abs(dx) > 1) {
        _debug("movimento horizontal maior que 1");
        return false;
    }
    if (abs(dy) > 2) {
        _debug("avanço vertical maior que 2");
        return false;
    }

    bool casa_inicial = (peca.cor == PRETA && mov.y1 == 6) ||
                        (peca.cor == BRANCA && mov.y1 == 1);

    if ((dy > 0 && peca.cor == PRETA) || (dy < 0 && peca.cor == BRANCA)) {
        _debug("branca descendo ou preta subindo");
        return false;
    }

    if (abs(dy) == 2 && !casa_inicial) {
        _debug("avanco duplo fora da casa incial");
        return false;
    }

    Cor cor_alvo = get_pos(tab, mov.x2, mov.y2)->cor;

    if (dx != 0 && cor_alvo == peca.cor) {
        _debug("movimento diagonal num espaço amigo");
        return false;
    } else if (dx != 0 && cor_alvo == INDEFINIDA) {
        Movimento umov = tab->ultimo_movimento;
        if (!cmp_pos(tab, umov.x2, umov.y2,
                     (Peca){PEAO, peca.cor == BRANCA ? PRETA : BRANCA})) {
            Peca *p = get_pos(tab, umov.x2, umov.y2);
            _debug("ultimo movimento não foi de peão inimigo (%d, %d)(%c, %c)",
                   umov.x2, umov.y2, p->classe, p->cor);
            return false;
        }

        bool linha_enpassant = (peca.cor == BRANCA && mov.y1 == 4) ||
                               (peca.cor == PRETA && mov.y1 == 3);

        if (!linha_enpassant) {
            _debug("não tá na linha en passant");
            return false;
        }

        bool alvo_mesma_linha = tab->ultimo_movimento.y2 == mov.y1;
        bool avanco_duplo =
            (tab->ultimo_movimento.x1 == tab->ultimo_movimento.x2) &&
            abs(tab->ultimo_movimento.y2 - tab->ultimo_movimento.y1) == 2;
        bool alvo_do_lado = abs(tab->ultimo_movimento.x2 - mov.x1) == 1;

        if (!alvo_do_lado) {
            _debug("alvo não está no lado");
            return false;
        }
        if (!avanco_duplo) {
            _debug("ultimo movimento não foi duplo");
            return false;
        }
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
