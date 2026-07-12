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

bool validar_peao(Peca tab[8][8], Movimento mov) {
  Peca peca = tab[mov.y1][mov.x1];
  if (peca.classe != PEAO) {
    return false;
  }

  i8 dy = mov.y2 - mov.y1;
  bool casa_inicial =
      (peca.cor == PRETA && mov.y1 == 6) || (peca.cor == BRANCA && mov.y1 == 1);

  if (abs(dy) > 2) {
    // avanço vertical maior que 2
    return false;
  }

  if ((dy > 0 && peca.cor == PRETA) || (dy < 0 && peca.cor == BRANCA)) {
    // branca descendo ou preta subindo
    return false;
  }

  return true;
} // [TODO]

bool validar_bispo(Peca tab[8][8], Movimento mov) {
  if (tab[mov.y1][mov.x1].classe != BISPO) {
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
  // if (checar_colisao(tab, mov) == COLIDE) {
  //     return false;
  // }

  return true;
}

bool validar_torre(Peca tab[8][8], Movimento mov) {
  if (tab[mov.y1][mov.x1].classe != TORRE) {
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

  // if (checar_colisao(tab, mov) == COLIDE) {
  //     return false;
  // }

  return true;
}

bool validar_cavalo(Peca tab[8][8], Movimento mov) {
  Peca peca = tab[mov.y1][mov.x1];
  if (peca.classe != CAVALO) {
    return false;
  }

  i8 dx = mov.x2 - mov.x1;
  i8 dy = mov.y2 - mov.y1;

  if (!esta_dentro(mov.x2, mov.y2)) {
    return false;
  }
  if (tab[mov.y2][mov.x2].cor == peca.cor) {
    return false;
  }

  return dx * dx + dy * dy == 5; // pitagoras
}

bool validar_rainha(Peca tab[8][8], Movimento mov) {
  if (tab[mov.y1][mov.x1].classe != RAINHA) {
    return false;
  }
  return validar_bispo(tab, mov) || validar_torre(tab, mov);
}

bool validar_rei(Peca tab[8][8], Movimento mov) {
  Peca peca = tab[mov.y1][mov.x1];
  if (peca.classe != REI) {
    return false;
  }

  i8 dx = mov.x2 - mov.x1;
  i8 dy = mov.y2 - mov.y1;

  if (!esta_dentro(mov.x2, mov.y2)) {
    return false;
  }
  if (tab[mov.y2][mov.x2].cor == peca.cor) {
    return false;
  }

  return abs(dx) <= 1 && abs(dy) <= 1;
}

bool validar_movimento(Peca tab[8][8], Movimento mov) {
  switch (tab[mov.y1][mov.x1].classe) {
  case BISPO:
    return validar_bispo(tab, mov);
  case CAVALO:
    return validar_cavalo(tab, mov);
  case TORRE:
    return validar_torre(tab, mov);
  case PEAO:
    return validar_peao(tab, mov);
  case REI:
    return validar_rei(tab, mov);
  case RAINHA:
    return validar_rainha(tab, mov);
  default:
    return false;
  }
}
