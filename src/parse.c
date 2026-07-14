#include "xadrez.h"

// Tokens
// Pecas: C B T D R
// Coluna: a-h
// Linha: 1-8
// Captura: x
// Coluna: a-h
// Linha: 1-8
// Check: +
// Checkmate: #

// Roque: O-O O-O-O

typedef enum { TKN_NUL, TKN_PECA, TKN_COL, TKN_LIN, TKN_CAP } Token;

int parse_ch_peca(char ch, Jogada *jog, Token *ult_tkn) {
    if (*ult_tkn != TKN_NUL) {
        // [TODO] de peca não no inicio
        return 1;
    }
    jog->peca.classe = ch;
    *ult_tkn = TKN_PECA;
    return 0;
}

int parse_linha(char ch, Jogada *jog, Token *ult_tkn) {
    if (jog->mov.y2 != -1) {
        jog->mov.y1 = jog->mov.y2;
    } else if (jog->mov.y1 != -1) {
        // [TODO] mais de 2 char de coluna
        return 1;
    }
    jog->mov.y2 = ch - '1';
    *ult_tkn = TKN_LIN;
    return 0;
}

int parse_coluna(char ch, Jogada *jog, Token *ult_tkn) {
    if (jog->mov.x2 != -1) {
        jog->mov.x1 = jog->mov.x2;
    } else if (jog->mov.x1 != -1) {
        // [TODO] mais de 2 char de linha
        return 1;
    }
    jog->mov.x2 = ch - 'a';
    *ult_tkn = TKN_COL;
    return 0;
}

int parse_captura(Jogada *jog, Token *ult_tkn) {
    if (jog->captura) {
        // [TODO] mais de 1 x
        return 1;
    }
    jog->captura = true;

    *ult_tkn = TKN_CAP;
    return 0;
}

Jogada parse_comando(char *cmd, Cor cor, bool *sucesso) {
    Jogada jogada = {new_peca(PEAO, cor), false, MOVIMENTO_VAZIO,
                     NAO_RESOLVIDA};
    Token ult_tkn = TKN_NUL;

    int i = 0;
    while (cmd[i] != '\0') {
        char ch = cmd[i];

        switch (ch) {
        case 'B':
        case 'C':
        case 'D':
        case 'R':
        case 'T':
            parse_ch_peca(ch, &jogada, &ult_tkn);
            break;
        case '1' ... '8':
            parse_linha(ch, &jogada, &ult_tkn);
            break;
        case 'a' ... 'h':
            parse_coluna(ch, &jogada, &ult_tkn);
            break;
        case 'x':
            parse_captura(&jogada, &ult_tkn);
            break;
        }

        i++;
    }

    return jogada;
}
