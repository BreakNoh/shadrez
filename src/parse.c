#include "xadrez.h"
#include <stdbool.h>
#include <stdio.h>

bool eh_maiuscula(char c) { return c >= 'A' && c <= 'Z'; }

bool eh_coluna(char c) { return c >= 'a' && c <= 'h'; }
bool eh_linha(char c) { return c >= '1' && c <= '8'; }

Classe char_pra_classe(char c) {
  switch (c) {
  case 'C':
    return CAVALO;
  case 'B':
    return BISPO;
  case 'T':
    return TORRE;
  case 'R':
    return REI;
  case 'D':
    return RAINHA;
  default:
    return VAZIO;
  }
}

#define ERRO_DE_CLASSE 1
#define ERRO_DE_POSICAO 1

int parse_classe(char c, int i, Classe *peca, Classe *promo) {
  Classe cls = char_pra_classe(c);
  if (cls == VAZIO) {
    return ERRO_DE_CLASSE;
  }

  if (i == 0) { // X...
    *peca = cls;
    return 0;
  } else if (*promo == VAZIO) { // ...X...
    *promo = cls;
    return 0;
  } else { // X...X...X
    return ERRO_DE_CLASSE;
  }
}

int parse_coluna(char c, int *x1, int *x2) {
  int col = c - 'a';

  if (*x2 != -1 && *x1 == -1) {
    *x1 = *x2;
    *x2 = col;
  } else if (*x1 == -1) {
    *x2 = col;
  } else {
    return ERRO_DE_POSICAO;
  }

  return 0;
}

int parse_linha(char c, int *y1, int *y2) {
  int col = c - 'a';

  if (*y2 != -1 && *y1 == -1) {
    *y1 = *y2;
    *y2 = col;
  } else if (*y1 == -1) {
    *y2 = col;
  } else {
    return ERRO_DE_POSICAO;
  }

  return 0;
}

int parse_comando(char *cmd) {
  Classe peca = PEAO;
  Classe promo = VAZIO;
  int x1 = -1, y1 = -1, x2 = -1, y2 = -1;

  int i = 0;

  while (cmd[i] != '\0') {
    char tkn = cmd[i];
    int res = 0;

    if (eh_maiuscula(tkn)) {
      res = parse_classe(tkn, i, &peca, &promo);
    } else if (eh_coluna(tkn)) {
      res = parse_coluna(tkn, &x1, &x2);
    } else if (eh_linha(tkn)) {
      res = parse_coluna(tkn, &y1, &y2);
    }

    if (res != 0) {
      return res;
    }
  }

  printf("%d %d %d, %d %d", peca, x1, y1, x2, y2);
}
